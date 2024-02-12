#include "MainSubfunctions.h"

void read_command()
{
    char command[MAX_COMMAND_LENGTH];
    strcpy(command, "");
    scanf("%s", command);

    if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
        continue_gen_all_pos_mov();
    if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        cotinue_gen_all_pos_mov_cut_if_game_over();
    if (strcmp(command, "SOLVE_GAME_STATE") == 0)
        continue_solve_game_state();
}


void continue_gen_all_pos_mov()
{
    game_data_t current_game;
    parse_input(&current_game);

    int possible_moves_number;
    possible_moves_number = get_possible_moves_number(&current_game, current_game.starting_player);

    print_all_possible_moves(&current_game, possible_moves_number);

    free_board_data(&current_game, current_game.board_data);
}

void cotinue_gen_all_pos_mov_cut_if_game_over()
{
    game_data_t current_game;
    parse_input(&current_game);

    int possible_moves_number;
    possible_moves_number = get_possible_moves_number(&current_game, current_game.starting_player);

    if(!print_board_with_win(&current_game, current_game.board_data, possible_moves_number, current_game.starting_player))
        print_all_possible_moves(&current_game, possible_moves_number);

    free_board_data(&current_game, current_game.board_data);
}

void continue_solve_game_state()
{
    game_data_t current_game;
    parse_input(&current_game);

    int result;

    if (game_finished(&current_game, current_game.starting_player))
    {
        if (current_game.starting_player == PLAYER_1)
            result = 1;
        else
            result = -1;
    }

    result = minimax(&current_game, current_game.starting_player, NEG_INF, POS_INF);

    if (result == 1)
        printf("FIRST_PLAYER_WINS\n");
    else
    {
        if (result == -1)
            printf("SECOND_PLAYER_WINS\n");
        else
            printf("BOTH_PLAYERS_TIE\n");
    }

    free_board_data(&current_game, current_game.board_data);
}


void parse_input(game_data_t* current_game)
{
    scanf("%d %d %d %d", &current_game->size_y, &current_game->size_x, &current_game->k, &current_game->starting_player);

    current_game->board_data = (board_data_t*)malloc(sizeof(board_data_t));

    current_game->board_data->board = (int**)malloc(current_game->size_y * sizeof(int*));

    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        current_game->board_data->board[y] = (int*)malloc(current_game->size_x * sizeof(int));

        int x;
        for (x = 0; x < current_game->size_x; x++)
        {
            scanf("%d", &current_game->board_data->board[y][x]);
        }
    }

    set_threats_number(current_game);
    set_longest_sequences(current_game);
}