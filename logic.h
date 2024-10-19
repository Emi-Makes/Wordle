#ifndef LOGIC_H_
#define LOGIC_H_

/* Represents the strlen() of a valid wordle word */
#define WORD_LENGTH 5

/* Represents the byte size of a valid wordle word, including '\0' and '\n' */
#define WORD_BUF_SIZE 8

#define MAX_TURNS 6

/* Represents the escape sequence required to color text in terminal */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

/*
0: Correct Letter, Correct Position
1: Correct Letter, Incorrect Position
2: Incorrect Letter
*/
typedef enum letter_grade{
    CL_CP,
    CL_IP,
    IL
}letter_grade;

/*
Represents a "graded" letter in a string presented to the player.
A letter is graded by standard wordle rules; If letter exists in
the target word, and if the letter is in its correct position.
*/
typedef struct graded_letter{
    char value;
    letter_grade grade;
}graded_letter;

/*
Represents all relevant variables within the game
*/
typedef struct game_values{
    // initialize these on startup
    const char *word_bank_fp;
    const int word_count;

    // buffers
    char *input_buf;
    char *target_buf;
    graded_letter *graded_input_buf[MAX_TURNS];
    
    int num_turns;
}game_values;

/*
Returns the number of words in the given filepath.

NOTE: Function assumes all words in the bank are valid.
Checking word validity in this function is unnecessary
since check_input() ignores all input where strlen(word) != 5.
*/
int num_valid_words(const char *file_path);

/*
Returns a random word in the given filepath as a char*.
Memory is assigned using malloc(), be sure to free(word).

NOTE: Randomness contained in this function is currently 
extremely flawed. Better implementation preferred.
*/
char *get_rand_word(const char *file_path, const int word_count);

/*
Checks if the given input string is a valid wordle word.
Returns 0 when true. Returns 1 if strlen(word) != 5, if
wordbank does not exist, or if word does not exist in bank.
*/
int check_input(const char* file_path, const char* input);

/*
Outputs formatted display string to the terminal.
*/
void out_display_word(graded_letter *word);

/*
Remove '\n' from a given string.
*/
void truncate_newline(char *word);

/*
Grades input word by comparing it to target word.
Returns a graded_letter* assigned using malloc().
*/
graded_letter* grade_word(char *input, char *target);

int check_for_win(graded_letter* word);

void free_graded_input_buf(graded_letter** ptr);

#endif