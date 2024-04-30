#ifndef CURSOR_H
#define CURSOR_H

#include "../../Table/include/Table.h"

class Cursor {
    private:
        Table* table_;
        uint32_t row_num_;
        bool b_table_end_; // Indicates position one past the end of the table
    public:
        Cursor(Table* table, uint32_t row);
        Cursor& operator++();
        Cursor& operator--();
        bool isTableEnd();
        uint32_t getRowNum();
};

#endif