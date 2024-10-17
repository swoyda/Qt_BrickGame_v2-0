#include "main.h"

#include <ncurses.h>
void menu();

void snake_start() { s21::Controller a; }
/*!

    \brief Точка входа в игровую консоль
*/
int main() {
  menu();
  return 0;
}

void menu() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  WINDOW* my_win = newwin(HEIGHT, WIDTH /*WIDTH*/, 0, 0);
  box(my_win, 0, 0);
  const char* choices[] = {"Tetris", "Snake", "EXIT"};
  char input;
  int on_choise = 0;
  int n_choices = 2;
  while (input != 'q') {
    for (int i = 0; i < 3; ++i) {
      if (i == on_choise) {
        wattron(my_win, A_REVERSE);
      }
      mvwaddstr(my_win, i + 1, 1, choices[i]);
      wattroff(my_win, A_REVERSE);
    }
    input = getch();
    if (input == DOWN) {
      on_choise = (on_choise == n_choices) ? 0 : on_choise + 1;
    } else if (input == UP) {
      on_choise = (on_choise == 0) ? n_choices : on_choise - 1;
    } else if (input == 10) {
      if (on_choise == 1) {
        snake_start();
      } else if (on_choise == 0) {
        clear();
        game_tetris();
        clear();
        endwin();
      } else {
        input = 'q';
      }
    }
    wrefresh(my_win);
  }

  clear();
  endwin();
  // wrefresh(my_win);
}
