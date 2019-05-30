#include <strings.h>
#ifndef UTILS_H

struct {
	int x;
	int y;
	char character;
} typedef coordinate;

struct{
	int type;
	coordinate* crds;
} typedef ship;

struct{
	coordinate* crds;
	ship* ships;
	
	void (* set_char_for_coordinate)(int, int, char);
}typedef shgameboard;

struct {
	coordinate* crds;
		
	void (* set_char_for_coordinate)(int, int, char);
}typedef fgameboard;

struct {
	fgameboard* fgb;
	shgameboard* shgb;
	char* name;
	
	void (* add_ship)(char, int, int, char*);
	void (* attack)(int ,int);
}typedef player;

struct {
	player* players;
	
	void (* new_player)(player*, char*);
	void (* new_ship)(int, int, int, char*);
	void (* new_shgameboard)(void);
	void (* new_fgameboard)(void);
	void (* new_coordinate)(int, int, char);
}typedef game;

void add_player(player* pl, char* name);

#define UTILS_H
#endif
