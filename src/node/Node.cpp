#include "./include/Node.h"

Node::Node(void* node): node_(node) {}

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

void Node::setRoot(bool isRoot) {
    uint8_t value = static_cast<uint8_t>(isRoot);
    *static_cast<uint8_t*>(node_ + IS_ROOT_OFFSET) = value;
}
