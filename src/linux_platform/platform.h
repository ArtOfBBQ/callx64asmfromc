#ifndef LINUX_PLATFORM_H
#define LINUX_PLATFORM_H

#define uint32_t unsigned int
#define int32_t signed int
#define uint64_t unsigned long

extern void tok_print(char * input, uint32_t input_len);
extern void * tok_malloc(uint32_t len);
extern uint64_t tok_time();
extern void tok_exit();

#endif // LINUX_PLATFORM_H

