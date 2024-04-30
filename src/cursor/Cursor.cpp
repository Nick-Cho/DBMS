#include "./include/Cursor.h"

Cursor::Cursor(Table* table, uint32_t row): table_(table), row_num_(row), b_table_end_(row >= table->getNumRows()) {}

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