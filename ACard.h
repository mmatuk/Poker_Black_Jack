//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  ACard.h
//Description:
//
//Editor:                          Emacs
//*******************************************************

#ifndef ACard_H
#define ACard_H

#include <string>

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

class ACard
{
  friend class CardDeck;

public:
  int num;           //value of card
  const char *pSuit; //suit in unicode

  ACard();
  ACard(char const, char *);
  std::string getDisplayNum() const;
  bool operator>(const ACard &c1);
  bool operator>=(const ACard &c1);
  bool operator<(const ACard &c1);
  bool operator<=(const ACard &c1);
  bool operator==(const ACard &c1);
  bool operator!=(const ACard &c1);
};

#endif