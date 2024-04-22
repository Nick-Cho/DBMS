#ifndef STATEMENT_H
#define STATEMENT_H

#include "../Row/Row.h"
#include "../Table/Table.h"
#include <string>

enum class StatementType {
    INSERT,
    SELECT
};

enum class PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum class ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
};

class Statement {
    private:
        StatementType statement_type_;
        Row row_;
        ExecuteResult execute_insert(Table* table);
        ExecuteResult execute_select(Table* table);
    public:
        Statement();        
        PrepareResult prepareStatement(const std::string& input);
        ExecuteResult executeStatement(Table* table);
};

#endif 