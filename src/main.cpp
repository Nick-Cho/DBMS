#include "./lib/inputBuffer/InputBuffer.h"
#include <iostream>

int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = InputBuffer::getBufferInstance();
	while (true) {
		input_buffer->printPrompt();
		input_buffer->readInput(std::cin);
		std::string ipt = input_buffer->getBuffer();

		if (ipt == "0") {			
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command '%s'. \n", ipt.c_str());
		}
	}
}
