#ifndef PAGER_H
#define PAGER_H

#include "../../row/include/Row.h"
#include <iostream>
#include <vector> 
#include <fstream>

static const size_t PAGE_SIZE = 4096; // 4Kb
static const int TABLE_MAX_PAGES = 100;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / sizeof(Row);
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

class Pager {
    private:
        uint32_t file_length_;
        std::fstream file_stream_;
        std::vector<std::unique_ptr<char[]>> pages_;
    public:
        Pager(const std::string &filename);
        void* getPage(uint32_t page_num);
        uint32_t getFileLength();
        void flush(uint32_t page_num, uint32_t size);
        int close();
        std::vector<std::unique_ptr<char[]>>& getPages();
};


#endif