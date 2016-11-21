#include "minimax_solver.h"
#include "2048.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

move_type compute_best_move(struct grid* grid, int depth){
  //return move ?
  struct node root;
  root.grid = *grid;

  compute_best_move_play(&root, depth);
  return root.best_move;
}

float compute_best_move_play(struct node* node, int depth){
  // We have to compute the heuristic
  struct grid *base_grid = &(node->grid);
  float max_value = -1, prev_max_value = -1;
  float computed_value;
  int i;
  int max_i;
  
  if(depth == -1){
    return compute_heuristic(base_grid);
  }
  node->node_child = malloc(4*sizeof(struct node));
  
  node->node_child[0].possible = move_left(base_grid, &(node->node_child[0].grid));
  node->node_child[1].possible = move_right(base_grid, &(node->node_child[1].grid));
  node->node_child[2].possible = move_up(base_grid, &(node->node_child[2].grid));
  node->node_child[3].possible = move_down(base_grid, &(node->node_child[3].grid));

  for(int i=0; i<4; i++){
    if(node->node_child[i].possible){
      computed_value = MAX(compute_best_move_put_tile(&node->node_child[0], depth-1), max_value);
    }else{
      computed_value = -1;
    }
    prev_max_value = max_value;
    max_value = MAX(max_value, computed_value);
    if(prev_max_value < max_value){
      max_i = i;
    }
    //if(depth == 4)
    //printf("%i - %f\n", i, MAX(compute_best_move_put_tile(&node->node_child[0], depth-1), max_value));
  }
  node->value = max_value;
  switch(max_i){
  case 0:
    node->best_move = MOVE_LEFT;
    break;
  case 1:
    node->best_move = MOVE_RIGHT;
    break;
  case 2:
    node->best_move = MOVE_UP;
    break;
  case 3:
    node->best_move = MOVE_DOWN;
    break;
  }

  free(node->node_child);
  return max_value;
}

float compute_best_move_put_tile(struct node* node, int depth){
  // We have to compute the heuristic
  int free_tile,i;
  float value = 0;
  struct grid *base_grid;
  if(depth == -1){
    return compute_heuristic(&(node->grid));
  }
  // We can go deeper in the expectimax evaluation
  base_grid = &(node->grid);
  free_tile = count_free_tile(base_grid);

  // We will create two nodes for a free tile
  free_tile *= 2;
  node->node_child = malloc(free_tile*sizeof(struct node));
  for(i=0; i<free_tile;i++){
    memcpy(&(node->node_child[i].grid), &(node->grid),sizeof(struct grid));
  }
  // We have to scale from [1, free_tile] to [0, free_tile-1], in order to use it in array
  free_tile--;
  for(i=0; i<16;i++){
    if(base_grid->grid[i] == 0){
      node->node_child[free_tile].grid.grid[i] = 2;
      value += 0.9*compute_best_move_play(&(node->node_child[free_tile]), depth-1);
      free_tile--;
      
      node->node_child[free_tile].grid.grid[i] = 4;
      value += 0.1*compute_best_move_play(&(node->node_child[free_tile]), depth-1);
      free_tile--;
    }
  }
  node->value = value;
  // We destruct the tree when we have the value we need
  free(node->node_child);
  return value;
  
}

float compute_heuristic(struct grid *grid){
  float value = 0;
  float array[16] = {0,1,2,3,
		     7,6,5,4,
		     8,9,10,11,
		     15,14,13,12};
  int i;
  for(i=0; i<16; i++){
    value += array[i]*grid->grid[i];
  }
  return value;
}
