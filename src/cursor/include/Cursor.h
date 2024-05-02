#ifndef CURSOR_H
#define CURSOR_H

#include "../../table/include/Table.h"

// Main purpose is to keep track of the current position in the table

class Table;
class Cursor {
    private:
        Table* table_;
        uint32_t page_num_; // Need both page number and cell number to access a row for Btree structure
        uint32_t cell_num_;
        bool b_table_end_; // Indicates position one past the end of the table
    public:
        Cursor(Table* table, uint32_t page_num, uint32_t cell_num, bool isEndOfTable);

        Cursor& operator++();
        
        Cursor& operator--();
        
        bool isTableEnd();

        uint32_t getPageNum();

        uint32_t getCellNum();

        void setCellNum(uint32_t cell_num);
};

#endif