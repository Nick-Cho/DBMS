#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H
#include <iostream>

class InputBuffer {
	protected:
		InputBuffer();
	public:
		void printPrompt();
		void readInput();
		void closeInputBuffer();
		char* getBuffer(); // Returns the buffer_ char array
	private:
		char* buffer_;
		size_t buffer_length_;
		ssize_t input_length_;
		static InputBuffer* _s_input_buffer_;		
};

#endif
