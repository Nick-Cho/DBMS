#ifndef STATEMENT_H
#define STATEMENT_H

#include "../../row/include/Row.h"
#include "../../table/include/Table.h"
#include <string>

enum class StatementType {
    INSERT,
    SELECT
};

enum class PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum class ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_DUPLICATE_KEY,
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