#include "WinChecking.h"
#include "Subfunctions.h"

char game_finished(game_data_t* current_game, int player)
{
    if (current_game->board_data->longest_sequence[get_player_index(player)] >= current_game->k)
        return TRUE;
    return FALSE;
}

void set_threats_number(game_data_t* current_game)
{
    current_game->board_data->threats[PLAYER_1_INDEX] = 0;
    current_game->board_data->threats[PLAYER_2_INDEX] = 0;

    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        int x;
        for (x = 0; x < current_game->size_x; x++)
        {
            if (current_game->board_data->board[y][x] != EMPTY)
                continue;

            if (player_has_threat_in_position(current_game, x, y, PLAYER_1))
                current_game->board_data->threats[PLAYER_1_INDEX]++;
            if (player_has_threat_in_position(current_game, x, y, PLAYER_2))
                current_game->board_data->threats[PLAYER_2_INDEX]++;
        }
    }
}

void set_longest_sequences(game_data_t* current_game)
{
    set_longest_sequences_for_player(current_game, PLAYER_1);
    set_longest_sequences_for_player(current_game, PLAYER_2);
}


void set_longest_sequences_for_player(game_data_t* current_game, int player)
{
    int player_index = get_player_index(player);
    current_game->board_data->longest_sequence[player_index] = 0;
    current_game->board_data->longest_sequence_repetitions[player_index] = 0;

    check_longest_sequences_from_y(current_game, player);
    check_longest_sequences_from_x(current_game, player);
}

void check_longest_sequences_from_y(game_data_t* current_game, int player)
{
    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        int player_index;
        player_index = get_player_index(player);

        int longest_sequence_in_row;
        longest_sequence_in_row = get_longest_sequence_in_row(current_game, y, player);

        if (longest_sequence_in_row > current_game->board_data->longest_sequence[player_index])
        {
            current_game->board_data->longest_sequence_repetitions[player_index] = 1;
            current_game->board_data->longest_sequence[player_index] = longest_sequence_in_row;
        }
        else
        {
            if (longest_sequence_in_row == current_game->board_data->longest_sequence[player_index])
                current_game->board_data->longest_sequence_repetitions[player_index]++;
        }

        if (y != current_game->size_y - 1) //single-pawn sequence already checked earlier
        {
            int longest_sequence_in_down_cross_from_given_y;
            longest_sequence_in_down_cross_from_given_y = get_longest_sequence_in_down_cross_from_given_y(current_game, y, player);

            if (longest_sequence_in_down_cross_from_given_y > current_game->board_data->longest_sequence[player_index])
            {
                current_game->board_data->longest_sequence_repetitions[player_index] = 1;
                current_game->board_data->longest_sequence[player_index] = longest_sequence_in_down_cross_from_given_y;
            }
            else
            {
                if (longest_sequence_in_down_cross_from_given_y == current_game->board_data->longest_sequence[player_index])
                    current_game->board_data->longest_sequence_repetitions[player_index]++;
            }
        }
        if (y != 0) //single-pawn sequence already checked earlier
        {
            int longest_sequence_in_up_cross_from_given_y;
            longest_sequence_in_up_cross_from_given_y = get_longest_sequence_in_up_cross_from_given_y(current_game, y, player);

            if (longest_sequence_in_up_cross_from_given_y > current_game->board_data->longest_sequence[player_index])
            {
                current_game->board_data->longest_sequence_repetitions[player_index] = 1;
                current_game->board_data->longest_sequence[player_index] = longest_sequence_in_up_cross_from_given_y;
            }
            else
            {
                if (longest_sequence_in_up_cross_from_given_y == current_game->board_data->longest_sequence[player_index])
                    current_game->board_data->longest_sequence_repetitions[player_index]++;
            }
        }
    }
}

