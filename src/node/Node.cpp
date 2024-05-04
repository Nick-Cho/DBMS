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

void Node::printLeafNode() {
    uint32_t num_cells = *leafNodeNumCells();
    std::cout << "leaf (size " << num_cells << "): ";
    for (uint32_t i=0; i<num_cells; ++i) {
        uint32_t key = *leafNodeKey(i);
        std::cout <<"- " << i << " :"<< key << " \n";
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
        return internalNodeRightChild();
    } else {
        return internalNodeCell(child_num);
    }
}

uint32_t* Node::internalNodeKey(uint32_t key_num) {
    return internalNodeCell(key_num) + INTERNAL_NODE_CHILD_SIZE;
}