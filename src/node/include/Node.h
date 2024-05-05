#ifndef NODE_H
#define NODE_H

#include "../../row/include/Row.h"
#include "../../pager/include/Pager.h"

#include <iostream> 

typedef enum {NODE_INTERNAL, NODE_LEAF} NodeType;

/*
 Common Node Header Layout
*/
const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
const uint32_t NODE_TYPE_OFFSET = 0;
const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
const uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
const uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

/*
* Leaf Node Header Layout
*/
const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
const uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;
const uint32_t LEAF_NODE_NEXT_LEAF_OFFSET = LEAF_NODE_NUM_CELLS_OFFSET + LEAF_NODE_NUM_CELLS_SIZE;

/*
* Leaf Node Body Layout
*/
const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
const uint32_t LEAF_NODE_KEY_OFFSET = 0;
const uint32_t LEAF_NODE_VALUE_SIZE = sizeof(Row);
const uint32_t LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
const uint32_t LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
const uint32_t LEAF_NODE_MAX_CELLS = LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;

/*
* Leaf Node Splitting Constants
*/
const uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) / 2;
const uint32_t LEAF_NODE_LEFT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) - LEAF_NODE_RIGHT_SPLIT_COUNT;


/*
 * Internal Node Header Layout
 */
// Left child should just be at the start of the internal node body
const uint32_t INTERNAL_NODE_NUM_KEYS_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_NODE_NUM_KEYS_OFFSET = COMMON_NODE_HEADER_SIZE;
const uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET = INTERNAL_NODE_NUM_KEYS_OFFSET + INTERNAL_NODE_NUM_KEYS_SIZE;
const uint32_t INTERNAL_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + INTERNAL_NODE_NUM_KEYS_SIZE + INTERNAL_NODE_RIGHT_CHILD_SIZE;

/*
 * Internal Node Body Layout
 */
// The body is an array of cells where each cell contains at least one child pointer and a key. 
// Every key should be the maximum key contained in the child to its left.
const uint32_t INTERNAL_NODE_KEY_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_NODE_CHILD_SIZE = sizeof(uint32_t);
const uint32_t INTERNAL_NODE_CELL_SIZE = INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE;
const uint32_t LEAF_NODE_NEXT_LEAF_SIZE = sizeof(uint32_t);
const uint32_t LEAF_NODE_NEXT_LEAF_OFFSET = LEAF_NODE_NUM_CELLS_OFFSET + LEAF_NODE_NUM_CELLS_SIZE;
const uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE + LEAF_NODE_NEXT_LEAF_SIZE;
const uint32_t INTERNAL_NODE_MAX_CELLS = 3;


class Node {
    private:
        void *node_;
    public:
        Node(void *node);
        
        void initializeLeafNode();

        uint32_t* leafNodeNumCells();
        
        void* leafNodeCell(uint32_t cell_num);
        
        uint32_t* leafNodeKey(uint32_t cell_num);
        
        void* leafNodeValue(uint32_t cell_num);    
        
        uint32_t* leafNodeNextLeaf(); 
        
        void initializeLeafNode();
        
        void setRoot(bool isRoot);   

        void printTree(Pager &pager, uint32_t page_num, uint32_t indentation_level);

        void indent(uint32_t level);

        NodeType getNodeType();

        void setNodeType(NodeType type);

        uint32_t* internalNodeNumKeys();

        uint32_t* internalNodeRightChild();

        uint32_t* internalNodeCell(uint32_t cell_num);

        uint32_t* internalNodeChild(uint32_t child_num);

        uint32_t* internalNodeKey(uint32_t key_num); // Gets the key associated with the internal node (should be the maximum key in the left child)

        uint32_t getNodeMaxKey();

        bool isRoot();

        void setRoot(bool is_root);

        void initializeInternalNode();

        uint32_t* leafNodeNextLeaf();

        uint32_t* nodeParent();

        void updateInternalNodeKey(uint32_t old_key, uint32_t new_key);

        uint32_t internalNodeFindChild(uint32_t key); // Returns the index of the child which should contain the key
};
#endif