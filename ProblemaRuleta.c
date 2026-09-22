#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defino los limtes de manera global, podria hacerlo para cada player pero prefiero q sean globales
#define MAX_BET 4000
#define MIN_BET 5
#define NUM_PLAYERS 6
#define NUM_SPINS 10000
#define MAX_NOTEBOOK 4096

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
    int notebook[MAX_NOTEBOOK]; // el cuaderno crece hasta ~4000 numeros, por eso 4096
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

// Genera un numero aleatorio entre 0 y 36
int spinRoulette(void)
{
    return rand() % 37;
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

// Creo a los jugadores
void createPlayer(Player *p, char name, Bet tipoApuesta)
{
    p->playerchar = name;
    p->bet = tipoApuesta;
    p->balance = 0;
    resetNotebook(p);
}

// Seteo cada tipo de apuesta con su funcion correspondiente
int playerWins(const Player *p, int number)
{
    switch (p->bet)
    {
    case BET_RED:
        return isRed(number);
    case BET_BLACK:
        return isBlack(number);
    case BET_HIGH:
        return isHigh(number);
    case BET_LOW:
        return isLow(number);
    case BET_ODD:
        return isOdd(number);
    case BET_EVEN:
        return isEven(number);
    }
    return 0;
}

int main()
{

    srand((unsigned)time(NULL));

    Player players[5];
    char names[5] = {'A', 'B', 'C', 'D', 'E', 'F'};
    Bet types[5] = {BET_RED, BET_BLACK, BET_HIGH, BET_LOW, BET_ODD, BET_EVEN};

    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        createPlayer(&players[i], names[i], types[i]);
    }

    // 10000 tiradas, siento que es para nada eficiente, lo tome de manera literal
    for (int spin = 0; spin < 10000; spin++)
    {
        int number = spinRoulette();
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            int bet = calcBet(&players[i]);
            // Reseteo si la apuesta sale del minimo
            if (bet < MIN_BET)
            {
                resetNotebook(&players[i]);
                bet = calcBet(&players[i]);
            }
            int won = playerWins(&players[i], number);
            resolveBet(&players[i], bet, won);
        }
    }
    // Sumo los balances y los imprimo
    int teamBalance = 0;
    for (int i = 0; i < 5; i++)
    {
        teamBalance += players[i].balance;
        printf("Jugador %c balance: %d\n", players[i].playerchar, players[i].balance);
    }

    printf("Balance del equipo: %d\n", teamBalance);
    if (teamBalance > 0)
    {
        printf("El equipo gano dinero.\n");
    }
    else if (teamBalance < 0)
    {
        printf("El equipo perdio dinero.\n");
    }
    else
    {
        printf("El equipo quedo en cero.\n");
    }

    return 0;
}
