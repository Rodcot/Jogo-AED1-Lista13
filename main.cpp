#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "declarations.h"

unsigned int sleep(unsigned int seconds);

int main(){
    //Declarando variaveis que serao usadas em varios escopos.
    int rand1,rand2,rand3;
    int phDamageP1, phDamageP2, mgDamageP1, mgDamageP2;
    int checkPhAttackP1 = 0,checkMgAttackP1 = 0,checkBulKathosP1 = 0;
    int checkPhAttackP2 = 0,checkMgAttackP2 = 0,checkBulKathosP2 = 0;

    //Criando player 1
    Character *p1;
    Weapons *wp1 = new Weapons();
    Magic *mp1 = new Magic();

    int menuP1;
    cout << string( 100, '\n' );
    cout << "\n" << "Player 1, Qual o seu personagem?\n" << "|1- Guerreiro|2- Ladrao|3- Mago|4- Paladino|5- Animal|6- Troll|7- Dragao|8- Zumbi|\n" <<":";
    cin >> menuP1;

    if(menuP1 == 1){
        p1 = new Warrior (mp1, wp1); 
        p1 -> initializeCharacter();
    }else if(menuP1 == 2){
        p1 = new Thief (mp1, wp1);  
        p1 -> initializeCharacter();
    }else if(menuP1 == 3){
        p1 = new Wizard (mp1, wp1); 
        p1 -> initializeCharacter();
    }else if(menuP1 == 4){
        p1 = new Paladin (mp1, wp1); 
        p1 -> initializeCharacter();
    }else if(menuP1 == 5){
        p1 = new Animal(mp1, wp1);
        p1 -> initializeCharacter();        
    }else if(menuP1 == 6){
        p1 = new Troll (mp1, wp1);
        p1 -> initializeCharacter();        
    }else if(menuP1 == 7){
        p1 = new Dragon (mp1, wp1);
        p1 -> initializeCharacter();        
    }else if(menuP1 == 8){
        p1 = new Zombie (mp1, wp1);
        p1 -> initializeCharacter();        
    }else{
        cout << "Operacao invalida" << "\n";
    }

    //Criando player 2
    Character *p2;
    Weapons *wp2 = new Weapons();
    Magic *mp2 = new Magic();

    //Menu
    int menuP2;
    cout << string( 100, '\n' );
    cout << "\n" << "Player 2, Qual o seu personagem?\n" << "|1- Guerreiro|2- Ladrao|3- Mago|4- Paladino|5- Animal|6- Troll|7- Dragao|8- Zumbi|\n" <<":";
    cin >> menuP2;

    if(menuP2 == 1){
        p2 = new Warrior (mp2, wp2); 
        p2 -> initializeCharacter();
    }else if(menuP2 == 2){
        p2 = new Thief (mp2, wp2);  
        p2 -> initializeCharacter();
    }else if(menuP2 == 3){
        p2 = new Wizard (mp2, wp2); 
        p2 -> initializeCharacter();
    }else if(menuP2 == 4){
        p2 = new Paladin (mp2, wp2); 
        p2 -> initializeCharacter();
    }else if(menuP2 == 5){
        p2 = new Animal(mp2, wp2);
        p2 -> initializeCharacter();        
    }else if(menuP2 == 6){
        p2 = new Troll (mp2, wp2);
        p2 -> initializeCharacter();        
    }else if(menuP2 == 7){
        p2 = new Dragon (mp2, wp2);
        p2 -> initializeCharacter();        
    }else if(menuP2 == 8){
        p2 = new Zombie (mp2, wp2);
        p2 -> initializeCharacter();        
    }else{
        cout << "Operacao invalida" << "\n";
    }

    //Turno do Player 1
    while(1){
        srand(time(0));
        rand1 = (rand() % 5) + 1;
        rand2 = (rand() % 3) + 1;

        if(menuP1 == 8){
            if( p1->getNumberRound() != -1){
                p1->useSpecial(p2);
            }
        }

        if(p1 -> print() > 0 && p2 -> print() > 0){
            rand3 = (rand() % 4 ) + 1;
            int magicMenu, specialChanceP1, checkWeapon, roundsP1;

            //Calculando se a arma vai ser especial.
            specialChanceP1 = (rand()% 100 ) + 1;

            //Menu
            int p1Action;
            cout << string( 100, '\n' );

            if( p1->getBleed() == 1){ p1->receiveDamageIgnoreArmor(30); cout<<"\n|Status: Sangrando(-30 de HP)|\n"; sleep(2); if(rand3 == 2){ p1->removeBleed();  cout<<"\n|Status de Sangramento Curado|\n"; sleep(2); }   }
            if( p1->getPoison() == 1){ p1->receiveDamageIgnoreArmor(50); cout<<"\n|Status: Envenenado(-50 de HP)\n"; sleep(2); if(rand1 == 2){ p1->removePoison();  cout<<"\n|Status de Envenenamento Curado|\n";  sleep(2);}   }
        
        while(1){
            cout << "\nPlayer 1:\n" << "1- Ataque fisico\n2- Usar magia\n3- Melhorar arma\n4- Checar Status\n5- Ataque especial\n:";
            if (p1-> getSpecialPoints() == p1 -> getMaxSpecialPoints()){
                cout << "*(Ataque especial Disponivel)\n:";
            }

            int rememberAction;
            cin >> p1Action;
            rememberAction = p1Action;

            rand2 = (rand() % 2) + 1;

            if(p1->getConfusion() == 1){ cout<<"\n|Voce se confundiu e perdeu o turno|\n"; sleep(3); p1Action = 10; if(rand2 == 1){ p1->removeConfusion(); p1Action = rememberAction; cout<<"\n|Status de Confusao Curado|\n"; sleep(3); }   }

            switch (p1Action){
            case 1: //Ataque fisico
                if (specialChanceP1 < 5){
                    phDamageP1 = p1 -> bulKathos();
                    p2->receiveDamagePhys(phDamageP1);
                    checkBulKathosP1 ++;
                    p1->addMana();
                    p1->addSpecialPoints();
                    break;
                }else{
                    phDamageP1 = p1->physicalDamageCalculation(p2);
                    checkPhAttackP1 ++;
                    p2->receiveDamagePhys(phDamageP1);
                    p1->addMana();
                    p1->addSpecialPoints();
                    break;
                }
            case 2: //Usar magia
                magicMenu = p1->showMagicMenu(p2);
                if (magicMenu > 0){
                    mgDamageP1 = magicMenu;
                    p2->receiveDamageMag(magicMenu);
                }
                if(magicMenu == -2){ sleep(2); cout << string( 100, '\n' ); continue;}
                p1->addSpecialPoints();
                break;

            case 3: //Melhorar Arma
                checkWeapon = p1->changeWeapon();
                if(checkWeapon == 1){
                    p1->addMana();
                    p1->addSpecialPoints();
                    break;
                }
                else{
                    cout << string( 100, '\n' );
                }
                continue;

            case 4: //Checar Status
                p1->checkStats(p2);
                cout << string( 100, '\n' );
                continue;

            case 5: //Ataque especial
                if(p1 -> getSpecialPoints() == p1 -> getMaxSpecialPoints()){
                    p1 -> useSpecial(p2);
                    break;
                }else{
                    cout << "|Ataque especial indisponivel|\n";
                       sleep(3);
                       cout << string( 100, '\n' );
                    continue;
                }

            case 99:
                p1->addSpecialPoints();
                break;

            default:
                break;
            }
            break;
            }
        }
        else{ //Morte do Player 1
            cout << "Player 1 perdeu todo o seu hp\n|VITORIA DO PLAYER 2|\n";

            delete p1,p2,mp1,wp1,mp2,wp2;
            break;
        }
    
        //Turno do Player 2
        rand1 = ((rand() % 5) + 1);
        rand3 = ((rand() % 4) + 1);
        rand2 = ((rand() % 3) + 1);

        if(menuP2 == 8){
            if( p2->getNumberRound() != -1){
                p2->useSpecial(p2);
            }
        }

        if (p1 -> print() > 0 && p2 -> print() > 0){
            int magicMenu,specialChanceP2,checkWeapon,roundsP2;

            //Chance da arma especial
            specialChanceP2 = (rand()% 100) + 1;
            
            int p2Action;
            //Menu
            cout << string( 100, '\n' );
            if( p2->getBleed() == 1){ p2->receiveDamageIgnoreArmor(30); cout<<"\n|Status: Sangrando(-30 de HP)|\n"; sleep(2); if(rand3 == 2){ p2->removeBleed(); cout<<"\n|Status de Sangramento Curado|\n"; sleep(2); }   }
            if( p2->getPoison() == 1){ p2->receiveDamageIgnoreArmor(50); cout<<"\n|Status: Envenenado(-50 de HP)\n"; sleep(2); if(rand1 == 2){ p2->removePoison(); cout<<"\n|Status de Envenenamento Curado|\n";  sleep(2); }   }
        
        while(1){
            cout << "\nPlayer 2:\n" << "1- Ataque fisico\n2- Usar magia\n3- Melhorar arma\n4- Checar Status\n5- Ataque especial\n:";
            if (p2-> getSpecialPoints() == p2 -> getMaxSpecialPoints()){
                cout << "*(Ataque especial Disponivel)\n:";
            }
            cin >> p2Action;

            int rememberAction2;
            rememberAction2 = p2Action;
            rand2 = (rand() % 2) + 1;

            if( p2->getConfusion() == 1){ cout<<"\n|Voce se confundiu e perdeu o turno|\n"; sleep(3); p2Action = 10; if(rand2 == 1){ p2->removeConfusion(); p2Action = rememberAction2; cout<<"\n|Status de Confusao Curado|\n"; sleep(3); }   }

            switch (p2Action){
            case 1: //Ataque fisico
                if (specialChanceP2 < 5){
                    phDamageP1 = p2 -> bulKathos();
                    checkBulKathosP1 ++;
                    p1->receiveDamagePhys(phDamageP1);
                    p2->addMana();
                    p2->addSpecialPoints();
                    break;
                }else{
                    phDamageP1 = p2->physicalDamageCalculation(p1);
                    checkPhAttackP2 ++;
                    p1->receiveDamagePhys(phDamageP1);
                    p2->addMana();
                    p2->addSpecialPoints();
                    break;
                }

            case 2: //Usar magia
                magicMenu = p2->showMagicMenu(p1);
                if (magicMenu > 0){
                    mgDamageP2 = magicMenu;
                    p1->receiveDamageMag(mgDamageP2);
                }
                if(magicMenu == -2){ sleep(2); cout << string( 100, '\n' ); continue;}
                p2->addSpecialPoints();
                break;

            case 3: //Melhorar arma
                checkWeapon = p2->changeWeapon();
                if (checkWeapon == 1){
                    p2->addMana(); 
                    p2->addSpecialPoints();
                    break;
                }

                else{
                    cout << string( 100, '\n' );
                }
                continue;

            case 4: //Checar Status
                p2->checkStats(p1);
                cout << string( 100, '\n' );
                continue;

            case 5: //Ataque especial
                if(p2-> getSpecialPoints() == p2 -> getMaxSpecialPoints()){
                    p2 -> useSpecial(p1);
                    break;
                }else{
                    cout << "|Ataque especial indisponivel|\n";
                       sleep(3);
                       cout << string( 100, '\n' );
                    continue;
                }
            case 99:
                p2->addSpecialPoints();
                break;

            default:
                break;
            }
            break;
            }
        }

        else{ //Morte do Player 2
            cout << "Player 1 perdeu todo o seu hp\n|VITORIA DO PLAYER 2|\n";
            
            delete p1,mp1,wp1,p2,mp2,wp2;
            
            break;
        }
    }
}