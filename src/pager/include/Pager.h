#ifndef PAGER_H
#define STATEMENT_H

#include "../../row/include/Row.h"
#include <iostream>
#include <vector> 

static const size_t PAGE_SIZE = 4096; // 4Kb
static const int TABLE_MAX_PAGES = 100;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / sizeof(Row);
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

    
class Pager {
    private:
        int file_descriptor;
        uint32_t file_length;
        std::vector<std::unique_ptr<char[]>> pages;
    public:
};


#endif