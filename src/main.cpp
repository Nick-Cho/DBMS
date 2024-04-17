#include "./lib/inputBuffer/InputBuffer.h"
#include <iostream>

int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = InputBuffer::getBufferInstance();
	while (true) {
		input_buffer->printPrompt();
		input_buffer->readInput(std::cin);
		std::string ipt = input_buffer->getBuffer();

		if (ipt == ".") {								
			switch (doMetaCommand(input_buffer)){
				case (META_COMMAND_SUCCESS):
					continue;
				case (META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s'. \n", ipt.c_str());
					continue;
			}
			Statement statement;
			switch (prepareStatement(input_buffer, &statement)) {
				case (PREPARE_SUCCESS):
					break;
				case (PREPARE_SYNTAX_ERROR):
					printf("Syntax error. Could not parse statement. \n");
					continue;
				case (PREPARE_UNRECOGNIZED_STATEMENT):
					printf("Unrecognized keyword at start of '%s'. \n", ipt.c_str());
					continue;
			}

			executeStatement(&statement);
			printf("Executed. \n");
		} else {
			printf("Unrecognized command '%s'. \n", ipt.c_str());
		}
	}
}
