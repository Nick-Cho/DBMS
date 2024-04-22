#ifndef TABLE_H
#define TABLE_H

#include "../Row/Row.h"
#include <string>

static const size_t PAGE_SIZE = 4096; // 4Kb
static const int TABLE_MAX_PAGES = 100;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / sizeof(Row);
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

class Table {
    public:
        Table();
        ~Table();
        bool insert(const Row& row);
        void select();
    private:
        uint32_t num_rows_;
        void* pages_[TABLE_MAX_PAGES];

        void* row_slot(uint32_t row_num);
};

#endif