#include <stdio.h>
#include <stdbool.h>

int main() {
    int word_lengths[10]; // max word length is 10
    int c, curr_word_len, i, j;

    bool in_word = false;
    curr_word_len = 0;

    for (i = 0; i < 10; i++) {
        word_lengths[i] = 0;
    }



    // count in input
    while ((c = getchar()) != EOF) {
        // not in word anymore if we were
        if (c == '\n' || c == ' ' || c == '\t')  {
            if (in_word) {
                in_word = false;

                // only 10 slots so...
                if (curr_word_len < 10) {
                    word_lengths[curr_word_len]++;
                }

                curr_word_len = 0;
            }
        } else {
            in_word = true;
            curr_word_len++;
        }
    }


    // print histogram
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < word_lengths[i]; j++) {
            printf("█");
        }
        printf("\n");
    }

}
