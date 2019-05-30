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

void get_coordinate(int x, int y, coordinate** crd, shgameboard* board){
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
		get_coordinate(x, y, &sp->crds[i], board);
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
				get_coordinate(x, y, crd, attacker->shgb);
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


void new_player(char* name, player* pl, game* g, coordinate** fcrds, coordinate** shcrds){
	pl->name = name;
	strcpy(pl->name, name);
	shgameboard* shgb;
	g->new_shgameboard(shgb, g->board_x, g->board_y, shcrds);
	fgameboard* fgb;
	g->new_fgameboard(fgb, g->board_x, g->board_y, fcrds);
	pl->shgb = shgb;
	pl->fgb = fgb;
}
void new_shgameboard(shgameboard* shgb, int board_x, int board_y, coordinate** crds){
	int i, j;
	int total=0;
	shgb->crds = crds;
	for(i = 0;i<board_x; i++)
	{
		for(j = 0 ; j < board_y ; j++)
		{
			new_coordinate(shgb->crds[total], i, j, FREE_SPACE);
		}
	}
}
void new_fgameboard(fgameboard* fgb, int board_x, int board_y, coordinate** crds){
	int i, j;
	int total=0;
	fgb->crds = crds;
	for(i = 0;i<board_x; i++)
	{
		for(j = 0 ; j < board_y ; j++)
		{
			new_coordinate(fgb->crds[total], i, j, FREE_SPACE);
		}
	}
}

void new_coordinate(coordinate* crd, int x, int y, char ch){
	crd->x = x;
	crd->y = y;
	crd->character = ch;
}


