#define uint32_t unsigned int
#define uint64_t unsigned int

extern void tok_printf(char * input, uint32_t input_size);
extern void tok_exit(void);
extern uint64_t tok_time(void);

static uint64_t app_start_time = 0;

#define ANSI_RESET_STYLES_AND_COLORS "\x1b[0m"
#define ANSI_BOLD_RED                "\x1b[1;31m"

#define ANSI_CURSOR_HOME             "\x1b[H"
#define ANSI_ERASE_SCREEN            "\x1b[2J"
#define ANSI_ERASE_CURSOR_TO_END     "\x1b[0J"

static void uint_to_string(
    char * recipient,
    uint64_t input)
{
    if (input == 0) {
        recipient[0] = '0';
        recipient[1] = '\0';
        return;
    }
    
    uint32_t i = 0;
    uint32_t start_i = 0;
    uint32_t end_i;
    
    uint64_t decimal = 1;
    uint64_t input_div_dec = input;
    while (input_div_dec > 0 && decimal < 10000001) {
        uint64_t isolated_num = input % (decimal * 10);
        isolated_num /= decimal;
        recipient[i] = (char)('0' + isolated_num);
        i += 1;
        
        decimal *= 10;
        input_div_dec = input / decimal;
    }
    end_i = i - 1;
    
    recipient[end_i + 1] = '\0';
    
    // if we started with an input of -32, we should now have
    // the resut '-' '2' '3', with start_i at '2' and end_i at '3'
    // we want to swap from start_i to end_i
    while (start_i < end_i) {
        char swap = recipient[start_i];
        recipient[start_i] = recipient[end_i];
        recipient[end_i] = swap;
        end_i -= 1;
        start_i += 1; 
    }
}

static uint32_t strlen(char * str) {
    uint32_t return_value = 0;
    while (str[return_value] != '\0') {
        return_value += 1;
    }
    
    return return_value + 1;
}

static void strcat(char * recipient, char * input) {
    uint32_t i = 0;
    while (recipient[i] != '\0') {
        i++;
    }
    
    uint32_t j = 0;
    while (input[j] != '\0') {
        recipient[i++] = input[j++];
    }
    
    recipient[i] = '\0';
}

static uint32_t draw_frame() {
    char message[1024];
    message[0] = '\0';
    
    strcat(
        message,
        ANSI_CURSOR_HOME);
    strcat(
        message,
        ANSI_ERASE_CURSOR_TO_END);
    strcat(
        message,
        "Time stamps since app start: ");
    strcat(
        message,
        ANSI_BOLD_RED);
    
    uint64_t timestamps_elapsed = app_start_time - tok_time();
    char time_as_str[128];
    time_as_str[0] = '\0';
    
    uint_to_string(
        /* char * recipient: */
            time_as_str,
        /* uint64_t input: */
            timestamps_elapsed);
    
    strcat(
        message,
        time_as_str);
    strcat(
        message,
        ANSI_RESET_STYLES_AND_COLORS);
    
    tok_printf(
        message,
        strlen(message));
}

// entry point of our app, replaces main()
void start() {
    
    app_start_time = tok_time();
    
    for (uint32_t _ = 0; _ < 300000; _++) {
        draw_frame();
    }
    
    tok_printf("\n300000 TUI frames were drawn.", 30);
    
    tok_exit();
}

