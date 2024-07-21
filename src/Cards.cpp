#include <string>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;
using std::string;

#include "Cards.h"

//string Cards::cards_deck[8] = {"Carro", "Bola", "Gato", "Jornal", "Car", "Ball", "Cat", "Newspaper"};

Cards::Cards()
{
    //ctor
    //cards_deck[8] = {"Carro", "Bola", "Gato", "Jornal", "Car", "Ball", "Cat", "Newspaper"};
    //random_shuffle(&cards_deck[0], &cards_deck[7]);

    random_shuffle(std::begin(cards_deck), std::end(cards_deck));
    /* for (int i = 0; i < 8; i++) {
        cout << cards_deck[i] << "\n" << endl;
        cout << "-----" << endl;
    } */
}

string Cards::get_card_by_index(int index) {
    return cards_deck[index];
}

void Cards::shuffle_cards() {
    random_shuffle(std::begin(cards_deck), std::end(cards_deck));
}

Cards::~Cards()
{
    //dtor
}

string Cards::cards_deck[] = {"Carro", "Bola", "Gato", "Jornal", "Car", "Ball", "Cat", "Newspaper"};
