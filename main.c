#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#endif

#define MAX_TEXT_SIZE 1000
#define MAX_INPUT_SIZE 100
#define MAX_FILENAME_SIZE 50

int load_text(const char* filename, char* text) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > MAX_TEXT_SIZE - 1) {
        printf("Text file is too large.\n");
        fclose(file);
        return 0;
    }

    size_t bytes_read = fread(text, 1, file_size, file);
    text[bytes_read] = '\0';

    fclose(file);

    return bytes_read;
}

#ifdef _WIN32
char get_input_character() {
    return _getch();
}

int get_elapsed_time() {
    return clock() / CLOCKS_PER_SEC;
}

#endif


void print_help() {
    printf("Usage: <text_file> <time_limit> <max_errors>\n");
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Invalid arguments.\n");
        print_help();
        return 1;
    }

    char* text_file = argv[1];
    int time_limit = atoi(argv[2]);
    int max_errors = atoi(argv[3]);

    char text[MAX_TEXT_SIZE];
    if (!load_text(text_file, text)) {
        return 1;
    }

    printf("Typing Test\n\n");
    printf("Type the following text:\n\n%s\n\n", text);
    printf("Press Enter to start...\n");
    getchar();



    int textLength = strlen(text);
    int currentCharIndex = 0;
    int numMistakes = 0;
    int numLettersTyped = 0;
    int numWordsTyped = 0;
    double startTime = get_elapsed_time();
    double currentTime = startTime;
    double timeElapsed = 0.0;

    printf("%s\n", text);

    while (timeElapsed < time_limit && currentCharIndex < textLength) {
        char input = get_input_character();
        currentTime = get_elapsed_time();
        timeElapsed = currentTime - startTime;

        if (input == '\n') {
            printf("\nText typing test completed.\n");
            break;
        }

        if (input == text[currentCharIndex]) {
            printf("\033[32m%c\033[0m", input); // Подсветка правильного символа зеленым
            currentCharIndex++;
            numLettersTyped++;
        } else {
            printf("\033[31m%c\033[0m", text[currentCharIndex]); // Подсветка неправильного символа красным
            numMistakes++;
            numLettersTyped++;
        }

        if (input == ' ') {
            numWordsTyped++;
        }

        if (numMistakes > max_errors) {
            printf("\nMaximum number of errors exceeded. Game over.\n");
            break;
        }
    }
    printf("\nRight letters: %d\n", numLettersTyped - numMistakes);
    printf("Wrong letters: %d\n", numMistakes);
    printf("Total letters typed: %d\n", numLettersTyped);
    printf("Average typing speed (letters per minute): %.2f\n", (numLettersTyped / timeElapsed) * 60);
    printf("Average typing speed (words per minute): %.2f\n", (numWordsTyped / timeElapsed) * 60);

    printf("\n\nTest completed.\n");

    return 0;
}
