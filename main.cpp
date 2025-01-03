#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <array>
#include <iterator>
#include <cmath>
#include <tuple>

using namespace std;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
#define KEY_SEEN     1
#define KEY_RELEASED 2
#include "Cards.h"
#include "Card.h"

int CARD_DIMENSION_WIDTH = 100;
int CARD_DIMENSION_HEIGHT = 100;
bool ALL_CARDS_ARE_OPENED = true;

ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* selection;

bool is_pressing_the_key(int key) {
    if (key) {
        return true;
    }
    return false;
}

enum TURN {
    PRESENTATION,
    OPEN_FIRST,
    OPEN_SECOND,
    ENDGAME
};

typedef struct CONTROLLER_A
{
    int line, column, score = 0;
    TURN turn = TURN::PRESENTATION;

    Card* card1;
    Card* card2;

} CONTROLLER_A;

CONTROLLER_A controller_a;


void controller_a_restart(CONTROLLER_A* controller_a, Cards* cards_nivel) {
    cards_nivel->shuffle_cards();
    controller_a->turn = TURN::PRESENTATION;
    controller_a->score = 0;
}

void controller_a_set_line_column_by_key_direction_pressed(unsigned char *key, CONTROLLER_A* controller_a) {
    if(key[ALLEGRO_KEY_UP]) {
        controller_a->line = controller_a->line - 1;
    }

    if(key[ALLEGRO_KEY_DOWN]) {
        controller_a->line = controller_a->line + 1;
    }

    if(key[ALLEGRO_KEY_LEFT]) {
        controller_a->column = controller_a->column - 1;
    }

    if(key[ALLEGRO_KEY_RIGHT]) {
        controller_a->column = controller_a->column + 1;
    }

    if (controller_a->line < 0) {
        controller_a->line = 0;
    }

    if (controller_a->line > 3) {
        controller_a->line = 3;
    }

    if (controller_a->column < 0) {
        controller_a->column = 0;
    }

    if (controller_a->column > 6) {
        controller_a->column = 6;
    }
}

bool is_card_got_it_right(CONTROLLER_A* controller_a) {
    if (controller_a->card1->getIdentifier() == controller_a->card2->getIdentifier()) {
        return true;
    }
    return false;
}

