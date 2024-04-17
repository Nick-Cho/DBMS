#ifndef STATEMENT_H
#define STATEMENT_H

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
        
    public:
        Statement();        
        PrepareResult prepareStatement(const std::string& input);
        ExecuteResult executeStatement();
};

#endif 