void check_longest_sequences_from_x(game_data_t* current_game, int player)
{
    int x;
    for (x = 0; x < current_game->size_x; x++)
    {
        int player_index;
        player_index = get_player_index(player);

        int longest_sequence_in_column;
        longest_sequence_in_column = get_longest_sequence_in_column(current_game, x, player);

        if (longest_sequence_in_column > current_game->board_data->longest_sequence[player_index])
        {
            current_game->board_data->longest_sequence_repetitions[player_index] = 1;
            current_game->board_data->longest_sequence[player_index] = longest_sequence_in_column;
        }
        else
        {
            if (longest_sequence_in_column == current_game->board_data->longest_sequence[player_index])
                current_game->board_data->longest_sequence_repetitions[player_index]++;
        }

        if (x != 0 && x != current_game->size_x - 1) //those crosses down (up) already checked earlier, single-pawn sequence already checked earlier
        {
            int longest_sequence_in_down_cross_from_given_x;
            longest_sequence_in_down_cross_from_given_x = get_longest_sequence_in_down_cross_from_given_x(current_game, x, player);

            if (longest_sequence_in_down_cross_from_given_x > current_game->board_data->longest_sequence[player_index])
            {
                current_game->board_data->longest_sequence_repetitions[player_index] = 1;
                current_game->board_data->longest_sequence[player_index] = longest_sequence_in_down_cross_from_given_x;
            }
            else
            {
                if (longest_sequence_in_down_cross_from_given_x == current_game->board_data->longest_sequence[player_index])
                    current_game->board_data->longest_sequence_repetitions[player_index]++;
            }

            int longest_sequence_in_up_cross_from_given_x;
            longest_sequence_in_up_cross_from_given_x = get_longest_sequence_in_up_cross_from_given_x(current_game, x, player);

            if (longest_sequence_in_up_cross_from_given_x > current_game->board_data->longest_sequence[player_index])
            {
                current_game->board_data->longest_sequence_repetitions[player_index] = 1;
                current_game->board_data->longest_sequence[player_index] = longest_sequence_in_up_cross_from_given_x;
            }
            else
            {
                if (longest_sequence_in_up_cross_from_given_x == current_game->board_data->longest_sequence[player_index])
                    current_game->board_data->longest_sequence_repetitions[player_index]++;
            }
        }
    }
}

void check_sequence_made_by_added_pawn(game_data_t* current_game, int player, int added_pawn_x, int added_pawn_y)
{
    int player_index;
    player_index = get_player_index(player);

    int sequence_in_row;
    sequence_in_row = get_sequence_in_row(current_game, added_pawn_x, added_pawn_y, player) + 1; //+1, because the pawn on (added_pawn_x, added_pawn_y) is not accounted by the function

    if (sequence_in_row > current_game->board_data->longest_sequence[player_index])
    {
        current_game->board_data->longest_sequence_repetitions[player_index] = 1;
        current_game->board_data->longest_sequence[player_index] = sequence_in_row;
    }
    else
    {
        if (sequence_in_row == current_game->board_data->longest_sequence[player_index])
            current_game->board_data->longest_sequence_repetitions[player_index]++;
    }

    int sequence_in_column;
    sequence_in_column = get_sequence_in_column(current_game, added_pawn_x, added_pawn_y, player) + 1;

    if (sequence_in_column > current_game->board_data->longest_sequence[player_index])
    {
        current_game->board_data->longest_sequence_repetitions[player_index] = 1;
        current_game->board_data->longest_sequence[player_index] = sequence_in_column;
    }
    else
    {
        if (sequence_in_column == current_game->board_data->longest_sequence[player_index])
            current_game->board_data->longest_sequence_repetitions[player_index]++;
    }

    int sequence_in_right_cross;
    sequence_in_right_cross = get_sequence_in_right_cross(current_game, added_pawn_x, added_pawn_y, player) + 1;

    if (sequence_in_right_cross > current_game->board_data->longest_sequence[player_index])
    {
        current_game->board_data->longest_sequence_repetitions[player_index] = 1;
        current_game->board_data->longest_sequence[player_index] = sequence_in_right_cross;
    }
    else
    {
        if (sequence_in_right_cross == current_game->board_data->longest_sequence[player_index])
            current_game->board_data->longest_sequence_repetitions[player_index]++;
    }

    int sequence_in_left_cross;
    sequence_in_left_cross = get_sequence_in_left_cross(current_game, added_pawn_x, added_pawn_y, player) + 1;

    if (sequence_in_left_cross > current_game->board_data->longest_sequence[player_index])
    {
        current_game->board_data->longest_sequence_repetitions[player_index] = 1;
        current_game->board_data->longest_sequence[player_index] = sequence_in_left_cross;
    }
    else
    {
        if (sequence_in_left_cross == current_game->board_data->longest_sequence[player_index])
            current_game->board_data->longest_sequence_repetitions[player_index]++;
    }

}

char player_has_threat_in_position(game_data_t* current_game, int x, int y, int player)
{
    if (get_sequence_in_row(current_game, x, y, player) >= current_game->k - 1)
        return TRUE;
    if (get_sequence_in_column(current_game, x, y, player) >= current_game->k - 1)
        return TRUE;
    if (get_sequence_in_right_cross(current_game, x, y, player) >= current_game->k - 1)
        return TRUE;
    if (get_sequence_in_left_cross(current_game, x, y, player) >= current_game->k - 1)
        return TRUE;

    return FALSE;
}


