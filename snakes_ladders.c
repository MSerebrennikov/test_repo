#include <stdio.h>
#include <string.h>

#define Nsnakes   10
#define Nladders  11

int pl_pos[2] = {36, 23};  	// 2 players, start position for test complete, else {0, 0}
int pl_Num = 0;           	// current Player number
int pl_Win = 0;				// Winner

int snake_head[Nsnakes] = { 16, 46, 49, 62, 64, 74, 89, 92, 95, 99 };
int snake_tail[Nsnakes] = { 6, 25, 11, 19, 60, 53, 68, 88, 75, 80 };

int ladder_head[Nladders] = { 2, 7, 8, 15, 21, 28, 36, 51, 71, 78, 87 };
int ladder_tail[Nladders] = { 38, 14, 31, 26, 42, 84, 44, 67, 91, 98, 94 };

void itoa(int in, char s[]);

char* snakes_ladders(int die1, int die2)
{
    static char answ[30];
    static char sq_pos[5];

    answ[0] = '\0';                             // clear answer

    if (pl_Win)                                 // Winner is defined already
        return "Game Over!";

    pl_pos[pl_Num] += die1 + die2;              // regular step
    if (pl_pos[pl_Num] == 100)                  // is game over?
    {
        pl_Win = pl_Num + 1;

        return pl_Num ? "Player 2 Wins!" : "Player 1 Wins!";
    }

    if (pl_pos[pl_Num] > 100)                   // overstep
        pl_pos[pl_Num] -= 2 * (pl_pos[pl_Num] - 100); // go back

    for (int i = 0; i < Nsnakes; i++)           // is on snake head?
    {
        if (pl_pos[pl_Num] == snake_head[i])
            pl_pos[pl_Num] = snake_tail[i];     // go to tail
    }

    for (int i = 0; i < Nladders; i++)          // is on ladder head?
    {
        if (pl_pos[pl_Num] == ladder_head[i])
            pl_pos[pl_Num] = ladder_tail[i];    // go to tail
    }

    strcat(answ,
           (pl_Num ? "Player 2 is on square " : "Player 1 is on square "));
    itoa(pl_pos[pl_Num], sq_pos);
    strcat(answ, sq_pos);

    if (die1 != die2)                           // select player on next step
    {
        pl_Num = pl_Num ? 0 : 1;                // swap player   
    }

    return answ;
}

/////////lib func

void reverse(char* s)
{
    int tmp, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void itoa(int in, char s[])
{
    int sign;
    int i = 0;

    sign = in;
    if (in < 0)
        in = -in;
    do
    {
        s[i++] = in % 10 + '0';     // load least digit, reverse order
    }
    while ((in /= 10) > 0);         // not all digits loaded
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}