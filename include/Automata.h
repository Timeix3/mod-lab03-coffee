// Copyright 2022 UNN-IASR
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <map>
#include <string>

enum class State {
    OFF, WAIT, ACCEPT, CHECK, COOK
};

class Automata {
 private:
    unsigned int cash;
    std::map<std::string, unsigned int> menu;
    State state;
    bool check(std::string name);
    void cook();
    unsigned int finish(std::string name);
 public:
    Automata();
    State getState();
    void on();
    void off();
    void coin(int cash);
    unsigned int cancel();
    void getMenu();
    unsigned int choise(std::string name);
};

#endif  // INCLUDE_AUTOMATA_H_
