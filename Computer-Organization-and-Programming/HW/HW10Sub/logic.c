#include "logic.h"
#include <stdlib.h>
#include "gba.h"
#include "graphics.h"
#include "images/openMan.h"
#include "images/closedMan.h"
#include "images/fireball.h"
#include "images/arrow.h"

//mods
int score;
int lives;
int mo;
int rando;
int lifeCol;
int rand_13;

//this file handles all my actual game coding
PLAYER p1;
PLAYER p2;
PLAYER p3;

SELECTOR select;
PLAYER *currPlayer;

OBJECT col1[NUM_OB1];
OBJECT col2[NUM_OB1];
OBJECT col3[NUM_OB1];

//sets up all the values for every object in the game
void initgame(void) {
    lives = 5;
    score = 0;
    rando = randint(0,50);
    mo = 0;
    lifeCol = 57;
    initPlayers();
    initSelector();
    initObjects();
    *currPlayer = p1;
}
//draws the game
void drawGame(void) {
    drawPlayers();
    drawSelector();
    for(int i = 0;i < NUM_OB1; i++) {
        drawObj(&col1[i]);
        drawObj(&col2[i]);
        drawObj(&col3[i]);
    }
}
//this updates the game to its next stage
void updategame(unsigned short buttons, unsigned short oldButtons) {
    updateSelector(buttons, oldButtons);
    updatePlayer(buttons, oldButtons);
    for(int i = 0;i < NUM_OB1; i++) {
        updateObj1(&col1[i]);
        updateObj2(&col2[i]);
        updateObj3(&col3[i]);
    }
    updateLevel();
}

void initObjects(void){
    for(int i = 0; i < NUM_OB1; i++) {
        col1[i].row = -20;
        col1[i].col = 38;
        col1[i].oldRow = col1[i].row;
        col1[i].rdel = 1;
        col1[i].height = 17;
        col1[i].width = 15;
        col1[i].morality = 0;
        col1[i].active = 0;

        col2[i].row = -20;
        col2[i].col = 108;
        col2[i].oldRow = col2[i].row;
        col2[i].rdel = 1;
        col2[i].height = 17;
        col2[i].width = 15;
        col2[i].morality = 1;
        col2[i].active = 0;

        col3[i].row = -20;
        col3[i].col = 178;
        col3[i].oldRow = col3[i].row;
        col3[i].rdel = 1;
        col3[i].height = 17;
        col3[i].width = 15;
        col3[i].morality = 0;
        col3[i].active = 0;
    }
}

void reinitObj1(int moral) {
    for (int i = 0; i < NUM_OB1; i++) {
        if (!(col1[i].active)) {
            col1[i].row = -20;
            col1[i].morality = moral;
            col1[i].active = 1;
            break;
        }
    }
}
void reinitObj2(int moral) {
    for (int i = 0; i < NUM_OB1; i++) {
        if (!(col2[i].active)) {
            col2[i].row = -20;
            col2[i].morality = moral;
            col2[i].active = 1;
            break;
        }
    }
}
void reinitObj3(int moral) {
    for (int i = 0; i < NUM_OB1; i++) {
        if (!(col3[i].active)) {
            col3[i].row = -20;
            col3[i].morality = moral;
            col3[i].active = 1;
            break;
        }
    }
}

void drawObj(OBJECT *obj) {
    if(obj->active) {
        if(!obj->morality) {
            drawImageDMA(obj->row - 1,obj->col,obj->width,obj->height,fireball);
        }else {
            drawImageDMA(obj->row - 1,obj->col,obj->width,obj->height,arrow);

        }
    }
} 

