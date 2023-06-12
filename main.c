#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
//Определяем константы для максимального количества слов, максимальной длины слова и размера страницы
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 1000


void printText(char words[MAX_WORDS][MAX_WORD_LENGTH], int remainingWords) { //Функция для печати текста
    for (int i = 0; i < remainingWords; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
}

void setConsoleTextColor(int color) { //Определяем функцию для изменения цвета текста в консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Задаём атрибуты для шрифта консоли, чтобы ее покрасить
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Напечатайте текст как можно быстрее\n");
    printf("Нажмите Enter, чтобы начать...\n");
    getchar();

    FILE* file = fopen("C:\\Users\\dzhik\\CLionProjects\\rk1\\text.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    char words[MAX_WORDS][MAX_WORD_LENGTH]; //Создаем массив для слов и считываем текст из файла в массив
    int totalWords = 0;
    while (totalWords < MAX_WORDS && fgets(words[totalWords], MAX_WORD_LENGTH, file) != NULL) {
        // Удаляем символ новой строки из считанного слова
        words[totalWords][strcspn(words[totalWords], "\n")] = '\0'; //Если символов дальше нет, то конец строки
        totalWords++;
    }

    fclose(file);

    printf("\nТекст:\n");
    printText(words, totalWords);

    int totalChars = 0; //счетчик введенных символов
    int totalWordsTyped = 0; // счетчик всех написанных слов
    int totalWordsCorrect = 0; // счетчик правильных слов
    int currentCharIndex = 0; // индекс текущего введенного символа
    int numCorrectChars = 0; // Добавлено статистики по количеству правильно введённых символов

    clock_t startTime = clock(); // Засекаем время начала игры

    printf("%s: ", words[totalWordsTyped]);
    char userInput[MAX_WORD_LENGTH];
    char currentChar;

    do {
        currentChar = getch();// вводится символ
        totalChars++; // Увеличиваем общее количество введённых символов
        if (currentChar == words[totalWordsTyped][currentCharIndex]) {
            setConsoleTextColor(10); // Зеленый цвет
            printf("%c", currentChar);
            setConsoleTextColor(15); // Возвращаем белый цвет
            currentCharIndex++;
            numCorrectChars++; // Увеличиваем количество правильно введённых символов
        }
        else {
            setConsoleTextColor(12); // Красный цвет
            printf("%c", currentChar);
            setConsoleTextColor(15); // Возвращаем белый цвет
            currentCharIndex++;
        }

        if (currentCharIndex == strlen(words[totalWordsTyped])) {
            printf("\n");
            if (strcmp(userInput, words[totalWordsTyped]) == 0) { // Если строки равны, то увеличиваем кол-во правильных
                totalWordsCorrect++;
            }
            totalWordsTyped++;
            currentCharIndex = 0;
            if (totalWordsTyped < totalWords) {
                printf("%s: ", words[totalWordsTyped]);
            }
        }

    } while (totalWordsTyped < totalWords);

    clock_t endTime = clock(); // Засекаем время окончания игры

    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double speed = (double)totalWords / totalTime * 60;
    double accuracy = (double)numCorrectChars / totalChars * 100; // Вычисляем точность ввода символов


    printf("\n\nИгра окончена!\n");
    printf("Общее время: %.2f сек\n", totalTime);
    printf("Скорость: %.2f слов/мин\n", speed);
    printf("Точность ввода символов: %.2f %%\n", accuracy);
    printf("Общее количество введённых символов: %d\n", totalChars);

    return 0;
}