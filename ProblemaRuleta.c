#include <stdio.h>
#include <stdlib.h>

// Defino los limtes de manera global, podria hacerlo para cada player pero prefiero q sean globales
#define MAX_BET 4000
#define MIN_BET 5

// Enumero los tipos de apuestas
typedef enum
{
    BET_RED,
    BET_BLACK,
    BET_HIGH,
    BET_LOW,
    BET_ODD,
    BET_EVEN
} Bet;

// Defino que seria un jugador
typedef struct
{
    char playerchar;
    Bet bet;
    int notebook[100]; // Tengo duda en cual seria el tamano correcto arbitrariamente elegi 100
    int count;
    int balance;
} Player;

// Creo las funciones que definen que es cada numero
int isRed(int n)
{
    int reds[18] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    for (int i = 0; i < 18; i++)
    {
        if (n == reds[i])
        {
            return 1;
        }
    }
    return 0;
}

int isBlack(int n)
{
    return n >= 1 && n <= 36 && !isRed(n);
}

int isHigh(int n)
{
    return n >= 19 && n <= 36;
}

int isLow(int n)
{
    return n >= 1 && n <= 18;
}

int isOdd(int n)
{
    return n % 2 == 1;
}

int isEven(int n)
{
    return n >= 1 && n <= 36 && n % 2 == 0;
}

// Jamas use esta funcion, es la q genera numeros aleatorios
int spinRoulette(void)
{
    return rand() % 37;
}

int calcBet(const Player *p)
{
    if (p->count == 1)
    {
        return p->notebook[0];
    }
    return p->notebook[0] + p->notebook[p->count - 1];
}

// Sacamos la condicion final de la apuesa y sus consecuencias
void resolveBet(Player *p, int bet, int won)
{
    // Won actua como booleano
    if (won)
    {
        p->balance += bet;
        p->notebook[p->count] = bet;
        p->count++;
    }
    else
    {
        p->balance -= bet;
        if (p->count >= 2)
        {
            for (int i = 0; i < p->count - 2; i++)
            {
                p->notebook[i] = p->notebook[i + 1];
            }
            p->count -= 2;
        }
        else
        {
            p->count = 0;
        }
        if (p->count == 0)
        {
            resetNotebook(p);
        }
    }
}

// Reinicio hacia la notebook inicial
void resetNotebook(Player *p)
{
    p->notebook[0] = 1;
    p->notebook[1] = 2;
    p->notebook[2] = 3;
    p->notebook[3] = 4;
    p->count = 4;
}

int main()
{

    return 0;
}
