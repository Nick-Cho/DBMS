#ifndef TABLE_H
#define TABLE_H

#include "../../row/include/Row.h"
#include "../../pager/include/Pager.h"
#include "../../cursor/include/Cursor.h"

#include <string>

class Cursor;
class Table {
    public:
        Table();
        void db_close();
        void db_open(const std::string filename);
        bool insert(const Row& row);
        void select();
        Cursor tableStart();
        Cursor tableEnd();
        uint32_t getNumPages();
    private:
        uint32_t root_page_num_;
        std::shared_ptr<Pager> pager_;
        void* row_slot(uint32_t row_num);
        
};

#endif