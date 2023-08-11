"""
File:    jmps_and_hlts.py
Author:  Eric Ekey
Date:    11/01/2021
Section: 35
E-mail:  eekey1@umbc.edu
Description:
  This is a game similar to snakes and ladders, but it's ACTUALLY
  the brand new up and coming 'Where's My Alimony'
"""
import random
"""

    GAME: Where's My Alimony!
    Try and chase down your deadbeat
    ex-spouse to collect your long overdue
    alimony payment. 

"""

# GLOBAL VARIABLES
GRID_WIDTH = 8
GRID_HEIGHT = 3
DICE_SIDES = 6


def generate_random_map(length, the_seed=0):
    """
    :param length - the length of the map
    :param the_seed - the seed of the map
    :return: a randomly generated map based on a specific seed, and length.
    """
    if the_seed:
        random.seed(the_seed)
    map_list = []
    for _ in range(length - 2):
        random_points = random.randint(1, 100)
        random_position = random.randint(0, length - 1)
        map_list.append(random.choices(
            ['nop', f'add {random_points}', f'sub {random_points}', f'mul {random_points}', f'jmp {random_position}',
             'hlt'], weights=[5, 2, 2, 2, 3, 1], k=1)[0])

    return ['nop'] + map_list + ['hlt']


def make_grid(table_size):
    """
    :param table_size: this needs to be the length of the map
    :return: returns a display grid that you can then modify with fill_grid_square (it's a 2d-grid of characters)
    """
    floating_square_root = table_size ** (1 / 2)

    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_height = int_square_root
    if int_square_root * (int_square_root - 1) >= table_size:
        table_height -= 1

    the_display_grid = [[' ' if j % GRID_WIDTH else '*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        if i % GRID_HEIGHT else ['*' for j in range(GRID_WIDTH * int_square_root + 1)]
                        for i in range(table_height * GRID_HEIGHT + 1)]
    return the_display_grid


def fill_grid_square(display_grid, size, index, message):
    """
    :param display_grid:  the grid that was made from make_grid
    :param size:  this needs to be the length of the total map, otherwise you may not be able to place things correctly.
    :param index: the index of the position where you want to display the message
    :param message: the message to display in the square at position index, separated by line returns.
    """
    floating_square_root = size ** (1 / 2)
    int_square_root = int(floating_square_root) + (1 if floating_square_root % 1 else 0)
    table_row = index // int_square_root
    table_col = index % int_square_root

    if table_row % 2 == 0:
        column_start = GRID_WIDTH * table_col
    else:
        column_start = GRID_WIDTH * (int_square_root - table_col - 1)

    for r, message_line in enumerate(message.split('\n')):
        for k, c in enumerate(message_line):
            display_grid[GRID_HEIGHT * table_row + 1 + r][column_start + 1 + k] = c


def roll_dice():
    """
    Call this function once per turn.
    :return: returns the dice roll
    """
    return random.randint(1,DICE_SIDES)


def display(the_grid, the_board, size):
    """
    displays the board
    :param the_grid: this is the grid
    :param the_board: this is the board
    :param size: this is the size of the board
    """
    for j in range(len(the_board)):
        fill_grid_square(the_grid, size, j, str(j) + "\n" + the_board[j])
    for k in range(len(the_grid)):
        print(' '.join(the_grid[k]))


def get_user_input():
    """
    this gets input for the size and seed of the board from the user
    :return: the size or the size and the seed of the board
    """
    size_seed_input = input("Board Size and Seed:\n")
    size_seed = size_seed_input.split()
    size_map = int(size_seed[0])
    if len(size_seed) == 1:

        return [size_map]
    else:
        seed = int(size_seed[1])
        size_and_seed = [size_map, seed]

        return size_and_seed


def calc_points(command, starting_score):
    """
    this does calculations for the score depending on what spots the user lands on
    :param command: the command on the spot the user lands
    :param starting_score: the score the user has when they land here
    :return: the score the user has after they point calculations
    """
    command = command.split()

    if command[0] == "add":
        new_score = starting_score + int(command[1])
    elif command[0] == "sub":
        new_score = starting_score - int(command[1])
    elif command[0] == "mul":
        new_score = starting_score * int(command[1])
    else:
        new_score = starting_score

    return new_score


def jump(command):
    """
    this function moves the user to a new space when they land on a jump
    :param command: the jump command the user landed on
    :return: the user's new position on the table
    """
    command = command.split()
    position = int(command[1])

    return position  # position jumped to


def play_game(game_map):
    """
    this function runs the game
    :param game_map: the list of commands on the board
    """
    position_index = 0  # index in list of position on board
    score = 0
    math_commands = ["nop", "add", "mul", "sub"]
    jump_command = "jmp"
    end_command = "hlt"

    hlt_end_game = False
    while not hlt_end_game:
        dice_roll = roll_dice()
        if position_index + dice_roll >= len(game_map):  # if you go off the board
            position_index = (position_index + dice_roll) % len(game_map)
            if game_map[position_index] == end_command:
                hlt_end_game = True
            elif jump_command in game_map[position_index]:  # if you land on a jump square
                print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                      str(game_map[position_index]) + " Rolled: " + str(dice_roll))
                position_index = jump(game_map[position_index])  # position index after jump
                score = calc_points(game_map[position_index], score)
                while jump_command in game_map[position_index]:
                    print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                          str(game_map[position_index]) + " Rolled: " + str(dice_roll))
                    position_index = jump(game_map[position_index])
                    score = calc_points(game_map[position_index], score)
                if game_map[position_index] == end_command:
                    hlt_end_game = True
            else:
                for math_command in math_commands:
                    if math_command in game_map[position_index]:
                        score = calc_points(game_map[position_index], score)
            print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                  str(game_map[position_index]) + " Rolled: " + str(dice_roll))
        else:
            position_index = position_index + dice_roll
            if game_map[position_index] == end_command:
                hlt_end_game = True
            elif jump_command in game_map[position_index]:
                print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                      str(game_map[position_index]) + " Rolled: " + str(dice_roll))
                position_index = jump(game_map[position_index])
                score = calc_points(game_map[position_index], score)
                while jump_command in game_map[position_index]:
                    print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                          str(game_map[position_index]) + " Rolled: " + str(dice_roll))
                    position_index = jump(game_map[position_index])
                    score = calc_points(game_map[position_index], score)
                if game_map[position_index] == end_command:
                    hlt_end_game = True
            else:
                for math_command in math_commands:
                    if math_command in game_map[position_index]:
                        score = calc_points(game_map[position_index], score)  # score calculation

            print("Pos: " + str(position_index) + " Score: " + str(score) + ", instruction " +
                  str(game_map[position_index]) + " Rolled: " + str(dice_roll))

    print("Final pos: " + str(position_index) + " Final Score: " + str(score) + ", Instruction " +
          str(game_map[position_index]))
    """
    if score < 0:
        score = str(score)
        score = score[1:]
        print("You tried to collect your alimony but instead your greasy ex swiped $" + str(score) + " off you!")
    elif score == 0:
        print("You couldn't track down your money!")
    else:
        print("You succeeded in claiming $" + str(score) + " in alimony!")
    """


def check_size_seed(size_plus_seed):
    """
    this function checks whether the user entered a seed or not
    :param size_plus_seed: user input
    :return: a randomly generated map
    """
    if len(size_plus_seed) > 1:  # if a seed is provided
        board_to_return = generate_random_map(size_plus_seed[0], size_plus_seed[1])  # generates map as list of commands
    else:
        board_to_return = generate_random_map(size_plus_seed[0])

    return board_to_return


def main():
    """
    this function calls all of the functions to play the game
    """
    size_seed = get_user_input()
    the_size = size_seed[0]
    board_run = check_size_seed(size_seed)
    the_playing_grid = make_grid(the_size)
    display(the_playing_grid, board_run, the_size)
    play_game(board_run)
    replay()


def replay():
    """
    this function prompts the user for whether they want to play the game again
    """
    repeat = ["yes", "y"]
    play_again = input("Would you like to play again? (y/n)\n")
    play_again = play_again.strip().lower()
    if play_again in repeat:
        main()
    else:
        print("Game over!")


if __name__ == '__main__':
    main()

