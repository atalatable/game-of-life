#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void printGrid(const int grid[3][3]);
int  getInput();
void game(int players);
int menu();
void botChoice(int *line, int *column, const int grid[3][3]);

void botChoice(int *line, int *column, const int grid[3][3]) {
    // taking the center before everything
    if (grid[1][1] == 0) {
        *line = 2;
        *column = 2;
    }
    else {
        int initLine = *line, initColumn = *column;
        // checking if bot can win
        for(int i = 0; i < 3; i++){
            int lineFor = 0, columnFor = 0;
            for(int j = 0; j < 3; j++){
                lineFor += grid[i][j];
                columnFor += grid[j][i];
                if (lineFor == 2){
                    *line = i+1;
                    for(int k = 1; k < 4; k++){
                        if(grid[(*line)-1][k] == 0){
                            *column = k+1;
                            break;
                        }
                    }
                }
                else if (columnFor == 2){
                    *column = i+1;
                    for(int k = 1; k < 4; k++){
                        if(grid[k][(*column)-1] == 0){
                            *line = k+1;
                            break;
                        }
                    }
                }
            }
        }
        if(grid[0][0] + grid[1][1] + grid[2][2] == 2){
            if(grid[0][0] == 0){
                *line = 1;
                *column = 1;
            }
            else if(grid[1][1] == 0){
                *line = 2;
                *column = 2;
            }
            else {
                *line = 3;
                *column = 3;
            }
        }
        if(grid[2][0] + grid[1][1] + grid[0][2] == 2){
            if(grid[2][0] == 0){
                *line = 3;
                *column = 1;
            }
            else if(grid[1][1] == 0){
                *line = 2;
                *column = 2;
            }
            else {
                *line = 1;
                *column = 3;
            }
        }
        if(*column == initColumn && *line == initLine){
            // checking if the player has a chance to win
            // only if bot cant win
            for(int i = 0; i < 3; i++){
                int lineFor = 0, columnFor = 0;
                for(int j = 0; j < 3; j++){
                    lineFor += grid[i][j];
                    columnFor += grid[j][i];
                    if (lineFor == -2 || columnFor == -2){
                        *line = i+1;
                        *column = j+1;
                    }
                }
            }
            if(grid[0][0] + grid[1][1] + grid[2][2] == -2){
                if(grid[0][0] == 0){
                    *line = 1;
                    *column = 1;
                }
                else if(grid[1][1] == 0){
                    *line = 2;
                    *column = 2;
                }
                else {
                    *line = 3;
                    *column = 3;
                }
            }
            if(grid[2][0] + grid[1][1] + grid[0][2] == -2){
                if(grid[2][0] == 0){
                    *line = 3;
                    *column = 1;
                }
                else if(grid[1][1] == 0){
                    *line = 2;
                    *column = 2;
                }
                else {
                    *line = 1;
                    *column = 3;
                }
            }
        }
        // if neither bot or payer cant win
        // taking the first possible place
        if(*column == initColumn && *line == initLine) {
            for(int i = 0; i<3; i++) {
                for(int j = 0; j < 3; j++) {
                    if(grid[i][j] == 0) {
                        *line = i+1;
                        *column = j+1;
                        break;
                    }
                }
                if(grid[(*line)-1][(*column)-1] != 0){
                    break;
                }
            }
        }
    }
}

int menu() {
    int choice = 0;
    system("cls");
    printf("=== MOPRION ===\n");
    printf("1. Jouer seul\n2. Jouer a deux\n3. Quitter   ");
    while (choice != 1 && choice != 2 && choice != 3){
        scanf("%d", &choice);
    }
    return choice;
}

void printGrid(const int grid[3][3]) {
    system("cls");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == 0){
                printf(".");
            }
            else if (grid[i][j] == 1){
                printf("X");
            }
            else if (grid[i][j] == -1){
                printf("O");
            }
            printf("  ");
        }
        printf("\n");
    }
}

int getInput(char *wordBefore) {
    int saisie = 0;
    do {
        printf("%s", wordBefore);
        scanf("%d", &saisie);
    }while (saisie != 1 && saisie != 2 && saisie != 3);
    return saisie;
}

// returns  0 if game is not finished
// returns  2 if game is full
// returns  1 if X wins
// returns -1 if O wins
int checkGame(int grid[3][3]) {
    //checking for line or column win
    for(int i = 0; i < 3; i++){
        int line = 0, column = 0;
        for(int j = 0; j < 3; j++){
            line += grid[i][j];
            column += grid[j][i];
            if (line == 3 || column == 3){
                return 1;
            }
            if (line == -3 || column == -3){
                return -1;
            }
        }
    }
    // checking for a diagonal win
    if(grid[0][0] + grid[1][1] + grid[2][2] == 3 || grid[2][0] + grid[1][1] + grid[0][2] == -3){
        return 1;
    }
    if(grid[0][0] + grid[1][1] + grid[2][2] == -3 || grid[2][0] + grid[1][1] + grid[0][2] == -3){
        return -1;
    }
    // checking if grid is full
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == 0) {
                return 0;
            }
        }
    }
    return 2;
}

void game(int players) {
    int grid[3][3] = { {0,0,0},
                       {0,0,0},
                       {0,0,0}};
    int turn = 0;
    printGrid(grid);
    int line = 0, column = 0;
    while(1) {
        if (players == 2){
            do {
                printf((turn % 2 == 0) ? "---------------\nTour des O\n" : "---------------\nTour des X\n");
                line = getInput("Ligne : ");
                column = getInput("Colonne : ");
            } while (grid[line-1][column-1] != 0);
        }
        else if(players == 1) {
            if(turn % 2 == 0) {
                do {
                    printf((turn % 2 == 0) ? "---------------\nTour des O\n" : "---------------\nTour des X\n");
                    line = getInput("Ligne : ");
                    column = getInput("Colonne : ");
                } while (grid[line-1][column-1] != 0);
            }
            else{
                do {
                    botChoice(&line, &column, grid);
                } while (grid[line-1][column-1] != 0);
            }
        }
        if (turn % 2 == 0){
            grid[line-1][column-1] = -1;
        }
        else {
            grid[line-1][column-1] = 1;
        }
        printGrid(grid);
        if(checkGame(grid) == 1){
            printf("\nLes X ont gagne !\n");
            getch();
            break;
        }
        if(checkGame(grid) == -1){
            printf("\nLes O ont gagne !\n");
            getch();
            break;
        }
        if(checkGame(grid) == 2){
            printf("\nIl y a eu egalite !\n");
            getch();
            break;
        }
        turn += 1;
    }
}

int main(int argc, char *argv[]) {
    int choice = 0;
    while (choice != 3) {
        choice = menu();
        if(choice != 3){
            game(choice);
        }
    }
    return 0;
}