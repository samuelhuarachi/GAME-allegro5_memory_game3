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


ALLEGRO_BITMAP* some_img;
ALLEGRO_BITMAP* img_car;
ALLEGRO_BITMAP* img_dog;
ALLEGRO_BITMAP* img_cachorro;
ALLEGRO_BITMAP* img_gato;
ALLEGRO_BITMAP* img_cat;
ALLEGRO_BITMAP* img_casa;
ALLEGRO_BITMAP* img_house;
ALLEGRO_BITMAP* img_arvore;
ALLEGRO_BITMAP* img_tree;
ALLEGRO_BITMAP* img_bola;
ALLEGRO_BITMAP* img_ball;
ALLEGRO_BITMAP* img_livro;
ALLEGRO_BITMAP* img_book;
ALLEGRO_BITMAP* img_aviao;
ALLEGRO_BITMAP* img_airplane;
ALLEGRO_BITMAP* img_escola;
ALLEGRO_BITMAP* img_school;
ALLEGRO_BITMAP* img_sol;
ALLEGRO_BITMAP* img_sun;


ALLEGRO_BITMAP* get_img_by_card_name(string card_name) {
    if (card_name == "carro") {
        return some_img;
    } else if (card_name == "car") {
        return img_car;
    } else if (card_name == "dog") {
        return img_dog;
    } else if (card_name == "cachorro") {
        return img_cachorro;
    } else if (card_name == "gato") {
        return img_gato;
    } else if (card_name == "cat") {
        return img_cat;
    } else if (card_name == "casa") {
        return img_casa;
    } else if (card_name == "house") {
        return img_house;
    } else if (card_name == "arvore") {
        return img_arvore;
    } else if (card_name == "tree") {
        return img_tree;
    } else if (card_name == "bola") {
        return img_bola;
    } else if (card_name == "ball") {
        return img_ball;
    } else if (card_name == "livro") {
        return img_livro;
    } else if (card_name == "book") {
        return img_book;
    } else if (card_name == "aviao") {
        return img_aviao;
    } else if (card_name == "airplane") {
        return img_airplane;
    } else if (card_name == "school") {
        return img_school;
    } else if (card_name == "escola") {
        return img_escola;
    } else if (card_name == "sol") {
        return img_sol;
    } else if (card_name == "sun") {
        return img_sun;
    }
}



bool is_pressing_the_key(int key) {
    if (key) {
        return true;
    }
    return false;
}


// Swap<char>(c,d);
// Swap<int>(a,b);
template<typename T>
    void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

enum TURN {
    OPEN_FIRST,
    OPEN_SECOND,
    FINISH,
    ENDGAME
};

typedef struct CONTROLLER_A
{
    int line, column, score = 0;
    TURN turn = TURN::OPEN_FIRST;

    int selection_one_column, selection_one_line, selection_two_column, selection_two_line = -1;
    int card_number_one = -1;
    int card_number_two = -1;

    Card* card1;
    Card* card2;

    unsigned int block_events = 0;

    std::vector<int> got_right;

} CONTROLLER_A;

CONTROLLER_A controller_a;

