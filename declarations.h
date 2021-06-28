#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "characters.h" 

/* -------------------- Declaracoes sobre o Guerreiro -------------- */
Warrior::Warrior(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Guerreiro";
    this -> hp = attributes[0]; 
    this -> maxHp = attributes[0];
    this -> maxMana = attributes[1];
    this -> physicalStrenght = attributes[2];
    this -> magicalStrenght = attributes[3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes[5];
    this -> agility = attributes [6];
    this -> maxSpecial = 70;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> numberRound = -1;
    
    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 2;
    weaponIndex[1] = 6;
    spellIndex[0] = 6;
}

int Warrior::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Warrior::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Warrior::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Warrior::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}

int Warrior::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}

int Warrior::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Warrior::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Warrior::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Warrior::print(){return hp;}

int Warrior::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Warrior::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Warrior::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Warrior::returnHp(){
    return this -> hp;
}

int Warrior::returnMaxHp(){
    return this -> maxHp;
}

int Warrior::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Warrior::getSpecialPoints(){
    return this -> specialPoints;
}

int Warrior::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

// O Especial do Guerreiro é um ataque de 250 de dano que pode ser multiplicado randomicamente de 1 a 7, sendo o total de dano 1750.
int Warrior::useSpecial(Character *foe){
    int specialDamage = 0;
    int totalDamage = 0;
    int random = 0;

    cout << "\n|Guerreiro ativa -Furia-|\n";

    sleep(2);

    cout << string( 100, '\n' );
    specialDamage = 250; 
    random = (rand() % 7) + 1;
    totalDamage = specialDamage * random;

    sleep(2);

    foe -> receiveDamagePhys(totalDamage);
    cout<<"\n|Dano realizado: "<<totalDamage<<"|\n";

    sleep(3);
    this->specialPoints = 0;
    
return totalDamage;
}

int Warrior::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Warrior::removePoison(){
    this -> isPoisoned = 0;
}

int Warrior::getPoison(){
    return this -> isPoisoned;
}

int Warrior::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Warrior::removeConfusion(){
    this -> isConfused = 0;
}

int Warrior::getConfusion(){
    return this -> isConfused;
}

void Warrior::addConfusion(){
    this -> isConfused = 1;
}

int Warrior::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Warrior::getBleed(){
    return this -> isBleeding;
}

int Warrior::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Warrior::getNumberRound(){
    return this -> numberRound;
}

int Warrior::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Warrior::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Warrior::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Warrior::~Warrior(){ // Função Destrutiva
    delete magic;
    delete weapons;
};


/* -------------------- Declaracoes sobre o Paladino -------------- */

Paladin::Paladin(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Paladino";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 80;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> numberRound = -1;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 4;
    weaponIndex[1] = 5;
    spellIndex[0] = 0;
    spellIndex[1] = 4;
    spellIndex[2] = 6;

}

int Paladin::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Paladin::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Paladin::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Paladin::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Paladin::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Paladin::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Paladin::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Paladin::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Paladin::print(){return hp;}

int Paladin::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Paladin::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Paladin::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Paladin::returnHp(){
    return this -> hp;
}

int Paladin::returnMaxHp(){
    return this->maxHp;
}

int Paladin::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Paladin::getSpecialPoints(){
    return this -> specialPoints;
}

int Paladin::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Paladino faz sua vida voltar a 4/5 do máximo, mas só tem 25% de ser bem sucedido.
int Paladin::useSpecial(Character *foe){
    int random = (rand() % 4) + 1;

    cout << "\n|Paladino ativa -Veneracao Divina-|\n";

    if(random == 1){
        cout<<"\n|Veneracao Sucedida|";
        this -> hp =  (int)((this->maxHp / 5)*4);
        cout<<"\n|Voce recuperou sua vida para 4/5 do máximo.|\n";
    }else{
        cout<<"\n|Aposta Divina Falhou|\n";
    }

    sleep(3);

return 0;
}

