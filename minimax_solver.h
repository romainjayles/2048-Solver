#ifndef _MINIMAX_SOLVER_H_
#define _MINIMAX_SOLVER_H_

#include "2048.h"

struct node{
  struct node *node_left;
  struct node *node_right;
  struct node *node_up;
  struct node *node_down;
};

move_type compute_best_move(struct grid* grid);

float compute_heuristic(struct grid *grid);

#endif
