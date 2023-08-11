"""
File:    lost_and_found.py
Author:  Eric Ekey
Date:    11/14/2021
Section: 35
E-mail:  eekey1@umbc.edu
Description:
  traverses a map collecting items, searching for secrets, and opening doors
  until you escape
"""


import json


USE = 'e'
EMPTY = ''
FLOOR = '_'
EXIT = 'x'
DOOR = 'd'
SECRET = 's'
WALL = '*'
ITEMS = 'i'
STARTING_LOCATION = 'start'
QUIT = 'q'


def stay_in_bounds(row_y, column_x, command):  # finished
    """
    polices player movement near boundaries
    :param row_y: player row
    :param column_x: player column
    :param command: move command
    :return: new position
    """
    if command == "w":
        if (row_y - 1) < 0:
            return row_y, column_x
    elif command == "a":
        if (column_x - 1) < 0:
            return row_y, column_x
    elif command == "s":
        if (row_y + 1) > (len(the_game_map) - 1):
            return row_y, column_x
    elif command == "d":
        if (column_x + 1) > (len(the_game_map[0]) - 1):
            return row_y, column_x

    new_position = move_player(row_y, column_x, command)
    return new_position  # returns "y, x"


def move_player(row_y, column_x, command):  # finished
    """
    moves the player
    :param row_y: player row
    :param column_x: player column
    :param command: movement command
    :return: new position
    """
    restricted_spots = [SECRET, DOOR, WALL]

    if command == "w":
        if the_game_map[row_y - 1][column_x]["symbol"] in restricted_spots:
            return row_y, column_x
        else:
            return (row_y - 1), column_x
    elif command == "a":
        if the_game_map[row_y][column_x - 1]["symbol"] in restricted_spots:
            return row_y, column_x
        else:
            return row_y, (column_x - 1)
    elif command == "s":
        if the_game_map[row_y + 1][column_x]["symbol"] in restricted_spots:
            return row_y, column_x





        else:
            return (row_y + 1), column_x
    elif command == "d":
        if the_game_map[row_y][column_x + 1]["symbol"] in restricted_spots:
            return row_y, column_x
        else:
            return row_y, (column_x + 1)


def load_map(map_file_name):
    """
        When a map file name is passed the file will load the grid and return it.
        Should you modify this function? No you shouldn't.

    :param map_file_name: a string representing the file name.
    :return: a 2D list which contains the current map.
    """
    with open(map_file_name) as map_file:
        the_map = json.loads(map_file.read())

    return the_map


def the_grid(game_map, y, x):  # finished
    """
    prints the grid
    :param game_map: the game map
    :param y: player row
    :param x: player column
    :return: whether the player has escaped
    """
    winner = False
    exit_y = -1
    exit_x = -1

    print("\n\n")
    print("", end="\t")
    for i in range(len(game_map)):
        print(i, end="\t")
    print("\n")
    for row in range(len(game_map)):
        print(row, end="\t")
        for grid_square in range(len(game_map[row])):
            if game_map[row][grid_square]["symbol"] == EXIT:
                exit_y, exit_x = [row, grid_square]
            if len(game_map[row][grid_square]['items']) == 0:
                if (row == y) and (grid_square == x):
                    print("\u1330", end="\t")
                elif game_map[row][grid_square]['symbol'] == SECRET:
                    print("*", end="\t")
                else:
                    print(game_map[row][grid_square]['symbol'], end="\t")
            elif len(game_map[row][grid_square]["items"]) != 0:
                print(ITEMS, end="\t")
        print("\n")
    if game_map[y][x] == game_map[exit_y][exit_x]:  # when user position = exit position, kill the game
        print("You have escaped!")
        winner = True
    return winner