int Paladin::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Paladin::removePoison(){
    this -> isPoisoned = 0;
}

int Paladin::getPoison(){
    return this -> isPoisoned;
}

int Paladin::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Paladin::removeConfusion(){
    this -> isConfused = 0;
}

int Paladin::getConfusion(){
    return this -> isConfused;
}

void Paladin::addConfusion(){
    this -> isConfused = 1;
}

int Paladin::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Paladin::getBleed(){
    return this -> isBleeding;
}

int Paladin::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Paladin::getNumberRound(){
    return this -> numberRound;
}

int Paladin::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Paladin::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Paladin::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Paladin::~Paladin(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre o Ladrão -------------- */

Thief::Thief(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Ladrao";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 40;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> numberRound = -1;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 0;
    weaponIndex[1] = 2;
    weaponIndex[2] = 3;
    weaponIndex[3] = 5;
    spellIndex[0] = 5;
    spellIndex[1] = 6;

}

int Thief::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Thief::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Thief::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Thief::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Thief::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Thief::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Thief::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Thief::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Thief::print(){return hp;}

int Thief::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Thief::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Thief::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Thief::returnHp(){
    return this->hp;
}

int Thief::returnMaxHp(){
    return this->maxHp;
}

int Thief::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    } 
}

int Thief::getSpecialPoints(){
    return this -> specialPoints;
}

int Thief::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Ladrão aumenta a sua chance de desviar de ataques para 85%, mas só tem 20% de funcionar.
int Thief::useSpecial(Character *foe){
    int random = (rand() % 5) + 1;

    cout<<"\n|Ladrao Ativa -Acrobacia Ligeira-|\n";

    if(random == 1){
        cout<<"\n|Acrobacia Ligeira Sucedida|\n";
        this -> agility = 85;
    }else{
        cout<<"\n|Acrobacia Ligeira Falhou|\n";
    }

    sleep(3);
return 0;
}

int Thief::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Thief::removePoison(){
    this -> isPoisoned = 0;
}

int Thief::getPoison(){
    return this -> isPoisoned;
}

int Thief::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Thief::removeConfusion(){
    this -> isConfused = 0;
}

int Thief::getConfusion(){
    return this -> isConfused;
}

void Thief::addConfusion(){
    this -> isConfused = 1;
}

int Thief::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Thief::getBleed(){
    return this -> isBleeding;
}

int Thief::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Thief::getNumberRound(){
    return this -> numberRound;
}

