cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DBMS)

add_library(table STATIC src/table/include/table.h src/table/table.cpp)
target_include_directories(table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/table/include)

add_library(row STATIC src/row/include/row.h src/row/row.cpp)
target_include_directories(row PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/row/include)
target_link_libraries(row PUBLIC table)

add_library(statement STATIC src/statement/include/statement.h src/statement/statement.cpp)
target_include_directories(statement PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/statement/include)
target_link_libraries(statement PRIVATE row table)

add_library(inputBuffer STATIC src/inputBuffer/include/inputBuffer.h src/inputBuffer/inputBuffer.cpp)
target_include_directories(inputBuffer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/inputBuffer/include)

add_executable(DBMS src/main.cpp)
target_link_libraries(DBMS PUBLIC statement inputBuffer)