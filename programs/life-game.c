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
#include <unistd.h>

/* Alter the frame rate to accelerate state changes. */
#define FRAMERATE 6
#define MS_IN_SECOND 1000000
#define DELTA_TIME (MS_IN_SECOND / FRAMERATE)

/* This grid looks like a square in my terminal with my current font.
 * Alter values to modify the grid extension. */
#define GRID_HEIGHT 16
#define GRID_WIDTH 40

#define ALIVE '*'
#define DEAD '.'


/* Remaps a cell position in an acceptable value that make
 * moving cells wrapping around and continue from the other side.
 * In this way we simulate an infinite grid. */
int cell_to_index(int x, int y) {
  x = (x + GRID_HEIGHT) % GRID_HEIGHT;
  y = (y + GRID_WIDTH) % GRID_WIDTH;
  return x * GRID_WIDTH + y;
}

char get_cell(char *grid, int x, int y) {
  return grid[cell_to_index(x, y)];
}

void set_cell(char *grid, int x, int y, char state) {
  grid[cell_to_index(x, y)] = state;
}

/* Function that redraws the whole grid. */
void draw(char *grid) {

  // Clears the screen
  printf("\033[H\033[J");

  for (int x = 0; x < GRID_HEIGHT; x++) {
    for (int y = 0; y < GRID_WIDTH; y++) {
      printf("%c", get_cell(grid, x, y));
    }

    printf("\n");
  }

  return;
}

/* Sets up the initial state of the grid. */
void fill_grid(char *grid, char state) {

  for (int x = 0; x < GRID_HEIGHT; x++) {
    for (int y = 0; y < GRID_WIDTH; y++) {
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
  for (int x = 0; x < GRID_HEIGHT; x++) {
    for (int y = 0; y < GRID_WIDTH; y++) {

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
  char grid[GRID_WIDTH * GRID_HEIGHT];
  char new_grid[GRID_WIDTH * GRID_HEIGHT];

  fill_grid(grid, DEAD);

  set_cell(grid, 3, 10, ALIVE);
  set_cell(grid, 3, 11, ALIVE);
  set_cell(grid, 3, 12, ALIVE);
  set_cell(grid, 3, 13, ALIVE);
  set_cell(grid, 3, 14, ALIVE);
  set_cell(grid, 3, 15, ALIVE);

  set_cell(grid, 7, 17, ALIVE);
  set_cell(grid, 7, 18, ALIVE);
  set_cell(grid, 7, 19, ALIVE);
  set_cell(grid, 7, 20, ALIVE);
  set_cell(grid, 7, 21, ALIVE);
  set_cell(grid, 7, 22, ALIVE);

  game_loop(grid, new_grid);

  return 0;
}