int Thief::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Thief::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Thief::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Thief::~Thief(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre o Zumbi -------------- */

Zombie::Zombie(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Zumbi";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 40;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> numberRound = -1;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 0;
    weaponIndex[1] = 1;
    weaponIndex[2] = 2;
    spellIndex[0] = 5;

}

int Zombie::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Zombie::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Zombie::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Zombie::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Zombie::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Zombie::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Zombie::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Zombie::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Zombie::print(){return hp;}

int Zombie::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Zombie::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Zombie::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Zombie::returnHp(){
    return this->hp;
}

int Zombie::returnMaxHp(){
    return this->maxHp;
}

int Zombie::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Zombie::getSpecialPoints(){
    return this -> specialPoints;
}

int Zombie::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Zumbi da 1000 de dano que ignora armadura e recebe 1000 de cura.
int Zombie::useSpecial(Character *foe){
    cout<<"\n|Zumbi Ativa -Roubo de Corpo-|\n";

    this -> hp = (hp+1000);
    foe -> receiveDamageIgnoreArmor(1000);
    
return 0;
}

int Zombie::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Zombie::removePoison(){
    this -> isPoisoned = 0;
}

int Zombie::getPoison(){
    return this -> isPoisoned;
}

int Zombie::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Zombie::removeConfusion(){
    this -> isConfused = 0;
}

int Zombie::getConfusion(){
    return this -> isConfused;
}

void Zombie::addConfusion(){
    this -> isConfused = 1;
}

int Zombie::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Zombie::getBleed(){
    return this -> isBleeding;
}

int Zombie::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Zombie::getNumberRound(){
    return this -> numberRound;
}

int Zombie::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Zombie::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Zombie::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Zombie::~Zombie(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre a Besta -------------- */

Animal::Animal(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Animal";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 70;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 1;
    spellIndex[0] = 2;

}

int Animal::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Animal::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Animal::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Animal::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Animal::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Animal::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Animal::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Animal::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Animal::print(){return hp;}

int Animal::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Animal::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Animal::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Animal::returnHp(){
    return this->hp;
}

int Animal::returnMaxHp(){
    return this->maxHp;
}


int Animal::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Animal::getSpecialPoints(){
    return this -> specialPoints;
}

int Animal::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial da Besta um dano entre 500-1500 que ignora armadura e garante que o inimigo fique envenenadado.
int Animal::useSpecial(Character *foe){
    cout << "\nBesta ativa -Ataque da Garra Suja-\n";

    foe -> addPoison();
    int random = (rand() % 3) + 1;
    int specialDamage = 500 * random;

    foe -> receiveDamageIgnoreArmor(specialDamage);
    cout <<"|Dano realizado: "<<specialDamage<<" |\n";
return 0;
}

int Animal::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Animal::removePoison(){
    this -> isPoisoned = 0;
}

int Animal::getPoison(){
    return this -> isPoisoned;
}

int Animal::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Animal::removeConfusion(){
    this -> isConfused = 0;
}

int Animal::getConfusion(){
    return this -> isConfused;
}

void Animal::addConfusion(){
    this -> isConfused = 1;
}

int Animal::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Animal::getBleed(){
    return this -> isBleeding;
}

int Animal::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Animal::getNumberRound(){
    return this -> numberRound;
}

int Animal::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Animal::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Animal::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Animal::~Animal(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre o Dragão -------------- */

Dragon::Dragon(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Dragao";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 70;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 1;
    spellIndex[0] = 1;

}

int Dragon::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Dragon::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Dragon::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Dragon::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Dragon::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Dragon::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Dragon::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Dragon::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Dragon::print(){return hp;}

int Dragon::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Dragon::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Dragon::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Dragon::returnHp(){
    return this->hp;
}

int Dragon::returnMaxHp(){
    return this->maxHp;
}


int Dragon::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Dragon::getSpecialPoints(){
    return this -> specialPoints;
}

int Dragon::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Dragão faz com que o oponente receba envenenamento, confusão e sangramento com 100% de chance.
int Dragon::useSpecial(Character *foe){
    cout << "\n|Dragao ativa -O Poder Dormente de um rei- |\n";

    foe -> addPoison();
    foe -> addBleed();
    foe -> addConfusion();
    
return 0;
}

int Dragon::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Dragon::removePoison(){
    this -> isPoisoned = 0;
}

int Dragon::getPoison(){
    return this -> isPoisoned;
}

int Dragon::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Dragon::removeConfusion(){
    this -> isConfused = 0;
}

int Dragon::getConfusion(){
    return this -> isConfused;
}

void Dragon::addConfusion(){
    this -> isConfused = 1;
}

int Dragon::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Dragon::getBleed(){
    return this -> isBleeding;
}

int Dragon::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Dragon::getNumberRound(){
    return this -> numberRound;
}

int Dragon::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Dragon::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Dragon::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Dragon::~Dragon(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre o Mago -------------- */

Wizard::Wizard(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Mago";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 60;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 0;
    weaponIndex[1] = 4;
    spellIndex[0] = 0;
    spellIndex[1] = 2;
    spellIndex[2] = 3;
    spellIndex[3] = 4;
    spellIndex[4] = 5;
    spellIndex[5] = 6;

}

int Wizard::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Wizard::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Wizard::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Wizard::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Wizard::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}


int Wizard::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Wizard::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Wizard::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Wizard::print(){return hp;}

int Wizard::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Wizard::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Wizard::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Wizard::returnHp(){
    return this->hp;
}

int Wizard::returnMaxHp(){
    return this->maxHp;
}


int Wizard::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    }
}

int Wizard::getSpecialPoints(){
    return this -> specialPoints;
}

int Wizard::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Mago é Implacável
int Wizard::useSpecial(Character *foe){
    cout <<"\n|Contemplem o mago|\n|Com seus poderes|\n|Incriveis Poderes|\n";
    system("clear");

    cout <<"\n|O mago e implacavel|\n";
    foe -> receiveDamageIgnoreArmor(9999);

    system("clear");

    sleep(10);
return 0;
}

int Wizard::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Wizard::removePoison(){
    this -> isPoisoned = 0;
}

int Wizard::getPoison(){
    return this -> isPoisoned;
}

int Wizard::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Wizard::removeConfusion(){
    this -> isConfused = 0;
}

int Wizard::getConfusion(){
    return this -> isConfused;
}

void Wizard::addConfusion(){
    this -> isConfused = 1;
}

int Wizard::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Wizard::getBleed(){
    return this -> isBleeding;
}

int Wizard::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Wizard::getNumberRound(){
    return this -> numberRound;
}

int Wizard::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Wizard::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Wizard::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Wizard::~Wizard(){ // Função Destrutiva
    delete magic;
    delete weapons;
};

/* -------------------- Declaracoes sobre o Troll -------------- */

Troll::Troll(Magic *magic, Weapons *weapons){
    srand(time(0));

    //Propriedades basicas
    this -> classname = "Troll";
    this -> hp = attributes [0]; 
    this -> maxMana = attributes [1];
    this -> physicalStrenght = attributes [2];
    this -> magicalStrenght = attributes [3];
    this -> armor = attributes [4];
    this -> magicalResistance = attributes [5];
    this -> agility = attributes [6];
    this -> maxSpecial = 50;
    this -> specialPoints = 0;
    this -> magic = magic;
    this -> weapons = weapons;
    this -> isPoisoned = 0;
    this -> isConfused = 0;
    this -> rounds = 0;
    this -> maxHp = attributes[0];

    magic -> initialMana(this-> maxMana);
    weaponIndex[0] = 0;
    weaponIndex[1] = 2;
    spellIndex[0] = 5;

}

int Troll::dodgeCalculation(){
    int dodge = (rand() % 100) + 1;

    if(dodge < this->agility/2){
        cout<<"|O personagem se Esquivou.|";
        sleep(2);
        return 1;
    }else{
        return 0;
    }
}

int Troll::receiveDamagePhys(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->armor / 2)/(100.0)));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
        this -> hp = 0;
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}

