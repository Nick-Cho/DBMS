#include "./include/Row.h"
#include <iostream>

Row::Row() : id_(0) {
    std::memset(username_, 0, USERNAME_SIZE);
    std::memset(email_, 0, EMAIL_SIZE);
}

void Row::serializeRow(char* destination) const {
    std::memcpy(destination, &(id_), sizeof(id_));
    std::memcpy(destination + sizeof(id_), &(username_), USERNAME_SIZE);
    std::memcpy(destination + sizeof(id_) + USERNAME_SIZE, &(email_), EMAIL_SIZE);
}

void Row::deserializeRow(const char* source) {
    std::memcpy(&(id_), source, sizeof(id_));
    std::memcpy(&(username_), source + sizeof(id_), USERNAME_SIZE);
    std::memcpy(&(email_), source + sizeof(id_) + USERNAME_SIZE, EMAIL_SIZE);
}

void Row::printRow() const {
    std::cout << id_ << ", " << username_ << ", " << email_ << std::endl;
}

void Row::setId(uint32_t id) {
    id_ = id;
}

void Row::setUsername(const std::string& username) {
    std::strncpy(username_, username.c_str(), USERNAME_SIZE);
    this->username_[USERNAME_SIZE] = '\0';
}

void Row::setEmail(const std::string& email) {
    std::strncpy(email_, email.c_str(), EMAIL_SIZE);
    this->email_[EMAIL_SIZE] = '\0';
}

uint32_t Row::getId() const {
    return id_;
}

const char* Row::getUsername() const {
    return username_;
}   

const char* Row::getEmail() const {
    return email_;
}