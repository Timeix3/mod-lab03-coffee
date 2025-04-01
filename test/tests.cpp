// Copyright 2022 GHATestTeam
#include <gtest/gtest.h>
#include <string>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOff) {
    Automata* coffeMachine = new Automata();
    EXPECT_EQ(coffeMachine->getState(), State::OFF);
    delete(coffeMachine);
}

TEST(AutomataTest, CanTurnOnFromOff) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    EXPECT_EQ(coffeMachine->getState(), State::WAIT);
    delete(coffeMachine);
}

TEST(AutomataTest, CanTurnOffFromWait) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->off();
    EXPECT_EQ(coffeMachine->getState(), State::OFF);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotTurnOffFromAccept) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(150);
    coffeMachine->off();
    EXPECT_EQ(coffeMachine->getState(), State::ACCEPT);
    delete(coffeMachine);
}

TEST(AutomataTest, CanAddCoinsInWaitState) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(150);
    EXPECT_EQ(coffeMachine->getState(), State::ACCEPT);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotAddCoinsInOffState) {
    Automata* coffeMachine = new Automata();
    coffeMachine->coin(150);
    EXPECT_EQ(coffeMachine->getState(), State::OFF);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotGetMenuInOffState) {
    Automata* coffeMachine = new Automata();
    testing::internal::CaptureStdout();
    coffeMachine->getMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Incorrect state\n");
    delete(coffeMachine);
}

TEST(AutomataTest, CanChooseDrinkWithEnoughCash) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(200);
    unsigned int change = coffeMachine->choise("Latte");
    EXPECT_EQ(coffeMachine->getState(), State::WAIT);
    EXPECT_EQ(change, 100);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotChooseDrinkWithNotEnoughCash) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(50);
    testing::internal::CaptureStdout();
    unsigned int returnedCash = coffeMachine->choise("Cappuccino");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(coffeMachine->getState(), State::WAIT);
    EXPECT_EQ(returnedCash, 50);
    EXPECT_EQ(output, "Not enough money to buy\n");
    delete(coffeMachine);
}

TEST(AutomataTest, CanCancelInAcceptState) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(150);
    unsigned int returnedCash = coffeMachine->cancel();
    EXPECT_EQ(returnedCash, 150);
    EXPECT_EQ(coffeMachine->getState(), State::WAIT);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotChooseDrinkInOffState) {
    Automata* coffeMachine = new Automata();
    EXPECT_EQ(coffeMachine->choise("Espresso"), 0);
    delete(coffeMachine);
}

TEST(AutomataTest, CannotChoiseWrongDrink) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    coffeMachine->coin(150);
    testing::internal::CaptureStdout();
    coffeMachine->choise("Cola");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "The drink is not on the menu\n");
    delete(coffeMachine);
}

TEST(AutomataTest, CancelReturnsZeroIfNotInAcceptState) {
    Automata* coffeMachine = new Automata();
    coffeMachine->on();
    unsigned int returnedCash = coffeMachine->cancel();
    EXPECT_EQ(returnedCash, 0);
    delete(coffeMachine);
}