void controller_a_restart(CONTROLLER_A* controller_a) {
    controller_a->got_right.clear();
    controller_a->selection_one_column = -1;
    controller_a->selection_one_line = -1;
    controller_a->selection_two_column = -1;
    controller_a->selection_two_line = -1;
    controller_a->card_number_one = -1;
    controller_a->card_number_two = -1;
    controller_a->turn = TURN::OPEN_FIRST;
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

bool is_all_cards_are_opened(CONTROLLER_A* controller_a) {
    return controller_a->got_right.size() == 20;
}

bool is_card_got_it_right(CONTROLLER_A* controller_a) {
    if (controller_a->card1->getIdentifier() == controller_a->card2->getIdentifier()) {
        return true;
    }
    return false;
}

void controller_a_selection_by_space_pressed(CONTROLLER_A* controller_a, Cards* cards_nivel1) {

    int card_selected = controller_a->line * 7 + controller_a->column;
    Card* some_card = cards_nivel1->cards[card_selected];

    if (controller_a->turn == TURN::OPEN_FIRST) {
        some_card->isFaceDown = false;
        controller_a->card1 = some_card;
        controller_a->turn = TURN::OPEN_SECOND;
        return;
    }

    if (controller_a->turn == TURN::OPEN_SECOND && some_card->isFaceDown == true) {
        some_card->isFaceDown = false;
        controller_a->card2 = some_card;
        controller_a->turn = TURN::FINISH;

        if (is_card_got_it_right(controller_a)) {
            return;
        }

        // controller_a->block_events = 100;
    }
}


void check_card_got_it_right(CONTROLLER_A* controller_a, string card_name1, string card_name2) {
    controller_a->turn = TURN::OPEN_FIRST;

    // Check if the player got it right.
    if (((card_name1 == "dog" && card_name2 == "cachorro") || (card_name2 == "dog" && card_name1 == "cachorro")) ||
        ((card_name1 == "cat" && card_name2 == "gato") || (card_name1 == "gato" && card_name2 == "cat")) ||
        ((card_name1 == "house" && card_name2 == "casa") || (card_name1 == "casa" && card_name2 == "house")) ||
        ((card_name1 == "tree" && card_name2 == "arvore") || (card_name1 == "arvore" && card_name2 == "tree")) ||
        ((card_name1 == "ball" && card_name2 == "bola") || (card_name1 == "bola" && card_name2 == "ball")) ||
        ((card_name1 == "book" && card_name2 == "livro") || (card_name1 == "livro" && card_name2 == "book")) ||
        ((card_name1 == "car" && card_name2 == "carro") || (card_name1 == "carro" && card_name2 == "car")) ||
        ((card_name1 == "aviao" && card_name2 == "airplane") || (card_name1 == "airplane" && card_name2 == "aviao")) ||
        ((card_name1 == "school" && card_name2 == "escola") || (card_name1 == "escola" && card_name2 == "school")) ||
        ((card_name1 == "sun" && card_name2 == "sol") || (card_name1 == "sol" && card_name2 == "sun"))) {

        controller_a->got_right.push_back(controller_a->card_number_one);
        controller_a->got_right.push_back(controller_a->card_number_two);
        controller_a->score = controller_a->score + 10;

        if (is_all_cards_are_opened(controller_a)) {
            controller_a->turn = TURN::ENDGAME;
        }

        return;
    }
    controller_a->score = controller_a->score - 10;
    controller_a->selection_one_column = -1;
    controller_a->selection_one_line = -1;
    controller_a->selection_two_column = -1;
    controller_a->selection_two_line = -1;
    controller_a->card_number_one = -1;
    controller_a->card_number_two = -1;
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


    int CARD_DIMENSION_WIDTH = 100;
    int CARD_DIMENSION_HEIGHT = 100;
    ALLEGRO_BITMAP* title; title= al_load_bitmap("./images/title.png");
    ALLEGRO_BITMAP* selection; selection= al_load_bitmap("./images/selection.png");
    ALLEGRO_BITMAP* background; background= al_load_bitmap("./images/background.jpg");


    some_img = al_load_bitmap("./images/carro.jpg");
    img_car = al_load_bitmap("./images/car.jpg");
    img_dog = al_load_bitmap("./images/dog.jpg");
    img_cachorro = al_load_bitmap("./images/cachorro.jpg");
    img_gato = al_load_bitmap("./images/gato.jpg");
    img_cat = al_load_bitmap("./images/cat.jpg");
    img_casa = al_load_bitmap("./images/casa.jpg");
    img_house = al_load_bitmap("./images/house.jpg");
    img_arvore = al_load_bitmap("./images/arvore.jpg");
    img_tree = al_load_bitmap("./images/tree.jpg");
    img_bola = al_load_bitmap("./images/bola.jpg");
    img_ball = al_load_bitmap("./images/ball.jpg");
    img_livro = al_load_bitmap("./images/livro.jpg");
    img_book = al_load_bitmap("./images/book.jpg");
    img_aviao = al_load_bitmap("./images/aviao.jpg");
    img_airplane = al_load_bitmap("./images/airplane.jpg");
    img_escola = al_load_bitmap("./images/escola.jpg");
    img_school= al_load_bitmap("./images/school.jpg");
    img_sol = al_load_bitmap("./images/sol.jpg");
    img_sun= al_load_bitmap("./images/sun.jpg");

    Card* some_card;
    Card* card_carro = new Card("carro", 1);
    Card* card_car = new Card("car", 1);
    Card* card_cachorro = new Card("cachorro", 2);
    Card* card_dog = new Card("dog", 2);
    Card* card_gato = new Card("gato", 3);
    Card* card_cat = new Card("cat", 3);
    Card* card_casa = new Card("casa", 4);
    Card* card_house = new Card("house", 4);
    Card* card_arvore = new Card("arvore", 5);
    Card* card_tree = new Card("tree", 5);

    Cards cards_nivel1;
    cards_nivel1.cards.push_back(card_carro);
    cards_nivel1.cards.push_back(card_car);
    cards_nivel1.cards.push_back(card_cachorro);
    cards_nivel1.cards.push_back(card_dog);
    cards_nivel1.cards.push_back(card_gato);
    cards_nivel1.cards.push_back(card_cat);
    cards_nivel1.cards.push_back(card_casa);
    cards_nivel1.cards.push_back(card_house);
    cards_nivel1.cards.push_back(card_arvore);
    cards_nivel1.cards.push_back(card_tree);

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
            case ALLEGRO_EVENT_KEY_DOWN: // Key down
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;

                if(key[ALLEGRO_KEY_SPACE] && controller_a.block_events == 0) {
                    controller_a_selection_by_space_pressed(&controller_a, &cards_nivel1);
                    al_play_sample(sound_click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &sound_click_id);
                }

                if((key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_RIGHT]) && controller_a.block_events == 0) {
                    controller_a_set_line_column_by_key_direction_pressed(key, &controller_a);
                }

                if(key[ALLEGRO_KEY_ENTER] && controller_a.turn == TURN::ENDGAME) {
                    controller_a_restart(&controller_a);
                }

                break;
            case ALLEGRO_EVENT_KEY_UP: // Key up
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
            for (int i = 0; i < cards_nivel1.cards.size(); i++) {
                /**string card_name = cards_nivel1.get_card_by_index(i);

                if ((controller_a.card_number_one == i || controller_a.card_number_two == i) || is_card_got_it_right(&controller_a, i)) {
                    ALLEGRO_BITMAP* some_card = get_img_by_card_name(card_name);
                    al_draw_bitmap_region(some_card, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                } else {

                } **/

                some_card = cards_nivel1.cards[i];

                if (some_card->isFaceDown) {
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

            al_draw_bitmap_region(selection, 0, 0, 100, 100, card_position_x_initial + (controller_a.column * card_position_deslocation) , card_position_y_initial + (controller_a.line * card_position_deslocation), 0);

            //if (controller_a.turn == TURN::FINISH && controller_a.block_events == 0)
            //    check_card_got_it_right(&controller_a, cards_nivel1.get_card_by_index(controller_a.card_number_one), cards_nivel1.get_card_by_index(controller_a.card_number_two));
        }

        //if (controller_a.turn == TURN::ENDGAME) {
        //    al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 535, 0, "%s", "Press ENTER to restart");
        //}

        al_draw_textf(font, al_map_rgb(255, 255, 255), 255, 520, 0, "%s", "Controls: SPACE and ARROWS, ESC to exit");

        al_flip_display();

        if (controller_a.block_events > 0)
            controller_a.block_events = controller_a.block_events - 1;



    } // game loop

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_sample(background_sound);
    delete card_car, card_carro, card_cachorro, card_dog, card_gato, card_cat;

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
