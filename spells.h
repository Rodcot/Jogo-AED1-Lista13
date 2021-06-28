#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class Magic{

    protected:
        friend class Character;
        friend class Warrior;
        friend class Paladin;
        friend class Thief;
        friend class Zombie;
        friend class Animal;
        friend class Troll;
        friend class Dragon;
        friend class Wizard;

        int mana;
        int magic[7] = {200, 400, 360, 400, 320, 280, 200};
        int typeMagic[7] = {0, 1, 1, 0, 1, 2, 3};
        int manaWaste[7] = {12, 12, 14, 16, 14, 12, 12};
        std::string magicName[7] = {"Pocao da Vida" , "Halito de Fogo" , "Bio" , "Cura" , "Flama Gelada", "Intoxicacao", "Tempestade"};

    public:
        Magic(); 
        void initialMana(int maxMana);
        int getmana();
        int getMagic(int index);
        int getTypeMagic(int index);
        int getManaWaste(int index);
        string getMagicName(int index);
        int manaEveryRound();
        int baseMagicDamage(int choice);

};

Magic :: Magic(){}

void Magic :: initialMana(int maxMana){
    this->mana = maxMana;
}

int Magic :: getMagic(int index){
    return this->magic[index];
}

string Magic :: getMagicName(int index){
    return this->magicName[index];
}

int Magic :: getTypeMagic(int index){
    return this->typeMagic[index];
}

int Magic :: getManaWaste(int index){
    return this->manaWaste[index];
}


int Magic :: getmana(){
    return this->mana;
}

int Magic :: manaEveryRound(){
    mana += 10;
    return mana;
}

int Magic :: baseMagicDamage(int choice){
    int damage = 0;

    if(this->mana > this->manaWaste[choice]){
        this->mana -= this->manaWaste[choice];
        damage = magic[choice];
        return damage;
    }else{
        return -1;
    }
}

