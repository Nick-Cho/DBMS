#include "./include/Row.h"
#include <iostream>

Row::Row() : id_(0) {
    std::memset(username_, 0, USERNAME_SIZE);
    std::memset(email_, 0, EMAIL_SIZE);
}

void Row::serialize_row(char* destination) const {
    std::memcpy(destination, &(id_), sizeof(id_));
    std::memcpy(destination + sizeof(id_), &(username_), sizeof(username_));
    std::memcpy(destination + sizeof(id_) + sizeof(username_), &(email_), sizeof(email_));
}

void Row::deserialize_row(const char* source) {
    std::memcpy(&(id_), source, sizeof(id_));
    std::memcpy(&(username_), source + sizeof(id_), sizeof(username_));
    std::memcpy(&(email_), source + sizeof(id_) + sizeof(username_), sizeof(email_));
}

void Row::print_row() const {
    std::cout << id_ << ", " << username_ << ", " << email_ << std::endl;
}