int get_longest_sequence_in_row(game_data_t* current_game, int y, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int x;
    for (x = 0; x < current_game->size_x; x++)
    {
        if (current_game->board_data->board[y][x] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_longest_sequence_in_column(game_data_t* current_game, int x, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int y;
    for (y = 0; y < current_game->size_y; y++)
    {
        if (current_game->board_data->board[y][x] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_longest_sequence_in_down_cross_from_given_y(game_data_t* current_game, int starting_y, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int relative_addition;
    for (relative_addition = 0; starting_y + relative_addition < current_game->size_y && relative_addition < current_game->size_x; relative_addition++)
    {
        if (current_game->board_data->board[starting_y + relative_addition][relative_addition] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_longest_sequence_in_up_cross_from_given_y(game_data_t* current_game, int starting_y, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int relative_addition;
    for (relative_addition = 0; starting_y - relative_addition >= 0 && relative_addition < current_game->size_x; relative_addition++)
    {
        if (current_game->board_data->board[starting_y - relative_addition][relative_addition] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_longest_sequence_in_down_cross_from_given_x(game_data_t* current_game, int starting_x, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int relative_addition;
    for (relative_addition = 0; starting_x + relative_addition < current_game->size_x && relative_addition < current_game->size_y; relative_addition++)
    {
        if (current_game->board_data->board[relative_addition][starting_x + relative_addition] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_longest_sequence_in_up_cross_from_given_x(game_data_t* current_game, int starting_x, int player)
{
    int pawns_number, longest_sequence;
    pawns_number = 0;
    longest_sequence = 0;

    int relative_addition;
    for (relative_addition = 0; starting_x + relative_addition < current_game->size_x && relative_addition < current_game->size_y; relative_addition++)
    {
        if (current_game->board_data->board[current_game->size_y - 1 - relative_addition][starting_x + relative_addition] == player)
            pawns_number++;
        else
        {
            if (pawns_number > longest_sequence)
                longest_sequence = pawns_number;

            pawns_number = 0;
        }
    }

    if (pawns_number > longest_sequence)
        return pawns_number;
    return longest_sequence;
}

int get_sequence_in_row(game_data_t* current_game, int x, int y, int player)
{
    int pawns_number;
    pawns_number = 0;

    int relative_x;
    for (relative_x = 1; x - relative_x >= 0; relative_x++) //to the left
    {
        if (current_game->board_data->board[y][x - relative_x] == player)
            pawns_number++;
        else
            break;
    }
    for (relative_x = 1; x + relative_x < current_game->size_x; relative_x++) //to the right
    {
        if (current_game->board_data->board[y][x + relative_x] == player)
            pawns_number++;
        else
            break;
    }

    return pawns_number;
}

int get_sequence_in_column(game_data_t* current_game, int x, int y, int player)
{
    int pawns_number;
    pawns_number = 0;

    int relative_y;
    for (relative_y = 1; y - relative_y >= 0; relative_y++) //to the top
    {
        if (current_game->board_data->board[y - relative_y][x] == player)
            pawns_number++;
        else
            break;

    }
    for (relative_y = 1; y + relative_y < current_game->size_y; relative_y++) //to the bottom
    {
        if (current_game->board_data->board[y + relative_y][x] == player)
            pawns_number++;
        else
            break;

    }

    return pawns_number;
}

int get_sequence_in_right_cross(game_data_t* current_game, int x, int y, int player)
{
    int pawns_number;
    pawns_number = 0;

    int relative_addition;
    for (relative_addition = 1; y - relative_addition >= 0 && x - relative_addition >= 0; relative_addition++) //to the top
    {
        if (current_game->board_data->board[y - relative_addition][x - relative_addition] == player)
            pawns_number++;
        else
            break;

    }
    for (relative_addition = 1; y + relative_addition < current_game->size_y && x + relative_addition < current_game->size_x; relative_addition++) //to the bottom
    {
        if (current_game->board_data->board[y + relative_addition][x + relative_addition] == player)
            pawns_number++;
        else
            break;

    }

    return pawns_number;
}

int get_sequence_in_left_cross(game_data_t* current_game, int x, int y, int player)
{
    int pawns_number;
    pawns_number = 0;

    int relative_addition;
    for (relative_addition = 1; y - relative_addition >= 0 && x + relative_addition < current_game->size_x; relative_addition++) //to the top
    {
        if (current_game->board_data->board[y - relative_addition][x + relative_addition] == player)
            pawns_number++;
        else
            break;
    }
    for (relative_addition = 1; y + relative_addition < current_game->size_y && x - relative_addition >= 0; relative_addition++) //to the bottom
    {
        if (current_game->board_data->board[y + relative_addition][x - relative_addition] == player)
            pawns_number++;
        else
            break;
    }

    return pawns_number;
}