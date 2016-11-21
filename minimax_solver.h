#ifndef _MINIMAX_SOLVER_H_
#define _MINIMAX_SOLVER_H_

#include "2048.h"

struct node{
  struct grid grid;
  float value;
  bool possible;
  move_type best_move;
  // For a player node, we will have the following structure:
  //node_child[0] will be left move
  //node_child[1] will be right move
  //node_child[2] will be up move
  //node_child[3] will be down move
  struct node *node_child;
};

move_type compute_best_move(struct grid* grid, int depth);

float compute_best_move_play(struct node* node, int depth);

float compute_best_move_put_tile(struct node* node, int depth);

float compute_heuristic(struct grid *grid);

#endif
