#ifndef ROW_H
#define ROW_H

#include <string>

static const size_t USERNAME_SIZE = 32;
static const size_t EMAIL_SIZE = 255;

class Row {
    public:
        Row();
        void printRow() const;
        void serializeRow( char* destination) const;
        void deserializeRow(const char* source);
        void setId(uint32_t id);
        void setUsername(const std::string& username);
        void setEmail(const std::string& email);
        uint32_t getId() const;
        const char* getUsername() const;
        const char* getEmail() const;
    private:
        uint32_t id_;
        char username_[USERNAME_SIZE + 1]; // +1 for null terminator
        char email_[EMAIL_SIZE + 1];
    
};
#endif