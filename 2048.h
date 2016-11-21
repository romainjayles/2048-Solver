#ifndef _2048_H_
#define _2048_H_

#include <stdbool.h>

struct grid{
  int grid[16];
  bool blocked_left;
  bool blocked_right;
  bool blocked_down;
  bool blocked_up;
  bool blocked;
};

typedef enum {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN
}move_type;

int init_grid(struct grid* grid);
void free_grid(struct grid* grid);

bool move_left(struct grid *base_grid, struct grid *result_grid);
bool move_right(struct grid *base_grid, struct grid *result_grid);
bool move_up(struct grid *base_grid, struct grid *result_grid);
bool move_down(struct grid *base_grid, struct grid *result_grid);
void print_grid(struct grid *grid, bool print_state);

void put_random_tile(struct grid* base_grid, struct grid *result_grid);

int count_free_tile(struct grid *base_grid);

#endif
