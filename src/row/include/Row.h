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
    private:
        uint32_t id_;
        char username_[USERNAME_SIZE];
        char email_[EMAIL_SIZE];
    
};
#endif