void show_cards(Cards* cards_nivel) {
    int column_x = 0;
    int card_position_x = 2;
    int card_position_y = 90;
    int card_position_deslocation = 103;
    int margin_left = 37;
    int jump_line = 103;
    int card_position_x_initial = card_position_x + margin_left;
    int card_position_y_initial = card_position_y;
    card_position_x = card_position_x + margin_left;
    int period = 1;
    Card *some_card;

    ALL_CARDS_ARE_OPENED = true;
    for (unsigned int i = 0; i < cards_nivel->cards.size(); i++) {
        some_card = cards_nivel->cards[i];

        if (some_card->isFaceDown) {
            ALL_CARDS_ARE_OPENED = false;
            al_draw_bitmap_region(background, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
        } else {
            al_draw_bitmap_region(some_card->getImg(), 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
        }


        card_position_x = card_position_x + card_position_deslocation;
        if (period == 7) {
            card_position_y = card_position_y + jump_line;
            card_position_x = card_position_x_initial;
            period = 0;
        }
        column_x = column_x + 10;
        period = period + 1;
    } // for

     // Selection
     al_draw_bitmap_region(selection, 0, 0, 100, 100, card_position_x_initial + (controller_a.column * card_position_deslocation) , card_position_y_initial + (controller_a.line * card_position_deslocation), 0);

}

void controller_a_selection_by_space_pressed(CONTROLLER_A* controller_a, Cards* cards_nivel1) {

    int card_selected = controller_a->line * 7 + controller_a->column;
    Card* some_card = cards_nivel1->cards[card_selected];

    if (controller_a->turn == TURN::OPEN_FIRST && some_card->isFaceDown == true) {

        some_card->isFaceDown = false;
        controller_a->card1 = some_card;
        controller_a->turn = TURN::OPEN_SECOND;
        return;
    }

    if (controller_a->turn == TURN::OPEN_SECOND && some_card->isFaceDown == true) {
        some_card->isFaceDown = false;
        controller_a->card2 = some_card;

        show_cards(cards_nivel1);
        al_flip_display();

        if (!is_card_got_it_right(controller_a)) {
            controller_a->card1->isFaceDown = true;
            controller_a->card2->isFaceDown = true;

            al_rest(1.9);
        }

        controller_a->turn = TURN::OPEN_FIRST;
    }
}

void show_all_cards(Cards* cards_nivel) {
    Card *some_card;
    for (unsigned int i = 0; i < cards_nivel->cards.size(); i++) {
        some_card = cards_nivel->cards[i];
        some_card = cards_nivel->cards[i];
        some_card->isFaceDown = false;
    }
}

void hidden_all_cards(Cards* cards_nivel) {
    Card *some_card;
    for (unsigned int i = 0; i < cards_nivel->cards.size(); i++) {
        some_card = cards_nivel->cards[i];
        some_card = cards_nivel->cards[i];
        some_card->isFaceDown = true;
    }
}

int main()
{
    ALLEGRO_DISPLAY* display;

    if(!al_init())
        al_show_native_message_box(NULL,NULL,NULL,"Couldnt initialize",NULL,NULL);

    if(!al_install_keyboard())
        printf("Couldn't initialize keyboard\n");

    /*if(!al_install_mouse())
    {
        printf("couldn't initialize mouse\n");
    }*/
    al_init_primitives_addon();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    al_install_audio();
    al_init_acodec_addon();


    ALLEGRO_FONT* font;

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(800,600);
    if(!display)
        al_show_native_message_box(NULL,NULL,NULL,"Couldnt create Screen",NULL,NULL);


    ALLEGRO_EVENT_QUEUE* queue;

    ALLEGRO_TIMER* timer;
    timer = al_create_timer(1.0 / 60.0);
    queue = al_create_event_queue();
    font = al_create_builtin_font();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    //al_register_event_source(queue, al_get_mouse_event_source());

    ALLEGRO_EVENT event;

    al_start_timer(timer);
    unsigned char key[ALLEGRO_KEY_MAX];

    if(!al_init_image_addon())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro image addon couldnt initialize",NULL,NULL);


    bool abc = false;
    bool exit_game = false;

    al_reserve_samples(2);
    ALLEGRO_SAMPLE *background_sound;
    ALLEGRO_SAMPLE_ID background_sound_id;
    background_sound = al_load_sample("./backgroundsound.ogg");

    ALLEGRO_SAMPLE *sound_click;
    ALLEGRO_SAMPLE_ID sound_click_id;
    sound_click = al_load_sample("./click.ogg");

    ALLEGRO_BITMAP* title; title= al_load_bitmap("./images/title.png");
    selection= al_load_bitmap("./images/selection.png");
    background= al_load_bitmap("./images/background.jpg");


    Cards cards_nivel1;
    cards_nivel1.cards.push_back(new Card("corta_unhas", 1));
    cards_nivel1.cards.push_back(new Card("nail_clippers", 1));
    cards_nivel1.cards.push_back(new Card("cabeleireiro", 2));
    cards_nivel1.cards.push_back(new Card("hairdresser", 2));
    cards_nivel1.cards.push_back(new Card("lenco", 3));
    cards_nivel1.cards.push_back(new Card("tissues", 3));
    cards_nivel1.cards.push_back(new Card("mala", 4));
    cards_nivel1.cards.push_back(new Card("suitecase", 4));
    cards_nivel1.cards.push_back(new Card("torta", 5));
    cards_nivel1.cards.push_back(new Card("pie", 5));
    cards_nivel1.cards.push_back(new Card("macaneta", 6));
    cards_nivel1.cards.push_back(new Card("door_handle", 6));
    cards_nivel1.cards.push_back(new Card("almofada", 7));
    cards_nivel1.cards.push_back(new Card("cushion", 7));
    cards_nivel1.cards.push_back(new Card("fogao", 8));
    cards_nivel1.cards.push_back(new Card("stove", 8));
    cards_nivel1.cards.push_back(new Card("bode", 9));
    cards_nivel1.cards.push_back(new Card("goat", 9));
    cards_nivel1.cards.push_back(new Card("tartaruga", 10));
    cards_nivel1.cards.push_back(new Card("tortoise", 10));
    cards_nivel1.cards.push_back(new Card("cisnei", 11));
    cards_nivel1.cards.push_back(new Card("swan", 11));
    cards_nivel1.cards.push_back(new Card("caranguejo", 12));
    cards_nivel1.cards.push_back(new Card("crab", 12));
    cards_nivel1.cards.push_back(new Card("uva", 13));
    cards_nivel1.cards.push_back(new Card("grape", 13));
    cards_nivel1.cards.push_back(new Card("bus", 14));
    cards_nivel1.cards.push_back(new Card("onibus", 14));

    cards_nivel1.shuffle_cards();

    memset(key, 0, sizeof(key));

    // al_play_sample(background_sound, 0.3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &background_sound_id);

    while(!exit_game) {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER: // Holding key
                abc = is_pressing_the_key(key[ALLEGRO_KEY_S]);
                if (abc) {
                        printf("%d\n", abc);
                }

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;

                if(key[ALLEGRO_KEY_SPACE]) {
                    al_play_sample(sound_click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &sound_click_id);
                    controller_a_selection_by_space_pressed(&controller_a, &cards_nivel1);

                }

                if((key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT])) {
                    controller_a_set_line_column_by_key_direction_pressed(key, &controller_a);
                }

                if(key[ALLEGRO_KEY_ENTER] && controller_a.turn == TURN::ENDGAME) {
                    controller_a_restart(&controller_a, &cards_nivel1);
                }

                break;
            case ALLEGRO_EVENT_KEY_UP:
                if(key[ALLEGRO_KEY_A]) {
                }
                if(key[ALLEGRO_KEY_ESCAPE]) {
                    exit_game = true;
                }
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit_game = true;
                break;
            /*case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;
                break;*/

        }

        if (al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap_region(title, 0, 0, 400, 80, 200, 0, 0);
            //al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "%s %d", "Score:", controller_a.score);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 685, 585, 0, "%s", "version 1.0.0");

            if (controller_a.turn == TURN::PRESENTATION) {
                show_all_cards(&cards_nivel1);
                show_cards(&cards_nivel1);

                al_flip_display();
                al_rest(3.5);

                hidden_all_cards(&cards_nivel1);
                controller_a.turn = TURN::OPEN_FIRST;
            }

            show_cards(&cards_nivel1);

            if (ALL_CARDS_ARE_OPENED) {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 585, 0, "%s", "endgame");
                controller_a.turn = TURN::ENDGAME;
            }
        }

        al_draw_textf(font, al_map_rgb(255, 255, 255), 255, 520, 0, "%s", "Controls: SPACE and ARROWS, ESC to exit");
        al_flip_display();



    } // game loop

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(background_sound);

    return 0;
}

/**

Cão - Dog
Gato - Cat
Casa - House
Árvore - Tree
Bola - Ball
Livro - Book
Carro - Car
Avião - Airplane
Escola - School
Sol - Sun <---
Lua - Moon
Pássaro - Bird
Floresta - Forest
Praia - Beach
Cidade - City
Montanha - Mountain
Rio - River
Lago - Lake
Oceano - Ocean
Estrela - Star
Fruta - Fruit
Verdura - Vegetable
Leite - Milk
Água - Water
Suco - Juice
Pão - Bread
Queijo - Cheese
Ovo - Egg
Arroz - Rice
Feijão - Beans - 30
Carne - Meat
Peixe - Fish
Macaco - Monkey
Elefante - Elephant
Leão - Lion
Girafa - Giraffe
Zebra - Zebra
Tigre - Tiger
Urso - Bear
Cavalo - Horse - 40
Galinha - Chicken
Porco - Pig
Cabra - Goat
Sapo - Frog
Cobra - Snake
Tartaruga - Turtle
Camisa - Shirt
Calça - Pants
Sapato - Shoe
Chapéu - Hat - 50

**/
