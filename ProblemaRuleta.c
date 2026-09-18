#include <stdio.h>

typedef struct
{
    char PlayerChar;
    int notebook[100];
} Player;

typedef struct
{
    bool red;
    bool high;
    bool odd;
} roulette;

Player createPlayer(Player player[])
{
    // Deberia funcionar por el codigo ascii, pero no estoy seguro
    for (int i = 0; i < 5; i++)
    {
        player[i].PlayerChar = 'A' + i;
    }
    for (int i = 0; i < 5; i++)
    {
        player[i].notebook[i] = 0;
    }
    return player;
}
Player imprimirPlayer(Player player[])
{
    for (int i = 0; i < 5; i++)
    {
        printf("Jugador %c\n", player[i].PlayerChar);
        for (int j = 0; j < 100; j++)
        {
            printf("%d ", player[i].notebook[j]);
        }
        printf("\n");
    }
    return player;
}

int main()
{
    // Arranca entonces seteo los jugadores A, B...etc y le pongo su notebook inicial
    Player players[5];
    Player player = createPlayer(players);
    Player player = imprimirPlayer(players);

    return 0;
}
