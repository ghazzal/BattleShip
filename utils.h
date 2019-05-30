#include <strings.h>
#ifndef UTILS_H


#define SHIP_SPACE '#'
#define FREE_SPACE ' '
#define UNKNOWN_SPACE '?'
#define ATTACKED_SHIP_SPACE '*'

struct {
	int x;
	int y;
	char character;
} typedef coordinate;

struct{
	int type;
	int is_alive;
	coordinate** crds;
	int crds_length;
} typedef ship;

struct{
	coordinate** crds;
	int crds_length;
	ship** ships;
	int ships_length;
	
	void (* set_char_for_coordinate)(int, int, char, coordinate**, int);
}typedef shgameboard;

struct {
	coordinate** crds;
	int crds_length;
		
	void (* set_char_for_coordinate)(int, int, char, coordinate**, int);
}typedef fgameboard;

struct {
	fgameboard* fgb;
	shgameboard* shgb;
	char* name;
	
	void (* add_ship)(char, int, int, char*, shgameboard*);
}typedef player;

struct game{
	player* players[2];
	int board_x;
	int board_y;
	void (* new_player)(char*, player*, struct game*, coordinate**, coordinate**);
	void (* new_ship)(int, int, int, char*);
	void (* new_shgameboard)(shgameboard*, int, int, coordinate**);
	void (* new_fgameboard)(fgameboard*, int, int, coordinate**);
	void (* new_coordinate)(int, int, char);
	void (* attack)(int ,int, player*, player**);
}typedef game;



void set_char_for_coordinate(int, int, char, coordinate**, int);


void add_ship(char, int, int, char*, shgameboard*, ship* shp);
void attack(int, int, player*, player**);


void new_player(char* name, player*, game*, coordinate**, coordinate**);
void new_shgameboard(shgameboard* board, int, int, coordinate**);
void new_fgameboard(fgameboard* board, int, int, coordinate**);
void new_coordinate(coordinate* crd, int, int, char);

#define UTILS_H
#endif
