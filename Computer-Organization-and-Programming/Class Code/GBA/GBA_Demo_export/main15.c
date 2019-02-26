#include "lib.h"

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	int deltas[] = { -3, -2, -1, 1, 2, 3 };
        int ndeltas = sizeof(deltas) / sizeof(deltas[0]);
        unsigned short colors[] = {RED, BLUE, GREEN, WHITE, CYAN, YELLOW, MAGENTA};
        int ncolors = sizeof(colors) / sizeof(colors[0]);
	int score = 0;

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
                int size;
                int nballs;
                struct ball balls[MAXBALLS];
        } state[2];

        state[0].size = 5;
        state[0].nballs = MAXBALLS;
        for (int i = 0; i < MAXBALLS; i++) {
                state[0].balls[i].row = rand() % 160;
                state[0].balls[i].col = rand() % 240;
                state[0].balls[i].rd = deltas[rand() % ndeltas];
                state[0].balls[i].cd = deltas[rand() % ndeltas];
                state[0].balls[i].color = colors[i % ncolors];
        }


        while(1) {
                // Save the previous state
                state[1] = state[0];

		// See what's changed and update current input stat 
                for (int i = 0; i < NBUTTONS; i++) {
			button[i] = KEY_DOWN_NOW(i) == 0 && buttondown[i];
			buttondown[i] = KEY_DOWN_NOW(i) != 0;
		}


                // Compute the graphics for the current state
                if (button[BUTTON_UP]) {
                        state[0].size++;
                        if (state[0].size > 20)
                                state[0].size = 20;
                }
                if (button[BUTTON_DOWN]) {
                        state[0].size--;
                        if (state[0].size < 1)
                                state[0].size = 1;
                }

                for (int i = 0; i < state[0].nballs; i++) {
                        struct ball *bp = &state[0].balls[i];
                        bp->row += bp->rd;
                        bp->col += bp->cd;
                        if (bp->row < 0) {
                                bp->row = 0;
                                bp->rd = -bp->rd;
				score++;
                        }
                        if (bp->row > 159 - state[0].size + 1) {
                                bp->row = 159 - state[0].size + 1;
                                bp->rd = -bp->rd;
                        }
                        if (bp->col < 0) {
                                bp->col = 0;
                                bp->cd = -bp->cd;
                        }
                        if (bp->col > 239 - state[0].size + 1) {
                                bp->col = 239 - state[0].size + 1;
                                bp->cd = -bp->cd;
                        }
                }

                waitForVblank();

                // Erase graphics from previous state
                for (int i = 0; i < state[1].nballs; i++) {
                        drawRect(state[1].balls[i].row, state[1].balls[i].col,
                                        state[1].size, state[1].size, BLACK);
                }
		// Clear the score area
		drawRect(150, 0, 10, 80, BLACK);

                // Draw balls for the current state
                for (int i = 0; i < state[0].nballs; i++) {
                        drawRect(state[0].balls[i].row, state[0].balls[i].col,
                                        state[0].size, state[0].size,
                                        state[0].balls[i].color);
                }
		// Draw the score at the bottom
		char buffer[100];
		sprintf(buffer, "Score: %d", score);
		drawString(150, 5, buffer, YELLOW);
        }
}
