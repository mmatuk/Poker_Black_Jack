//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Account.h
//Description:
//  Bank account that will store the users infomation.
//      1) Balance
//      2) Current Bet being made
//      3) Total Winnings make during play
//Editor:                          Emacs
//*******************************************************

#ifndef Account_H
#define Account_H

#include <string>
#include "DisplayMod.h"

class Account
{
  private:
    std::string uname;
    int balance; // blance of bank account
    int currentBet; // current bet
    int totalWinnings; // total winning of current game
    int const MAX_WIDTH;
    
  public:
    //Constructor & Destructors
    Account();
    Account(int);
    Account(int, int);

    //functions
    void displayAccount();
    int didWinLose(bool const, double const); // update balnace  and return new balance

    //Getters
    std::string getUname();
    int getBal();
    int getWin();
    int getBet();

    // Setters
    void setUname(std::string);
    int setBet(int);
    void addToBal(int);
    void addToWin(int);
};

#endif