#ifndef CONTROLLER_A_H_INCLUDED
#define CONTROLLER_A_H_INCLUDED

#include "Card.h"
#include "turn.h"
#include "cutscene.h"
#include "Player.h"

typedef struct CONTROLLER_A
{
    unsigned int total_players = 1;
    unsigned int player_turn = 1;
    unsigned int line, column = 0;
    TURN turn = TURN::PRESENTATION;
    CUTSCENE cutscene = CUTSCENE::MENU;

    Card* card1;
    Card* card2;

    Player* player1;
    Player* player2;

} CONTROLLER_A;

#endif // CONTROLLER_A_H_INCLUDED
