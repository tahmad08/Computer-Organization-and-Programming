#include "gba.h"
#include "logic.h"
#include "graphics.h"
#include "images/background.h"

#include <stdio.h>
#include <stdlib.h>

void init(void);

// State Prototypes
void start(void);
void game(void);
void win(void);
void lose(void);
void instr(void);
void pause(void);
void goToStart(void);
void goToInstr(void);
void goToGame(void);
void goToWin(void);
void goToLose(void);
void goToPause(void);

// Button Variables
unsigned short buttons;
unsigned short oldButtons;

enum {START, INSTR, GAME, PAUSE, WIN, LOSE};
int state;

//characters
char buffer[41];

int main(void) {
    init();

    while(1) {
        // Load the current state of the buttons
        oldButtons = buttons;
        buttons = BUTTONS;
        // State Machine
        switch (state) {
            case START:
                start();
                break;
            case INSTR:
                instr();
                break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
        }
    }
}
void init(void) {
    buttons = BUTTONS;
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    goToStart();
}

// Sets up the start state
void goToStart(void) {
    //Waits for vertical blank and flips the page
    fillScreenDMA(LIGHTGRAY);

    state = START;
}
void start(void) {
    if(KEY_JUST_PRESSED(BUTTON_START, buttons, oldButtons)){
        goToGame();
    }
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        goToInstr();
    }
}

void goToInstr(void){
    fillScreenDMA(GRAY);

    state = INSTR;

}
void instr(void){
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        goToStart();
    }
}


void goToGame(void){
    drawFullScreenImageDMA(background);

    state = GAME;
    initgame();

}

void game(void){
    updategame(buttons, oldButtons);
    //put score in
    sprintf(buffer, "Score: %d", score);
    waitForVBlank();
    drawGame();

    //GGGGGGGOOOOOOOOOOOOOOOOOOOOAAAAAAAAAAAAAAAALLLLLLLLLLLLLLLLL
    drawRectDMA(150,151,70,8,BLACK);
    drawString(150, 151, buffer, WHITE);


    if(KEY_JUST_PRESSED(BUTTON_START, buttons, oldButtons)){
        goToPause();
    }
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        main();
    }
    if(lives <= 0) {
        goToLose();
    }

}

void goToPause(void) {
    fillScreenDMA(YELLOW);

    state = PAUSE;
}
void pause(void) {
    waitForVBlank();
    if(KEY_JUST_PRESSED(BUTTON_START, buttons, oldButtons)){
        goToGame();
    }
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        main();
    }

}
void goToWin(void){
    fillScreenDMA(GREEN);

    state = WIN;

}
void win(void){
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        main();
    }
}

void goToLose(void){
    fillScreenDMA(RED);
    state = LOSE;

}
void lose(void){
    if(KEY_JUST_PRESSED(BUTTON_SELECT, buttons, oldButtons)) {
        main();
    }
}

