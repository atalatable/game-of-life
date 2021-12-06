#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

#include "main.h"

char *wordDictionnary[100];
int lengthDictionnary = 0;
int gameLvl = 5;

int main(){
    int choice = 0;

    while(choice != 5){
        initGame();
        listWords(1);
        choice = menu();
        switch (choice){
        case 1:
            system("cls");
            gameMain();
            break;
        case 2:
            addWord();
            break;
        case 3:
            system("cls");
            listWords(0);
            break;
        case 4:
            system("cls");
            chooseGameLevel();
            break;
        default:
            break;
        }   
    }

    return 0; 
}

void gotoLigCol(int lig, int col){
    COORD mycoord;
    mycoord.Y = lig;
    mycoord.X = col;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void gameMain(){
    int i = 0, count = 0, level = gameLvl, k = 0;
    char word[TAILLE_MAX] = "\0";
    char choice = '0';
    srand(time(NULL));

    count = (rand() % (lengthDictionnary));
    for(i=0; i<strlen(wordDictionnary[count]); i++){
        word[i] = '*';
    }
    while(strcmp(word, wordDictionnary[count]) != 0 && level != 0){
        printf("\nmot mystere : %s\n", word);
        printf("il vous reste %d coups\n", level);
        printf("Quelle lettre voulez vous essayer : ");
        while(choice < 'a' || choice > 'z'){
            scanf("%c", &choice);
        }
        choice = toupper(choice);
        for(i=0; i<strlen(word); i++){
            if(choice == (wordDictionnary[count])[i]){
                word[i] = (wordDictionnary[count])[i];
                k++;
            }
        }
        choice = '0';
        if(k == 0){
            level--;
        }
        k=0;
    }
    if(level == 0){
        printf("\nVous avez perdu, le mot etait %s", wordDictionnary[count]);
    }
    else{
        printf("\nvous avez gagne le mot etait %s", word);
    }
    printf("\nAppuyez sur une touche pour revenir au menu");
    choice = getch();
}

int menu(){
    char choice = '0';
    int returnChoice = 0;
    
    system("cls");
    printf("========PENDU========\n");
    printf("1. Jouer\n2. Ajouter un mot\n3. Afficher la liste des mots\n4. Choisir son niveau (actuel = %d)\n5. Quitter\n", gameLvl);
    do{
        choice = getch();
    }while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5');
    returnChoice = (int) choice - (int) '0';
    
    return returnChoice;
} 

void addWordToArray(int *count, char *word){
    word[strlen(word) - 1] = '\0';
    wordDictionnary[*count - 1] = malloc(strlen(word) * sizeof(char));
    if(wordDictionnary[*count - 1] == NULL){
        printf("FATAL - failed allocating wordDictionnary");
        exit(1);
    }
    strcpy(wordDictionnary[*count - 1], word);
    lengthDictionnary++;
}

void initGame(){
    FILE *sources = NULL;
    int i = 0;
    
    sources = fopen("sources.txt", "a");
    if(sources == NULL){
        printf("FATAL - fail oppening sources.txt in initGame");
        exit(1);
    }
    fclose(sources);

    lengthDictionnary = 0;

    for(i=0; i<100; i++){
        wordDictionnary[i] = "\0";
    }
}

int addWord(){
    FILE *sources = NULL;
    char word[TAILLE_MAX] = "";
    int i = 0;

    if(lengthDictionnary == 100){
        printf("WARNING - La liste de mot est pleine\n");
        return 1;
    }
    sources = fopen("sources.txt", "a");
    if(sources == NULL){
        printf("WARNING - fail oppening sources.txt in addWord\n");
        return 1;
    }
    printf("\nTapez le mot que vous voulez ajouter a la liste : ");
    scanf_s("%s", &word);
    for(i=0; word[i] != '\0'; i++)
        word[i] = toupper(word[i]);
    
    for(i=0; i<lengthDictionnary; i++){
        if(strcmp(word, wordDictionnary[i]) == 0){
            printf("WARNING - le mot est deja dans la liste\n");
            return 1;
        }
    }
    word[strlen(word)] = '\n';
    addWordToArray(&lengthDictionnary, word);
    fprintf(sources, "%s\n", word);
    fclose(sources);
    return 0;
}

void chooseGameLevel(){
    printf("=CHOIX DU NIVEAU=");
    printf("\nTapez le nombre de coups que vous voulez : ");
    scanf_s("%d", &gameLvl);
}

int listWords(int loadInMemory){
    FILE *sources = NULL;
    int count = 1, lines = 0;
    char car = '0';
    char word[TAILLE_MAX] = "\0";

    //system("cls");
    sources = fopen("sources.txt", "r");
    if(sources == NULL){
        printf("WARNING - impossible d'afficher la liste de mots\n");
        return 1;
    }
    while(fgets(word, TAILLE_MAX, sources) != NULL){
        if(loadInMemory == 0){
            printf("mot %d : %s", count, word);
        }
        else if(loadInMemory == 1){
            addWordToArray(&count, word);
        }
        count++;
    }
    if(count == 1 && loadInMemory == 0){
        printf("la liste des mot est vide");
    }
    if(loadInMemory == 0){
        printf("\nAppuyez sur une touche pour revenir au menu");
        getch();
    }
    fclose(sources);
    return 0;
}