int Troll::receiveDamageMag(int dmgBase){
    if (dodgeCalculation() == 1){
        return 0;
    }

    float dmg = dmgBase;
    float effectiveDamage2 = dmg - (dmg*((float)(this->magicalResistance / 2)/(100.0) ));
    int effectiveDamage = effectiveDamage2;

    if(effectiveDamage > this -> hp){
      this -> hp = 0;  
    }else{
        this -> hp -= effectiveDamage;
    } 
return effectiveDamage;
}


int Troll::receiveDamageIgnoreArmor(int dmg){
    if(dmg > this -> hp){
        this -> hp = 0;  
    }else{
        this->hp -= dmg;
    }
}



int Troll::physicalDamageCalculation(Character *foe){
    int dmg = (rand() % 200) + 1;
    dmg += this -> weapons ->  returnDamage () - 200;
    float strengh = this -> physicalStrenght;
    dmg *= 1 + (strengh / 100);

    cout<<"\n| Dano Realizado:"<<dmg<<" |\n";
    sleep(1);

    int random = (rand() % 6) + 1;

    if(random == 4){
        if(this->weaponIndex[ this->weapons->weaponLevel ] == 1 || this->weaponIndex[ this->weapons->weaponLevel ] == 5 ){ 
            cout<<"\n| Personagem adquiriu o Status: Sangrando |\n"; foe->addBleed();   
        }
    }
return dmg;
}

