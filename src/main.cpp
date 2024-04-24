#include "./inputBuffer/include/InputBuffer.h"
#include "./statement/include/Statement.h"

#include <iostream>

typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult execMetaCommand(InputBuffer* input_buffer) {
	if (input_buffer->getBuffer() == ".exit") {
		exit(EXIT_SUCCESS);
	} else {
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}

int main(int argc, char* argv[]) {
	std::cout << "Flag 1";
	InputBuffer* input_buffer = InputBuffer::getBufferInstance();
	// Table* table = new Table();

	// while (true) {
	// 	// Reading input for database transaction
	// 	input_buffer->printPrompt();
	// 	input_buffer->readInput(std::cin);
	// 	std::string input = input_buffer->getBuffer();

	// 	// Input error handling
	// 	if (input == ".") {								
	// 		switch (execMetaCommand(input_buffer)){
	// 			case (META_COMMAND_SUCCESS):
	// 				continue;
	// 			case (META_COMMAND_UNRECOGNIZED_COMMAND):
	// 				printf("Unrecognized command '%s'. \n", input.c_str());
	// 				continue;
	// 		}

	// 		// Parsing and validating database transaction request
	// 		Statement statement;
			
	// 		switch (statement.prepareStatement(input)) {
	// 			case (PrepareResult::PREPARE_SUCCESS):
	// 				break;
	// 			case (PrepareResult::PREPARE_SYNTAX_ERROR):
	// 				printf("Syntax error. Could not parse statement. \n");
	// 				continue;				
	// 			case (PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT):
	// 				printf("Unrecognized keyword at start of '%s'. \n", input.c_str());
	// 				continue;
	// 		}

	// 		// Executing database transaction
	// 		switch (statement.executeStatement(table)) {
	// 			case (ExecuteResult::EXECUTE_SUCCESS):
	// 				printf("Executed. \n");
	// 				break;
	// 			case (ExecuteResult::EXECUTE_TABLE_FULL):
	// 				printf("Error: Table full. \n");
	// 				break;
	// 		}

	// 		printf("Executed. \n");
	// 	} else {
	// 		printf("Unrecognized command '%s'. \n", input.c_str());
	// 	}
	// }
	return 0;
}
