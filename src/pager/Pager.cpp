#include "./include/Pager.h"

#include <iostream>

Pager::Pager(const std::string &filename): file_length_(0), pages_() {
    file_stream_.open(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (!file_stream_.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(EXIT_FAILURE);
    }

    file_length_ = file_stream_.tellg();
    file_stream_.seekg(0, std::ios::beg);

    pages_.resize(TABLE_MAX_PAGES);
};

void* Pager::getPage(uint32_t page_num) {
    if (page_num > TABLE_MAX_PAGES) {
        std::cerr << "Tried to fetch page number out of bounds \n";
        exit(EXIT_FAILURE);
    }

    // std::cout << "Page num debug log: " << page_num;
    if (pages_[page_num] == nullptr) {
        // Cache miss, so allocate new memory and load from file
        pages_[page_num] = std::make_unique<char[]>(PAGE_SIZE);
        uint32_t num_pages = file_length_/PAGE_SIZE;
        if (file_length_ % PAGE_SIZE) {
            // Accounts for having a partially written page at the end of the file
            num_pages++;
        }
        
        if (page_num < num_pages) {
            file_stream_.seekg(page_num * PAGE_SIZE);
            if (file_stream_.fail()) {
                std::cerr << "Error while finding page starting point with seekg (line 35 Pager.cpp) \n";
            }

            file_stream_.read(pages_[page_num].get(), PAGE_SIZE);
            if (file_stream_.eof()) {
                // EOF triggers when reaching end of file so accessing the last page will trigger this
                // std::cerr << "Reached end of file error while reading file"; 
                file_stream_.clear(); //resets error flags
            }
            
            else if (file_stream_.fail()) {
                std::cerr << "Error reading file p1\n";
                exit(EXIT_FAILURE);
            }
        }
    }
    return pages_[page_num].get();
}

std::vector<std::unique_ptr<char[]>>& Pager::getPages() {
    return pages_;
}

int Pager::close() {
    file_stream_.close();
    if (file_stream_.fail()) {
        return 1;
    }
    return 0;
}

uint32_t Pager::getFileLength() {
    return file_length_;
}

void Pager::flush(uint32_t page_num, uint32_t size) {
    if (pages_[page_num] == nullptr) {
        printf("Trying to flush null page\n");
        exit(EXIT_FAILURE);
    }
    
    file_stream_.seekg(page_num * PAGE_SIZE);
    if (file_stream_.fail()) {
        std::cerr << "Error while finding page starting point with seekg (line 74 Pager.cpp) \n";
    }

    file_stream_.write(pages_[page_num].get(), size);
    file_stream_.flush();

    if (file_stream_.fail()) {
        std::cerr << "Error writing to file\n";
        exit(EXIT_FAILURE);
    }
}