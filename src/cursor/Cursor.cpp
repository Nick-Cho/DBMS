#include "./include/Cursor.h"
#include "../node/include/Node.h"

Cursor::Cursor(Table* table, uint32_t page_num, uint32_t cell_num, bool isEndOfTable): 
    table_(table), 
    page_num_(page_num), 
    cell_num_(cell_num), 
    b_table_end_(isEndOfTable) {}

Cursor& Cursor::operator++() {
    Node node = Node(table_->pager_->getPage(page_num_));
    cell_num_++;

    if (cell_num_ >= *(node.leafNodeNumCells())){
        uint32_t next_page_num = *node.leafNodeNextLeaf();
        if (next_page_num == 0){
            b_table_end_ = true;
        } else {
            page_num_ = next_page_num;
            cell_num_ = 0;
        }
        b_table_end_ = true;
    }
    return *this;
}

// Cursor& Cursor::operator--() {
//     row_num_--;
//     if (row_num_ < table_->getNumRows()) {
//          b_table_end_ = false;
//     }
//     return *this;
// }

bool Cursor::isTableEnd() {
    return b_table_end_;
}

uint32_t Cursor::getPageNum() {
    return page_num_;
}

uint32_t Cursor::getCellNum() {
    return cell_num_;
}

void Cursor::setCellNum(uint32_t cell_num) {
    cell_num_ = cell_num;
}