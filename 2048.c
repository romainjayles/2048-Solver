#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "2048.h"


int init_grid(struct grid* grid){
  time_t t;
  memset(grid->grid, 0, sizeof(struct grid));
  grid->blocked_left = false;
  grid->blocked_right = false;
  grid->blocked_down = false;
  grid->blocked_up = false;
  srand((unsigned) time(&t));
}

void free_grid(struct grid* grid){
  free(grid);
}

int move_left(struct grid *base_grid, struct grid *result_grid){
  memcpy(result_grid, base_grid, sizeof(struct grid));
  int *grid = result_grid->grid;
  result_grid->blocked_left = true;
  int i,j, k, current_cell;
  for(j=0; j<4; j++){
    for(i=0; i<4; i++){
      //The value is 0, we go further
      if(grid[i+j*4] != 0){
	//This is not the begining of the line
	if(i != 0){
	  //The left spot is not empty
	  if(grid[i-1+j*4] != 0){
	    if(grid[i-1+j*4] == grid[i+j*4]){
	      grid[i-1+j*4] *= 2;
	      grid[i+j*4] = 0;
	      for(k = i+1; k < 4; k++){
		grid[k-1+j*4] = grid[k+j*4];
	      }
	      grid[3+j*4] = 0;
	      i++;
	      result_grid->blocked_left = false;
	    }
	  }else{
	    for(k = i; k < 4; k++){
	      grid[k-1+j*4] = grid[k+j*4];
	      //grid[k+j*4] = 0;
	    }
	    grid[3+j*4] = 0;
	    i-=2; // i will be incremented, we have to take care of that
	    result_grid->blocked_left = false;
	  }
	}
      }
    }
  }
}

int move_right(struct grid *base_grid, struct grid *result_grid){
  memcpy(result_grid, base_grid, sizeof(struct grid));
  int *grid = result_grid->grid;
  result_grid->blocked_right = true;
  int i,j, k, current_cell;
  for(j=0; j<4; j++){
    for(i=3; i>=0; i--){
      //The value is 0, we go further
      if(grid[i+j*4] != 0){
	//This is not the begining of the line
	if(i != 3){
	  //The left spot is not empty
	  if(grid[i+1+j*4] != 0){
	    if(grid[i+1+j*4] == grid[i+j*4]){
	      grid[i+1+j*4] *= 2;
	      grid[i+j*4] = 0;
	      for(k = i-1; k >= 0; k--){
		grid[k+1+j*4] = grid[k+j*4];
	      }
	      grid[0+j*4] = 0;
	      i--;
	      result_grid->blocked_right = true;
	    }
	  }else{
	    for(k = i; k >= 0; k--){
	      grid[k+1+j*4] = grid[k+j*4];
	      //grid[k+j*4] = 0;
	    }
	    grid[0+j*4] = 0;
	    i+=2; // i will be incremented, we have to take care of that
	    result_grid->blocked_right = false;
	  }
	}
      }
    }
  }
}

int move_up(struct grid *base_grid, struct grid *result_grid){
  memcpy(result_grid, base_grid, sizeof(struct grid));
  int *grid = result_grid->grid;
  result_grid->blocked_up = true;
  int i,j, k, current_cell;
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      //The value is 0, we go further
      if(grid[i+j*4] != 0){
	//This is not the begining of the line
	if(j != 0){
	  //The left spot is not empty
	  if(grid[i+(j-1)*4] != 0){
	    if(grid[i+(j-1)*4] == grid[i+j*4]){
	      grid[i+(j-1)*4] *= 2;
	      grid[i+j*4] = 0;
	      for(k = j+1; k < 4; k++){
		grid[i+(k-1)*4] = grid[i+k*4];
	      }
	      grid[i+3*4] = 0;
	      j++;
	      result_grid->blocked_up = false;
	    }
	  }else{
	    for(k = j; k < 4; k++){
	      grid[i+(k-1)*4] = grid[i+(k)*4];
	      //grid[k+j*4] = 0;
	    }
	    grid[i+3*4] = 0;
	    j-=2; // i will be incremented, we have to take care of that
	    result_grid->blocked_up = false;
	  }
	}
      }
    }
  }
}

int move_down(struct grid *base_grid, struct grid *result_grid){
    memcpy(result_grid, base_grid, sizeof(struct grid));
  int *grid = result_grid->grid;
  result_grid->blocked_down = true;
  int i,j, k, current_cell;
  for(i=0; i<4; i++){
    for(j=3; j>=0; j--){
      //The value is 0, we go further
      if(grid[i+j*4] != 0){
	//This is not the begining of the line
	if(j != 3){
	  //The left spot is not empty
	  if(grid[i+(j+1)*4] != 0){
	    if(grid[i+(j+1)*4] == grid[i+j*4]){
	      grid[i+(j+1)*4] *= 2;
	      grid[i+j*4] = 0;
	      for(k = j-1; k >= 0; k--){
		grid[i+(k+1)*4] = grid[i+(k)*4];
	      }
	      grid[i+0*4] = 0;
	      j--;
	      result_grid->blocked_down = true;
	    }
	  }else{
	    for(k = j; k >= 0; k--){
	      grid[i+(k+1)*4] = grid[i+k*4];
	      //grid[k+j*4] = 0;
	    }
	    grid[i+0*4] = 0;
	    j+=2; // i will be incremented, we have to take care of that
	    result_grid->blocked_down = false;
	  }
	}
      }
    }
  }
}

void put_random_tile(struct grid* base_grid, struct grid *result_grid){
  int i, empty_tile_cnt = 0, tile_to_put = 0;
  int *grid_array = base_grid->grid;
  for(i=0; i<16; i++){
    if(grid_array[i] == 0){
      empty_tile_cnt++;
    }
  }
  tile_to_put = rand() % empty_tile_cnt + 1;
  for(i=0; i<16; i++){
    if(grid_array[i] == 0){
      if(--tile_to_put == 0){
	grid_array[i] = rand()%10 < 9 ? 2 : 4;
      }
    }
  }
}

void print_grid(struct grid *grid, bool print_state){
  printf("--------------------\n");
  for(int j=0; j<4; j++){
    for(int i=0; i<4;i++){
      printf("%i    ", grid->grid[i+j*4]);
    }
    printf("\n\n");
  }
  printf("\n");
  if(print_state){
    printf("Grid is %s\n", grid->blocked_left ? " blocked left": " free left");
    printf("Grid is %s\n", grid->blocked_right ? " blocked right": " free right");
    printf("Grid is %s\n", grid->blocked_up ? " blocked up": " free up");
    printf("Grid is %s\n", grid->blocked_down ? " blocked down": " free down");
  }
  printf("--------------------\n");
}
