#ifndef PAGER_H
#define PAGER_H

#include "../../row/include/Row.h"
#include <iostream>
#include <vector> 
#include <fstream>

static const size_t PAGE_SIZE = 4096; // 4Kb
static const int TABLE_MAX_PAGES = 100;

class Pager {
    private:
        uint32_t file_length_;
        std::fstream file_stream_;
        uint32_t num_pages_;
        std::vector<std::unique_ptr<char[]>> pages_;
    public:
        Pager(const std::string &filename);
        void* getPage(uint32_t page_num);
        uint32_t getFileLength();
        void flush(uint32_t page_num);
        int close();
        std::vector<std::unique_ptr<char[]>>& getPages();
};


#endif