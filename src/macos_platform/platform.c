#include "platform.h"

void tok_print(char * input, uint32_t input_len)
{
    printf("%s", input);
}

void * tok_malloc(uint32_t len) {
   void * return_value = mmap(
        /* void *addr: */
            NULL,
        /* size_t len: */
            len,
        /* int prot: */
            PROT_READ | PROT_WRITE,
        /* int flags: */
            MAP_SHARED | MAP_ANONYMOUS,
        /* int fildes: */
            -1,
        /* off_t offset: */
            0);
    
    return return_value;
}

