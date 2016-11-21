#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "2048.h"

#define INTERACTIVE true




int main(int argc, char **argv){
  int interactive = INTERACTIVE;
  int i;
  char ch1, ch2, ch3;
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
    do{
      ch3 = ch2;
      ch2 = ch1;
      ch1 = fgetc(stdin);
      //printf("\n%i - %i - %i \n", ch3, ch2, ch1);
    }while (!(ch3 == 27 && ch2== 91 && (ch1 == 68 || ch1 == 67 || ch1 == 66 | ch1 == 65)));
    clearerr(stdin);
    switch(ch1){
    case 68:
      printf("Left\n");
      move_left(&main_grid, &main_grid);
      break;
    case 67:
      printf("Right\n");
      move_right(&main_grid, &main_grid);
      break;
    case 66:
      printf("down\n");
      move_down(&main_grid, &main_grid);
      break;
    case 65:
      printf("Up\n");
      move_up(&main_grid, &main_grid);
      break;
    }
    
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


