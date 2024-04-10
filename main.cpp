#include <iostream>
#include <queue>
#include <ncurses.h>
#include <unistd.h> //for sleep() and usleep()
#include <string.h> 
#include <cstdlib> //for rand()

using namespace std;

const int SNAKE_SIZE = 5;
bool game_over = false;
int score = 0;

class POINT{
    public:
        int x,y;
        POINT() {x=0; y=0;}
        POINT(int x_init,int y_init) : x(x_init), y(y_init) {}
};

enum DIRECTION{UP, DOWN, LEFT, RIGHT};

class SNAKE{
    public:
        POINT head;
        DIRECTION move;
        queue<POINT> body;
        SNAKE() {
            move=RIGHT; 
            for(int i=1; i<=SNAKE_SIZE; i++){
                body.push(POINT(i,1));
            }
            head.x = body.back().x;
            head.y = body.back().y;
        }
        void snake_move(POINT fruit,bool *fruit_flag){
            if(head.x==fruit.x && head.y==fruit.y){
                body.push(POINT(head.x,head.y));
                *fruit_flag = false;
            }
            if(move==UP){
                body.push(POINT(head.x,--head.y));
                body.pop();
            }
            if(move==DOWN){
                body.push(POINT(head.x,++head.y));
                body.pop();
            }
            if(move==LEFT){
                body.push(POINT(--head.x,head.y));
                body.pop();
            }
            if(move==RIGHT){
                body.push(POINT(++head.x,head.y));
                body.pop();
            }
        }
};

void user_input(WINDOW *window,SNAKE *snake)
{
    switch(wgetch(window)) // Get character
    {
        case 'a':
            if(snake->move != RIGHT){
                snake->move = LEFT;
            }
            break;
        case 'd':
            if(snake->move != LEFT){
                snake->move = RIGHT;
            }
            break;
        case 'w':
            if(snake->move != DOWN){
                snake->move = UP;
            }
            break;
        case 's':
            if(snake->move != UP){
                snake->move = DOWN;
            }
            break;
        case ERR:
            break;
        default:
            game_over = true;
            break;
    }
}
WINDOW* draw_box(POINT point){
    WINDOW *window;
    window = newwin(point.y,point.x,0,0);
    box(window,0,0);
    wrefresh(window);
    return window;
}

void destroy_window(WINDOW *window){
    wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(window);
	delwin(window);
}

void draw_snake(SNAKE snake, WINDOW *win){
    queue<POINT> temp = snake.body;
    while(!temp.empty()){
        mvwaddch(win,temp.front().y,temp.front().x,'+');
        temp.pop();
    }
    wrefresh(win);
}

void create_fruit(POINT *fruit, POINT screen_size){
    fruit->x = 1+ rand()% (screen_size.x-2);
    fruit->y = 1+ rand()% (screen_size.y-2);
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    POINT screen_size;
    getmaxyx(stdscr,screen_size.y,screen_size.x);
    if(screen_size.x < 7 || screen_size.y < 7){
        cout << "Screen too small. Resize to a bigger size and run."<<endl;
        exit(1);
    }
    SNAKE s;
    WINDOW *win;
    POINT fruit(screen_size.x/2,screen_size.y/2);
    bool fruit_flag = true;
    while (!game_over)
    {
        win = draw_box(screen_size);
        wtimeout(win,300); //timeout for user input
        if(!fruit_flag){
            create_fruit(&fruit, screen_size);
            fruit_flag = true;
        }
        mvwaddch(win,fruit.y,fruit.x,'o');
        draw_snake(s,win);
        user_input(win,&s);
        s.snake_move(fruit,&fruit_flag);
        draw_snake(s,win);
        if(s.head.x>screen_size.x-1 || s.head.y>screen_size.y-1 || s.head.x<1 || s.head.y<1) {usleep(300000);game_over=true;}
        queue<POINT> temp = s.body;
        while(!temp.empty() && temp.front().x!=temp.back().x && temp.front().y!=temp.back().y){
            temp.pop();
            if(temp.front().x==s.head.x && temp.front().y==s.head.y){
                usleep(300000);
                game_over = true;
            }
        }
        destroy_window(win);
    }
    usleep(200000);
    mvprintw(screen_size.y/2,(screen_size.x-12)/2,"Game Over...\n");
    getch();
    endwin();
    return 0;
}