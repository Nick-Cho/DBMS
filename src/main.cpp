
int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = InputBuffer();
	while (true) {
		input_buffer->printPrompt();
		input_buffer->readInput(input_buffer);
		
		if (strcmp(input_buffer->_buffer, ".exit") == 0) {
			inputBuffer->closeInputBuffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command '%s'. \n", input_buffer->_buffer)
		}
	}
}
