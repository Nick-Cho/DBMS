cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DBMS)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

include(CTest)
add_subdirectory(test)
add_subdirectory(lib)
include_directories(src)

include(UpdateSubmodules.cmake)

add_library(node STATIC src/node/include/node.h src/node/node.cpp)
target_include_directories(node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/node/include)
target_link_libraries(node PUBLIC table)

add_library(cursor STATIC src/cursor/include/cursor.h src/cursor/cursor.cpp)
target_include_directories(cursor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/cursor/include)
target_link_libraries(cursor PUBLIC table)

add_library(table STATIC src/table/include/table.h src/table/table.cpp)
target_include_directories(table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/table/include)
target_link_libraries(table PUBLIC pager cursor node)

add_library(row STATIC src/row/include/row.h src/row/row.cpp)
target_include_directories(row PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/row/include)
target_link_libraries(row PUBLIC table)

add_library(pager STATIC src/pager/include/pager.h src/pager/pager.cpp)
target_include_directories(pager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/pager/include)
target_link_libraries(pager PUBLIC row table)

add_library(statement STATIC src/statement/include/statement.h src/statement/statement.cpp)
target_include_directories(statement PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/statement/include)
target_link_libraries(statement PRIVATE row table)

add_library(inputBuffer STATIC src/inputBuffer/include/inputBuffer.h src/inputBuffer/inputBuffer.cpp)
target_include_directories(inputBuffer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/inputBuffer/include)

add_executable(DBMS src/main.cpp)
target_link_libraries(DBMS PUBLIC statement inputBuffer)