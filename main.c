#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "2048.h"

#define INTERACTIVE true




int main(int argc, char **argv){
  int interactive = INTERACTIVE;
  int i;
  struct grid main_grid;
  struct grid move_grid;
  init_grid(&main_grid);
  /*main_grid.grid[0] = 0;
  main_grid.grid[1] = 0;
  main_grid.grid[2] = 2;
  main_grid.grid[3] = 0;
  
  main_grid.grid[4] = 0;
  main_grid.grid[5] = 2;
  main_grid.grid[6] = 0;
  main_grid.grid[7] = 2;

  main_grid.grid[8] = 2;
  main_grid.grid[9] = 2;
  main_grid.grid[10] = 4;
  main_grid.grid[11] = 8;

  main_grid.grid[12] = 2;
  main_grid.grid[13] = 4;
  main_grid.grid[14] = 8;
  main_grid.grid[15] = 16;*/
  put_random_tile(&main_grid, &main_grid);
  print_grid(&main_grid, false);
  while(1){
    scanf(" %i", &i);
    move_down(&main_grid, &main_grid);
    put_random_tile(&main_grid, &main_grid);
    print_grid(&main_grid, false);
  }
  
  print_grid(&main_grid, true);
  move_down(&main_grid, &move_grid);
  print_grid(&move_grid, true);
  move_down(&move_grid, &move_grid);
  print_grid(&move_grid, true);
  move_right(&move_grid, &move_grid);
  print_grid(&move_grid, true);
  return 0;
}


