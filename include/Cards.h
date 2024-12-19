#ifndef CARDS_H
#define CARDS_H

#include <string>

class Cards
{


    public:
        Cards();
        virtual ~Cards();
        string get_card_by_index(int position);
        void shuffle_cards();
        static string cards_deck[20];

    protected:

    private:

};

#endif // CARDS_H
