#include "platform.h"

#ifndef NULL
#define NULL 0
#endif

static void uint_to_string(
    char * recipient,
    uint64_t input)
{
    if (recipient == 0)
    {
        return; // input string is NULL
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
    
    // if we started with an input of -32, we
    // should now have
    // the resut '-' '2' '3', with start_i at '2' and
    // end_i at '3'
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

// entry point of our app, replaces main()
void _start(void) {
    
    tok_print("app start\n", 10);
    
    uint64_t app_start_time = tok_time();
     
    long heap_memory_size = 100;
    
    int * new_ptr = NULL;
    new_ptr = (int *)tok_malloc(
        /* size_t length : */
            heap_memory_size * sizeof(int));
    
    for (uint32_t i = 0; i < heap_memory_size; i++) {
        new_ptr[i] = i;
    }
    
    uint64_t app_runtime = tok_time() - app_start_time;
    tok_print("app ran for: ", 14);
    char app_runtime_str[512];
    app_runtime_str[0] = '0';
    app_runtime_str[1] = '\n';
    uint_to_string(
        /* char * recipient: */
            app_runtime_str,
        /* uint64_t input: */
            app_runtime);
    tok_print(
        app_runtime_str,
        tok_strlen(app_runtime_str));
    tok_print(" rdtsc cycles\n", 14);
    
    tok_exit();
}

