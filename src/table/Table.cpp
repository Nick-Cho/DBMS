#include "./include/Table.h"
#include "../row/include/Row.h"
#include "../pager/include/Pager.h"
#include "../cursor/include/Cursor.h"

#include <iostream>


bool Table::insert(const Row& row) {
    if (num_rows_ >= TABLE_MAX_ROWS) {
        return false;
    }

    row.serialize_row(static_cast<char*>(row_slot(num_rows_)));
    num_rows_++;
    return true;
}

void Table::select() {
    Cursor cursor = tableStart();
    Row row;
    while (!cursor.isTableEnd()) {
        row.deserialize_row(static_cast<char*>(row_slot(cursor.getRowNum())));
        row.print_row();
        ++cursor;
    }
    
}

Table::Table(): num_rows_(0), pager_(nullptr) {}

void Table::db_close() {
    uint32_t num_full_pages = num_rows_ / ROWS_PER_PAGE;
    for (uint32_t i=0; i<num_full_pages; ++i) {
        if (pager_->getPage(i) != nullptr) {
            pager_->flush(i, PAGE_SIZE);
            pager_->getPages()[i].reset();
        }
    }

    uint32_t num_additional_rows = num_rows_%ROWS_PER_PAGE;
    if (num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if (pager_->getPage(page_num) != nullptr) {
            pager_->flush(page_num, num_additional_rows * sizeof(Row));
            pager_->getPages()[page_num].reset();
        }
    }

    if (pager_->close()) {
        std::cerr << "Error closing DB\n";
        exit(EXIT_FAILURE);
    }
    pager_.reset();
}

void* Table::row_slot(uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = pager_->getPage(page_num);
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * sizeof(Row);
    return static_cast<char*>(page) + byte_offset;
}

void Table::db_open(const std::string filename) {
    pager_ = std::make_shared<Pager>(filename);
    // num of rows for full pages + additional rows from partially filled page
    num_rows_ = ((pager_->getFileLength() / PAGE_SIZE) * ROWS_PER_PAGE) + ((pager_->getFileLength() % PAGE_SIZE) / sizeof(Row));
}

Cursor Table::tableStart() {
    return Cursor(this, 0);
}

Cursor Table::tableEnd() {
    return Cursor(this, num_rows_);
}

uint32_t Table::getNumRows() {
    return num_rows_;
}