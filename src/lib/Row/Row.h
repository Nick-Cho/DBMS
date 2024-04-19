#ifndef ROW_H
#define ROW_H

#include <string>

static const size_t USERNAME_SIZE = 32;
static const size_t EMAIL_SIZE = 255;

class Row {
    public:
        Row();

        void serialize_row(Row* source, void* destination);
        void deserialize_row(void* source, Row* destination);
    private:
        uint32_t id_;
        char username_[USERNAME_SIZE];
        char email_[EMAIL_SIZE];
    
};
#endif