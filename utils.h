#ifndef UTILS_H

#include <strings.h>

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
}typedef shgameboard;

struct {
	coordinate* crds;
}typedef fgameboard;

struct {
	fgameboard* fgb;
	shgameboard* shgb;
	string name;
}typedef player;

struct {
	player* players;
}typedef game;
#define UTILS_H
#endif
