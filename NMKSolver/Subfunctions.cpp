#include "Subfunctions.h"


void print_all_possible_moves(game_data_t* current_game, int possible_moves_number)
{
    printf("%d\n", possible_moves_number);

    int possible_move_number;
    for (possible_move_number = 0; possible_move_number < possible_moves_number; possible_move_number++)
    {
        int added_pawn_x, added_pawn_y;
        add_pawn_to_board_data(current_game, possible_move_number, current_game->starting_player, &added_pawn_x, &added_pawn_y);

        print_board(current_game);

        remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);
    }
}

char print_board_with_win(game_data_t* current_game, board_data_t* base_board_data, int possible_moves_number, int player)
{
    int added_pawn_x, added_pawn_y;

    if (add_winning_pawn_to_board_data(current_game, possible_moves_number, player, &added_pawn_x, &added_pawn_y))
    {
        printf("1\n");
        print_board(current_game);
        
        remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);

        return TRUE;
    }
    return FALSE;
}

int minimax(game_data_t* current_game, int choosing_player, int guaranteed_for_player_1, int guaranteed_for_player_2)
{
    int possible_moves_number;
    possible_moves_number = get_possible_moves_number(current_game, choosing_player);

    if (possible_moves_number == 0)
        return evaluate_board(current_game);

    if (current_game->board_data->threats[PLAYER_1_INDEX] >= 2 && current_game->board_data->threats[PLAYER_2_INDEX] == 0)
        return 1;
    if (current_game->board_data->threats[PLAYER_2_INDEX] >= 2 && current_game->board_data->threats[PLAYER_1_INDEX] == 0)
        return -1;

    int score;
    if (choosing_player == PLAYER_1)
        score = NEG_INF;
    else
        score = POS_INF;

    int added_pawn_x, added_pawn_y;
    if (add_winning_pawn_to_board_data(current_game, possible_moves_number, choosing_player, &added_pawn_x, &added_pawn_y))
    {
        remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);

        if (choosing_player == PLAYER_1)
            return 1;
        return -1;
    }

    int possible_move_number;
    for (possible_move_number = 0; possible_move_number < possible_moves_number; possible_move_number++)
    {
        add_pawn_to_board_data(current_game, possible_move_number, choosing_player, &added_pawn_x, &added_pawn_y);

        int new_board_score;
        new_board_score = minimax(current_game, get_opposing_player(choosing_player), guaranteed_for_player_1, guaranteed_for_player_2);

        if (choosing_player == PLAYER_1 && new_board_score > score)
        {
            score = new_board_score;

            if (new_board_score > guaranteed_for_player_1)
                guaranteed_for_player_1 = new_board_score;

            if (score == 1 || guaranteed_for_player_2 <= guaranteed_for_player_1)
            {
                remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);
                break;
            }
        }
        if (choosing_player == PLAYER_2 && new_board_score < score)
        {
            score = new_board_score;

            if (new_board_score < guaranteed_for_player_2)
                guaranteed_for_player_2 = new_board_score;

            if (score == -1 || guaranteed_for_player_1 >= guaranteed_for_player_2)
            {
                remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);
                break;
            }
        }

        remove_pawn_from_board_data(current_game, added_pawn_x, added_pawn_y);
    }

    return score;
}


void add_pawn_to_board_data(game_data_t* current_game, int possible_move_number, int player, int* added_pawn_x, int* added_pawn_y)
{
    int empty_fields_skipped;
    empty_fields_skipped = 0;

    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        int x;
        for (x = 0; x < current_game->size_x; x++)
        {
            if (current_game->board_data->board[y][x] == EMPTY)
            {
                if (empty_fields_skipped < possible_move_number)
                    empty_fields_skipped++;
                else
                {
                    current_game->board_data->board[y][x] = player;

                    *added_pawn_x = x;
                    *added_pawn_y = y;

                    set_threats_number(current_game);
                    check_sequence_made_by_added_pawn(current_game, player, *added_pawn_x, *added_pawn_y);
                    return;
                }
            }
        }
    }
}

char add_winning_pawn_to_board_data(game_data_t* current_game, int possible_moves_number, int player, int* added_pawn_x, int* added_pawn_y)
{
    int possible_move_number;
    for (possible_move_number = 0; possible_move_number < possible_moves_number; possible_move_number++)
    {
        add_pawn_to_board_data(current_game, possible_move_number, player, added_pawn_x, added_pawn_y);

        if (game_finished(current_game, player))
            return TRUE;

        remove_pawn_from_board_data(current_game, *added_pawn_x, *added_pawn_y);
    }

    return FALSE;
}

void remove_pawn_from_board_data(game_data_t* current_game, int x, int y)
{
    current_game->board_data->board[y][x] = EMPTY;

    set_threats_number(current_game);
    set_longest_sequences(current_game);
}

int get_possible_moves_number(game_data_t* current_game, int player)
{
    int empty_fields_number;

    if (game_finished(current_game, get_opposing_player(player)))
        empty_fields_number = 0;
    else
        empty_fields_number = count_empty_fields(current_game);

    return empty_fields_number;
}

int evaluate_board(game_data_t* current_game)
{
    if (game_finished(current_game, PLAYER_1))
        return 1;
    if (game_finished(current_game, PLAYER_2))
        return -1;
    return 0;
}


int count_empty_fields(game_data_t* current_game)
{
    int empty_fields_number;
    empty_fields_number = 0;

    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        int x;
        for (x = 0; x < current_game->size_x; x++)
        {
            if (current_game->board_data->board[y][x] == EMPTY)
                empty_fields_number++;
        }
    }

    return empty_fields_number;
}

void print_board(game_data_t* current_game)
{
    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        int x;
        for (x = 0; x < current_game->size_x; x++)
        {
            printf("%d ", current_game->board_data->board[y][x]);
        }
        putchar('\n');
    }
}

int get_opposing_player(int player)
{
    if (player == PLAYER_1)
        return PLAYER_2;
    else
        return PLAYER_1;
}

int get_player_index(int player)
{
    return player - 1;
}

void free_board_data(game_data_t* current_game, board_data_t* board_data)
{
    free_board(current_game, board_data->board);
    free(board_data);
}

void free_board(game_data_t* current_game, int** board)
{
    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        free(board[y]);
    }
    free(board);
}