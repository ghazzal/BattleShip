#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10


void get_ships(player* pl){
    int i;
    for(i = 0 ; i < SHIP_NUMBERS ; i++){
        char line[100];
        scanf("%99[^\n]%*c", line);
        char type, *dir;
        int x, y;
       // printf("%s\n", line);
        sscanf(line, "%c @ (%d,%d) %s", &type, &x, &y, dir);
       // printf("%c @ (%d,%d) %s\n", type, x, y, dir);
        ship* sp = pl->shgb->ships[i];
        
        add_ship(type, x, y, dir, pl->shgb, sp);        
    }
}

int game_not_finished_yet(player* pl){
    int i;
    for ( i = 0 ; i < SHIP_NUMBERS ; i++ )
        if( pl->shgb->ships[i]->is_alive)
            return 1;
    return 0;
}

void do_main_loop(game* g){
    int turn = 1;
    while(game_not_finished_yet(g->players[1 - turn])){
        g->print_game(g, g->players[turn]);
        printf("Player number %d turn.\n", turn);
        printf("Get your target point:\n");
        int x, y;
        scanf("%d %d", &x, &y);
        printf("Ok %d %d\n", x, y);
        g->attack(x, y, g->players[turn], g->players);
        g->print_game(g, g->players[turn]);
        turn = 1 - turn;
    }
    printf("Player number %d win the game.\n", turn);
}



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
    ship sp_1[SHIP_NUMBERS], sp_2[SHIP_NUMBERS];
    char name_1[] = "First";
    char name_2[] = "Second";
    shgb_1.ships = (ship**)malloc(sizeof(ship*)*SHIP_NUMBERS);
    shgb_2.ships = (ship**)malloc(sizeof(ship*)*SHIP_NUMBERS);
    for(i = 0 ; i < 100 ; i ++ ){
    	shcrdsp_1[i] = &shcrds_1[i];
    	shcrdsp_2[i] = &shcrds_2[i];
    	fcrdsp_2[i] = &fcrds_2[i];
    	fcrdsp_1[i] = &fcrds_1[i];
    }
    for ( i = 0 ; i < SHIP_NUMBERS ; i++){
        shgb_1.ships[i] = &sp_1[i];
        shgb_2.ships[i] = &sp_2[i];
    }
/*
B @ (1,2) Up
A @ (3,3) Left
C @ (0,0) Left
A @ (7,7) Right    
*/
    printf("In aval %p\n", &shcrds_2);
    printf("Get player 1 name:\n");
//    scanf("%s", name_1);
//    scanf("%s", name_2);
    printf("Done\n");
    g.new_player(name_1, &pl1, &g, &fcrdsp_1, &shcrdsp_1, &shgb_1, &fgb_1);
    g.new_player(name_2, &pl2, &g, &fcrdsp_2, &shcrdsp_2, &shgb_2, &fgb_2);
    get_ships(&pl1);
    get_ships(&pl2);
    do_main_loop(&g);
//    g.print_game(&g, &pl1);
//    char line[100];
//    for ( i = 0 ; i < SHIP_NUMBERS; i++){
//        scanf("%99[^\n]%*c", line);
//
//        printf("%s\n", line);
//    }

//    g.print_game(&g, &pl2);
}


