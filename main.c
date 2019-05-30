#include <stdlib.h>
#include "utils.h"
#include "utils.h"

struct player{
	int (*functionPtr)(int,int);
};


int (*functionPtr)(int,int);


int addInt(int n, int m) {
    return n+m;
}



int main(){
	struct player pl;
	coordinate crd;
	pl.functionPtr = &addInt;
	functionPtr = &addInt;
	
	int sum = (*pl.functionPtr)(2, 3); // sum == 5
    printf("%d\n", sum);
}
