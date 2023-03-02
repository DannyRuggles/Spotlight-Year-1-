#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

//generate fruit within boundary
void setup()
{
    gameover = 0;

    //starting point
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 10;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 10;
    if (fruity == 0)
        goto label2;
    score = 0;
}

// draws boundaries
void draw()
{
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1
                || j == 0
                || j == height - 1) {
                printf("#");
            }
            else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx
                         && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    // prints score
    printf("score = %d", score);
    printf("\n");
    printf("press X to quit the game");
}

//take the input
void input()
{
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

// movement logic
void logic()
{
    sleep(0.5); //Game speed
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    //the game is over when hitting wall
    if (x < 1 || x > height  //0 = underneath the boundary
        || y < 1 || y > width)
        gameover = 1;


    //update score after fruit
    if (x == fruitx && y == fruity) {
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;

    //generate new fruit after getting
    label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        score += 10;
    }
}

void snakegame()
{
    int m, n;

    // gen boundary
    setup();

    // game is over
    while (!gameover) {

        //function Call
        draw();
        input();
        logic();
    }
}
