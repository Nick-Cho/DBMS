#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H
#include <iostream>
#include <string>

class InputBuffer {
	protected:
		InputBuffer();
	public:
		static InputBuffer* getBufferInstance();

		void printPrompt();
		void readInput(std::istream& in);
		// void closeInputBuffer(); // Destructor functionality overlap
		std::string getBuffer(); // Getter for buffer_
	private:
		std::string buffer_;
		size_t buffer_length_;
		ssize_t input_length_;
		static InputBuffer* _s_input_buffer_;		
};

#endif
