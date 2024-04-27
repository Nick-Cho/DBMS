#ifndef ROW_H
#define ROW_H

#include <string>

static const size_t USERNAME_SIZE = 32;
static const size_t EMAIL_SIZE = 255;

class Row {
    public:
        Row();
        void print_row() const;
        void serialize_row( char* destination) const;
        void deserialize_row(const char* source);
        void set_id(uint32_t id);
        void set_username(const std::string& username);
        void set_email(const std::string& email);
        uint32_t get_id() const;
        const char* get_username() const;
        const char* get_email() const;
    private:
        uint32_t id_;
        char username_[USERNAME_SIZE + 1]; // +1 for null terminator
        char email_[EMAIL_SIZE + 1];
    
};
#endif