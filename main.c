#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logic.h"

int main(int argc, char** argv){
    // "good enough"
    srand(time(NULL));

    // initialize values
    game_values gv = {
        "words.txt",                      // word_bank_fp
        num_valid_words(gv.word_bank_fp), // word_count
    };
    
    while(1){
        gv.num_turns = 0;
        gv.target_buf = get_rand_word(gv.word_bank_fp, gv.word_count);

        do{
            // display
            system("cls");
            for (int i = 0; i < MAX_TURNS; i++){
                if (gv.graded_input_buf[i] != NULL){
                    printf("# ");
                    out_display_word(gv.graded_input_buf[i]);
                }
                else{
                    printf("# \n");
                }
            }
            printf("\n>");

            // input check
            do{
                if (gv.input_buf == NULL){gv.input_buf = (char*) malloc(WORD_BUF_SIZE);}
                fgets(gv.input_buf, WORD_BUF_SIZE, stdin);
                truncate_newline(gv.input_buf);
            }while(check_input(gv.word_bank_fp, gv.input_buf) != 0);

            // grading
            gv.graded_input_buf[gv.num_turns] = grade_word(gv.input_buf, gv.target_buf);
            out_display_word(gv.graded_input_buf[gv.num_turns]);

            // win condition
            if (check_for_win(gv.graded_input_buf[gv.num_turns]) == 0){break;}
            gv.num_turns++;
        }while(gv.num_turns < MAX_TURNS);
    }
    

    // all values that may be assigned using malloc()
    free(gv.input_buf);
    free(gv.target_buf);
    free_graded_input_buf(gv.graded_input_buf);
    return 0;
}