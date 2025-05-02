// Name: Uma Lord
// Date: 4/24/25
// Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define MAX_GUESSES 6
#define INPUT_FILE "word.txt"


int str_len(char* str);
bool only_letters(char* str);
void to_lower(char* str);
void prompt_for_guess(int guess_num, char* guess);
bool compare_words(char* guess, char* mystery);
bool is_letter_in_word(char letter, char* word, int skip_index);
void build_result_line1(char* guess, char* mystery, char* line1);
void build_result_line2(char* guess, char* mystery, char* line2);
void show_result(char* guess, char* mystery);

int main() {
    char mystery[WORD_LEN + 1];
    char guess[WORD_LEN + 1];
    int guess_count = 1;

    
    FILE* input = fopen(INPUT_FILE, "r");
    if (input == NULL) {
        printf("Could not open %s, goodbye.\n", INPUT_FILE);
        return 0;
    }
    fscanf(input, "%5s", mystery);
    fclose(input);

    
    while (guess_count <= MAX_GUESSES) {
        prompt_for_guess(guess_count, guess);
        to_lower(guess);
        show_result(guess, mystery);

        if (compare_words(guess, mystery)) {
            printf("%s\n", mystery);
            printf("\tYou won in %d guesses!\n", guess_count);
            printf("\t\tAmazing!\n");
            return 0;
        }

        guess_count++;
    }

    printf("You lost, better luck next time!\n");
    return 0;
}

int str_len(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool only_letters(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || 
              (str[i] >= 'A' && str[i] <= 'Z'))) {
            return false;
        }
    }
    return true;
}

void to_lower(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}

void prompt_for_guess(int guess_num, char* guess) {
    if (guess_num == MAX_GUESSES) {
        printf("FINAL GUESS: ");
    } else {
        printf("GUESS %d! Enter your guess: ", guess_num);
    }

    int length = 0;
    int letters = 0;

    do{
        scanf("%s", guess);
        length = str_len(guess);
        letters = only_letters(guess);

        if (length != WORD_LEN && !letters) {
            printf("Your guess must be 5 letters long.Your guess must contain only letters.\nPlease try again: ");
        } else if (length != WORD_LEN) {
            printf("Your guess must be 5 letters long.\nPlease try again: ");
        }
    } while(length != WORD_LEN || !letters);
}   
       
bool compare_words(char* guess, char* mystery) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] != mystery[i]){
        	return false;
   	 }
    }
    return true;
}

bool is_letter_in_word(char letter, char* word, int skip_index) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (i != skip_index && letter == word[i]){
        	return false;
    }
    return true;
}
}

void build_result_line1(char* guess, char* mystery, char* line1) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == mystery[i]) {
            line1[i] = guess[i] - ('a' - 'A');
        } else {
            line1[i] = guess[i];
        }
    }
    line1[WORD_LEN] = '\0';
}

void build_result_line2(char* guess, char* mystery, char* line2) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == mystery[i]) {
            line2[i] = ' ';
        } else if (is_letter_in_word(guess[i], mystery, i)) {
            line2[i] = '^';
        } else {
            line2[i] = ' ';
        }
    }
    line2[WORD_LEN] = '\0';
}

void show_result(char* guess, char* mystery) {
    char line1[WORD_LEN + 1];
    char line2[WORD_LEN + 1];

    build_result_line1(guess, mystery, line1);
    build_result_line2(guess, mystery, line2);

    printf("================================\n");
    printf("%s\n", line1);
    printf("%s\n", line2);
}

