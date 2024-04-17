#include "Statement.h"
#include <iostream>


Statement::Statement()
: statement_type_(StatementType::INSERT) {}

PrepareResult Statement::prepareStatement(const std::string& input) {
    if (input.substr(0, 6) == "insert") {
        statement_type_ = StatementType::INSERT;
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