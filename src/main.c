#include <stdint.h>

extern void tok_printf(char * input, uint32_t input_size);
extern void tok_exit(void);

void start() {
    
    // on the mac os x platform there are alignment rules, so we're doing
    // this stuff which isn't nescessary on linux
    
    char * message = "Hello\n";
    
    tok_printf(message, 6);
    tok_exit();
}

