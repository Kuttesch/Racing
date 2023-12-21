#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIELD_HEIGHT 3
#define FIELD_WIDTH 5

void userinput();  // function declaration
void obstacle();
void printField(char field[FIELD_HEIGHT][FIELD_WIDTH]);
void drawBorders();
int position = 1;

char field[FIELD_HEIGHT][FIELD_WIDTH];
int counter = 0;

int main() {
    system("cls");
    printf("***************************\n");
    printf("*                         *\n");
    printf("*The RACING Game!*\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    usleep(2000 * 1000); // usleep takes microseconds
    system("cls");
    printf("Press any key to start the game!\n");
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[i][j] = ' ';
        }
    }
    userinput();
    return 0;
}

void increaseCounter() {
    for (int j = 0; j < FIELD_WIDTH; j++) {
        if (field[FIELD_HEIGHT - 1][j] == 'X') {
            counter++;
        }
    }
}


void endGame(int pos) {
    if (field[FIELD_HEIGHT - 1][pos - 1] == 'X') {
        printf("Game Over!\nYour Score %d\n", counter);
        exit(0);
    }
}

void userinput() {
    while (1) {
        obstacle();
        increaseCounter();
        char ch = getch();
        switch (ch) {
            case 'a':
                if (position > 1) {
                    position--;
                }
                break;
            case 'd':
                if (position < FIELD_WIDTH) {  // Change 3 to FIELD_WIDTH
                    position++;
                }
                break;
            case 'q':
                printf("Game Over!\nYour Score %d\n", counter);
                return;
        }
        printf("\r                                         \r");
        fflush(stdout);
        // Clear the last position of 'H'
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (field[FIELD_HEIGHT - 1][j] == 'H') {
                field[FIELD_HEIGHT - 1][j] = ' ';
            }
        }
        // Set the new position of 'H'
        endGame(position);
        field[FIELD_HEIGHT - 1][position - 1] = 'H';  // Implement
        system("cls");
        printf("Counter: %d\n", counter);
        printField(field);

    }
}

void obstacle() {
    // Move existing Xs one row down
    for (int i = FIELD_HEIGHT - 1; i > 0; i--) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[i][j] = field[i - 1][j];
        }
    }

    // Generate a new random X in the top row with a 2/3 chance
    int spawnChance = rand() % 3;
    if (spawnChance != 0) {
        int randNum = rand() % FIELD_WIDTH;
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (j == randNum) {
                field[0][j] = 'X';
            } else {
                field[0][j] = ' ';
            }
        }
    } else {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[0][j] = ' ';
        }
    }
}

void drawBorders() {
    for (int i = 0; i < FIELD_WIDTH + 8; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        printf("| ");
        for (int j = 0; j < FIELD_WIDTH; j++) {
            printf("%c ", field[i][j]);
        }
        printf("|\n");
    }
    for (int i = 0; i < FIELD_WIDTH + 8; i++) {
        printf("-");
    }
    printf("\n");
}

void printField(char field[FIELD_HEIGHT][FIELD_WIDTH]) {
    drawBorders();
}