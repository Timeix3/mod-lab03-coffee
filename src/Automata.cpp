// Copyright 2022 UNN-IASR
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Automata.h"

Automata::Automata() {
    menu = { {"Espresso", 80}, {"Latte", 100},
    {"Cappuccino", 60}, {"Americano", 50} };
    cash = 0;
    state = State::OFF;
}

State Automata::getState() {
    return state;
}

void Automata::on() {
    if (state == State::OFF) state = State::WAIT;
    else std::cout << "Incorrect state" << std::endl;
    return;
}

void Automata::off() {
    if (state == State::WAIT) state = State::OFF;
    else std::cout << "Incorrect state" << std::endl;
    return;
}

void Automata::coin(int cash) {
    if (state == State::WAIT || state == State::ACCEPT) {
        state = State::ACCEPT;
        this->cash += cash;
        return;
    }
    else std::cout << "Incorrect state" << std::endl;
    return;
}

unsigned int Automata::cancel() {
    if (state == State::ACCEPT || state == State::CHECK) {
        state = State::WAIT;
        unsigned int returnedCash = cash;
        cash = 0;
        return returnedCash;
    }
    else std::cout << "Incorrect state" << std::endl;
    return 0;
}

void Automata::getMenu() {
    if (state == State::WAIT || state == State::ACCEPT) {
        for (const auto& [name, price] : menu)
            std::cout << "Name: " << name << ", Price: " << price << std::endl;
        return;
    }
    else std::cout << "Incorrect state" << std::endl;
    return;
}

bool Automata::check(std::string name) {
    if (menu[name] <= cash) return true;
    return false;
}

void Automata::cook() {
    state = State::COOK;
    std::cout << "Cooking has started..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Cooking is complete" << std::endl;
    return;
}

unsigned int Automata::finish(std::string name) {
    state = State::WAIT;
    unsigned int change = cash - menu[name];
    cash = 0;
    return change;
}

unsigned int Automata::choise(std::string name) {
    if (state == State::ACCEPT) {
        state = State::CHECK;
        if (menu.find(name) == menu.end()) {
            std::cout << "The drink is not on the menu" << std::endl;
            return 0;
        }
        if (check(name)) {
            cook();
            return finish(name);
        }
        std::cout << "Not enough money to buy" << std::endl;
        return cancel();
    }
    std::cout << "Incorrect state" << std::endl;
    return 0;
}