void updateObj1(OBJECT *obj) {
    if(obj->active) {
        //if(p1.timer%2) {
            obj->row += obj->rdel;
        //} 
        if(collision(&p1, obj)) {
            drawRectDMA(obj->row - 1, obj->col, obj->width, obj->height, LIGHTGRAY);
            obj->active = 0;
            if((&p1)->active){
                if(obj->morality){
                    score++;
                } else {
                    updateLives();
                }
            } else {
                if(obj->morality) {
                    updateLives();
                }else {
                    score++;
                }
            }
        }
    }
}
void updateObj2(OBJECT *obj) {
    if(obj->active) {
        //if(p2.timer%2) {
            obj->row += obj->rdel;
        //} 
        if(collision(&p2, obj)) {
            drawRectDMA(obj->row - 1, obj->col, obj->width, obj->height, LIGHTGRAY);
            obj->active = 0;
            if((&p2)->active){
                if(obj->morality){
                    score++;
                } else {
                    updateLives();
                }
            } else {
                if(obj->morality) {
                    updateLives();
                }else {
                    score++;
                }
            }
        }
    }
}
void updateObj3(OBJECT *obj) {
    if(obj->active) {
        //if(p3.timer%2) {
            obj->row += obj->rdel;
        //} 
        if(collision(&p3, obj)) {
            drawRectDMA(obj->row - 2, obj->col, obj->width, obj->height, LIGHTGRAY);
            obj->active = 0;
            if((&p3)->active){
                if(obj->morality){
                    score++;
                } else {
                    updateLives();
                }
            } else {
                if(obj->morality) {
                    updateLives();
                }else {
                    score++;
                }
            }
        }
    }
}
void initPlayers(void){
    p1.row = 103;
    p1.col = 30;
    p1.height = 43;
    p1.width = 31;
    p1.timer = 0;
    p1.open = openMan;
    p1.closed = closedMan;
    p1.active = 1;

    p2.row = 103;
    p2.col = 100;
    p2.height = 43;
    p2.width = 31;
    p2.timer = 0;
    p2.open = openMan;
    p2.closed = closedMan;
    p2.active = 1;

    p3.row = 103;
    p3.col = 170;
    p3.height = 43;
    p3.width = 31;
    p3.timer = 0;
    p3.open = openMan;
    p3.closed = closedMan;
    p3.active = 1;
}
void initSelector(void) {
    select.row = 146;
    select.col = p1.col - 2;
    select.oldCol = select.col;
    select.height = 1;
    select.width = p1.width + 2;
    select.position = 1;
    select.cdel = (p2.col) - (p1.col + p1.width);
    select.color = ORANGE;
}
void drawPlayers(void) {
    if(p1.active) {
        drawImageDMA(p1.row, p1.col, p1.width, p1.height, openMan);
    } else {
        drawImageDMA(p1.row, p1.col, p1.width, p1.height, closedMan);
    }

    if(p2.active) {
        drawImageDMA(p2.row, p2.col, p2.width, p2.height, openMan);
    } else {
        drawImageDMA(p2.row, p2.col, p2.width, p2.height, closedMan);
    }

    if(p3.active) {
        drawImageDMA(p3.row, p3.col, p3.width, p3.height, openMan);
    } else {
        drawImageDMA(p3.row, p3.col, p3.width, p3.height, closedMan);
    }
}
void drawSelector(void) {
    drawRectDMA(select.row, select.oldCol, select.width, select.height, LIGHTGRAY);
    drawRectDMA(select.row, select.col, select.width, select.height, select.color);
    select.oldCol = select.col;
}
void updateSelector(unsigned short buttons, unsigned short oldButtons) {
    if(KEY_JUST_PRESSED(BUTTON_RIGHT, buttons, oldButtons) 
        && select.position < 3) {
        select.position++;
        select.col = (select.col + select.width) + select.cdel;
    }
    if(KEY_JUST_PRESSED(BUTTON_LEFT, buttons, oldButtons) 
        && select.position > 1) {
        select.position--;
        select.col = (select.col) - (select.cdel + select.width);
    }
}
void updatePlayer(unsigned short buttons, unsigned short oldButtons) {
    if(KEY_JUST_PRESSED(BUTTON_A, buttons, oldButtons)) {
        //score++;
        //updateLives();
        if(select.position == 1) {
            if(p1.active) {
                p1.active = 0;
            }else {
                p1.active = 1;
            }
        } else if(select.position == 2) {
            if(p2.active) {
                p2.active = 0;
            }else {
                p2.active = 1;
            }
        } else {
            if(p3.active) {
                p3.active = 0;
            }else {
                p3.active = 1;
            }
        }
    }
}
void updateLives(void){
    lives--;
    drawRectDMA(150, lifeCol, 13, 10, BLACK);
    lifeCol -= 14;
}
void updateLevel(void) {
    p1.timer++;
    p2.timer++;
    p3.timer++;
    if(score < 10) {
        if ((p1.timer > 120) && (p1.timer % 120 == 0)) {
            rand_13 = randint(1,4);
            if(rand_13 == 1) {
                mo = ((rando+rand_13)%2);
                reinitObj1(mo);
            } else if (rand_13 == 2) {
                mo = ((rando+rand_13)%2);
                reinitObj2(mo);
            }
            else if (rand_13 == 3) {
                mo = ((rando+rand_13)%2);
                reinitObj3(mo);
            }
        }
    }
    if(score >= 10) {
        if(!(p1.timer % (TIMER1))){
            rando = randint(0,10);
            mo = (rando%2);
            reinitObj1(mo);
            //p2.timer = 0;
        } else if(!(p2.timer % (TIMER1+30))){
            rando = randint(0,10);
            mo = (rando%2);
            reinitObj2(mo);
            //p2.timer = 0;
        }
        if(!(p3.timer % (TIMER1*2-20))){
            rando = randint(0,5);
            mo = (rando%2);
            reinitObj3(mo);
            //p3.timer = 0;
        }
    }
    // if(score > 5 && score < 25) {
    //     if(p1.timer >= TIMER1){
    //         mo = (rando%2);
    //         reinitObj1(mo);
    //         p1.timer = 0;
    //     }
    //     if(p2.timer >= TIMER1 + 20){
    //         rando = randint(0,100);
    //         mo = (rando%2);
    //         reinitObj2(mo);
    //         p2.timer = 0;
    //     }
    //     if(p3.timer >= TIMER1 + 50){
    //         rando = randint(0,35);
    //         mo = (rando%2);
    //         reinitObj3(mo);
    //         p3.timer = 0;
    //     }
    // }
}