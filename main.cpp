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

int main()
{
    ALLEGRO_DISPLAY* display;

    if(!al_init())
        al_show_native_message_box(NULL,NULL,NULL,"Allegro couldnt initialize",NULL,NULL);

    if(!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
    }
    /*if(!al_install_mouse())
    {
        printf("couldn't initialize mouse\n");
    }*/
    al_init_primitives_addon();
    al_install_audio();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    al_init_acodec_addon();

    ALLEGRO_FONT* font;


    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
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

    /* Your Code Here */
    string cards1_br[4] = {"Carro", "Bola", "Gato", "Teste"};
    Cards cards_nivel1;

    int CARD_DIMENSION_WIDTH = 150;
    int CARD_DIMENSION_HEIGHT = 150;
    ALLEGRO_BITMAP* img_carro;
    img_carro = al_load_bitmap("./images/carro.jpg");
    ALLEGRO_BITMAP* img_car;
    img_car = al_load_bitmap("./images/car.jpg");
    ALLEGRO_BITMAP* img_dog;
    img_dog = al_load_bitmap("./images/dog.jpg");
    ALLEGRO_BITMAP* img_cachorro;
    img_cachorro = al_load_bitmap("./images/cachorro.jpg");
    ALLEGRO_BITMAP* img_gato;
    img_gato = al_load_bitmap("./images/gato.jpg");
    ALLEGRO_BITMAP* img_cat;
    img_cat = al_load_bitmap("./images/cat.jpg");
    ALLEGRO_BITMAP* img_casa;
    img_casa = al_load_bitmap("./images/casa.jpg");
    ALLEGRO_BITMAP* img_house;
    img_house = al_load_bitmap("./images/house.jpg");
    ALLEGRO_BITMAP* img_arvore;
    img_arvore = al_load_bitmap("./images/arvore.jpg");
    ALLEGRO_BITMAP* img_tree;
    img_tree = al_load_bitmap("./images/tree.jpg");
    ALLEGRO_BITMAP* img_bola;
    img_bola = al_load_bitmap("./images/bola.jpg");
    ALLEGRO_BITMAP* img_ball;
    img_ball = al_load_bitmap("./images/ball.jpg");
    ALLEGRO_BITMAP* img_livro;
    img_livro = al_load_bitmap("./images/livro.jpg");
    ALLEGRO_BITMAP* img_book;
    img_book = al_load_bitmap("./images/book.jpg");
    ALLEGRO_BITMAP* img_aviao;
    img_aviao = al_load_bitmap("./images/aviao.jpg");
    ALLEGRO_BITMAP* img_airplane;
    img_airplane = al_load_bitmap("./images/airplane.jpg");
    ALLEGRO_BITMAP* img_escola;
    img_escola = al_load_bitmap("./images/escola.jpg");
    ALLEGRO_BITMAP* img_school;
    img_school= al_load_bitmap("./images/school.jpg");
    ALLEGRO_BITMAP* img_sol;
    img_sol = al_load_bitmap("./images/sol.jpg");
    ALLEGRO_BITMAP* img_sun;
    img_sun= al_load_bitmap("./images/sun.jpg");
    ALLEGRO_BITMAP* title;
    title= al_load_bitmap("./images/title.png");
    ALLEGRO_BITMAP* selection;
    selection= al_load_bitmap("./images/selection.png");
    ALLEGRO_BITMAP* background;
    background= al_load_bitmap("./images/background.jpg");

    memset(key, 0, sizeof(key));
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
        //al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "X: %f", 1.2);

        if (al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap_region(title, 0, 0, 400, 80, 200, 0, 0);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "%s", "Score: 0");
            al_draw_textf(font, al_map_rgb(255, 255, 255), 685, 585, 0, "%s", "version 1.0.0");



            int column_x = 0;
            int card_position_x = 2;
            int card_position_y = 90;
            int card_position_deslocation = 103;
            int margin_left = 142;
            int jump_line = 103;
            int card_position_x_initial = card_position_x + margin_left;
            card_position_x = card_position_x + margin_left;
            int period = 1;
            for (int i = 0; i < 20; i++) {
                string card_name = cards_nivel1.get_card_by_index(i);
                // al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20 + column_x, 0, "%s", card_name.c_str());




                if (card_name == "Carro") {
                    al_draw_bitmap_region(img_carro, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Car") {
                    al_draw_bitmap_region(img_car, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Dog") {
                    al_draw_bitmap_region(img_dog, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Cachorro") {
                    al_draw_bitmap_region(img_cachorro, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Gato") {
                    al_draw_bitmap_region(img_gato, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Cat") {
                    al_draw_bitmap_region(img_cat, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Casa") {
                    al_draw_bitmap_region(img_casa, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "House") {
                    al_draw_bitmap_region(img_house, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Arvore") {
                    al_draw_bitmap_region(img_arvore, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Tree") {
                    al_draw_bitmap_region(img_tree, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Bola") {
                    al_draw_bitmap_region(img_bola, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Ball") {
                    al_draw_bitmap_region(img_ball, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Livro") {
                    al_draw_bitmap_region(img_livro, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Book") {
                    al_draw_bitmap_region(img_book, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Aviao") {
                    al_draw_bitmap_region(img_aviao, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Airplane") {
                    al_draw_bitmap_region(img_airplane, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "School") {
                    al_draw_bitmap_region(img_school, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Escola") {
                    al_draw_bitmap_region(img_escola, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Sol") {
                    al_draw_bitmap_region(img_sol, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                } else if (card_name == "Sun") {
                    al_draw_bitmap_region(img_sun, 0, 0, CARD_DIMENSION_WIDTH, CARD_DIMENSION_HEIGHT, card_position_x, card_position_y, 0);
                    card_position_x = card_position_x + card_position_deslocation;
                }

                if (period == 5) {
                    card_position_y = card_position_y + jump_line;
                    card_position_x = card_position_x_initial;
                    period = 0;
                }




                column_x = column_x + 10;
                period = period + 1;
            } // for

            al_draw_bitmap_region(background, 0, 0, 100, 100, 144, 90, 0);
            al_draw_bitmap_region(selection, 0, 0, 100, 100, 144, 90, 0);

            //al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 200, 0, "X: %f", 1.1);
            //al_draw_textf(font, al_map_rgb(255,255,255), 20,30,0, "abc %d", 111);
            //al_draw_rectangle(200, 200, 600, 280, al_map_rgb(255, 255, 255), 1);

        }
        al_flip_display();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

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
