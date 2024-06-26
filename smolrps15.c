#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define FIRST16 0b11111111111111110000000000000000
#define LAST16  0b00000000000000001111111111111111

const char *STATE_NAMES[15] =
{
    "Rock",
    "Fire",
    "Scissors",
    "Snake",
    "Human",
    "Tree",
    "Wolf",
    "Sponge",
    "Paper",
    "Air",
    "Water",
    "Dragon",
    "Devil",
    "Lightning",
    "Gun",
};

void PickChoice(unsigned long int *g, unsigned short int *s, bool *p, bool h)
{
    unsigned int temp = 2; unsigned short int i=0;
    if((*s - 1) != temp)
    {
        for(i ; i < (*s - 1) ; i++)
        { temp <<= 1;  }
    }
    
    if(h){printf("The computer has made it's move.\n");}
    else{printf("The computer has picked %s.\n", STATE_NAMES[(*s-1)]);}

    if(*p){ *g |= ((temp + 1) << 16); return; }
    *g |= (temp + 1);
}

void SelectionLogic(unsigned long int *g, bool p)
{
    bool cpuOne = *g & 65536;
    unsigned short int i = 0, s;
    if(p && cpuOne)
    {
        printf("Human player, make your selection:\n");
        for(i; i < 15; i++) { printf("%hu. %s\n", (i + 1), STATE_NAMES[(i)]); }
        scanf(" %hu", &s); 
        if(s < 1) {s = 1;} if(s > 15) {s = 15;}
        PickChoice(g, &s, &p, false); return;
    }
    s = (rand() % 15) + 1;
    PickChoice(g, &s, &p, true);
}

unsigned short int BitExtract(unsigned int *n)
{
    unsigned short int r = 0;
    while(*n != 0) 
    { 
        *n >>= 1; 
        r++;
    }
    return (r - 2);
}

void WinLogic(unsigned long int *g, const unsigned int arr[])
{
    unsigned int a = ((*g & FIRST16) >> 16), b = (*g & LAST16), c;
    unsigned short int i=0, j=0; bool win;
    if(a == b){printf("Aw crud, a draw.\n"); return;}
    i = BitExtract(&a); 
    c = (((b & arr[i]) - 1));
    j = BitExtract(&b);
    if (c > 1)
    { printf("Your %s won against the computer's %s!\n", STATE_NAMES[i], STATE_NAMES[j]); }
    else
    { printf("Your %s lost against the computer's %s, darn.\n", STATE_NAMES[i], STATE_NAMES[j]); }
}

int main()
{
    srand(time(NULL));
    const unsigned int WIN_CHART[15] =
    {
        0b0000000111111101,
        0b0000001111111001,
        0b0000011111110001,
        0b0000111111100001,
        0b0001111111000001,
        0b0011111110000001,
        0b0111111100000001,
        0b1111111000000001,
        0b1111110000000011,
        0b1111100000000111,
        0b1111000000001111,
        0b1110000000011111,
        0b1100000000111111,
        0b1000000001111111,
        0b0000000011111111,
    };
    long unsigned int gameState;
    bool selection = 1;
    printf("Welcome to Smol RPS15!\n(Any selection numbers bigger than 1 will default to 1!)\n");
    while(selection != 0)
    {
        gameState = 0;
        printf("Enter 1 to play, 0 for the CPU to play for you!\n(Player 2 will always be a CPU)\n");
        scanf(" %hu", &selection);
        if(selection){ gameState += 65536; }
        gameState += 1;
        SelectionLogic(&gameState, true); SelectionLogic(&gameState, false);
        gameState != 65537;
        WinLogic(&gameState, WIN_CHART);
        printf("Care to play again? (0 quits the program, 1 doesn't)\n");
        scanf(" %hu", &selection);
    }
    printf("See you next time!\n(program by kinker31)\n");
}