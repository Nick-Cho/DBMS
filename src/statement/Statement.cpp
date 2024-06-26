#include "Statement.h"
#include <iostream>
#include <sstream>

Statement::Statement()
: statement_type_(StatementType::INSERT) {}

PrepareResult Statement::prepareStatement(const std::string& input) {
    if (input.substr(0, 6) == "insert") {
        statement_type_ = StatementType::INSERT;
        
        uint32_t id;
        std::string username;
        std::string email;
        int num_args = 0;
        std::istringstream iss;
        iss.str(input);
        std::string command;
        iss >> command;
        if (command != "insert") {
            return PrepareResult::PREPARE_SYNTAX_ERROR;
        } else {
            iss >> id; // id can't be negative by definition
            iss >> username;
            iss >> email;
            num_args = (iss.fail() ? 0 : 3);
        }

        // Checking for Input Errors:
        
        if (num_args != 3) {
            return PrepareResult::PREPARE_SYNTAX_ERROR;
        }
        if (id < 0) {
            std::cout << "Error: ID must be positive.\n";
            return PrepareResult::PREPARE_NEGATIVE_ID;
        }

        if (username.length() >  USERNAME_SIZE) {
            std::cout << "Error: Username is too long.\n";
            return PrepareResult::PREPARE_STRING_TOO_LONG;
        }

        if (email.length() > EMAIL_SIZE) {
            std::cout << "Error: Email is too long.\n";
            return PrepareResult::PREPARE_STRING_TOO_LONG;
        }

        row_.set_id(id);
        row_.set_username(username);
        row_.set_email(email);

        return PrepareResult::PREPARE_SUCCESS;
    }
    if (input.substr(0, 6) == "select") {
        statement_type_ = StatementType::SELECT;
        return PrepareResult::PREPARE_SUCCESS;
    }
    return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult Statement::executeStatement(Table* table) {
    switch (statement_type_) {
        case (StatementType::INSERT):
            return execute_insert(table);
        case (StatementType::SELECT):
            return execute_select(table);
    }
    std::cout << "Error: Table full.\n";
    return ExecuteResult::EXECUTE_TABLE_FULL;
}

ExecuteResult Statement::execute_insert(Table* table) {
    if (table->insert(row_)) {
        return ExecuteResult::EXECUTE_SUCCESS;
    } else {
        return ExecuteResult::EXECUTE_TABLE_FULL;
    }
}

ExecuteResult Statement::execute_select(Table* table) {
    table->select();
    return ExecuteResult::EXECUTE_SUCCESS;
}