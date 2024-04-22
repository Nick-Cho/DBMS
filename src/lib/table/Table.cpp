#include "Table.h"
#include <iostream>
#include "../Row/Row.h"

bool Table::insert(const Row& row) {
    if (num_rows_ >= TABLE_MAX_ROWS) {
        return false;
    }

    row.serialize_row(row_slot(num_rows_));
    num_rows_++;
    return true;
}

void Table::select() {
    Row row;
    for (uint32_t i = 0; i < num_rows_; i++) {
        row.deserialize_row(row_slot(i));
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