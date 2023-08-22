#define uint32_t unsigned int
#define uint64_t unsigned long int

extern void tok_print(char * input, uint32_t input_size);
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
    if (recipient == 0)
    {
        return;
    }
    
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
    uint64_t max_decimal = 1;
    max_decimal <<= 62;
    while (input_div_dec > 0 && decimal < max_decimal) {
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

static uint32_t tok_strlen(char * str) {
    uint32_t return_value = 0;
    while (str[return_value] != '\0') {
        return_value += 1;
    }
    
    return return_value + 1;
}

static void tok_strcat(char * recipient, char * input) {
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

static char message[1024];
static char time_as_str[256];

static void draw_frame() {
    message[0] = '\0';
    
    tok_strcat(
        message,
        ANSI_CURSOR_HOME);
    tok_strcat(
        message,
        ANSI_ERASE_CURSOR_TO_END);
    tok_strcat(
        message,
        "Time stamps since app start: ");
    tok_strcat(
        message,
        ANSI_BOLD_RED);
    
    uint64_t timestamps_elapsed = app_start_time - tok_time();
    time_as_str[0] = '\0';
    uint_to_string(
        /* char * recipient: */
            time_as_str,
        /* uint64_t input: */
            timestamps_elapsed);
    tok_strcat(
        message,
        time_as_str);
    tok_strcat(
        message,
        ANSI_RESET_STYLES_AND_COLORS);
    
    tok_print(
        message,
        tok_strlen(message));
}

// entry point of our app, replaces main()
void _start(void) {
    
    app_start_time = tok_time();
    uint64_t frames_drawn = 0;
    uint64_t max_wait = 1;
    max_wait <<= 34;
    
    while ((tok_time() - app_start_time) < max_wait) {
        draw_frame();
        frames_drawn += 1;
    }
    
    tok_print("\n\n\n", 5);
    
    char frames_as_str[128];
    uint_to_string(
        /* char * recipient: */
            frames_as_str,
        /* uint64_t input: */
            frames_drawn);
    
    tok_print(frames_as_str, tok_strlen(frames_as_str));
    tok_print(
        " TUI frames were drawn.",
        24);
    
    tok_print("\n.....", 6);
    
    tok_exit();
}

