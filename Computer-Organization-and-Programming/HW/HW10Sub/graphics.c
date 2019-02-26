#include "graphics.h"
#include "gba.h"

int collision(PLAYER *player, OBJECT *object) {
	int rowA = player->row;
	//int colA = player->col;
	int heightA = player->height;
	//int widthA = player->width;
	
	int rowB = object->row;
	//int colB = object->height;
	int heightB = object->height;
	//int widthB = object->width;

	if(rowA < rowB + heightB && rowA + heightA > rowB) {
		return 1;
	}else {
		return 0;
	}
	// rowA < rowB + heightB - 1 && rowA + heightA - 1 > rowB
	//     && colA < colB + widthB - 1 && colA + widthA - 1 > colB
}
