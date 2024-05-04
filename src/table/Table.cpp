#include "./include/Table.h"
#include "../row/include/Row.h"
#include "../pager/include/Pager.h"
#include "../cursor/include/Cursor.h"
#include "../node/include/Node.h"

#include <iostream>


bool Table::insert(const Row& row) {
    Node node = Node(pager_->getPage(root_page_num_));
    uint32_t num_cells = *(node.leafNodeNumCells());
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // Table full
        return false;
    }
    uint32_t insert_key = row.getId();
    Cursor cursor = tableFind(insert_key);

    Node node = Node(pager_->getPage(cursor.getPageNum()));
    if (cursor.getCellNum() < num_cells) {
        uint32_t key_at_index = *(node.leafNodeKey(cursor.getCellNum()));
        if (key_at_index == insert_key) {
            return false;
        }
    }

    leafNodeInsert(&Cursor(this, root_page_num_, 0, true), row.getId(), const_cast<Row*>(&row));
    
    return true;
}

// void Table::select() {
//     Cursor cursor = tableStart();
//     Row row;
//     while (!cursor.isTableEnd()) {
//         row.deserialize_row(static_cast<char*>(row_slot(cursor.getRowNum())));
//         row.print_row();
//         ++cursor;
//     }
    
// }

Table::Table(): root_page_num_(0), pager_(nullptr) {}

void Table::dbClose() {
    for (uint32_t i=0; i<pager_->getNumPages(); ++i) {
        if (pager_->getPage(i) != nullptr) {
            pager_->flush(i);
            pager_->getPages()[i].reset();
        }
    }

    if (pager_->close()) {
        std::cerr << "Error closing DB\n";
        exit(EXIT_FAILURE);
    }
    pager_.reset();
}

// void* Table::row_slot(uint32_t row_num) {
//     uint32_t page_num = row_num / ROWS_PER_PAGE;
//     void* page = pager_->getPage(page_num);
//     uint32_t row_offset = row_num % ROWS_PER_PAGE;
//     uint32_t byte_offset = row_offset * sizeof(Row);
//     return static_cast<char*>(page) + byte_offset;
// }

void Table::dbOpen(const std::string filename) {
    pager_ = std::make_shared<Pager>(filename);
    if (pager_->getNumPages() == 0) {
        void *root_node = pager_->getPage(0);
        static_cast<Node*>(root_node)->setRoot(true);
        Node node = Node(root_node);
        node.initializeLeafNode();
        node.setRoot(true);
    }
}

Cursor Table::tableStart() {
    void* root_node = pager_->getPage(root_page_num_);
    Node node = Node(root_node);
    uint32_t num_cells = *(node.leafNodeNumCells());
    return Cursor(this, root_page_num_, 0, num_cells == 0); // Can be end of the table if there is nothing in it
}

// Cursor Table::tableEnd() {
//     uint32_t end_page_num = pager_->getNumPages();
//     void* end_node = pager_->getPage(end_page_num);
//     Node node = Node(end_node);
//     uint32_t num_cells = *(node.leafNodeNumCells());
//     return Cursor(this, end_page_num, num_cells, true); 
// }

void Table::leafNodeInsert(Cursor* cursor, uint32_t key, Row* value) {
    void *node = pager_->getPage(cursor->getPageNum());

    uint32_t num_cells = *(Node(node).leafNodeNumCells());
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // Node full
        // printf("Need to implement splitting a leaf node\n");
        // exit(EXIT_FAILURE);
        leafNodeSplitAndInsert(cursor, key, value);
    }

    if (cursor->getCellNum() < num_cells) {
        // Make room for new cell
        for (uint32_t i=num_cells; i>cursor->getCellNum(); --i) {
            std::copy(
                static_cast<char*>(Node(node).leafNodeCell(i-1)),
                static_cast<char*>(Node(node).leafNodeCell(i-1)) + LEAF_NODE_CELL_SIZE,
                static_cast<char*>(Node(node).leafNodeCell(i))                
            );            
        }
    }
}