int Troll::magicalDamageCalculation (int option){
    int dmg = magic->baseMagicDamage(option);
    float magicalStrengh = this-> magicalStrenght;

    if (dmg != -1){
        dmg *=  1 + (magicalStrengh / 100.0);
        cout<<"\n| Dano Realizado:"<<dmg<<" |\n";

        sleep(3);
        return dmg;
    }else{
        cout << "\n|Mana insuficiente.|\n";
    }
return -1;
}

int Troll::changeWeapon(){
    int a = weapons -> upgrade(weaponIndex);
    sleep(2);
    return a;
}

void Troll::initializeCharacter(){
    weapons->setInitialDamage(weaponIndex[0]);
    magic->initialMana(maxMana);
}

int Troll::print(){return hp;}

int Troll::showMagicMenu(Character *p2){
    while(1){
        cout << string( 100, '\n' );
        cout<<"|Selecione sua Magia: |\n";

        int counter = 0;
        cout<<"0. Voltar\n";

        for(int i : this->spellIndex){
            if(i == -1){break;}
            counter++;
            cout<<counter<<". "<<magic->magicName[i]<<"\n";
        }

        int breaker = 0;
        int answer = 0;

        while(1){
            cout<<"\n";
            cout<<": ";

            cin>>answer;

            if(answer == 0){return -2;}
            for(int i = 0; i < counter; i++ ){
                if(answer - 1 == i){breaker = 1; break;}
            }

            if(breaker == 1){ break;}else{ cout<<"Opcao Invalida. Tente denovo:\n"; }
        }

        if(magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if(magic->typeMagic[ spellIndex[answer-1] ] == 0){ 
                
                hp += magic->magic[answer - 1]; magic->mana -= magic->manaWaste[ spellIndex[answer-1] ]; 
                cout<<"\n|Personagem Curou:"<<magic->magic[answer - 1]<<" pontos de vida.|\n";  
                
                if(this->hp > this->maxHp){hp = maxHp;}
                sleep(3);
                return 0; 
                } 
        }

        int random = 0;
        int dmg = 0;

        if(magic->typeMagic[ spellIndex[answer-1] ] != 0 && magic->mana > magic->manaWaste[ spellIndex[answer-1] ]){
            if( magic->typeMagic[ spellIndex[answer-1] ] == 2){ random = (rand() % 5) + 1; if(random == 3 || random == 2){ p2->addPoison(); cout<<"\n|Personagem recebeu o Status: Envenenado|\n\n";} }
            if( magic->typeMagic[ spellIndex[answer-1] ] == 3){ random = (rand() % 7) + 1; if(random == 3 || random == 2){ p2->addConfusion(); cout<<"\n|Personagem recebeu o Status: Confuso|\n";} }
            dmg = magicalDamageCalculation(spellIndex[answer-1]);
            return dmg;
        }
        if (magic->mana < magic->manaWaste[ spellIndex[answer-1] ]){cout<<"\n|Pontos de Mana insuficiente para realizar essa açao|\n"; return -2;}
    }
    cout<<"\n";
}

int Troll::addMana(){
    int extraMana = magic->manaEveryRound();
    if(extraMana > maxMana){
        this->magic->mana = maxMana;
    }
}

