#include <stdlib.h>
#include "utils.h"



int main(){
    game g;
    player pl;
    g.new_player = &add_player;
	g.new_player(&pl, "salam");
}
