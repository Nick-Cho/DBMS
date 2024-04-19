#include "Row.h"

Row::Row() : id_(0) {
    std::memset(username_, 0, USERNAME_SIZE);
    std::memset(email_, 0, EMAIL_SIZE);
}

void Row::serialize_row(Row* source, void* destination) {
    std::memcpy(destination, &(source->id_), sizeof(source->id_));
    std::memcpy(destination + sizeof(source->id_), &(source->username_), USERNAME_SIZE);
    std::memcpy(destination + sizeof(source->id_) + sizeof(source->username_), &(source->email_), EMAIL_SIZE);
}

void Row::deserialize_row(void* source, Row* destination) {
    std::memcpy(&(destination->id_), source, sizeof(destination->id_));
    std::memcpy(&(destination->username_), source + sizeof(destination->id_), USERNAME_SIZE);
    std::memcpy(&(destination->email_), source + sizeof(destination->id_) + USERNAME_SIZE, EMAIL_SIZE);
}