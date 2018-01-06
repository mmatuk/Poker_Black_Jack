//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/15/2017
//Source File:                  Poker.h
//Description:
//  Game to play 5 Card Draw poker.
//
//  The user will be given five cards at first. Then asked
//  if they would like any of the five cards to be replaced.
//  After selection of th cards to replace. The game will
//  determine if the user won any money.
//
//  Standard hands apply when determining the ammoount won.
//
//  Hands are:
//      1)
//      2)
//      3)
//
//Editor:                          Emacs
//*******************************************************
#include <string>
#include "CardDeck.h"
#include "Account.h"

#ifndef Poker_H
#define Poker_H

class Poker : public CardDeck
{
public:
  //Functions
  Poker();
  Poker(Account &);          // constructor for passed account.
  void playGame();           // plays a hand of poker and asks the user if they want to play again after
  void playGameAdmin();      // Allow user to enter hand
  void setAccout(Account &); // Sets the current accoun to be used

private:
  //var
  ACard **hand;            // hand for user
  Account *acc;            //Pointer to the users account.
  int const DISPLAY_WIDTH; // max width to allow for displaying

  //Reward ammount multiplier
  static const int JACK_BETTER;
  static const int TWO_PAIR;
  static const int THREE_KIND;
  static const int STRAIGHT;
  static const int FLUSH;
  static const int FULL_HOUSE;
  static const int FOUR_KIND;
  static const int STRAIGHT_FLUSH;
  static const int ROYAL_STRAIGHT_FLUSH;

  static const int MAX_BET;   // max allowed bet.
  static const int HAND_SIZE; // max size for a hand

  //Functions
  void drawHand();                                           // draw a hand of cards, passed value is amount to draw.
  ACard *drawCard();                                         // draw one card.
  void calResult();                                          // calculate result.
  void displayIntro();                                       // display intro message.
  void updateDisplay();                                      // update display after card exchange
  void stayOrRedraw();                                        // display message asking if stay or redraw current card.
  void stayOrRedrawAdmin();                                   // Allows user to pick cards
  void displayResult(std::string const, int const);          // display the results of the game
  void placeBet();                                           // ask user for a bet
  void determineHand(ACard **, int &, int &, std::string &); // determine the users hand type
  void clearHand();                                          //Clears out users hand
  bool yesNo(std::string const);                             // chekc for only y or n input from keyboard
};

#endif