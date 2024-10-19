#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

int num_valid_words(const char *file_path){
    // open file
    FILE *bank = fopen(file_path, "r");
    if (bank == NULL){
        fclose(bank);
        return 0;
    }
    
    // read from file
    int count = 0;
    char word[WORD_BUF_SIZE];
    while(fgets(word, WORD_BUF_SIZE, bank)){
        count++;
    }

    fclose(bank);
    return count;
}

char *get_rand_word(const char *file_path, const int word_count){
    // open file
    FILE *bank = fopen(file_path, "r");
    if (bank == NULL){
        fclose(bank);
        return NULL;
    }

    // this sucks
    int index = rand() % (word_count + 1); // rand() % (max_number + 1 - minimum_number) + minimum_number

    // read from file until desired word is reached
    int count = 0;
    char *word = malloc(WORD_BUF_SIZE);
    do{
        fgets(word, WORD_BUF_SIZE, bank);
        count++;
    }while (count != index);

    truncate_newline(word);
    
    fclose(bank);
    return word;
}

int check_input(const char* file_path, const char* input){
    // escape if letter count != 5
    int len = strlen(input);
    if (len != WORD_LENGTH){
        return 1;
    }

    // read from file
    FILE *bank = fopen(file_path, "r");
    if (bank == NULL){
        fclose(bank);
        return 1;
    }

    char word[WORD_BUF_SIZE];
    while (fgets(word, WORD_BUF_SIZE, bank)){
        truncate_newline(word);

        // valid input detected
        if (strncmp(word, input, WORD_BUF_SIZE) == 0){
            fclose(bank);
            return 0;
        }
    }

    // if function reaches this point, word does not exist in bank
    fclose(bank);
    return 1;
}

void out_display_word(graded_letter *word){
    for (int i = 0; i < WORD_LENGTH; i++){
        switch(word[i].grade){
            // CL_CP
            case 0:
                printf(GRN "%c" RESET, word[i].value);
                break;
            // CL_IP
            case 1:
                printf(YEL "%c" RESET, word[i].value);
                break;
            // IL
            case 2:
                printf(RED "%c" RESET, word[i].value);
                break;
            // this should never happen
            default:
                printf("%c", word[i].value);
                break;
        }
    }
    printf("\n");
    return;
}

void truncate_newline(char *word){
    if (word == NULL){return;}

    int len = strlen(word);
    if (len == 0){return;}

    if (strncmp(&word[len-1], "\n", 1) != 0){return;}

    strncpy(word, strtok(word, "\n"), WORD_BUF_SIZE);
}

graded_letter* grade_word(char *input, char *target){
    graded_letter *word = (graded_letter*) malloc(sizeof(graded_letter) * WORD_BUF_SIZE);

    // compare each letter in input to each letter in target
    int comparison_result;
    for (int i = 0; i < WORD_LENGTH; i++){
        // default value to assign
        graded_letter letter = {input[i], IL};

        for (int j = 0; j < WORD_LENGTH; j++){
            // loop until match is found
            comparison_result = strncmp(&input[i], &target[j], 1);
            if (comparison_result != 0){continue;}

            // grading
            if (i == j){letter.grade = CL_CP;}
            else{letter.grade = CL_IP;}
        }

        word[i] = letter;
    }

    return word;
}

int check_for_win(graded_letter* word){
    for (int i = 0; i < WORD_LENGTH; i++){
        if (word[i].grade == 0){continue;}
        // if loop reaches this point, word does not match
        return 1;
    }
    // word matches, game won
    return 0;
}

void free_graded_input_buf(graded_letter** ptr){
    int index = 0;
    do{
        free(ptr[index]);
        index++;
    }while(*ptr != NULL || index == MAX_TURNS);
}