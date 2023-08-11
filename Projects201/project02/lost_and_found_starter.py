"""
    Starter code for Lost and Found Project 2, CMSC 201 Fall 2021
"""

import json


USE = 'e'
EMPTY = ''
FLOOR = '_'
EXIT = 'X'
DOOR = 'D'
SECRET = 'S'
WALL = '*'
ITEMS = 'i'
STARTING_LOCATION = 'start'


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


if __name__ == '__main__':
    map_file_name = input('What map do you want to load? ')
    the_game_map = load_map(map_file_name)
    if the_game_map:
        # call your function now with the_game_map as a parameter.
        pass  # delete me as soon as you can
