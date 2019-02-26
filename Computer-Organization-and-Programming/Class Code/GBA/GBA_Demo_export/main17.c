#include "lib.h"


int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	int deltas[] = { -3, -2, -1, 1, 2, 3 };
	int ndeltas = sizeof(deltas) / sizeof(deltas[0]);
	int colors[] = { RED, BLUE, GREEN, WHITE, CYAN, YELLOW, MAGENTA };
	int ncolors = sizeof(colors) / sizeof(colors[0]);
	unsigned short bgcolor = GRAY;
	int score = 0;
	enum gamestate { GS_INIT, GS_SPLASH, GS_BOUNCE, GS_PAUSE };
	int buttondown[NBUTTONS] = {0};
	int button[NBUTTONS] = {0};

        struct ball {
                int row;
                int col;
                int rd;
                int cd;
                unsigned short color;
        };

	struct state {
		enum gamestate gamestate;
		int size;
		int nballs;
		int initnballs;
		struct ball balls[MAXBALLS];
	} state[2];


	state[0].gamestate = GS_SPLASH;
	state[0].size = 5;
	state[0].nballs = 0;
	state[0].initnballs = 1;
	for (int i = 0; i < MAXBALLS; i++) {
		state[0].balls[i].row = 0;
		state[0].balls[i].col = 80 + i * 2 * state[0].size;
		state[0].balls[i].rd = deltas[rand() % ndeltas];
		state[0].balls[i].cd = deltas[rand() % ndeltas];
		state[0].balls[i].color = colors[i % ncolors];
	}

	// clear the screen to 
	DMA[3].src = &bgcolor;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;

	while(1) { // Game Loop
		// Remember the previous state structure
		state[1] = state[0];	

		// See what's changed and update the current input state
		for (int i = 0; i < NBUTTONS; i++) {
			button[i] = KEY_DOWN_NOW(i) == 0 && buttondown[i];
			buttondown[i] = KEY_DOWN_NOW(i) != 0;
		}

		// Compute the graphics for the current state
		if (state[0].gamestate == GS_BOUNCE) {
			// See if we need to do something with buttons
			if (button[BUTTON_UP]) {
				state[0].size++;
				if(state[0].size>150) {
					state[0].size = 150;
				}
			}
			if (button[BUTTON_DOWN]) {
				state[0].size--;
				if(state[0].size<3) {
					state[0].size = 3;
				}
			}
			if(button[BUTTON_RIGHT]) {
				if (state[0].nballs > 1)
					state[0].nballs--;
			}
			if(button[BUTTON_LEFT]) {
				if (state[0].nballs < MAXBALLS)
					state[0].nballs++;
			}
			// see if we need to bounce
			for (int i = 0; i < state[0].nballs; i++) {
				struct ball *bp = &state[0].balls[i];
				bp->row = bp->row + bp->rd;
				bp->col += bp->cd;
				if(bp->row < 0) {
					bp->row = 0;
					bp->rd = -bp->rd;
					score++;
				}
				if(bp->row > 159-state[0].size+1) {
					bp->row = 159-state[0].size+1;
					bp->rd = -bp->rd;
				}
				if(bp->col < 0) {
					bp->col = 0;
					bp->cd = -bp->cd;
				}
				if(bp->col > 239-state[0].size+1) {
					bp->col = 239-state[0].size+1;
					bp->cd = -bp->cd;
				}
			}

		} else if (state[0].gamestate == GS_SPLASH) {
			struct ball *bp = &state[0].balls[state[0].initnballs - 1];
			// When we've reached the bottom, start the next ball
			if (bp->row >= 159 - state[0].size + 1)
				state[0].initnballs++;	// next ball
			else
				bp->row += 4;	// move ball down by 4
			// Don't let the ball extend below the bottom
			if (bp->row > 159 - state[0].size + 1)
				bp->row = 159 - state[0].size + 1;
			// Draw the balls we've touched up to this point
			if (state[0].initnballs <= MAXBALLS)
				state[0].nballs = state[0].initnballs;

	/* debugging code
			char buffer[51];
			drawRect(150, 5, 8, 100, bgcolor);
			sprintf(buffer, "r,c=%d,%d,%d", bp->row, bp->col, state[0].nballs);
			drawString(150, 5, buffer, YELLOW);
	*/
		} else if (state[0].gamestate == GS_INIT) {
			state[0].nballs = MAXBALLS;
			for (int i = 0; i < state[0].nballs; i++) {
				state[0].balls[i].row = rand() % 160;
				state[0].balls[i].col = rand() % 240;
				state[0].balls[i].rd = deltas[rand() % ndeltas];
				state[0].balls[i].cd = deltas[rand() % ndeltas];
				state[0].balls[i].color = colors[i % ncolors];
			}
		}

		// Wait for a Vblank to update the screen
		waitForVblank();

		// Erase the old images
		if (state[1].gamestate != GS_PAUSE) {
			for (int i = 0; i < state[1].nballs; i++) {
				struct ball *obp = &state[1].balls[i];
				drawRect(obp->row, obp->col,
					state[1].size, state[1].size,
					bgcolor);
			}
			if (state[0].gamestate == GS_BOUNCE) {
				drawRect(150, 5, 10, 80, bgcolor);
			}
		}

		// Draw the new images
		if (state[0].gamestate != GS_PAUSE) {
			for (int i = 0; i < state[0].nballs; i++) {
				struct ball *bp = &state[0].balls[i];
				drawRect(bp->row, bp->col,
					state[0].size, state[0].size,
					bp->color);
			}
			if (state[0].gamestate == GS_BOUNCE) {
				char buffer[51];
				sprintf(buffer, "Score: %d", score);
				drawString(150, 5, buffer, YELLOW);
			}
		}
			
		// Choose the next state
		switch (state[0].gamestate) {
			// Do the splash screen animation
			case GS_SPLASH: 
				if (state[0].initnballs > MAXBALLS)
					state[0].gamestate = GS_INIT;
				break;
			// Initialize the balls for bouncing
			case GS_INIT: 
				state[0].gamestate = GS_BOUNCE;
				break;
			// Bounce the balls around
			case GS_BOUNCE:
				if (button[BUTTON_A])
					state[0].gamestate = GS_PAUSE;
				break;
			// Pause the graphics
			case GS_PAUSE:
				if (button[BUTTON_A])
					state[0].gamestate = GS_BOUNCE;
				break;
			
		}


	} // Game Loop


}
