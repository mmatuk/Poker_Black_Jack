//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  CardDeck.h
//Description:
//  This class will contains a deck of 52 cards that can
//  be shuffled and accessed from another class in order
//  to create a casino card game.
//Editor:                          Emacs
//*******************************************************

#ifndef CardDeck_H
#define CardDeck_H

#include "ACard.h"
#include "DisplayMod.h"

#define INDEX_SPADE 0
#define INDEX_CLUB 1
#define INDEX_HEART 2
#define INDEX_DIAMOND 3

class CardDeck
{
protected:
  static const int DECK_SIZE;    // Size of Deck
  static const char suits[4][4]; // Unicode for the Pctures of the Suits

private:
  //Variables
  ACard *deck;  // Array of Cards
  int topCard;  // -1 if no cards left in deck, else index of top card
  int numDecks; // Number of playable decks

  // Functions
  void createDeck();   // create deck
  int moveTopCard();   // Move top card to next card
  void resetTopCard(); // Rest the top card index to 0

public:
  //Constryctors and Destructors
  CardDeck();
  CardDeck(int); // passed number of playable decks
  //~CardDeck();

  //Functions
  void displayCards(ACard const *hand[], int);            // dispaly cards
  void displayCards(ACard const *hand[], int, int const); // dispaly cards with some face down
  void shuffleDeck();                                     // shuffle the deck randomly
  ACard *getDeck();                                       // return deck
  int getDeckSize();                                      // Return the size of Deck
  ACard *removeTopCard();                                 // return top card of deck
};

#endif