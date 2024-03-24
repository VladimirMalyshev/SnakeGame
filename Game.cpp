#include <iostream>
#include "stdlib.h"
#include "conio.h"
#include <windows.h>
#include "time.h"
#include "Game.h"

using namespace std;

bool gameOver;
enum eDir { STOP, UP, DOWN, LEFT, RIGHT } dir;

int x, y, fruitX, fruitY, score, nTail;
int tailX[100], tailY[100];
int width = 23;
int height = 21;


void Game::Letsplay()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();        
        Sleep(200);
    }
    cout << "Game over!" << endl;
}


void Game::getRandom()
{
    fruitY = rand() % height;
    fruitX = rand() % width;
    if (fruitX <= 0 || fruitX >= width - 1 || fruitY <= 0 || fruitY >= height)
    {
        getRandom();
    }
    
    for (int i = 0; i < nTail; i++) {
        if (fruitX == tailX[i] && fruitY == tailY[i]) 
        {
            getRandom();
        }
    }
}

void Game::Setup()
{
    gameOver = false;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    getRandom();
    score = 0;

}

void Game::horisontalline()
{
    for (int i = 0; i < width; i++) cout << "#";
    cout << endl;
}

void Game::Draw()
{
    system("cls");
    horisontalline();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) cout << "#";
            else if (j == x && i == y) cout << "0";
            else if (j == fruitX && i == fruitY) cout << "f";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    horisontalline();
    cout << "Score: " << score << endl;  
}

void Game::control()
{
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
}

void Game::makeTail()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = prevX;
        prev2Y = prevY;
        prevX = tailX[i];
        prevY = tailY[i];
        tailX[i] = prev2X;
        tailY[i] = prev2Y;
    }
}

void Game::Logic()
{
    makeTail();
    control();
    if (x < 1) x = width - 2;
    else if (x >= width - 1) x = 1;
    else if (y < 0) y = height - 1;
    else if (y >= height) y = 0;

    if (x == fruitX && y == fruitY) {
        score += 10;
        getRandom();
        nTail++;
    }

    

    for (int i = 1; i < nTail; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            gameOver = true;
        }
    }

    if (x == tailX[0] && y == tailY[0])
    {
        switch (dir) {
        case LEFT:
            dir = RIGHT;
            break;
        case RIGHT:
            dir = LEFT;
            break;
        case UP:
            dir = DOWN;
            break;
        case DOWN:
            dir = UP;
            break;
        }
    }
}

void Game::Input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

