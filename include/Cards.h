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

    protected:

    private:
        static string cards_deck[8];
};

#endif // CARDS_H
