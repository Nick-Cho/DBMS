#ifndef TABLE_H
#define TABLE_H

#include "../../row/include/Row.h"
#include "../../pager/include/Pager.h"
#include "../../cursor/include/Cursor.h"

#include <string>

class Cursor;
class Table {
    friend class Cursor;
    public:
        Table();
        
        void dbClose();
        
        void dbOpen(const std::string filename);
        
        bool insert(const Row& row);
        
        void select();
        
        Cursor tableStart();
        
        // Cursor tableEnd(); -- deprecated for tableFind()
        
        void leafNodeInsert(Cursor* cursor, uint32_t key, Row* value);

        void printConstants();

        void printTree(uint32_t page_num);

        Cursor tableFind(uint32_t search_key);
    private:
        uint32_t root_page_num_;
        std::shared_ptr<Pager> pager_;
        void* row_slot(uint32_t row_num);
        
};

#endif