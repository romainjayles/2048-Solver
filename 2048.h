#ifndef _2048_H_
#define _2048_H_

struct grid{
  int grid[16];
  bool blocked_left;
  bool blocked_right;
  bool blocked_down;
  bool blocked_up;
  bool blocked;
};

int init_grid(struct grid* grid);
void free_grid(struct grid* grid);

int move_left(struct grid *base_grid, struct grid *result_grid);
int move_right(struct grid *base_grid, struct grid *result_grid);
int move_up(struct grid *base_grid, struct grid *result_grid);
int move_down(struct grid *base_grid, struct grid *result_grid);
void print_grid(struct grid *grid, bool print_state);

void put_random_tile(struct grid* base_grid, struct grid *result_grid);

#endif
