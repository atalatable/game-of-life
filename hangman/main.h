#ifndef DEF_MAIN
#define DEF_MAIN

#define TAILLE_MAX 50

int menu();
void addWordToArray(int *count, char *word);
void initGame();
int addWord();
int listWords(int loadInMemory);
void chooseGameLevel();
void gameMain();
void dessinPendu();
void gotoLigCol(int lig, int col);

#endif