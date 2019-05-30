#include <stdlib.h>
#include "utils.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10


int main(){
	int i;
    game g;
//    shgameboard* sh = (shgameboard*)malloc(sizeof(shgameboard));
//    sh->crds = (coordinate**)malloc(sizeof(coordinate*));
//    sh->crds[0] = (coordinate*)malloc(sizeof(coordinate));
//    printf("sss");
//    coordinate** cpp = (coordinate**)malloc(sizeof(coordinate*));
//    cpp[0] = (coordinate*)malloc(sizeof(coordinate)*100);
//    sh.crds= cpp;
	player pl1, pl2;
//    printf("Hm?\n");
    new_game(&g, &pl1, &pl2, BOARD_WIDTH, BOARD_HEIGHT);
    
//	coordinate *shcrds_1 = (coordinate*)malloc(sizeof(coordinate)*BOARD_WIDTH*BOARD_HEIGHT);
//    coordinate *fcrds_1 = (coordinate*)malloc(sizeof(coordinate)*BOARD_WIDTH*BOARD_HEIGHT);
	coordinate *shcrdsp_1[100];
    coordinate *fcrdsp_1[100];
    coordinate shcrds_2[100];
    coordinate shcrds_1[100];
    coordinate fcrds_1[100];
    coordinate fcrds_2[100];
	shgameboard shgb_1;
    fgameboard fgb_1;
	shgameboard shgb_2;
    fgameboard fgb_2;
    coordinate *shcrdsp_2[100];
    coordinate *fcrdsp_2[100];
    char name_1[20];
    char name_2[20];
	for(i = 0 ; i < 100 ; i ++ ){
		shcrdsp_1[i] = &shcrds_1[i];
		shcrdsp_2[i] = &shcrds_2[i];
		fcrdsp_2[i] = &fcrds_2[i];
		fcrdsp_1[i] = &fcrds_1[i];
	}
    
	printf("In aval %p\n", &shcrds_2);
    
	printf("Get player 1 name:\n");
    scanf("%s", name_1);
    scanf("%s", name_2);
    printf("Done\n");
    g.new_player(name_1, &pl1, &g, &fcrdsp_1, &shcrdsp_1, &shgb_1, &fgb_1);
    g.new_player(name_2, &pl2, &g, &fcrdsp_2, &shcrdsp_2, &shgb_2, &fgb_2);
    g.print_game(&g, &pl2);
}


