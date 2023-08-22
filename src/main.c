#define uint32_t unsigned int

extern void tok_printf(char * input, uint32_t input_size);
extern void tok_exit(void);

#define ANSI_RESET_STYLES_AND_COLORS "\x1b[0m"
#define ANSI_BOLD_RED                "\x1b[1;31m"


static uint32_t strlen(char * str) {
    uint32_t return_value = 0;
    while (str[return_value] != '\0') {
        return_value += 1;
    }
    
    return return_value + 1;
}

void start() {
    
    // on the mac os x platform there are alignment rules, so we're doing
    // this stuff which isn't nescessary on linux
    
    char * message =
        "Hello"ANSI_BOLD_RED" world\n"ANSI_RESET_STYLES_AND_COLORS;
    
    tok_printf(message, strlen(message));
    tok_exit();
}

