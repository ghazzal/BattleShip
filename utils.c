//#include <strings.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "utils.h"

void set_char_for_coordinate(int x, int y, char new_char, coordinate** crds, int crds_length){
	int i;
	for(i = 0 ; i < crds_length ; i++ ){
		if ( crds[i]->x == x && crds[i]->y == y){
			crds[i]->character = new_char;
			break;
		}
	}
}

void get_coordinate_shbg(int x, int y, coordinate** crd, shgameboard* board){
	int i;
	for ( i = 0 ; i < board->crds_length ; i++){
//		printf("Nis %d ? %d %p\n", board->crds_length, i, board->crds[i]);
		if ( x == board->crds[i]->x && y == board->crds[i]->y){
			*crd = board->crds[i];
		}
	}
}


void get_coordinate_fgb(int x, int y, coordinate** crd, fgameboard* board){
	int i;
	for ( i = 0 ; i < board->crds_length ; i++){
		if ( x == board->crds[i]->x && y == board->crds[i]->y){
			*crd = board->crds[i];
		}
	}
}


void add_ship(char type, int x, int y, char* direction, shgameboard* board, ship* sp){
	int x_plus=0, y_plus=0;
	if(strcmp(direction, "Up") == 0){
		y_plus = 1;
	}else if (strcmp(direction, "Down") == 0){
		y_plus = -1;
	}else if (strcmp(direction, "Left") == 0){
		x_plus = 1;
	}else{
		x_plus = -1;
	}
	int length = type - 'A' + 1;
	int i = 0;
//	int* ptr = (int*) malloc(100 * sizeof(int));
	sp->crds = (coordinate**)malloc(sizeof(coordinate*)*length);

	for ( i = 0 ; i < length ; i ++){
		get_coordinate_shbg(x, y, &sp->crds[i], board);
		sp->crds[i]->character = SHIP_SPACE;
		x += x_plus;
		y += y_plus;
	}
	sp->is_alive = 1;
	sp->type = type;
	sp->crds_length = type - 'A' + 1;
}

void attack(int x, int y, player* attacker, player** players){
	player* defenser;
	if(attacker == players[0])
		defenser = players[1];
	else
		defenser = players[0];
	int i = 0 ; 
	int flag = 1;
	ship* shp;
	for (i = 0 ; i < defenser->shgb->ships_length && flag ; i++ ){
		int j = 0 ; 
		shp = defenser->shgb->ships[i];
		for (j = 0 ; j < shp->crds_length ; j++){
			coordinate* crd = shp->crds[j];
			if ( x == crd->x && x == crd->y)
			{
				crd->character = ATTACKED_SHIP_SPACE;
				get_coordinate_fgb(x, y, &crd, attacker->fgb);
				crd->character = ATTACKED_SHIP_SPACE;
				flag = 0;
				break;
			}
		}
	}
	if(!flag){
		for(i = 0 ; i < shp->crds_length ; i++){
			if(shp->crds[i]->character == SHIP_SPACE)
				return;
		}
		shp->is_alive = 0;
	}
}


void new_player(char* name, player* pl, game* g, coordinate** fcrds, coordinate** shcrds, shgameboard* shgb, fgameboard* fgb){
	printf("Creating player %s\n", name);
	pl->name = name;
	strcpy(pl->name, name);
	g->new_shgameboard(shgb, g->board_x, g->board_y, shcrds);
	g->new_fgameboard(fgb, g->board_x, g->board_y, fcrds);
	pl->shgb = shgb;
	pl->fgb = fgb;
	pl->add_ship = &add_ship;
	printf("Player created!\n");
}
void new_shgameboard(shgameboard* shgb, int board_x, int board_y, coordinate** crds){
	int i, j;
	int total=0;
	printf("Creating new shipped game board\n");
	shgb->crds = crds;
	shgb->crds_length = board_x*board_y;
	for(i = 0;i < board_x; i++)
	{
		for(j = 0 ; j < board_y ; j++)
		{
//			printf("in shgameboard creation: %d %d %d\n", i, j, sizeof(crds));
//			printf("this: %p\n", &shgb->crds[total]);
			new_coordinate(shgb->crds[total++], i, j, FREE_SPACE);
//			printf("%d %d %c\n", shgb->crds[0]->x, shgb->crds[0]->y, shgb->crds[0]->character);
		}
	}
	shgb->set_char_for_coordinate = &set_char_for_coordinate;
}
void new_fgameboard(fgameboard* fgb, int board_x, int board_y, coordinate** crds){
	int i, j;
	int total=0;
	fgb->crds_length = board_x*board_y;
	fgb->crds = crds;
	for(i = 0;i<board_x; i++)
	{
		for(j = 0 ; j < board_y ; j++)
		{
			new_coordinate(fgb->crds[total++], i, j, UNKNOWN_SPACE);
		}
	}
	fgb->set_char_for_coordinate = set_char_for_coordinate;
}

void new_coordinate(coordinate* crd, int x, int y, char ch){
	printf("%d %d %c\n", x, y, ch);
	crd->x = x;
	crd->y = y;
	crd->character = ch;
}

void new_game(game* g, player* pl1, player* pl2, int board_x, int board_y){
	g->players[0] = pl1;
	g->players[1] = pl2;
	g->board_x = board_x;
	g->board_y = board_y;
	g->new_player = new_player;
	g->new_coordinate = new_coordinate;
	g->new_fgameboard = new_fgameboard;
	g->new_shgameboard = new_shgameboard;
	g->attack = attack;
	g->print_game = &print_game;
}


void print_game(game* g){
	int i, j;
	printf("Player number one boards:\n");
	printf("Shipped board:\n");
	for(j = 0 ; j < g->board_x ; j++){
		for ( i = 0 ; i < g->board_y ; i++){
			coordinate* tmp;
//			printf("inja %p\n", g->players[0]->shgb);
			get_coordinate_shbg(i, j, &tmp, g->players[0]->shgb);
			printf("%c ", tmp->character);
		}
		printf("\n");
	}
	printf("Foreign board:\n");
	for(j = 0 ; j < g->board_x ; j++){
		for ( i = 0 ; i < g->board_y ; i++){
			coordinate* tmp;
			get_coordinate_fgb(i, j, &tmp, g->players[0]->fgb);
			printf("%c ", tmp->character);
		}
		printf("\n");
	}
}




