//to check: >= instead of == in threat
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//boolean values:
#define FALSE 0
#define TRUE 1

//test initial value:
#define TEST_INIT_VALUE -1

//fixed string valuees:
#define MAX_COMMAND_LENGTH 40

//board fields states:
#define EMPTY 0
#define PLAYER_1 1
#define PLAYER_2 2

//players:
#define PLAYERS_NUMBER 2
#define PLAYER_1_INDEX 0
#define PLAYER_2_INDEX 1

//minimax infinities substitutes:
#define POS_INF 2
#define NEG_INF -2


typedef struct board_data_t
{
    int** board;

    int threats[PLAYERS_NUMBER];

    int longest_sequence[PLAYERS_NUMBER];
    int longest_sequence_repetitions[PLAYERS_NUMBER];
}
board_data_t;

typedef struct game_data_t
{
    int size_x, size_y;
    int k;

    board_data_t* board_data;

    int starting_player;
}
game_data_t;