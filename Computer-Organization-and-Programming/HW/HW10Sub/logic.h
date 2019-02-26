#ifndef LOGIC_SEEN
#define LOGIC_SEEN

#include "gba.h"

extern int score;
extern int lives;
extern int mo;
extern int rando;
extern int lifeCol;
extern int rand_13;
//Constants
#define NUM_OB1 5

#define BAR_ROW 149
#define BAR_HEIGHT 11

#define TIMER1 200
#define TIMER2 220
#define TIMER3 240

// Player Struct
typedef struct {
    int row;
    int col;
    int height;
    int width;
    int timer;
    const u16 *open;
    const u16 *closed;
    int active; //1 == open arms, 2 == closed
} PLAYER;

// Player Struct
typedef struct {
    int row;
    int col;
    int oldCol;
    int height;
    int width;
    int position;
    int cdel; //this is the gap between the 
    u16 color;
    int active;
} SELECTOR;

// Object Struct
typedef struct {
    int row;
    int col;
    int oldRow;
    int oldCol;
    int rdel;
    int cdel;
    int height;
    int width;
    int morality; //good boy or bad boy
    const u16 *image; 
    int active;
} OBJECT;

//each object struct
extern OBJECT col1[NUM_OB1];
extern OBJECT col2[NUM_OB1];
extern OBJECT col3[NUM_OB1];

void updategame(unsigned short buttons, unsigned short oldButtons);
void updateSelector(unsigned short buttons, unsigned short oldButtons);
void updatePlayer(unsigned short buttons, unsigned short oldButtons);

void initgame(void);
void drawGame(void);

void drawPlayers(void);
void initPlayers(void);

void initSelector(void);
void drawSelector(void);

void initObjects(void);
void updateObj1(OBJECT *obj);
void updateObj2(OBJECT *obj);
void updateObj3(OBJECT *obj);
void drawObj(OBJECT *obj);
void reinitObj1(int moral);
void reinitObj2(int moral);
void reinitObj3(int moral);

void updateLevel(void);

void updateLives(void);

#endif
