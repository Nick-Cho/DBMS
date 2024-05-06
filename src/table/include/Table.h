#ifndef TABLE_H
#define TABLE_H

#include "../../row/include/Row.h"
#include "../../pager/include/Pager.h"
#include "../../cursor/include/Cursor.h"
#include "../../node/include/Node.h"
#include <string>

#define INVALID_PAGE_NUM UINT32_MAX

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
        
        void leafNodeInsert(Cursor cursor, uint32_t key, Row* value);

        void printConstants();

        void printTree(uint32_t page_num);

        Cursor tableFind(uint32_t search_key);

        Cursor leafNodeFind(uint32_t page_num, uint32_t key);

        void leafNodeSplitAndInsert(Cursor* cursor, uint32_t key, Row* value);

        void createNewRoot(uint32_t right_child_page_num);

        Cursor internalNodeFind(uint32_t page_num, uint32_t key);

        void internalNodeInsert(uint32_t parent_page_num, uint32_t child_page_num);

        void internalNodeSplitAndInsert(uint32_t parent_page_num, uint32_t child_page_num);

        uint32_t getNodeMaxKey(Node node);
    private:
        uint32_t root_page_num_;
        std::shared_ptr<Pager> pager_;
        // void* row_slot(uint32_t row_num);
};

#endif