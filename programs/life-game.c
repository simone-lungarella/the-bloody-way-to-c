/* Conway's game of life is a simple game that take place in an infinite two dimensional universe
 * and produce particles living and dying while applying a few simple rules:
 *
 * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation;
 * 2. Any live cell with two or three live neighbours lives on to the next generation;
 * 3. Any live cell with more than three live neighbours dies, as if by overpopulation;
 * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 * 
 * Starting from a specific system state, the game produce many interesting scenarios. This program
 * reproduce them in a simple matrix in the terminal. The code is highly inspired by Salvatore Sanfilippo. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Alter the frame rate to accelerate state changes. */
#define FRAMERATE 4
#define MS_IN_SECOND 1000000
#define DELTA_TIME (MS_IN_SECOND / FRAMERATE)

/* This grid looks like a square in my terminal with my current font.
 * Alter values to modify the grid extension. */
#define GRID_WIDTH 16
#define GRID_HEIGHT 40

#define ALIVE '*'
#define DEAD '.'


/* Remaps a cell position in an acceptable value that make
 * moving cells wrapping around and continue from the other side.
 * In this way we simulate an infinite grid. */
int cell_to_index(int x, int y) {
  if (x < 0) {
    x = (-x) % GRID_WIDTH;
    x = GRID_WIDTH - x;
  }

  if (y < 0) {
    y = (-y) % GRID_HEIGHT;
    y = GRID_HEIGHT - y;
  }

  if (x >= GRID_WIDTH) x = x % GRID_WIDTH;
  if (y >= GRID_HEIGHT) y = y % GRID_HEIGHT;

  return y * GRID_WIDTH + x;
}

char get_cell(char *grid, int x, int y) {
  return grid[cell_to_index(x, y)];
}

void set_cell(char *grid, int x, int y, char state) {
  grid[cell_to_index(x, y)] = state;
}

/* Function that redraws the whole grid. */
void draw(char *grid) {

  system("clear");

  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
      printf("%c", get_cell(grid, x, y));
    }

    printf("\n");
  }

  return;
}

/* Sets up the initial state of the grid. */
void fill_grid(char *grid, char state) {

  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
      set_cell(grid, x, y, state);
    }
  }
}

/* Returns the number of living neighbours of a given cell. */
int count_neighbors(char *grid, int x, int y) {
  int living_neighbors = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {

      if (i == 0 && j == 0) {
        // Skipping central cell as not part of neighbours.
        continue;
      }

      if (get_cell(grid, x + i, y + j) == ALIVE) {
        living_neighbors++;
      }
    }
  }

  return living_neighbors;
}

/* Creates a new grid updating cell state following the rules. */
void update_new_grid(char *grid, char *new_grid) {
  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {

      int living_neighbors = count_neighbors(grid, x, y);
      char new_state = DEAD;

      if (get_cell(grid, x, y) == ALIVE) {
        if (living_neighbors == 2 || living_neighbors == 3) {
          new_state = ALIVE;
        }
      } else if (living_neighbors == 3) {
        new_state = ALIVE;
      }

      set_cell(new_grid, x, y, new_state);
    }
  }

}

void game_loop(char *grid, char *new_grid) {

  while(1) {
    update_new_grid(grid, new_grid);
    draw(new_grid);

    usleep(DELTA_TIME);

    // Swap grid buffers
    char *temp = grid;
    grid = new_grid;
    new_grid = temp;
  }
}

int main(void) {

  /* Setup starting system state. */
  char grid[GRID_HEIGHT * GRID_WIDTH];
  char new_grid[GRID_HEIGHT * GRID_WIDTH];

  fill_grid(grid, DEAD);

  set_cell(grid, 5, 5, ALIVE); set_cell(grid, 2, 5, ALIVE);
  set_cell(grid, 5, 6, ALIVE); set_cell(grid, 2, 6, ALIVE);
  set_cell(grid, 17, 8, ALIVE); set_cell(grid, 16, 8, ALIVE);
  set_cell(grid, 22, 6, ALIVE); set_cell(grid, 22, 7, ALIVE);
  set_cell(grid, 21, 5, ALIVE); set_cell(grid, 23, 5, ALIVE);

  game_loop(grid, new_grid);

  return 0;
}

