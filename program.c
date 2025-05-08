#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void cursor_move(char ch, int LINES, int COLS, int y, int x) {
  // Обработка ввода
  switch(ch) {
      case KEY_UP:    y = y > 0 ? y - 1 : 0; break;
      case 'w':       y = y > 0 ? y - 1 : 0; break;
      case KEY_DOWN:  y = y < LINES-4 ? y + 1 : LINES-4; break;
      case 's':       y = y < LINES-4 ? y + 1 : LINES-4; break;
      case KEY_LEFT:  x = x > 0 ? x - 1 : 0; break;
      case 'a':       x = x > 0 ? x - 1 : 0; break;
      case KEY_RIGHT: x = x < COLS-1 ? x + 1 : COLS-1; break;
      case 'd':       x = x < COLS-1 ? x + 1 : COLS-1; break;
  }
  mvaddch(LINES-2, COLS-1, ch);
  // printf("%c", ch);

}

int main() {
    int ch;
    char str[16];
    int x = 0, y = 0;
    char string[] = __FILE__;

    // Инициализация ncurses
    initscr();
    raw();                  // Отключаем буферизацию ввода
    keypad(stdscr, TRUE);   // Включаем обработку функциональных клавиш
    noecho();               // Отключаем отображение вводимых символов
    curs_set(0);            // Скрываем курсор

    // Проверка и инициализация цветов
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
    }

    // Вывод инструкций
    mvprintw(LINES - 2, 0, "Use arrows or WASD for moving. Q for quit.");

    // Основной цикл
    while ((ch = getch()) != 'q') {
        // Очистка экрана
        clear();

        cursor_move(ch, LINES, COLS, y, x);

        // Рисуем персонаж с изменяющимся цветом
        if (has_colors()) {
            attron(COLOR_PAIR((x + y) % 3 + 1));
        }
        mvaddch(y, x, '@');

        // Рисуем границу
        for (int i = 0; i < COLS; i++) {
            mvaddch(LINES - 3, i, '-');
        }

        for (int j = 0; j < sizeof(string)-1; j++) {
            char charer = string[j];
            mvaddch(LINES - 2, j, charer);
        }

        // Обновляем экран
        refresh();
    }

    // Завершение работы
    endwin();
    return 0;
}