void Troll::checkStats(Character *p2){
    float percentage = (float)(this->hp) / (float)(this->maxHp); 
    float lifeDivisor = this->maxHp / 10;

    percentage *= 100;
    int counter = 1;

    cout << string( 100, '\n' );
    cout<<"|Status do Personagem("<<this->classname<<")|";
    cout << string(2, '\n');

    cout<<"HP:"<<(int)(percentage)<<"%"<<" ("<<this->hp<<"hp )"<<"\n";
    cout<<"-Mana: "<<this->magic->mana<<"\n";
    cout<<"-Ataque Especial:" << "(MAX-"<< this->maxSpecial <<"): "<<this->specialPoints<<"\n";
    cout<<"-Arma atual: "<<weapons->currentWeaponName<<" ( Dano: "<<weapons->weaponDamage<<" )"<<"\n\n";

    cout<<"-Envenenado: ";
    if(this->getPoison() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}
    
    cout<<"-Sangrando: ";
    if(this->getBleed() == 1){cout<<"Sim\n";}else{ cout<<"Nao\n";}


    cout<<"...........................................\n";

    counter = 1;
    percentage = (float)(p2->returnHp()) / (float)(p2->returnMaxHp()); 
    lifeDivisor = p2->returnMaxHp()  / 10;
    percentage *= 100;

    int keyPressed;

    while(1){
        cout<<"DIGITE 0 PARA SAIR\n";
        cout<<":";
        cin>>keyPressed;

        if(keyPressed == 0){ break; }
    }
}

int Troll::returnHp(){
    return this->hp;
}

int Troll::returnMaxHp(){
    return this->maxHp;
}


int Troll::addSpecialPoints(){
    if(specialPoints < maxSpecial){
        specialPoints += 10;
    } 
}

int Troll::getSpecialPoints(){
    return this -> specialPoints;
}

int Troll::getMaxSpecialPoints(){
    return this -> maxSpecial;
}

//O Especial do Troll aumenta sua armadura fisica, hp máximo e aumenta seu hp atual por 1/5 do máximo.
int Troll::useSpecial(Character *foe){
    cout << "\n|Troll ativa -Faminto como um Troll- |\n";

    this -> armor = 90;
    this -> maxHp = 4000;
    this -> hp = (hp+(maxHp/5));

    sleep(3);

return 0;
}

int Troll::bulKathos(){
    int dmg = 700, critical;
    float strengh = this -> physicalStrenght;
    critical = (rand () % 3);

    if(critical == 3){
        dmg *= 2 + (strengh / 100);
    }else{
        dmg *= 1 + (strengh / 100);
    }
    
    cout<<"\n|Dano realizado: "<<dmg<<" -Pesongem conseguiu usar a BUL-KHATOS(ESPADA LENDARIA)-|\n";

    sleep(3);

return dmg;
}

void Troll::removePoison(){
    this -> isPoisoned = 0;
}

int Troll::getPoison(){
    return this -> isPoisoned;
}

int Troll::addPoison(){
    this -> isPoisoned = 1;
    return 0;
}

void Troll::removeConfusion(){
    this -> isConfused = 0;
}

int Troll::getConfusion(){
    return this -> isConfused;
}

void Troll::addConfusion(){
    this -> isConfused = 1;
}

int Troll::removeBleed(){
    this -> isBleeding = 0;
    return 0;
}

int Troll::getBleed(){
    return this -> isBleeding;
}

int Troll::addBleed(){
    this->isBleeding = 1;
    return 0;
}

int Troll::getNumberRound(){
    return this -> numberRound;
}

int Troll::returnDamageEnemy(){
    return this->weapons->weaponDamage;
}

string Troll::returnWeaponStringEnemy(){
    return this->weapons->currentWeaponName;
}

void Troll::changeEnemyWeaponLevel(){
    this->weapons->weaponLevel = 0;
    this->weapons->weaponDamage = weapons->weapons[ weaponIndex[0] ];
    this->weapons->currentWeaponName = weapons->weaponName[ weaponIndex[0] ];
}

Troll::~Troll(){ // Função Destrutiva
    delete magic;
    delete weapons;
};