void Table::leafNodeSplitAndInsert(Cursor* cursor, uint32_t key, Row* value) {
    // Create a new node and move half the cells over
    // Insert the new value in one of the two nodes
    // Update parent or create a new parent

    void* old_node = pager_->getPage(cursor->getPageNum());
    uint32_t new_page_num = pager_->getUnusedPageNum();
    void* new_node = pager_->getPage(new_page_num);
    Node(new_node).initializeLeafNode();

    // Need to balance all existing keys into the old (left) and new nodes (right) evenly
    // Starting from right, move every key into its correct position in the new node
    for (uint32_t i=LEAF_NODE_MAX_CELLS; i>=0; i--) {
        void* destination_node = nullptr;
        // Check which side the current key is on (left or right)
        
        if (i >= LEAF_NODE_LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }

        // Calculate the index within the node
        // % is for the case that the new cell has to go into the right node
        // so the cell number will be greater than the max number of cells
        uint32_t index_within_node = i % LEAF_NODE_LEFT_SPLIT_COUNT;
        void* destination = static_cast<Node*>(destination_node)->leafNodeCell(index_within_node);

        if (i == cursor->getCellNum()) {
            // Case where we are on the new cell location
            value->serializeRow(static_cast<char*>(Node(destination).leafNodeValue(index_within_node)));
        } 
        
        else if (i > cursor->getCellNum()) {
            // Case where we are moving cells to the right node
            std::copy(
                static_cast<char*>(Node(old_node).leafNodeCell(i-1)),
                static_cast<char*>(Node(old_node).leafNodeCell(i-1)) + LEAF_NODE_CELL_SIZE,
                static_cast<char*>(destination)
            );
        }

        else {
            // Case where we are moving cells to the left node
            std::copy(
                static_cast<char*>(Node(old_node).leafNodeCell(i)),
                static_cast<char*>(Node(old_node).leafNodeCell(i) + LEAF_NODE_CELL_SIZE),
                static_cast<char*>(destination)
            );
        }

        *(Node(old_node).leafNodeNumCells()) = LEAF_NODE_LEFT_SPLIT_COUNT;
        *(Node(new_node).leafNodeNumCells()) = LEAF_NODE_RIGHT_SPLIT_COUNT;

        if (Node(old_node).isRoot()) {
            return createNewRoot(new_page_num);
        } else {
            printf("Need to implement updating parent after split\n");
            exit(EXIT_FAILURE);
        }
    }
}

void Table::printConstants() {
    std::cout << "ROW_SIZE: " << sizeof(Row) << std::endl;
    std::cout << "COMMON_NODE_HEADER_SIZE: " << (int) COMMON_NODE_HEADER_SIZE << std::endl;
    std::cout << "LEAF_NODE_HEADER_SIZE: " << LEAF_NODE_HEADER_SIZE << std::endl;
    std::cout << "LEAF_NODE_CELL_SIZE: " << LEAF_NODE_CELL_SIZE << std::endl;
    std::cout << "LEAF_NODE_SPACE_FOR_CELLS: " << LEAF_NODE_SPACE_FOR_CELLS << std::endl;
    std::cout << "LEAF_NODE_MAX_CELLS: " << LEAF_NODE_MAX_CELLS << std::endl;
}

void Table::printTree(uint32_t page_num) {
    std::cout << "Tree:\n";
    Node node = Node(pager_->getPage(page_num));
    node.printTree(pager_, 0, 0);
}

Cursor Table::tableFind(uint32_t search_key) {
    Node node = Node(pager_->getPage(root_page_num_));
    if (node.getNodeType() == NODE_LEAF) {
        return leafNodeFind(root_page_num_, search_key);
    } else {
        printf("Need to implement searching for internal node");
        exit(EXIT_FAILURE);
    }
}

Cursor Table::leafNodeFind(uint32_t page_num, uint32_t key) {
    Node node = Node(pager_->getPage(page_num));
    uint32_t num_cells = *(node.leafNodeNumCells());

    Cursor cursor = Cursor(this, page_num, 0, num_cells == LEAF_NODE_MAX_CELLS);

    // Binary Search
    uint32_t min_index = 0;

    // num_cells count starts at 1 while index is 0 based
    while (min_index < num_cells) {
        uint32_t mid = (min_index + num_cells) / 2;
        uint32_t key_at_mid = *(node.leafNodeKey(mid));
        if (key == key_at_mid) {
            cursor.setCellNum(mid);
            return cursor;
        }

        if (key < key_at_mid) {
            num_cells = mid;
        } else {
            min_index = mid + 1;
        }
    }

    cursor.setCellNum(min_index);
    return cursor;
}

void Table::createNewRoot(uint32_t right_child_page_num) {
    /*
    Handle splitting the root.
    Old root copied to new page, becomes left child.
    Address of right child passed in.
    Re-initialize root page to contain the new root node.
    New root node points to two children.
    */

    void *root = pager_->getPage(root_page_num_);
    void *right_child = pager_->getPage(right_child_page_num);
    uint32_t left_child_page_num = pager_->getUnusedPageNum();
    void *left_child = pager_->getPage(left_child_page_num);

    // Moving old root to left child
    std::copy(
        static_cast<char*>(root),
        static_cast<char*>(root) + PAGE_SIZE,
        static_cast<char*>(left_child)
    );
    Node(left_child).setRoot(false);

    // Root node is a new internal node with one key and two children
    // Allocating new root node
    Node n_root = Node(root);
    n_root.initializeInternalNode();
    n_root.setRoot(true);
    *(n_root.internalNodeNumKeys()) = 1;
    *(n_root.internalNodeChild(0)) = left_child_page_num;
    uint32_t left_child_max_key = *(Node(left_child).internalNodeKey(0));
    *(n_root.internalNodeKey(0)) = left_child_max_key;
    *(n_root.internalNodeRightChild()) = right_child_page_num;

}