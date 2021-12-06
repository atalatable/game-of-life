#include <stdio.h>
#include <string.h>
#include <windows.h>

#define WIDTH 30
#define HEIGHT 9

/*******PROTOTYPES DES FONCTIONS **********/

/* Initialise la grille de façon à ce qu’elle contienne ce qu’il y a à la figure de droite */
void init_grille (char grille[HEIGHT][WIDTH], int pos_balle_x, int pos_balle_y);

/* Affiche le rectangle d’étoiles et la balle (tout ceci en même temps et non pas le rectangle puis la balle...) */
void affiche_grille (char grille[HEIGHT][WIDTH]);

/*10 lignes 10 colonnes*/
/* Calcule la nouvelle position de la balle en fonction de l’ancienne position de la balle (old_pos_balle_x, old_pos_balle_y)
   et du vecteur de déplacement (deplacement_x, deplacement_y). */
void calcule_position_balle (char grille[HEIGHT][WIDTH], int *pos_balle_x, int *pos_balle_y, int *deplacement_x, int * deplacement_y);


/************* IMPLEMENTATION DES FONCTIONS ****************/

void init_grille (char grille[HEIGHT][WIDTH], int pos_balle_x,int pos_balle_y) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grille[i][j] = ' ';
        }
    }
    for(int i = 0; i < HEIGHT; i++) {
        grille[i][0] = '*';
        grille[i][WIDTH-1] = '*';
    }
    for(int i = 0; i < WIDTH; i++) {
        grille[0][i] = '*';
        grille[HEIGHT-1][i] = '*';
    }
    grille[pos_balle_x][pos_balle_y] = 'O';
}

void affiche_grille (char grille[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", grille[i][j]);
        }
        printf("\n");
    }
}

void calcule_position_balle (char grille[HEIGHT][WIDTH], int *pos_balle_x, int *pos_balle_y, int *deplacement_x, int * deplacement_y) {
    if (grille[*pos_balle_x + *deplacement_x][*pos_balle_y + *deplacement_y] == '*') {
        if (grille[*pos_balle_x + *deplacement_x][*pos_balle_y] == '*') {
            *deplacement_x = -*deplacement_x;
        }
        if (grille[*pos_balle_x][*pos_balle_y + *deplacement_y] == '*') {
            *deplacement_y = -*deplacement_y;
        }
    }
    grille[*pos_balle_x][*pos_balle_y] = ' ';
    grille[*pos_balle_x + *deplacement_x][*pos_balle_y + *deplacement_y] = 'O';
    *pos_balle_x += *deplacement_x;
    *pos_balle_y += *deplacement_y;
}

int main () {
    int pos_balle_x = 1, pos_balle_y = 1;                  /* position balle au départ */
    int deplacement_x = 1, deplacement_y = 1;               /* déplacement balle */
    char grille[HEIGHT][WIDTH];                             /* grille qui contiendra 3 caractères : */
                                                            /* ’*’ ou ’O’ ou le caractère espace ’ ’*/
    init_grille (grille, pos_balle_x, pos_balle_y) ;
    
    while (1) {
        system("cls");
        affiche_grille(grille);
        calcule_position_balle (grille, &pos_balle_x, &pos_balle_y, &deplacement_x, &deplacement_y);
        Sleep(50);
    }
}
