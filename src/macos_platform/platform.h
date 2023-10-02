#ifndef MACOS_PLATFORM_H
#define MACOS_PLATFORM_H

#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>

void tok_print(char * input, uint32_t input_len);
void * tok_malloc(uint32_t len);
extern uint64_t tok_time();
extern void tok_exit();

#endif // MACOS_PLATFORM_H

