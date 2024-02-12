#include "Definitions.h"

//Checks if the game is won by the given player
char game_finished(game_data_t* current_game, int player);

//Sets the threats-counting variables
void set_threats_number(game_data_t* current_game);

//Sets the sequence-length-counting variables
void set_longest_sequences(game_data_t* current_game);


//Sets the sequence-length-counting variables of the given player
void set_longest_sequences_for_player(game_data_t* current_game, int player);

//set_longest_sequences_for_player's subfunction to check starting from y-s
void check_longest_sequences_from_y(game_data_t* current_game, int player);

//set_longest_sequences_for_player's subfunction to check starting from x-es
void check_longest_sequences_from_x(game_data_t* current_game, int player);

//Updates the longest sequence data of the given player if the new pawn made it longer
void check_sequence_made_by_added_pawn(game_data_t* current_game, int player, int added_pawn_x, int added_pawn_y);

//Checks if the given player has a threat on this position
char player_has_threat_in_position(game_data_t* current_game, int x, int y, int player);


//Returns the length of the longest sequence in a row y
int get_longest_sequence_in_row(game_data_t* current_game, int y, int player);

//Returns the length of the longest sequence in a column x
int get_longest_sequence_in_column(game_data_t* current_game, int x, int player);

//Returns the length of the longest sequence in a down-headed cross starting from the position (0, starting_y)
int get_longest_sequence_in_down_cross_from_given_y(game_data_t* current_game, int starting_y, int player);

//Returns the length of the longest sequence in a up-headed cross starting from the position (0, starting_y)
int get_longest_sequence_in_up_cross_from_given_y(game_data_t* current_game, int starting_y, int player);

//Returns the length of the longest sequence in a down-headed cross starting from the position (starting_x, 0)
int get_longest_sequence_in_down_cross_from_given_x(game_data_t* current_game, int starting_x, int player);

//Returns the length of the longest sequence in a up-headed cross starting from the position (starting_x, m - 1)
int get_longest_sequence_in_up_cross_from_given_x(game_data_t* current_game, int starting_x, int player);

//Returns the length of the given player's sequence in the row, ended next to or interrupted by the given position
int get_sequence_in_row(game_data_t* current_game, int x, int y, int player);

//Returns the length of the given player's sequence in the column, ended next to or interrupted by the given position
int get_sequence_in_column(game_data_t* current_game, int x, int y, int player);

//Returns the length of the given player's sequence in the right-down going cross, ended next to or interrupted by the given position
int get_sequence_in_right_cross(game_data_t* current_game, int x, int y, int player);

//Returns the length of the given player's sequence in the left-down going cross, ended next to or interrupted by the given position
int get_sequence_in_left_cross(game_data_t* current_game, int x, int y, int player);