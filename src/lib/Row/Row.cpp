#include "Row.h"
#include <iostream>

Row::Row() : id_(0) {
    std::memset(username_, 0, USERNAME_SIZE);
    std::memset(email_, 0, EMAIL_SIZE);
}

void Row::serialize_row(void* destination) const {
    std::memcpy(destination, &(id_), sizeof(id_));
    std::memcpy(destination + sizeof(id_), &(username_), USERNAME_SIZE);
    std::memcpy(destination + sizeof(id_) + sizeof(username_), &(email_), EMAIL_SIZE);
}

void Row::deserialize_row(void* source) {
    std::memcpy(&(id_), source, sizeof(id_));
    std::memcpy(&(username_), source + sizeof(id_), USERNAME_SIZE);
    std::memcpy(&(email_), source + sizeof(id_) + USERNAME_SIZE, EMAIL_SIZE);
}

void Row::print_row() const {
    std::cout << id_ << ", " << username_ << ", " << email_ << std::endl;
}