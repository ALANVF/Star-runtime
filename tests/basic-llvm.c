#include <stdio.h>

#include "../runtime/star.h"

int main(void) {
	star_initStar();
	star_initLLVM();
	
	printf("# of types: %li\n# of categories: %li\n", star_getNumTypes(), star_getNumCategories());

	for(int i = 0; i < star_getNumTypes(); i++) {
		printf("type: %-15s size: %li\n", Type_fromID(i)->name, Type_fromID(i)->size);
	}

	star_deinitStar();
	return 0;
}