def check_area(row_y, column_x, backpack):  # finished
    """
    checks the area around the player
    :param row_y: player row
    :param column_x: player column
    :param backpack: backpack contents
    """
    bottom_right, bottom_left, top_right, top_left = find_corners(row_y, column_x)
    right_edge, left_edge, top_edge, bottom_edge = find_edges(row_y, column_x)
    requires = "requires"
    symbol = "symbol"

    if bottom_right:
        left = the_game_map[row_y][column_x - 1]
        up_left = the_game_map[row_y - 1][column_x - 1]
        above = the_game_map[row_y - 1][column_x]
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x - 1, ") requires ", end="")
                    print(left[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in up_left:
            if up_left[symbol] == DOOR:  # door up left
                requirements_met = reqs_met(up_left[requires], backpack)
                if requirements_met:
                    up_left[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x - 1, ") requires ", end="")
                    print(up_left[requires])
        elif up_left[symbol] == DOOR:
            up_left[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
        if up_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x - 1, ")")
            up_left[symbol] = DOOR
    elif bottom_left:
        right = the_game_map[row_y][column_x + 1]
        up_right = the_game_map[row_y - 1][column_x + 1]
        above = the_game_map[row_y - 1][column_x]
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in up_right:
            if up_right[symbol] == DOOR:  # door up right
                requirements_met = reqs_met(up_right[requires], backpack)
                if requirements_met:
                    up_right[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x + 1, ") requires ", end="")
                    print(up_right[requires])
        elif up_right[symbol] == DOOR:
            up_right[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
        if up_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x + 1, ")")
            up_right[symbol] = DOOR
    elif top_right:
        down_left = the_game_map[row_y + 1][column_x - 1]
        left = the_game_map[row_y][column_x - 1]
        below = the_game_map[row_y + 1][column_x]
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x - 1, ") requires ", end="")
                    print(left[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in down_left:
            if down_left[symbol] == DOOR:  # door down left
                requirements_met = reqs_met(down_left[requires], backpack)
                if requirements_met:
                    down_left[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x - 1, ") requires ", end="")
                    print(down_left[requires])
        elif down_left[symbol] == DOOR:
            down_left[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
        if down_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x - 1, ")")
            down_left[symbol] = DOOR
    elif top_left:
        right = the_game_map[row_y][column_x + 1]
        below = the_game_map[row_y + 1][column_x]
        down_right = the_game_map[row_y + 1][column_x + 1]
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in down_right:
            if down_right[symbol] == DOOR:  # door down right
                requirements_met = reqs_met(down_right[requires], backpack)
                if requirements_met:
                    down_right[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x + 1, ") requires ", end="")
                    print(down_right[requires])
        elif down_right[symbol] == DOOR:
            down_right[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
        if down_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x + 1, ")")
            down_right[symbol] = DOOR
    elif left_edge:
        right = the_game_map[row_y][column_x + 1]
        up_right = the_game_map[row_y - 1][column_x + 1]
        down_right = the_game_map[row_y + 1][column_x + 1]
        above = the_game_map[row_y - 1][column_x]
        below = the_game_map[row_y + 1][column_x]
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in up_right:
            if up_right[symbol] == DOOR:  # door up right
                requirements_met = reqs_met(up_right[requires], backpack)
                if requirements_met:
                    up_right[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x + 1, ") requires ", end="")
                    print(down_right[requires])
        elif up_right[symbol] == DOOR:
            up_right[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
        if up_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x + 1, ")")
            up_right[symbol] = DOOR
        if requires in down_right:
            if down_right[symbol] == DOOR:  # door down right
                requirements_met = reqs_met(down_right[requires], backpack)
                if requirements_met:
                    down_right[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x + 1, ") requires ", end="")
                    print(down_right[requires])
        elif down_right[symbol] == DOOR:
            down_right[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
        if down_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x + 1, ")")
            down_right[symbol] = DOOR
    elif right_edge:
        down_left = the_game_map[row_y + 1][column_x - 1]
        left = the_game_map[row_y][column_x - 1]
        up_left = the_game_map[row_y - 1][column_x - 1]
        above = the_game_map[row_y - 1][column_x]
        below = the_game_map[row_y + 1][column_x]
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in up_left:
            if up_left[symbol] == DOOR:  # door up left
                requirements_met = reqs_met(up_left[requires], backpack)
                if requirements_met:
                    up_left[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x - 1, ") requires ", end="")
                    print(down_left[requires])
        elif up_left[symbol] == DOOR:
            up_left[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
        if up_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x - 1, ")")
            up_left[symbol] = DOOR
        if requires in down_left:
            if down_left[symbol] == DOOR:  # door down left
                requirements_met = reqs_met(down_left[requires], backpack)
                if requirements_met:
                    down_left[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x - 1, ") requires ", end="")
                    print(down_left[requires])
        elif down_left[symbol] == DOOR:
            down_left[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
        if down_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x - 1, ")")
            down_left[symbol] = DOOR
    elif bottom_edge:
        above = the_game_map[row_y - 1][column_x]
        up_right = the_game_map[row_y - 1][column_x + 1]
        up_left = the_game_map[row_y - 1][column_x - 1]
        left = the_game_map[row_y][column_x - 1]
        right = the_game_map[row_y][column_x + 1]
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x - 1, ") requires ", end="")
                    print(left[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in up_right:
            if up_right[symbol] == DOOR:  # door up right
                requirements_met = reqs_met(up_right[requires], backpack)
                if requirements_met:
                    up_right[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x + 1, ") requires ", end="")
                    print(up_right[requires])
        elif up_right[symbol] == DOOR:
            up_right[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
        if up_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x + 1, ")")
            up_right[symbol] = DOOR
        if requires in up_left:
            if up_left[symbol] == DOOR:  # door up left
                requirements_met = reqs_met(up_left[requires], backpack)
                if requirements_met:
                    up_left[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x - 1, ") requires ", end="")
                    print(up_left[requires])
        elif up_left[symbol] == DOOR:
            up_left[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
        if up_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x - 1, ")")
            up_left[symbol] = DOOR
    elif top_edge:
        below = the_game_map[row_y + 1][column_x]
        down_right = the_game_map[row_y + 1][column_x + 1]
        down_left = the_game_map[row_y + 1][column_x - 1]
        left = the_game_map[row_y][column_x - 1]
        right = the_game_map[row_y][column_x + 1]
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x - 1, ") requires ", end="")
                    print(left[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in down_right:
            if down_right[symbol] == DOOR:  # door down right
                requirements_met = reqs_met(down_right[requires], backpack)
                if requirements_met:
                    down_right[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x + 1, ") requires ", end="")
                    print(down_right[requires])
        elif down_right[symbol] == DOOR:
            down_right[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
        if down_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x + 1, ")")
            down_right[symbol] = DOOR
        if requires in down_left:
            if down_left[symbol] == DOOR:  # door down left
                requirements_met = reqs_met(down_left[requires], backpack)
                if requirements_met:
                    down_left[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x - 1, ") requires ", end="")
                    print(down_left[requires])
        elif down_left[symbol] == DOOR:
            down_left[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
        if down_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x - 1, ")")
            down_left[symbol] = DOOR
    else:  # not in a corner or on an edge
        down_left = the_game_map[row_y + 1][column_x - 1]
        left = the_game_map[row_y][column_x - 1]
        up_left = the_game_map[row_y - 1][column_x - 1]
        above = the_game_map[row_y - 1][column_x]
        up_right = the_game_map[row_y - 1][column_x + 1]
        right = the_game_map[row_y][column_x + 1]
        below = the_game_map[row_y + 1][column_x]
        down_right = the_game_map[row_y + 1][column_x + 1]
        if requires in right:
            if right[symbol] == DOOR:  # door to the right
                requirements_met = reqs_met(right[requires], backpack)
                if requirements_met:
                    right[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x + 1, ") requires ", end="")
                    print(right[requires])
        elif right[symbol] == DOOR:
            right[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x + 1, ")")
        if right[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x + 1, ")")
            right[symbol] = DOOR
        if requires in left:
            if left[symbol] == DOOR:  # door to the left
                requirements_met = reqs_met(left[requires], backpack)
                if requirements_met:
                    left[symbol] = FLOOR
                    print("A door was opened at (", row_y, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y, ",", column_x - 1, ") requires ", end="")
                    print(left[requires])
        elif left[symbol] == DOOR:
            left[symbol] = FLOOR
            print("A door was opened at (", row_y, ",", column_x - 1, ")")
        if left[symbol] == SECRET:
            print("A secret was revealed at (", row_y, ",", column_x - 1, ")")
            left[symbol] = DOOR
        if requires in above:
            if above[symbol] == DOOR:  # door above
                requirements_met = reqs_met(above[requires], backpack)
                if requirements_met:
                    above[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x, ") requires ", end="")
                    print(above[requires])
        elif above[symbol] == DOOR:
            above[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x, ")")
        if above[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x, ")")
            above[symbol] = DOOR
        if requires in below:
            if below[symbol] == DOOR:  # door below
                requirements_met = reqs_met(below[requires], backpack)
                if requirements_met:
                    below[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x, ") requires ", end="")
                    print(below[requires])
        elif below[symbol] == DOOR:
            below[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x, ")")
        if below[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x, ")")
            below[symbol] = DOOR
        if requires in up_right:
            if up_right[symbol] == DOOR:  # door up right
                requirements_met = reqs_met(up_right[requires], backpack)
                if requirements_met:
                    up_right[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x + 1, ") requires ", end="")
                    print(up_right[requires])
        elif up_right[symbol] == DOOR:
            up_right[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x + 1, ")")
        if up_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x + 1, ")")
            up_right[symbol] = DOOR
        if requires in up_left:
            if up_left[symbol] == DOOR:  # door up left
                requirements_met = reqs_met(up_left[requires], backpack)
                if requirements_met:
                    up_left[symbol] = FLOOR
                    print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y - 1, ",", column_x - 1, ") requires ", end="")
                    print(up_left[requires])
        elif up_left[symbol] == DOOR:
            up_left[symbol] = FLOOR
            print("A door was opened at (", row_y - 1, ",", column_x - 1, ")")
        if up_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y - 1, ",", column_x - 1, ")")
            up_left[symbol] = DOOR
        if requires in down_right:
            if down_right[symbol] == DOOR:  # door down right
                requirements_met = reqs_met(down_right[requires], backpack)
                if requirements_met:
                    down_right[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x + 1, ") requires ", end="")
                    print(down_right[requires])
        elif down_right[symbol] == DOOR:
            down_right[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x + 1, ")")
        if down_right[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x + 1, ")")
            down_right[symbol] = DOOR
        if requires in down_left:
            if down_left[symbol] == DOOR:  # door down left
                requirements_met = reqs_met(down_left[requires], backpack)
                if requirements_met:
                    down_left[symbol] = FLOOR
                    print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
                else:
                    print("The door at (", row_y + 1, ",", column_x - 1, ") requires ", end="")
                    print(down_left[requires])
        elif down_left[symbol] == DOOR:
            down_left[symbol] = FLOOR
            print("A door was opened at (", row_y + 1, ",", column_x - 1, ")")
        if down_left[symbol] == SECRET:
            print("A secret was revealed at (", row_y + 1, ",", column_x - 1, ")")
            down_left[symbol] = DOOR


def reqs_met(requirements, backpack):  # finished
    """
    checks if backpack has all the requirements to open a door
    :param requirements: requirements to open a door
    :param backpack: contents of backpack
    :return: whether requirements are met
    """
    reqs = 0
    requirements_met = False

    for requirement in requirements:
        if requirement in backpack:
            reqs = reqs + 1
    if len(requirements) <= reqs:
        requirements_met = True
    return requirements_met


def play_game(game_map):  # finished
    """
    plays the game
    :param game_map: the game map
    """
    backpack = []
    y, x = get_start_position()
    winner = the_grid(game_map, y, x)

    while not winner:
        user_command = get_user_input()  # returns a movement command as a string
        if user_command == QUIT:
            print("You died.")
            winner = True
        else:
            while user_command != QUIT and (not winner):  # if the user entered wasd or e, move the dude
                if user_command == USE:  # if the user entered e, search
                    check_area(y, x, backpack)
                    winner = the_grid(game_map, y, x)
                    if not winner:
                        display_backpack(backpack)
                        user_command = get_user_input()
                else:  # if they entered wasd, move
                    player_position = stay_in_bounds(y, x, user_command)
                    y, x = player_position
                    backpack = pick_up_items(y, x, backpack)
                    winner = the_grid(game_map, y, x)
                    if not winner:
                        display_backpack(backpack)
                        user_command = get_user_input()
            if not winner:
                print("You died.")
                winner = True


def display_backpack(backpack):  # finished
    """
    displays contents of player backpack
    :param backpack: contents of backpack
    """
    print("Your inventory is:")
    for i in range(len(backpack)-1):
        print(backpack[i], end=", ")
    if len(backpack) != 0:
        print(backpack[-1])


def pick_up_items(y, x, backpack):  # finished
    """
    picks up item on the space the user is standing
    :param y: user row
    :param x: user column
    :param backpack: contents of backpack
    :return: contents of bakpack with new items
    """
    backpack.extend(the_game_map[y][x]["items"])
    the_game_map[y][x]["items"] = []
    the_game_map[y][x]["symbol"] = "_"
    return backpack


def get_user_input():  # finished
    """
    gets input from the user
    :return: command the user enters
    """
    command = input("Enter Move (wasd) (e to activate doors or secrets) (q to quit): ")
    command = command.strip().lower()
    commands = ["w", "a", "s", "d", USE, QUIT]
    while command not in commands:
        print("Invalid input")
        command = input("Enter Move (wasd) (e to activate doors or secrets) (q to quit): ")
        command = command.strip().lower()
    return command


def get_start_position():  # finished
    """
    looks for start position in map file
    :return: position to start the player at
    """
    for row_y in range(len(the_game_map)):
        for grid_square_x in range(len(the_game_map[row_y])):
            if STARTING_LOCATION in the_game_map[row_y][grid_square_x]:
                if the_game_map[row_y][grid_square_x][STARTING_LOCATION]:
                    print("there")  # t b r
                    player_position = [row_y, grid_square_x]
                    print(player_position)  # t b r
                    return player_position
    player_position = [0, 0]
    return player_position


def find_corners(y, x):  # finished
    """
    checks if the user is in a corner of the map
    :param y: user row
    :param x: user column
    :return: boolean values for whether the user is in each of the corners
    """
    bottom_right = False
    bottom_left = False
    top_right = False
    top_left = False
    if (y, x) == (len(the_game_map)-1, len(the_game_map[0])-1):  # bottom right corner
        bottom_right = True
    elif (y, x) == (0, 0):  # top left corner
        top_left = True
    elif (y, x) == (len(the_game_map)-1, 0):  # bottom left corner
        bottom_left = True
    elif (y, x) == (0, len(the_game_map[0])-1):
        top_right = True
    return [bottom_right, bottom_left, top_right, top_left]


def find_edges(y, x):  # finished
    """
    checks whether the user is on an edge of the board but not a corner
    :param y: user row
    :param x: user column
    :return: boolean values for whether the user is on an edge of the board but not a corner
    """
    right_edge = False
    left_edge = False
    top_edge = False
    bottom_edge = False
    if y == 0:
        if x != 0 and x != (len(the_game_map[0]) - 1):
            top_edge = True
    if y == (len(the_game_map) - 1):
        if x != 0 and x != (len(the_game_map[0]) - 1):
            bottom_edge = True
    if x == 0:
        if y != 0 and y != (len(the_game_map) - 1):
            left_edge = True
    if x == (len(the_game_map[0]) - 1):
        if y != 0 and y != (len(the_game_map) - 1):
            right_edge = True
    return [right_edge, left_edge, top_edge, bottom_edge]


if __name__ == '__main__':
    map_file_name = input('What map do you want to load? ')
    the_game_map = load_map(map_file_name)
    if the_game_map:
        play_game(the_game_map)