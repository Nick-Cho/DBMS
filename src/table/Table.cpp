#include "./include/Table.h"
#include <iostream>
#include "../row/include/Row.h"
#include "../pager/include/Pager.h"

bool Table::insert(const Row& row) {
    if (num_rows_ >= TABLE_MAX_ROWS) {
        return false;
    }

    row.serialize_row(static_cast<char*>(row_slot(num_rows_)));
    num_rows_++;
    return true;
}

void Table::select() {
    Row row;
    for (uint32_t i = 0; i < num_rows_; i++) {
        row.deserialize_row(static_cast<char*>(row_slot(i)));
        row.print_row();
    }    
}

Table::Table(): num_rows_(0) {
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pages_[i] = nullptr;
    }
}

Table::~Table() {
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        if (pages_[i] != nullptr) {
            free(pages_[i]);
            pages_[i] = nullptr;
        }
    }
}

void* Table::row_slot(uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = pages_[page_num];
    if (page == nullptr) {
        page = pages_[page_num] = std::make_unique<char[]>(PAGE_SIZE).get();
    }

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * sizeof(Row);
    return static_cast<char*>(page) + byte_offset;
}