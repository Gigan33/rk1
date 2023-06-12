#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
//���������� ��������� ��� ������������� ���������� ����, ������������ ����� ����� � ������� ��������
#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 1000


void printText(char words[MAX_WORDS][MAX_WORD_LENGTH], int remainingWords) { //������� ��� ������ ������
    for (int i = 0; i < remainingWords; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
}

void setConsoleTextColor(int color) { //���������� ������� ��� ��������� ����� ������ � �������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //����� �������� ��� ������ �������, ����� �� ���������
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("����������� ����� ��� ����� �������\n");
    printf("������� Enter, ����� ������...\n");
    getchar();

    FILE* file = fopen("C:\\Users\\dzhik\\CLionProjects\\rk1\\text.txt", "r");
    if (file == NULL) {
        printf("������ �������� �����.\n");
        return 1;
    }

    char words[MAX_WORDS][MAX_WORD_LENGTH]; //������� ������ ��� ���� � ��������� ����� �� ����� � ������
    int totalWords = 0;
    while (totalWords < MAX_WORDS && fgets(words[totalWords], MAX_WORD_LENGTH, file) != NULL) {
        // ������� ������ ����� ������ �� ���������� �����
        words[totalWords][strcspn(words[totalWords], "\n")] = '\0'; //���� �������� ������ ���, �� ����� ������
        totalWords++;
    }

    fclose(file);

    printf("\n�����:\n");
    printText(words, totalWords);

    int totalChars = 0; //������� ��������� ��������
    int totalWordsTyped = 0; // ������� ���� ���������� ����
    int totalWordsCorrect = 0; // ������� ���������� ����
    int currentCharIndex = 0; // ������ �������� ���������� �������
    int numCorrectChars = 0; // ��������� ���������� �� ���������� ��������� �������� ��������

    clock_t startTime = clock(); // �������� ����� ������ ����

    printf("%s: ", words[totalWordsTyped]);
    char userInput[MAX_WORD_LENGTH];
    char currentChar;

    do {
        currentChar = getch();// �������� ������
        totalChars++; // ����������� ����� ���������� �������� ��������
        if (currentChar == words[totalWordsTyped][currentCharIndex]) {
            setConsoleTextColor(10); // ������� ����
            printf("%c", currentChar);
            setConsoleTextColor(15); // ���������� ����� ����
            currentCharIndex++;
            numCorrectChars++; // ����������� ���������� ��������� �������� ��������
        }
        else {
            setConsoleTextColor(12); // ������� ����
            printf("%c", currentChar);
            setConsoleTextColor(15); // ���������� ����� ����
            currentCharIndex++;
        }

        if (currentCharIndex == strlen(words[totalWordsTyped])) {
            printf("\n");
            if (strcmp(userInput, words[totalWordsTyped]) == 0) { // ���� ������ �����, �� ����������� ���-�� ����������
                totalWordsCorrect++;
            }
            totalWordsTyped++;
            currentCharIndex = 0;
            if (totalWordsTyped < totalWords) {
                printf("%s: ", words[totalWordsTyped]);
            }
        }

    } while (totalWordsTyped < totalWords);

    clock_t endTime = clock(); // �������� ����� ��������� ����

    double totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double speed = (double)totalWords / totalTime * 60;
    double accuracy = (double)numCorrectChars / totalChars * 100; // ��������� �������� ����� ��������


    printf("\n\n���� ��������!\n");
    printf("����� �����: %.2f ���\n", totalTime);
    printf("��������: %.2f ����/���\n", speed);
    printf("�������� ����� ��������: %.2f %%\n", accuracy);
    printf("����� ���������� �������� ��������: %d\n", totalChars);

    return 0;
}