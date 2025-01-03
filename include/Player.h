#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player
{
    public:
        Player();
        virtual ~Player();
        void setName(const std::string& name);
        std::string getName() const;

    protected:

    private:
        std::string name;
};

#endif // PLAYER_H
