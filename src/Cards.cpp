#include <string>
#include <algorithm>
#include <array>
#include <iostream>
#include <ctime>
using namespace std;
using std::string;
#include "Cards.h"

int int_random (int i) { return std::rand()%i;}

Cards::Cards()
{
    std::srand ( unsigned ( std::time(0) ) );
    random_shuffle(std::begin(cards_deck), std::end(cards_deck), int_random);
}

string Cards::get_card_by_index(int index) {
    return cards_deck[index];
}

string* get_cards() {
    return Cards::cards_deck;
}

void Cards::shuffle_cards() {
    random_shuffle(std::begin(cards_deck), std::end(cards_deck));
}

Cards::~Cards()
{
    //dtor
}

string Cards::cards_deck[] = {"Dog", "Cachorro", "Cat", "Gato", "House", "Casa", "Arvoce", "Tree", "Bola", "Ball", "Livro", "Book", "Carro", "Car", "Aviao", "Airplane", "Escola", "School", "Sol", "Sun"};
