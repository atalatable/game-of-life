/***************************************/
/*             JEU DE LA VIE           */
/***************************************/

/***************************************/
/*             COMPILATION             */
/***************************************/

/* ~ gcc gameOfLife.c -o gameOfLife -Wall*/
/* ~ ./gameofLife.exe                    */

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define TAILLE_SOUS_MATRICE 20
#define TAILLE_SUR_MATRICE 22             /* Taille de la matrice contenant les cellules + 2 pour la bordure */

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_SUPPR 83
#define KEY_ENTER 13

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"

/****************************************/
/********* P R O T O T Y P E S **********/
/****************************************/

/* Initialisation de la matrice de départ */
void init(int matrice [TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]);

/* Indique pour la cellule de coordonnées (ligne,colonne) */
/* le nombre de cellules voisines vivantes                */
int nombre_voisins(int matrice [TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE], int ligne, int colonne);

/* Réalise une étape de plus dans la mise à jour de la matrice: */
/* autrement dit, on réalise un cycle de vie                    */
void mise_a_jour(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]);

/* Affichage de la matrice en cours */
void affiche_matrice(int matrice [TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]);

/* Menu */
char menu();

/* permettant de placer le curseur sur le terminal */
void gotoLigCol(int ligne, int colonne);

/* 2. du menu */
void customize_grid(int matrice [TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]);

/****************************************/
/********* F O N C T I O N S ************/
/****************************************/

int main(int argv, char *argc[]){
    int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE];
    init(matrice);
    char menuChoice = '0';

    while(menuChoice != '3' && menuChoice != KEY_ESC) {

        menuChoice = menu();

        if(menuChoice == '1') {
            int nbr_cycles = 0;
            system("cls");
            printf("%sSur combien de generation lancer la vie : %s", KBLU, KRED);
            while(nbr_cycles <= 0) {
                scanf("%d", &nbr_cycles);
            }

            for(int i = 1; i <= nbr_cycles; i++) {
                affiche_matrice(matrice);
                printf("%s\nGeneration : %s%d",KBLU, KRED, i);
                Sleep(300);
                mise_a_jour(matrice);
            }
            printf("\n\n%sAppuyez sur une touche pour revenir au menu", KMAG);
            getch();
        }
        if (menuChoice == '2') {
            customize_grid(matrice);
        }
    }

    return 0;
}

char menu() {
    char choice = '0';
    system("cls");
    printf("%s===== JEU DE LA VIE =====\n", KRED);
    printf("%s1. Lancer le jeu\n", KBLU);
    printf("%s2. Personaliser la grille\n", KBLU);
    printf("%s3. Quitter               %s", KBLU, KNRM);
    while (choice != '1' && choice != '2' && choice != '3' && choice != KEY_ESC) {
        choice = getch();
    }
    return choice;
}

int nombre_voisins(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE], int ligne, int colonne){
    int nombre = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(i < TAILLE_SUR_MATRICE-1 && j < TAILLE_SUR_MATRICE-1)
                nombre += matrice[ligne+i][colonne+j];
        }
    }
    nombre -= matrice[ligne][colonne];
    return nombre;
}

void init(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]){
    for(int i = 0; i < TAILLE_SUR_MATRICE; i++){
        for(int j = 0; j < TAILLE_SUR_MATRICE; j++){
            matrice[i][j] = 0;
        }
    }
}

void mise_a_jour(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]){
    int matrice_densite[TAILLE_SOUS_MATRICE][TAILLE_SOUS_MATRICE];

    for(int i = 1; i<TAILLE_SOUS_MATRICE+1; i++) {
        for(int j = 1; j<TAILLE_SOUS_MATRICE+1; j++) {
            matrice_densite[i-1][j-1] = nombre_voisins(matrice, i, j);
        }
    }
    for(int i = 1; i<TAILLE_SOUS_MATRICE+1; i++) {
        for(int j = 1; j<TAILLE_SOUS_MATRICE+1; j++) {
            if(matrice_densite[i-1][j-1] < 2 || matrice_densite[i-1][j-1] > 3){
                matrice[i][j] = 0;
            }
            if(matrice_densite[i-1][j-1] == 3){
                matrice[i][j] = 1;
            }
        }
    }
}

void affiche_matrice(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]){
    system("cls");
    for(int i = 0; i < TAILLE_SUR_MATRICE; i++){
        for(int j = 0; j < TAILLE_SUR_MATRICE; j++){
            if((i != 0 && i != TAILLE_SUR_MATRICE-1) && (j != 0 && j != TAILLE_SUR_MATRICE-1)) {
                if(matrice[i][j] == 1){
                    printf("%s#", KGRN);
                }
                if(matrice[i][j] == 0){
                    printf("%s.", KRED);
                }
            }
            else {
                if((i == 0 && j == 0) || (i == TAILLE_SUR_MATRICE-1 && j == TAILLE_SUR_MATRICE-1) || (i == TAILLE_SUR_MATRICE-1 && j == 0) || (i == 0 && j == TAILLE_SUR_MATRICE-1)) {
                    printf("%s+", KBLU);
                } 
                else if (i == 0 || i == TAILLE_SUR_MATRICE-1) {
                    printf("%s-", KBLU);
                } 
                else if(j == 0 || j == TAILLE_SUR_MATRICE-1) {
                    printf("%s|", KBLU);
                }
            }
            printf(" ");
        }
        printf("\n%s", KNRM);
    }
}

void customize_grid(int matrice[TAILLE_SUR_MATRICE][TAILLE_SUR_MATRICE]) {
    affiche_matrice(matrice);
    printf("%s\nDeplacez vous avec les fleches\nAppuyez sur entree pour changer l'etat d'une case\nAppuyez sur ESC pour revenir au menu", KYEL);
    char choice = '0';
    int i = 2, j = 2;
    while(choice != KEY_ESC) {
        gotoLigCol(i, j*2);
        choice = getch();
        if (choice == KEY_UP && i > 1) {
            i--;
            gotoLigCol(i, j*2);
        }
        else if (choice == KEY_DOWN && i < TAILLE_SOUS_MATRICE) {
            i++;
            gotoLigCol(i, j*2);
        }
        if (choice == KEY_LEFT && j > 1) {
            j -= 1;
            gotoLigCol(i, j*2);
        }
        else if (choice == KEY_RIGHT && j < TAILLE_SOUS_MATRICE) {
            j += 1;
            gotoLigCol(i, j*2);
        }
        if (choice == KEY_ENTER) {
            if (matrice[i][j] == 0) {
                printf("%s#", KGRN);
                matrice[i][j] = 1;
            }
            else {
                printf("%s.", KRED);
                matrice[i][j] = 0;
            }
        }
    }
}

void gotoLigCol(int ligne, int colonne){
    COORD mycoord;
    mycoord.Y = ligne;
    mycoord.X = colonne;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}