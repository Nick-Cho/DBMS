#include "./include/Cursor.h"

Cursor::Cursor(Table* table, uint32_t page_num, uint32_t cell_num, bool isEndOfTable): 
    table_(table), 
    page_num_(page_num), 
    cell_num_(cell_num), 
    b_table_end_(isEndOfTable) {}

Cursor& Cursor::operator++() {
    row_num_++;
    if (row_num_ >= table_->getNumRows()){
        b_table_end_ = true;
    }
    return *this;
}

Cursor& Cursor::operator--() {
    row_num_--;
    if (row_num_ < table_->getNumRows()) {
         b_table_end_ = false;
    }
    return *this;
}

bool Cursor::isTableEnd() {
    return b_table_end_;
}

uint32_t Cursor::getRowNum() {
    return row_num_;
}