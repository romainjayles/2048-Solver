#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "2048.h"
#include "minimax_solver.h"

//#define INTERACTIVE

int main(int argc, char **argv){
  char ch1, ch2, ch3;
  struct grid main_grid;
  bool move_sucess;
  move_type move;
  
  init_grid(&main_grid);
  put_random_tile(&main_grid, &main_grid);
  
  print_grid(&main_grid, false);
  while(1){
    #ifdef INTERACTIVE
    do{
      ch3 = ch2;
      ch2 = ch1;
      ch1 = fgetc(stdin);
    }while (!(ch3 == 27 && ch2== 91 && (ch1 == 68 || ch1 == 67 || ch1 == 66 | ch1 == 65)));
    clearerr(stdin);
    switch(ch1){
    case 68:
      move = MOVE_LEFT;
      break;
    case 67:
      move = MOVE_RIGHT;
      break;
    case 66:
      move = MOVE_DOWN;
      break;
    case 65:
      move = MOVE_UP;
      break;
    }
    #else
    move = compute_best_move(&main_grid, 5);
    #endif
    switch(move){
    case MOVE_LEFT:
      move_sucess = move_left(&main_grid, &main_grid);
      break;
    case MOVE_RIGHT:
      move_sucess = move_right(&main_grid, &main_grid);
      break;
    case MOVE_UP:
      move_sucess = move_up(&main_grid, &main_grid);
      break;
    case MOVE_DOWN:
      move_sucess = move_down(&main_grid, &main_grid);
      break;
    }
    if(!move_sucess){
      printf("This move is impossible\n");
    }else{
      put_random_tile(&main_grid, &main_grid);
    }
    
    print_grid(&main_grid, false);
  }
  
  return 0;
}


