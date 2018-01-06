//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  Account.cpp
//Description:
//  Bank account that will store the users infomation.
//      1) Balance
//      2) Current Bet being made
//      3) Total Winnings make during play
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "Account.h"

//int const MAX_WIDTH = 81; // width of display for uname setw()

Account::Account() : MAX_WIDTH(81)
{
    uname = "";
    balance = 0;       // blance of bank account
    currentBet = 0;    // current bet
    totalWinnings = 0; // total winning of current game
}

Account::Account(int bal, int width) : balance(bal), MAX_WIDTH(width)
{
    uname = "";
    balance = 0;       // blance of bank account
    currentBet = 0;    // current bet
    totalWinnings = 0; // total winning of current game
}

/**
 * Displays the info about the account.
 * ie:
 *      UserName: Matt            Account Balance: 1000000
 *      Current Bet: 50           Total Winnings: 5000
 */
void Account::displayAccount()
{
    std::stringstream ss;
    ss.imbue(std::locale("")); // use local curencey
    std::string strBet, strWin, strBal;
    std::string displayName = "UserName: ";
    std::string displayBal = "Account Balance: $";
    std::string displayBet = "Bet:      $";
    std::string displayWin = "Total Winnings: ";

    //Set bet string
    ss << std::fixed << currentBet;
    strBet = ss.str();
    ss.str(""); //clear contents

    //Set bal string
    ss << std::fixed << balance;
    strBal = ss.str();
    ss.str(""); //clear contents

    //display line 1
    std::cout << displayName << uname
              << std::setw(MAX_WIDTH - displayName.length() - uname.length() - strBal.length())
              << displayBal << strBal << std::endl;

    //set winnings string
    if (totalWinnings < 0) // displays red text if negitive winnings
    {
        ss << "-$" << std::fixed << -totalWinnings;
        strWin = ss.str();

        //display line two
        std::cout << displayBet << strBet
                  << std::setw(MAX_WIDTH - displayBet.length() - strBet.length() - strWin.length())
                  << displayWin << DISPLAY_RED << strWin << DISPLAY_CLEAR << std::endl;
    }
    else
    {
        ss << "$" << std::fixed << totalWinnings;
        strWin = ss.str();

        //display line two
        std::cout << displayBet << strBet
                  << std::setw(MAX_WIDTH - displayBet.length() - strBet.length() - strWin.length())
                  << displayWin << strWin << std::endl;
    }
}

/**
 * Update the account balnace with how much the user won or lost acording to the bet placed.
 * 
 * @param didWin Did the user win or lose.
 * @param multipler Ammount to multiply the bet by if the user won.
 * 
 * @return New bank balance.
 */
int Account::didWinLose(bool const didWin, double const multipler)
{
    if (didWin) // User won
    {
        int winnings = currentBet * multipler;    // ammount won
        balance = balance + winnings;             // add to balance ammount won
        totalWinnings = totalWinnings + winnings; // add to total winnings the ammount won
        currentBet = 0;                           // reset bet
        return balance;
    }
    else // user lost the ammount bet
    {
        balance = balance - currentBet; // subtract current bet from
        totalWinnings = totalWinnings - currentBet;
        currentBet = 0; // reset bet
        return balance;
    }
}

void Account::setUname(std::string name)
{
    uname = name;
}

void Account::addToBal(int add)
{
    balance = balance + add;
}

void Account::addToWin(int add)
{
    totalWinnings = totalWinnings + add;
}

/**\
 * Set the ammount to be bet. Only allows bet amount to not exceed the total balance.
 * 
 * @return -1 if bet exceeds balance, bet ammount if not.
 */
int Account::setBet(int bet)
{
    if (bet > balance)
    {
        return -1;
    }
    else
    {
        currentBet = bet;
        return currentBet;
    }
}

std::string Account::getUname()
{
    return uname;
}

int Account::getBal()
{
    return balance;
}

int Account::getBet()
{
    return currentBet;
}

int Account::getWin()
{
    return totalWinnings;
}