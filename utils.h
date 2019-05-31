#include <strings.h>
#ifndef UTILS_H

#define SHIP_NUMBERS 2
#define SHIP_SPACE '#'
#define FREE_SPACE '_'
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
	char name[20];
	
	void (* add_ship)(char, int, int, char*, shgameboard*, ship* shp);
}typedef player;

struct game{
	player* players[2];
	int board_x;
	int board_y;
	void (* new_player)(char*, player*, struct game*, coordinate**, coordinate**, shgameboard*, fgameboard*);
	void (* new_shgameboard)(shgameboard*, int, int, coordinate**);
	void (* new_fgameboard)(fgameboard*, int, int, coordinate**);
	void (* new_coordinate)(coordinate*, int, int, char);
	void (* attack)(int ,int, player*, player**);
	void ( * print_game)(struct game*, player*);
}typedef game;



void set_char_for_coordinate(int, int, char, coordinate**, int);


void add_ship(char, int, int, char*, shgameboard*, ship* shp);
void attack(int, int, player*, player**);


void new_player(char* name, player*, game*, coordinate**, coordinate**, shgameboard*, fgameboard*);
void new_shgameboard(shgameboard* board, int, int, coordinate**);
void new_fgameboard(fgameboard* board, int, int, coordinate**);
void new_coordinate(coordinate* crd, int, int, char);

void new_game(game *, player*, player*, int, int);

void print_game(game* g, player*);


#define UTILS_H
#endif
