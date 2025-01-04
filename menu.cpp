#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <vector>

using namespace std;



enum OPTIONS {
    INTRO,
    MENU,
    INGAME,
    EXIT
};

std::vector<int> MENU_LIST_OPTIONS = {OPTIONS::INTRO, OPTIONS::MENU, OPTIONS::INGAME, OPTIONS::EXIT};

int MENU_OPTION_SELECTED = OPTIONS::INGAME;


void show_menu(ALLEGRO_BITMAP* menu_background, ALLEGRO_FONT* font) {
    //cout << "showing menu" << endl;
    al_draw_tinted_bitmap(menu_background, al_map_rgba_f(1, 1, 1, 1), 0, 0, 0);

    al_draw_filled_rectangle(300,200, 500, 270, al_map_rgb(0, 0, 0));

    int axis_x = 325;
    int axis_y = 200;
    for (int i = 0; i < MENU_LIST_OPTIONS.size(); i++) {
        int option = MENU_LIST_OPTIONS[i];

        if (option == OPTIONS::INGAME) {
            if (option == MENU_OPTION_SELECTED) {
                al_draw_text(font, al_map_rgb(230, 255, 0), axis_x, axis_y + 20, 0, "Jogar");
            } else {
                al_draw_text(font, al_map_rgb(255, 255, 255), axis_x, axis_y + 20, 0, "Jogar");
            }
        } else if (option == OPTIONS::EXIT) {
            if (option == MENU_OPTION_SELECTED) {
                al_draw_text(font, al_map_rgb(234, 234, 28), axis_x, axis_y + 40, 0, "Sair");
            } else {
                al_draw_text(font, al_map_rgb(255, 255, 255), axis_x, axis_y + 40, 0, "Sair");
            }
        }
    }

}
