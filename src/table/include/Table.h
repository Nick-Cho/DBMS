#ifndef TABLE_H
#define TABLE_H

#include "../../row/include/Row.h"
#include <string>

class Table {
    public:
        Table();
        ~Table();
        void db_open(const std::string filename);
        bool insert(const Row& row);
        void select();
    private:
        uint32_t num_rows_;
        std::shared_ptr<Pager> pager;
        void* row_slot(uint32_t row_num);
};

#endif