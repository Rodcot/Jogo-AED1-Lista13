#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "weapons.h"
#include "spells.h"

unsigned int sleep(unsigned int seconds);
using namespace std;

class Character{

    protected:
        //Declarando um monte de propriedades que todas as classes tem.
        int hp,physicalStrenght,armor,magicalStrenght,magicalResistance,agility,maxMana,maxSpecial,specialPoints,isPoisoned,isConfused,isBleeding,numberRound,maxHp,rounds;

        int weaponIndex[7] = {-1, -1, -1, -1, -1, -1, -1};
        int spellIndex[7] = {-1, -1, -1, -1, -1, -1, -1};
    
    public:
        virtual int print() {};

        virtual int receiveDamagePhys(int dmg) {}; 
        virtual int physicalDamageCalculation(Character *foe) {}; 

        virtual int receiveDamageMag(int dmg) {}; 
        virtual int magicalDamageCalculation(int option) {};

        virtual int receiveDamageIgnoreArmor(int dmg) {};

        virtual int changeWeapon() {};

        virtual int dodgeCalculation() {};

        virtual void initializeCharacter() {};

        virtual int showMagicMenu(Character *p2) {};

        virtual int addSpecialPoints() {};
        virtual int getMaxSpecialPoints() {};
        virtual int getSpecialPoints() {};
        virtual int useSpecial(Character *foe) {};

        virtual int addMana() {};

        virtual int returnHp() {};
        virtual int returnMaxHp (){};

        virtual void checkStats(Character *p2) {};

        virtual int addPoison() {};
        virtual void removePoison() {};
        virtual int getPoison() {};

        virtual void addConfusion() {};
        virtual void removeConfusion() {};
        virtual int getConfusion() {};
        
        virtual int addBleed() {};
        virtual int removeBleed() {};
        virtual int getBleed() {};

        virtual int getNumberRound() {};

        virtual int returnDamageEnemy() {};

        virtual string returnWeaponStringEnemy() {};

        virtual void changeEnemyWeaponLevel() {};
        
        virtual int bulKathos() {};
};




class Warrior : public Character{
    
    private:
        int attributes [7] = {4000, 30, 70, 20, 80, 20, 20};

        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Warrior (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;
        
        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;

        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;
        
        int bulKathos() override;

        ~Warrior (); //Destrutiva
};

class Thief : public Character{

    private:
        int attributes [7] = {2800, 50, 50, 30, 40, 50, 60};

        Magic *magic; 
        Weapons *weapons;
        string classname;
    
    public:
        Thief (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;
        
        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;
        
        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Thief (); //Destrutiva
};

class Wizard : public Character{
    private:
        int attributes [7] = {2500, 100, 40, 100, 30, 80, 40};

        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Wizard (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;
        
        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;
        
        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;
        
        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Wizard (); //Destrutiva
};

class Paladin : public Character{
    private:
        int attributes [7] = {3200, 80, 60, 50, 60, 60, 60};
        
        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Paladin (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;
        
        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;

        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;
        
        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;
        
        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Paladin (); //Destrutiva
};

class Animal : public Character{
    private:
        int attributes [7] = {3200, 30, 70, 20, 80, 20, 50};
        
        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:

        Animal (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;
        

        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;

        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Animal (); //Destrutiva
};

class Troll : public Character{
    private:
        int attributes [7] = {2800, 20, 80, 20, 80, 20, 20};

        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Troll (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;

        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;

        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;
        
        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Troll (); //Destrutiva
};

class Dragon : public Character{
    private:
        int attributes [7] = {3000, 40, 80, 20, 50, 50, 30};

        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Dragon (Magic *magic, Weapons *weapons);
        
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;

        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;

        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;

        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;

        ~Dragon (); //Destrutiva
};

class Zombie : public Character{
    private:
        int attributes [7] = {3500, 30, 50, 30, 60, 80, 60};

        Magic *magic; 
        Weapons *weapons;
        string classname;

    public:
        Zombie (Magic *magic, Weapons *weapons);
    
        int print() override;

        int receiveDamagePhys(int dmg) override;
        int physicalDamageCalculation(Character *foe) override;
        
        int receiveDamageMag(int dmg) override;
        int magicalDamageCalculation(int option) override;

        int receiveDamageIgnoreArmor(int dmg) override;

        int changeWeapon() override;

        int dodgeCalculation() override;

        void initializeCharacter() override;

        int showMagicMenu(Character *p2) override; 

        int addSpecialPoints() override;
        int getSpecialPoints() override;
        int getMaxSpecialPoints() override;
        int useSpecial(Character *foe) override;
        
        int addMana() override;

        int returnHp() override;
        int returnMaxHp () override;

        void checkStats(Character *p2) override;

        int addPoison() override;
        void removePoison() override;
        int getPoison() override;

        void addConfusion() override;
        void removeConfusion() override;
        int getConfusion() override;

        int addBleed() override;
        int removeBleed() override;
        int getBleed() override;

        int getNumberRound() override;

        int returnDamageEnemy() override;

        string returnWeaponStringEnemy() override;

        void changeEnemyWeaponLevel() override;

        int bulKathos() override;
        
        ~Zombie (); //Destrutiva
};
 
