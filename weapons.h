#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class Weapons{

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

        int weaponId[7] = {0, 1, 2, 3, 4, 5, 6};
        int weapons[7] = {250, 300, 380, 400, 420, 420, 500}; 
        int weaponDamage = 0;
        int weaponLevel = 0;
        std::string weaponName[7] = {"Cajado" , "Garra letal" , "Porrete" , "Esfera de ataque" , "Tridente sagrado", "Besta", "Espada barroca"};
        string currentWeaponName;

    public:
        Weapons(); 
        void setInitialDamage(int index);
        int upgrade(int weaponArray[]);
        int returnDamage();

};

Weapons :: Weapons(){}

int Weapons :: returnDamage(){
    return weaponDamage;
}

void Weapons :: setInitialDamage(int index){
    this->weaponDamage = this->weapons[index];
    this->currentWeaponName = this->weaponName[index];
}

int Weapons :: upgrade (int weaponArray[]){
    if(weaponArray[weaponLevel + 1] != -1){
        weaponLevel ++;
        weaponDamage = weapons[weaponArray[weaponLevel]];
        this->currentWeaponName = weaponName[weaponArray[weaponLevel]];

        cout<<"\n|Nova Arma: "<<this->currentWeaponName<<" ( "<<this->weaponDamage<<" dano )|\n";
        return 1;
    }   
    cout<<"\n|Utilizando Arma de maior Nivel|\n";

return 0;
}