#ifndef CONTROLLER_A_H_INCLUDED
#define CONTROLLER_A_H_INCLUDED

#include "Card.h"
#include "turn.h"
#include "cutscene.h"

typedef struct CONTROLLER_A
{
    int total_players = 1;
    int line, column, score = 0;
    TURN turn = TURN::PRESENTATION;
    CUTSCENE cutscene = CUTSCENE::MENU;

    Card* card1;
    Card* card2;

} CONTROLLER_A;

#endif // CONTROLLER_A_H_INCLUDED
