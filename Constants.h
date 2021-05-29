#pragma once

#define SIZETANK    13
#define SIZEBLOCK   8
#define PROPORTION  3

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define CREATE 0
#define DELETE 1
#define MOVE   2
#define TURN   3

#define OBJECT          0
#define TANK            10
#define PLAYER_TANK     11
#define DISTR_BLOCK     20
#define UNDISTR_BLOCK   21
#define WATER_BLOCK     22
#define HEADQUARTERS    31 
#define SPAWNER         32
#define BULLET          5
#define EXPLOSION       6

#define POST_SC_SIZE       24
#define POST_C_SIZE         8

// Для PostCS
#define SETSTOP     100
#define SETUP       101
#define SETDOWN     102
#define SETLEFT     103
#define SETRIGHT    104
#define SETSHOOT    105