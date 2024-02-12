#pragma once

#include "Definitions.h"
#include "WinChecking.h"

//Prints all boards with one active player's pawn added
void print_all_possible_moves(game_data_t* current_game, int possible_moves_number);

//Prints a board with a winning sequence created by adding one given player's pawn to the board and returns TRUE or returns FALSE if such board doesn't exist
char print_board_with_win(game_data_t* current_game, board_data_t* base_board_data, int possible_moves_number, int player);

//Returns the value of game started by the given player counted by the minimax algorithm 
int minimax(game_data_t* current_game, int choosing_player, int guaranteed_for_player_1, int guaranteed_for_player_2);


//Adds the given player's pawn to the given empty position on the board
void add_pawn_to_board_data(game_data_t* current_game, int possible_move_number, int player, int* added_pawn_x, int* added_pawn_y);

//Adds the given player's pawn to the board so that the game is finished; returs TRUE if succeded or FALSE if there's no such place to put a pawn
char add_winning_pawn_to_board_data(game_data_t* current_game, int possible_moves_number, int player, int* added_pawn_x, int* added_pawn_y);

//Removes the pawn on the given position from the board
void remove_pawn_from_board_data(game_data_t* current_game, int x, int y);

//Returns the number of empty fields or 0 if the game is already won
int get_possible_moves_number(game_data_t* current_game, int player);

//Returns the static evaluation of the board: 0 if tie; 1 if player 1 wins; -1 if player 2 wins
int evaluate_board(game_data_t* current_game);


//Returns the number of empty fields on the board
int count_empty_fields(game_data_t* current_game);

//Prints the board
void print_board(game_data_t* current_game);

//Returns the symbol of the previous player
int get_opposing_player(int player);

//Returns 0 for player 1 and 1 for player 2
int get_player_index(int player);

//Frees the memory allocated fot the given board_data
void free_board_data(game_data_t* current_game, board_data_t* board_data);

//Frees the memory allocated fot the given board
void free_board(game_data_t* current_game, int** board);