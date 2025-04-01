// Copyright 2022 UNN-IASR
#include <iostream>
#include "Automata.h"

int main() {
    Automata *coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->getMenu();
    coffeMachine->coin(100);
    std::cout << "buy Cappuccino: " << std::endl;
    std::cout << "change: " << coffeMachine->choise("Cappuccino") << std::endl;
    coffeMachine->coin(10);
    std::cout << "buy Cola: " << std::endl;
    std::cout << "change: " << coffeMachine->choise("Cola") << std::endl;
    std::cout << "buy Cappuccino: " << std::endl;
    coffeMachine->coin(10);
    std::cout << "change: " << coffeMachine->choise("Cappuccino") << std::endl;
    delete (coffeMachine);
}
