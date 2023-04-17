# cub3D
Learning proyect - 42 Málaga 

## Description

This project is inspired by the world renowned Wolfenstein 3D, the first FPS ever created. It allows to explore the technique of ray-casting. The goal is to create a dynamic view inside a maze.

This proyect was developed in collaboration with [IcaroJam](https://www.github.com/IcaroJam)

## How to use

$> ./cube3D map.cub

The map are composed of: 0 for an empty space, 1 for a wall and N, S, E and W for the starting position of the player and its initial orientation.

Also the map will have the following:

NO ./path_to_north_texture

SO ./path_to_south_texture

EA ./path_to_east_texture

WE ./path_to_west_texture

F 220,100,0

C 225,30,0

* F is for floor color
* C is for ceiling color

The W, A, S and D are used to move the point of view through the labyrinth.

Left and right arrow or the mouse to look towards the left or right in the maze

Press the ESC key to close the window and the program.
