#include "./include/Pager.h"
#include <iostream>

Pager::Pager(const std::string &filename): file_length(0), pages() {
    file_stream.open(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    if (!file_stream.is_open()) {
        std::cerr << "Unable to open file\n";
        exit(EXIT_FAILURE);
    }

    file_length = file_stream.tellg();
    file_stream.seekg(0, std::ios::beg);

    pages.resize(TABLE_MAX_PAGES);
};