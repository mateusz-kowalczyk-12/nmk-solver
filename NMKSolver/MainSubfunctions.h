#include "Definitions.h"
#include "Subfunctions.h"

//Reads the next command
void read_command();


//Executes the command "gen_all_pos_mov"
void continue_gen_all_pos_mov();

//Executes the command "gen_all_pos_mov_cut_if_game_over"
void cotinue_gen_all_pos_mov_cut_if_game_over();

//Executes the command "solve_game_state"
void continue_solve_game_state();


//Parses the input of a command
void parse_input(game_data_t* current_game);