#include "./include/InputBuffer.h"

InputBuffer* InputBuffer::_s_input_buffer_ = nullptr;

InputBuffer::InputBuffer()
: buffer_length_(0), input_length_(0) {}

void InputBuffer::closeBuffer() {
    delete _s_input_buffer_;
    _s_input_buffer_ = nullptr;
}

InputBuffer* InputBuffer::getBufferInstance() {    
    if (_s_input_buffer_ == nullptr) {
        _s_input_buffer_ = new InputBuffer();
    }
    return _s_input_buffer_;
}

void InputBuffer::printPrompt() {
    printf("db > ");
}

void InputBuffer::readInput(std::istream& in) {
    std::getline(in, buffer_);
    buffer_length_ = buffer_.length();

    if (buffer_length_ <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // C++ getline implementation already discards new line character
}

std::string InputBuffer::getBuffer() {
    return buffer_;
}


