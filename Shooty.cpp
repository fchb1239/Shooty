#include <iostream>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>

using namespace::std;

int moves;

bool leftOnce = false;
bool rightOnce = false;
bool shootOnce = false;

bool shooting;
int shoot[50];
int shootX[50];

int lastShootIndex;

int astroidX[20];
int astroidY[20];

int hits;

void coord(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw(string frame, int x, int y) {
    coord(x, y);
    cout << frame;
}

void handleShoot() {
    shooting = true;
    shoot[lastShootIndex] = 20;
    shootX[lastShootIndex] = moves;
    lastShootIndex++;
    if (lastShootIndex > 50)
        lastShootIndex = 0;
}

void update() {
    // Clears screen
    system("CLS");

    // Hit counter
    draw("Hits: " + to_string(hits), 0, 0);

    // Player
    if (moves < 2)
        moves = 2;
    draw("<-#->", moves - 2, 20);

    // Astroids
    for (int a = 0; a < 20; a++) {
        draw("*", astroidX[a], astroidY[a]);
    }

    // Shooting and hit detection
    if (shooting) {
        for (int i = 0; i < 50; i++) {
            if (shoot[i] > 0) {
                shoot[i]--;
                draw("|", shootX[i], shoot[i]);
                for (int j = 0; j < 20; j++) {
                    if (shoot[i] == astroidY[j] && shootX[i] == astroidX[j]) {
                        astroidX[j] = rand() % 100 + 2;
                        astroidY[j] = rand() % 13 + 1;
                        shoot[i] = 0;
                        hits++;
                    }
                }
                if (shoot[i] < 2)
                    shoot[i] = 0;
            }
        }
    }

    // Moves the while line thingy to 0, 0 so it doesn't get in the way of the gameplay
    draw("", 0, 0);
}


// I am not that good with C++ so this is the best I can do with key input handling
void handleKeys() {
    if (GetKeyState('A'))
    {
        if (!leftOnce)
        {
            if (moves > 0)
                moves--;

            leftOnce = true;
        }
    }
    else
    {
        if (leftOnce)
        {
            if (moves > 0)
                moves--;

            leftOnce = false;
        }
    }

    if (GetKeyState('D'))
    {
        if (!rightOnce)
        {
            if (moves < 100)
                moves++;

            rightOnce = true;
        }
    }
    else
    {
        if (rightOnce)
        {
            if (moves < 100)
                moves++;

            rightOnce = false;
        }
    }

    if (GetKeyState('E'))
    {
        if (!shootOnce)
        {
            handleShoot();

            shootOnce = true;
        }
    }
    else
    {
        if (shootOnce)
        {
            handleShoot();

            shootOnce = false;
        }
    }
}

int main()
{
    // Sets console title
    SetConsoleTitleA("Shooty");
    // Title screen
    cout << " ____          ____\n|    | Shooty |    |\n|    |        |    |\n|    | Press  |    |\n|    | Enter  |    |\n|    |        |    |";
    // Checks if a key is pressed
    cin.get();

    for (int i = 0; i < 20; i++) {
        astroidX[i] = rand() % 100 + 2;
        astroidY[i] = rand() % 13 + 1;
    }

    // Calls update as much as possible
    while (true) {
        handleKeys();
        update();
    }
}
