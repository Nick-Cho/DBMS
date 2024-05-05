#include "./include/Node.h"
#include "../../table/include/Table.h"

Node::Node(void* node): node_(node) {}

void Node::initializeLeafNode() {
    setNodeType(NODE_LEAF);
    setRoot(false);
    *leafNodeNumCells() = 0;    
    *leafNodeNextLeaf() = 0;
}

uint32_t* Node::leafNodeNumCells() {
    // This is the location of the byte representing num_cells in the Leaf Node header
    return static_cast<uint32_t*>(node_ + LEAF_NODE_NUM_CELLS_OFFSET);
}

void* Node::leafNodeCell(uint32_t cell_num) {
    return node_ + LEAF_NODE_HEADER_SIZE + (cell_num * LEAF_NODE_CELL_SIZE);
}

uint32_t* Node::leafNodeKey(uint32_t cell_num) {
    return static_cast<uint32_t*>(leafNodeCell(cell_num));
}

void* Node::leafNodeValue(uint32_t cell_num) {
    return leafNodeCell(cell_num) + LEAF_NODE_KEY_SIZE;
}

uint32_t* Node::leafNodeNextLeaf() {
    return static_cast<uint32_t*>(node_ + LEAF_NODE_HEADER_SIZE + LEAF_NODE_CELL_SIZE);
}

void Node::setRoot(bool is_root) {
    uint8_t value = static_cast<uint8_t>(is_root);
    *static_cast<uint8_t*>(node_ + IS_ROOT_OFFSET) = value;
}

void Node::indent(uint32_t level) {
    for (uint32_t i=0; i<level; ++i) {
        printf("  ");
    }
}

void Node::printTree(Pager &pager_, uint32_t page_num, uint32_t indentation_level) {
    void* node = pager_.getPage(page_num);
    uint32_t num_keys, child;

    switch (getNodeType()) {
        case NODE_LEAF:
            num_keys = *leafNodeNumCells();
            indent(indentation_level);
            printf("- leaf (size %d)\n", num_keys);
            for (uint32_t i=0; i<num_keys; ++i) {
                indent(indentation_level + 1);
                printf("- %d\n", *leafNodeKey(i));
            }
            break;
        case NODE_INTERNAL:
            num_keys = *internalNodeNumKeys();
            indent(indentation_level);
            printf("- internal (size %d)\n", num_keys);
            if (num_keys > 0) {
                for (uint32_t i=0; i<num_keys; ++i) {
                    child = *internalNodeChild(i);
                    printTree(pager_, child, indentation_level + 1);

                    indent(indentation_level + 1);
                    printf("- key %d\n", *internalNodeKey(i));
                }
            }
            child = *internalNodeRightChild();
            printTree(pager_, child, indentation_level + 1);
            break;
    }
}

NodeType Node::getNodeType() {
    uint8_t value = *static_cast<uint8_t*>(node_ + NODE_TYPE_OFFSET);
    return static_cast<NodeType>(value);
}

void Node::setNodeType(NodeType type) {
    uint8_t value = static_cast<uint8_t>(type);
    *static_cast<uint8_t*>(node_ + NODE_TYPE_OFFSET) = value;
}

void Node::initializeLeafNode() {
    setNodeType(NODE_LEAF);
    setRoot(false);
    *leafNodeNumCells() = 0;
    *leafNodeNextLeaf() = 0; // since it has no siblings
}

uint32_t* Node::internalNodeNumKeys() {
    return static_cast<uint32_t*>(node_ + INTERNAL_NODE_NUM_KEYS_SIZE);
}

uint32_t* Node::internalNodeRightChild() {
    return static_cast<uint32_t*>(node_ + INTERNAL_NODE_RIGHT_CHILD_OFFSET);
}

uint32_t* Node::internalNodeCell(uint32_t cell_num) {
    return static_cast<uint32_t*>(node_ + INTERNAL_NODE_HEADER_SIZE + (cell_num * INTERNAL_NODE_CELL_SIZE));
}

uint32_t* Node::internalNodeChild(uint32_t child_num) {
    uint32_t num_keys = *internalNodeNumKeys();
    if (child_num > num_keys) {
        printf("Tried to access child_num %d > num_keys %d\n", child_num, num_keys);
        exit(EXIT_FAILURE);
    } else if (child_num == num_keys) {
        // return internalNodeRightChild();
        uint32_t right_child = *internalNodeRightChild();
        if (right_child == INVALID_PAGE_NUM) {
            printf("Tried to access right child when it doesn't exist\n");
            exit(EXIT_FAILURE);
        } else {
            return &right_child;
        }
    } else {
        uint32_t child_num = *internalNodeCell(child_num);
        if (child_num == INVALID_PAGE_NUM) {
            printf("Tried to access child at invalid page number\n");
            exit(EXIT_FAILURE);
        } else {
            return &child_num;
        }
        // return internalNodeCell(child_num);
    }
}

uint32_t* Node::internalNodeKey(uint32_t key_num) {
    return internalNodeCell(key_num) + INTERNAL_NODE_CHILD_SIZE;
}

bool Node::isRoot() {
    return *static_cast<uint8_t*>(node_ + IS_ROOT_OFFSET);
}

void Node::initializeInternalNode() {
    setNodeType(NODE_INTERNAL);
    setRoot(false);
    *internalNodeNumKeys() = 0;
    /*
    Necessary because the root page number is 0; by not initializing an internal 
    node's right child to an invalid page number when initializing the node, we may
    end up with 0 as the node's right child, which makes the node a parent of the root
    */
    *internalNodeRightChild() = INVALID_PAGE_NUM;
}

uint32_t* Node::leafNodeNextLeaf() {
    return static_cast<uint32_t*>(node_ + LEAF_NODE_NEXT_LEAF_OFFSET);
}

uint32_t* Node::nodeParent() {
    return static_cast<uint32_t*>(node_ + PARENT_POINTER_OFFSET);
}

void Node::updateInternalNodeKey(uint32_t old_key, uint32_t new_key) {
    uint32_t old_child_num = internalNodeFindChild(old_key);
    *internalNodeKey(old_child_num) = new_key;
}

uint32_t Node::internalNodeFindChild(uint32_t key) {
    uint32_t num_keys = *internalNodeNumKeys();
    uint32_t left = 0;
    uint32_t right = num_keys;

    while(left != right) {
        uint32_t mid = (left + right) / 2;
        uint32_t key_to_right = *internalNodeKey(mid);
        if (key_to_right >= key) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}