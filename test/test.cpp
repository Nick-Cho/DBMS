#include <gtest/gtest.h>

#include <iostream>

#include "../src/inputBuffer/include/InputBuffer.h"
#include "../src/statement/include/Statement.h"
#include "../src/table/include/Table.h"
#include "../src/row/include/Row.h"

using namespace std;

TEST(DBTest, rWUnitTest1) { 
    //Tests basic read and write functionality
    
    Row row;
    row.set_id(1);
    row.set_username("foo");
    row.set_email("foo@bar.com");
    
    size_t PAGE_SIZE = 4096;
    size_t TABLE_MAX_PAGES = 100;
    
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
    
    ASSERT_STREQ(test_row.get_email(), "foo@bar.com"); // ASSERT_EQ checks for pointer equality and not value equality
}

TEST(DBTest, rWUnitTest2) {
    //Tests max input length
    Row row;
    string username = string(32, 'a');
    string email = string(255, 'a');
    
    row.set_id(1);
    row.set_username(username);
    row.set_email(email);

    size_t PAGE_SIZE = 4096;
    size_t TABLE_MAX_PAGES = 100;

    void* pages[TABLE_MAX_PAGES];
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pages[i] = nullptr;
    }
    pages[0] = new char[PAGE_SIZE];
    void* destination = static_cast<char*>(pages[0]);

    row.serialize_row(static_cast<char*>(destination));
    ASSERT_STREQ(row.get_username(), username.c_str());
}

TEST(DBTest, rWEdgeCase1) {
    // Tests overloading the table edge case
    Table* table = new Table();
    Statement statement;    
    
    char response[] = "";
    char* response_ptr = response;

    size_t TABLE_MAX_PAGES = 100;
    static const size_t PAGE_SIZE = 4096; // 4Kb
    static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / sizeof(Row);
    static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;
    
    
    for (uint32_t i = 0; i < TABLE_MAX_ROWS+1; i++) {                
        statement.prepareStatement("insert 1 foo foo@test.com");
        switch (statement.executeStatement(table)) {
			case (ExecuteResult::EXECUTE_SUCCESS):
				response_ptr = "Executed.";
				break;
			case (ExecuteResult::EXECUTE_TABLE_FULL):
				response_ptr = "Error: Table full.";
				break;
		}
    }

    ASSERT_STREQ(response_ptr, "Error: Table full.");
}

TEST(DBTest, rWEdgeCase2) {
    // Tests overloading row input length edge case

    Statement statement;    
    string username = string(33, 'a');
    string email = string(256, 'a');

    string cmd = "insert 1 " + username + " " + email;
    testing::internal::CaptureStdout();
    statement.prepareStatement(cmd);
    std:string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, std::string("Error: Username is too long.\n"));       

    cmd = "insert 1  foo " + email; 
    testing::internal::CaptureStdout();
    statement.prepareStatement(cmd);
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, std::string("Error: Email is too long.\n"));    
}

TEST (DBTest, persistenceTest) {
    string file_name = "mydb.db";
    ofstream file(file_name, ios::binary);
    file.close();

    Table *table = new Table();
    table->db_open(file_name);

    Statement statement;    
    string username = string(33, 'a');
    string email = string(256, 'a');
    string cmd = "insert 1 " + username + " " + email;
    statement.prepareStatement(cmd);

    statement.executeStatement(table);

    table->db_close();

    Table *table2 = new Table();
    table2->db_open(file_name);

    Statement statement;
    string cmd = "select";
    statement.prepareStatement(cmd);
    statement.executeStatement(table2);
    std:string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output, std::string(" "));  
    table2->db_close();
}