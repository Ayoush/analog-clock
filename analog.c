// simple analog clock.
// under the mit license or something i dunno use it

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <ncurses.h>

int kbhit();

int main() {
        time_t rawt = time(NULL);
        struct tm *timeinfo;

        timeinfo = localtime(&rawt);

        int hour, min, sec;
        int Xmax, Ymax;
        int i;

        initscr();
        raw();
        if (has_colors() == FALSE) {
                endwin();
                printf("You need to have color support to use this program.\n");
                return 1;
        }
        start_color();
        noecho();
        curs_set(0);

        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);


        getmaxyx(stdscr, Ymax, Xmax);

        WINDOW *analog = newwin(9, 19, (Ymax - 9) / 2, (Xmax - 19) / 2);
        wattron(analog, COLOR_PAIR(1));
        wattron(analog, A_BOLD);
        wborder(analog, '|', '|', '-', '-', '/', '\\', '\\', '/');
        wattroff(analog, COLOR_PAIR(1));
        wattroff(analog, A_BOLD);

        wattron(analog, COLOR_PAIR(2));
        mvwprintw(analog, 4, 9, "O");
        wattroff(analog, COLOR_PAIR(2));
        
        int processed_time;
        int j;
        loop:while (!kbhit()) {
                for (j = 0; j < 7; j++) {
                        mvwprintw(analog, j+1, 1, "                 ");
                }
                wattron(analog, COLOR_PAIR(2));
                mvwprintw(analog, 4, 9, "O");
                wattroff(analog, COLOR_PAIR(2));
                rawt = time(NULL);
                timeinfo = localtime(&rawt);
                wattron(analog, COLOR_PAIR(3));
                mvwprintw(analog, 1, 9, "12");
                mvwprintw(analog, 1, 5, "11");
                mvwprintw(analog, 2, 1, "10");
                mvwprintw(analog, 4, 1, "9");
                mvwprintw(analog, 6, 1, "8");
                mvwprintw(analog, 7, 5, "7");
                mvwprintw(analog, 7, 9, "6");
                mvwprintw(analog, 7, 13, "5");
                mvwprintw(analog, 6, 17, "4");
                mvwprintw(analog, 4, 17, "3");
                mvwprintw(analog, 2, 17, "2");
                mvwprintw(analog, 1, 13, "1");

                wattroff(analog, COLOR_PAIR(3));
                wattron(analog, A_BOLD);
                for (i = 0; i <3; i++) {
                        switch (i) {
                                case 0:
                                        wattron(analog, COLOR_PAIR(2));
                                        processed_time = timeinfo->tm_hour % 12;
                                        break;
                                case 1:
                                        wattron(analog, COLOR_PAIR(3));
                                        processed_time = timeinfo->tm_min / 5 % 12;
                                        break;
                                case 2:
                                        wattron(analog, COLOR_PAIR(4));
                                        processed_time = timeinfo->tm_sec / 5 % 12;
                                        break;
                        }

                        switch (processed_time) {
                                case 0:
                                        mvwprintw(analog, 1, 9, "|");
                                        mvwprintw(analog, 2, 9, "|");
                                        mvwprintw(analog, 3, 9, "|");
                                        break;
                                case 1:
                                        mvwprintw(analog, 1, 12, "/");
                                        mvwprintw(analog, 2, 11, "/");
                                        mvwprintw(analog, 3, 10, "/");
                                        break;
                                case 2:
                                        mvwprintw(analog, 3, 14, "/");
                                        mvwprintw(analog, 3, 13, "_");
                                        mvwprintw(analog, 3, 12, "_");
                                        mvwprintw(analog, 4, 11, "/");
                                        mvwprintw(analog, 4, 10, "-");
                                        break;
                                case 3:
                                        mvwprintw(analog, 4, 10, "------");
                                        break;
                                case 4:
                                        mvwprintw(analog, 6, 14, "\\");
                                        mvwprintw(analog, 5, 13, "_");
                                        mvwprintw(analog, 5, 12, "_");
                                        mvwprintw(analog, 5, 11, "\\");
                                        mvwprintw(analog, 4, 10, "_");
                                        break;
                                case 5:
                                        mvwprintw(analog, 5, 10, "\\");
                                        mvwprintw(analog, 6, 11, "\\");
                                        mvwprintw(analog, 7, 12, "\\");
                                        break;
                                case 6:
                                        mvwprintw(analog, 5, 9, "|");
                                        mvwprintw(analog, 6, 9, "|");
                                        mvwprintw(analog, 7, 9, "|");
                                        break;
                                case 7:
                                        mvwprintw(analog, 5, 8, "/");
                                        mvwprintw(analog, 6, 7, "/");
                                        mvwprintw(analog, 7, 6, "/");
                                        break;
                                case 8:
                                        mvwprintw(analog, 4, 8, "_");
                                        mvwprintw(analog, 5, 7, "/");
                                        mvwprintw(analog, 5, 6, "_");
                                        mvwprintw(analog, 6, 5, "/");
                                        mvwprintw(analog, 6, 4, "_");
                                        break;
                                case 9:
                                        mvwprintw(analog, 4, 3, "------");
                                        break;
                                case 10:
                                        mvwprintw(analog, 4, 8, "_");
                                        mvwprintw(analog, 4, 7, "\\");
                                        mvwprintw(analog, 3, 6, "_");
                                        mvwprintw(analog, 3, 5, "\\");
                                        mvwprintw(analog, 2, 4, "\\");
                                        break;
                                case 11:
                                        mvwprintw(analog, 1, 6, "\\");
                                        mvwprintw(analog, 2, 7, "\\");
                                        mvwprintw(analog, 3, 8, "\\");
                                        break;
                                default:
                                        break;
                        }
                }
                wattroff(analog, COLOR_PAIR(2));
                wattroff(analog, COLOR_PAIR(3));
                wattroff(analog, COLOR_PAIR(4));
                wattroff(analog, A_BOLD);
                mvprintw((Ymax / 2) + 4, (Xmax / 2) - 4, "%02d:%02d:%02d   ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
                refresh();
                wrefresh(analog);
        }


        switch (getch()) {
                case 'q':
                case 3:
                        endwin();
                        return 0;
                default:
                        goto loop;
        }
        refresh();
        wrefresh(analog);
        endwin();
        return 0;
}

int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

