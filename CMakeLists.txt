cmake_minimum_required(VERSION 3.20)

project(data_struct_learning)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(CMAKE_CXX_COMPILE_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Werror -fsanitize=address)
    add_link_options(-fsanitize=address)
else()
    set(CMAKE_COMPILE_WARNING_AS_ERROR true)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(src SRC)

add_executable(${PROJECT_NAME} ${SRC})
