//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  ACard.cpp
//Description:
//
//Editor:                          Emacs
//*******************************************************

#include <string>

#include "ACard.h"

ACard::ACard()
{
}

ACard::ACard(char const n, char *suit)
{
    num = n;
    pSuit = suit; //suit in unicode
}

bool ACard::operator>(const ACard &c1) { return num > c1.num; }
bool ACard::operator>=(const ACard &c1) { return num >= c1.num; }
bool ACard::operator<(const ACard &c1) { return num < c1.num; }
bool ACard::operator<=(const ACard &c1) { return num <= c1.num; }
bool ACard::operator==(const ACard &c1) { return (num != c1.num); }
bool ACard::operator!=(const ACard &c1) { return (num != c1.num); }

std::string ACard::getDisplayNum() const
{
    if (num >= 2 && num <= 10)
    {
        return std::to_string(num);
    }
    else if (num == JACK)
    {
        return "J";
    }
    else if (num == QUEEN)
    {
        return "Q";
    }
    else if (num == KING)
    {
        return "K";
    }
    else if (num == ACE)
    {
        return "A";
    }
    else
    {
        return NULL; 
    }
}
