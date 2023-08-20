#include <stdlib.h>
#include <stdint.h>

extern void tok_printf(char * input, uint32_t input_size);
extern void tok_exit(void);

int main() {
    
    // on the mac os x platform there are alignment rules, so we're doing
    // this stuff which isn't nescessary on linux
    
    char * message = (char *)malloc(100 + 64);
    while ((uintptr_t)message % 16 != 0) {
        message += 1;
    }
    
    message[0] = 'H';
    message[1] = 'e';
    message[2] = 'l';
    message[3] = 'l';
    message[4] = 'o';
    message[5] = '\n';
    
    tok_printf(message, 6);
    tok_exit();
}

