#include "./inputBuffer/include/InputBuffer.h"
#include "./statement/include/Statement.h"

#include <iostream>

typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult execMetaCommand(InputBuffer* input_buffer, Table* table) {
	if (input_buffer->getBuffer() == ".exit") {
		table->dbClose();
		exit(EXIT_SUCCESS);
	} 
	else if (input_buffer->getBuffer() == ".constants") {
		std::cout << "Constants: \n";
		table->printConstants();
		return META_COMMAND_SUCCESS;
	}
	else {
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Must supply a database name\n";
		exit(EXIT_FAILURE);
	}

	char* filename = argv[1];

	InputBuffer* input_buffer = InputBuffer::getBufferInstance();
	Table* table = new Table();
	table->dbOpen(filename);

	while (true) {
		// Reading input for database transaction
		input_buffer->printPrompt();
		input_buffer->readInput(std::cin);
		std::string input = input_buffer->getBuffer();

		// Input error handling
		if (input[0] == '.') {								
			switch (execMetaCommand(input_buffer, table)){
				case (META_COMMAND_SUCCESS):
					continue;
				case (META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s'. \n", input.c_str());
					continue;
			}
		}	
			// Parsing and validating database transaction request
		Statement statement;
		
		switch (statement.prepareStatement(input)) {
			case (PrepareResult::PREPARE_SUCCESS):
				break;
			case (PrepareResult::PREPARE_SYNTAX_ERROR):
				printf("Syntax error. Could not parse statement. \n");
				continue;				
			case (PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword at start of '%s'. \n", input.c_str());
				continue;
			case (PrepareResult::PREPARE_NEGATIVE_ID):
				printf("Id provided for insert is negative \n");
				continue;
			case(PrepareResult:: PREPARE_STRING_TOO_LONG):
				printf("The string provided for insertion is too long \n");
				continue;
		}

		// Executing database transaction
		switch (statement.executeStatement(table)) {
			case (ExecuteResult::EXECUTE_SUCCESS):
				printf("Executed. \n");
				break;
			case (ExecuteResult::EXECUTE_TABLE_FULL):
				printf("Error: Table full. \n");
				break;
		}
	}
	return 0;
}
