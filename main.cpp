#include <iostream>
#include <ncurses.h>


using namespace std;

bool game_over = false;
int score = 0;

class point{
    int x,y;
    public:
        void point(int x_init,int y_init) : x(x_init), y(y_init) {x=0; y=0;}
}

enum direction{
    up;
    down;
    left;
    right;
}

class snake{
    point head {};
    int tail_x, tail_y;
    direction move = right;
}
// coordinates
int scr_x, scr_y;

int snake_size=3;
int fruit_x, fruit_y;

void userInput()
{
        switch(getch()) // Get character
        {
            case 'a':
                currentDirection = LEFT;
                break;
            case 'd':
                currentDirection = RIGHT;
                break;
            case 'w':
                currentDirection = UP;
                break;
            case 's':
                currentDirection = DOWN;
                break;
            case 'k':
                game_over = true;
                break;
        }
}
void draw{
    
}


int main() {
    initscr();
    getmaxyx(stdscr,scr_y,scr_x);
    if(scr_y < 10 && scr_x < 10)
    while (!game_over)
    {
        draw();
        refresh();
        userInput();
        snake_move();
        game_state();
        Sleep(10); // control the speed of the game - milliseconds
    }
    endwin();
    return 0;
}