#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "controller_a.h"

void show_menu(ALLEGRO_BITMAP* menu_background, ALLEGRO_FONT* font);
void menu_keydown(unsigned char *key, CONTROLLER_A* controller_a);


#endif // MENU_H_INCLUDED
