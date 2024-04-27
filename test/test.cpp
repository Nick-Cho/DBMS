#include <gtest/gtest.h>

#include <iostream>

#include "../src/inputBuffer/include/InputBuffer.h"
#include "../src/statement/include/Statement.h"
#include "../src/table/include/Table.h"
#include "../src/row/include/Row.h"

using namespace std;

TEST(DBTest, readWrite1) { 
    //Tests basic read and write functionality
    
    Row row;
    row.set_id(1);
    row.set_username("foo");
    row.set_email("foo@bar.com");

    
    size_t PAGE_SIZE = 4096;
    size_t TABLE_MAX_PAGES = 100;
    size_t ROWS_PER_PAGE = PAGE_SIZE / sizeof(Row);
    size_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;
    
    void* pages[TABLE_MAX_PAGES];
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pages[i] = nullptr;
    }

    pages[0] = new char[PAGE_SIZE];
    void* destination = static_cast<char*>(pages[0]);

    row.serialize_row(static_cast<char*>(destination));

    Row test_row;
    test_row.deserialize_row(static_cast<const char*>(destination));
    test_row.print_row();
    
    ASSERT_EQ(test_row.get_email(), "foo@bar.com");
}