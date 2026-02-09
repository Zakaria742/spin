cmake_minimum_required( VERSION 3.21 )
project(spin)

set(SOURCES src/main.c src/utils.c)
set(HEADERS libs/utils.h)
set(EXE spin)
add_executable(${EXE} ${SOURCES} ${HEADERS})
target_compile_options(${EXE} PRIVATE -g -Wall -Werror -Wextra)
target_link_libraries(${EXE} PRIVATE m)
