#include <iostream>
#include <conio.h> // console I/O - kbhit()
#include <windows.h> // Sleep() function

using namespace std;

bool game_over = false;
int score = 0;

// coordinates
int snake_x, snake_y;
int snake_size=3;
int fruit_x, fruit_y;

void userInput()
{
    if(kbhit()) // Check if a key has been pressed on the keyboard without needing to continuously hold down the directional buttons
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
}
void draw{
    
}


int main() {

    initializeGame();

    while (!game_over)
    {
        draw();
        userInput();
        snakeLogic();
        Sleep(10); // control the speed of the game - milliseconds
    }
    return 0;
}