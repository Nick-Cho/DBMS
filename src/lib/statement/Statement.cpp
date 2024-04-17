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
            return PrepareResult::PREPARE_SYNTAX_ERROR;
        }

        if (username.length() >  USERNAME_SIZE) {
            std::cout << "Error: Username is too long.\n";
            return PrepareResult::PREPARE_SYNTAX_ERROR;
        }

        if (email.length() > EMAIL_SIZE) {
            std::cout << "Error: Email is too long.\n";
            return PrepareResult::PREPARE_SYNTAX_ERROR;
        }


        return PrepareResult::PREPARE_SUCCESS;
    }
    if (input.substr(0, 6) == "select") {
        statement_type_ = StatementType::SELECT;
        return PrepareResult::PREPARE_SUCCESS;
    }
    return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult Statement::executeStatement() {
    switch (statement_type_) {
        case (StatementType::INSERT):
            std::cout << "Insert succesful.\n";
            return ExecuteResult::EXECUTE_SUCCESS;
        case (StatementType::SELECT):
            std::cout << "Select succesful.\n";
            return ExecuteResult::EXECUTE_SUCCESS;
    }
    std::cout << "Error: Table full.\n";
    return ExecuteResult::EXECUTE_TABLE_FULL;
}