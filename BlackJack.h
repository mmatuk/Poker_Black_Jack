//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/24/2017
//Source File:                  BlackJack.h
//Description:
//  This calass will contain all the need info to play a
//  black jack game.
//Editor:                          Emacs
//*******************************************************
#include "Account.h"
#include "CardDeck.h"

#ifndef BlackJack_H
#define BlackJack_H

class BlackJack : public CardDeck
{
public:
  //Constructors
  BlackJack();
  BlackJack(Account &);
  BlackJack(Account &, int);

  //Functions
  void playGame();            // play a game of black jack and ask to play again
  void setAccount(Account &); // set eh users account

private:
  //Variables
  ACard **usrHand; // users hand
  int usrHandSize; // amount of cards in users hand
  int usrHandValue;
  int insurance;

  ACard **dealerHand; //dealsers hand
  int dealerHandSize; // amount of cards in dealers hand
  int dealerHandValue;

  Account *acc; // Users bank account

  //Reward ammount multiplier
  static const double PlAYER_BLACK_JACK;
  static const double PLAYER_WON;
  static const double PLAYER_LOST;
  static const double PLAYER_TIE;

  const int DISPLAY_WIDTH;  // max width to allow for displaying
  const int MAX_HAND_SIZE;  // max size for a hand
  static const int MAX_BET; // max allowed bet.

  //Functions
  void drawInitHands();                                                      // Draw the init two cards for the dealer and displays
  void usrHitStay();                                                         // ask user to hit or stay
  bool isBust(ACard const **, int const, int &);                             // determine if current hand is bust or not
  void dealerHitStay();                                                      // ask dealer to hit or stay
  ACard *drawCard();                                                         // draw the next card fromm the deck
  void calResult();                                                          // determine oif the
  void displayIntro();                                                       // dispalay the current game title
  void updateDisplay(int const);                                                      // update the dispaly
  void clearHands();                                                         // reset the hands for another game
  bool yesNo(std::string const, char const, char const);                     // chekc for only char or char input from keyboard
  void placeBet();                                                           // user places bet
  bool determineInsurance();                                                 // dealer has an Ace as open card
  void initVar();                                                            // Init all Vars
  void displayResults(std::string const, bool const, double const, bool const); // Display the results of the hand
};

#endif /* BlackJack_H */