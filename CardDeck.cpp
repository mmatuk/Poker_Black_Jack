//*******************************************************
//Author:                       Matt Matuk
//Created:                      09/07/2017
//Source File:                  CardDeck.cpp
//Description:
//  This class will contains a deck of 52 cards that can
//  be shuffled and accessed from another class in order
//  to create a casino card game.
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "CardDeck.h"

using namespace std;

const char CardDeck::suits[4][4] = {
	{"\xe2\x99\xa0"},
	{"\xe2\x99\xa3"},
	{"\xe2\x99\xa5"},
	{"\xe2\x99\xa6"}};

const int CardDeck::DECK_SIZE = 52; // Size of Deck

/* 
 *Contructor for createing the deck of cards
 */
CardDeck::CardDeck()
{
	deck = new ACard[DECK_SIZE * 1];
	topCard = 0;
	numDecks = 1;
	createDeck();
}

/* 
 *Contructor for createing the deck of cards
 *
 * @param numberOfDecks The number of playable decks
 */
CardDeck::CardDeck(int numberOfDecks)
{
	deck = new ACard[DECK_SIZE * numberOfDecks];
	topCard = 0;
	numDecks = 1;
	createDeck();
}

/*
 *Creates a Deck of unsorted cards
 */
void CardDeck::createDeck()
{
	for (int i = 0; i < numDecks; i++)
	{
		int index = (i * DECK_SIZE);		 // location of the deck
		for (int suit = 0; suit < 4; suit++) // Loop 4 times once for each suit
		{
			for (int num = 2; num < 15; num++) // sets card value and suit
			{
				if (num < 11) // Creates the number cards
				{
					deck[index].num = (char)num;
					deck[index].pSuit = suits[suit];
				}
				else
				{
					// Creates the face cards
					switch (num)
					{
					case (11): //Jack Card
					{
						deck[index].num = JACK;
						deck[index].pSuit = suits[suit];
						break;
					}
					case (12): //Queen Card
					{
						deck[index].num = QUEEN;
						deck[index].pSuit = suits[suit];
						break;
					}
					case (13): //King Card
					{
						deck[index].num = KING;
						deck[index].pSuit = suits[suit];
						break;
					}
					case (14): //Ace card
					{
						deck[index].num = ACE;
						deck[index].pSuit = suits[suit];
						break;
					}
					default:
						cout << "Error: Face cards not created properly!";
					}
				}
				index++; //go to next index in the deck
			}
		}
	}
}

/**
 * Displays the passed array of ACard accross the  screen with one card next to each other,
 * up to a max of 13 cards per line.
 * 
 * @param hand The pointer to the array of cards to display
 * @param handSize The ammount of cards to display in the array.
 */
void CardDeck::displayCards(ACard const *hand[], int handSize)
{
	int width = 9;   //width of card
	int height = 11; //height of card
	int handIndex = 0;
	int tmpHandSize = handSize;
	int currentRowSize = 0;
	int rowsOfCards = (handSize / 13) + 1;

	//system("clear");
	do
	{
		if (tmpHandSize > 13)
		{
			currentRowSize = 13;
		}
		else
		{
			currentRowSize = tmpHandSize;
		}

		//Display top line
		for (int col = 0; col < currentRowSize; col++)
		{
			cout << DISPLAY_BLACK;
			cout << "---------";
			cout << DISPLAY_CLEAR;
			cout << " ";
		}
		cout << endl;

		//Display next rows for current row of cards
		for (int row = 2; row <= height - 1; row++)
		{
			for (int index = 0; index < currentRowSize; index++)
			{
				cout << DISPLAY_BACK_WHITE << DISPLAY_BLACK;
				cout << "|";
				if (hand[handIndex]->pSuit == suits[INDEX_HEART] || hand[handIndex]->pSuit == suits[INDEX_DIAMOND])
				{
					cout << DISPLAY_RED;
				}
				switch (row)
				{
					//******************
					//Displays row 2
					//******************
				case 2:
				{
					if (hand[handIndex]->num > 10) // card is face card
					{
						cout << "" << hand[handIndex]->pSuit << hand[handIndex]->getDisplayNum() << "     ";
					}
					else // card is a number card 2 - 10
					{
						cout << "";
						cout.width(2);
						cout << left << (int)hand[handIndex]->num << "     ";
					}
					break;
				}
					//******************
					//Displays row three
					//******************
				case 3:
				{
					if ((int)hand[handIndex]->num >= 4 && (int)hand[handIndex]->num <= 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if ((int)hand[handIndex]->num == 3) // card is 3
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//*****************
					//Displays Row 4
					//*****************
				case 4:
				{
					if (((int)hand[handIndex]->num >= 7 && (int)hand[handIndex]->num <= 10) || (int)hand[handIndex]->num == 2)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*****************
					//Displays Row 5
					//*****************
				case 5:
				{
					if ((int)hand[handIndex]->num == 9 || (int)hand[handIndex]->num == 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*********************
					//Display row 6
					//*********************
				case 6:
				{
					if ((int)hand[handIndex]->num == 2 || (int)hand[handIndex]->num == 4)
					{
						cout << "       ";
					}
					else if ((int)hand[handIndex]->num == 3 || (int)hand[handIndex]->num == 5)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else if ((int)hand[handIndex]->num >= 6 && (int)hand[handIndex]->num <= 8) // 6-8 cards
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if (hand[handIndex]->num == ACE) // Ace card
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//*****************
					//Displays Row 7
					//*****************
				case 7:
				{
					if ((int)hand[handIndex]->num == 9 || (int)hand[handIndex]->num == 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*****************
					//Displays Row 8
					//*****************
				case 8:
				{
					if ((int)hand[handIndex]->num == 2 || (int)hand[handIndex]->num == 8 || (int)hand[handIndex]->num == 10)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//******************
					//Displays row 9
					//******************
				case 9:
				{
					if ((int)hand[handIndex]->num >= 4 && (int)hand[handIndex]->num <= 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if ((int)hand[handIndex]->num == 3) // card is 3
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//******************
					//Displays row 10
					//******************
				case 10:
				{
					if (hand[handIndex]->num > 10) // card is face card
					{
						cout << "     " << hand[handIndex]->getDisplayNum() << hand[handIndex]->pSuit << "";
					}
					else // card is a number card 2 - 10
					{
						cout << "     ";
						cout.width(2);
						cout << right << (int)hand[handIndex]->num << "";
					}
					break;
				}
				default:
				{
					cout << "       ";
					break;
				}
				}
				handIndex++; //move to next card
				cout << DISPLAY_CLEAR;
				cout << DISPLAY_BACK_WHITE << DISPLAY_BLACK;
				cout << "|";
				cout << DISPLAY_CLEAR;
				cout << " ";
			}
			// moves down a line and back to the first card in the hand
			cout << endl;
			handIndex = handIndex - currentRowSize;
		}

		//Display Bottom Card Edge
		for (int col = 0; col < currentRowSize; col++)
		{
			cout << DISPLAY_BLACK;
			cout << "---------";
			cout << DISPLAY_CLEAR;
			cout << " ";
		}
		cout << endl;

		tmpHandSize = tmpHandSize - 13; // amount left to display
		rowsOfCards--;
		handIndex = handIndex + 13;

	} while (tmpHandSize > 0);
}

/**
 * Displays the passed array of ACard accross the  screen with one card next to each other,
 * up to a max of 13 cards per line.
 * 
 * @param hand The pointer to the array of cards to display
 * @param handSize The ammount of cards to display in the array.
 */
void CardDeck::displayCards(ACard const *hand[], int handSize, int const numFaceDown)
{
	int width = 9;   //width of card
	int height = 11; //height of card
	int handIndex = 0;
	int tmpHandSize = handSize;
	int currentRowSize = 0;
	int rowsOfCards = (handSize / 13) + 1;
	int numLeftFaceDown = numFaceDown;
	int faceDown = numLeftFaceDown;
	//system("clear");
	do
	{
		if (tmpHandSize > 13)
		{
			currentRowSize = 13;
		}
		else
		{
			currentRowSize = tmpHandSize;
		}

		//Display top line
		for (int col = 0; col < currentRowSize; col++)
		{
			cout  << DISPLAY_BLACK;
			cout << "---------";
			cout << DISPLAY_CLEAR;
			cout << " ";
		}
		cout << endl;

		//Display next rows for current row of cards
		for (int row = 2; row <= height - 1; row++)
		{
			for (int index = 0; index < currentRowSize; index++)
			{
				cout << DISPLAY_BACK_WHITE << DISPLAY_BLACK;
				cout << "|";
				if (hand[handIndex]->pSuit == suits[INDEX_HEART] || hand[handIndex]->pSuit == suits[INDEX_DIAMOND])
				{
					cout << DISPLAY_RED;
				}
				switch (row)
				{
					//******************
					//Displays row 2
					//******************
				case 2:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if (hand[handIndex]->num > 10) // card is face card
					{
						cout << "" << hand[handIndex]->pSuit << hand[handIndex]->getDisplayNum() << "     ";
					}
					else // card is a number card 2 - 10
					{
						cout << "";
						cout.width(2);
						cout << left << (int)hand[handIndex]->num << "     ";
					}
					break;
				}
					//******************
					//Displays row three
					//******************
				case 3:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num >= 4 && (int)hand[handIndex]->num <= 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if ((int)hand[handIndex]->num == 3) // card is 3
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//*****************
					//Displays Row 4
					//*****************
				case 4:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if (((int)hand[handIndex]->num >= 7 && (int)hand[handIndex]->num <= 10) || (int)hand[handIndex]->num == 2)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*****************
					//Displays Row 5
					//*****************
				case 5:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num == 9 || (int)hand[handIndex]->num == 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*********************
					//Display row 6
					//*********************
				case 6:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num == 2 || (int)hand[handIndex]->num == 4)
					{
						cout << "       ";
					}
					else if ((int)hand[handIndex]->num == 3 || (int)hand[handIndex]->num == 5)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else if ((int)hand[handIndex]->num >= 6 && (int)hand[handIndex]->num <= 8) // 6-8 cards
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if (hand[handIndex]->num == ACE) // Ace card
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//*****************
					//Displays Row 7
					//*****************
				case 7:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num == 9 || (int)hand[handIndex]->num == 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//*****************
					//Displays Row 8
					//*****************
				case 8:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num == 2 || (int)hand[handIndex]->num == 8 || (int)hand[handIndex]->num == 10)
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}

					break;
				}
					//******************
					//Displays row 9
					//******************
				case 9:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if ((int)hand[handIndex]->num >= 4 && (int)hand[handIndex]->num <= 10)
					{
						cout << " " << hand[handIndex]->pSuit << "   " << hand[handIndex]->pSuit << " ";
					}
					else if ((int)hand[handIndex]->num == 3) // card is 3
					{
						cout << "   " << hand[handIndex]->pSuit << "   ";
					}
					else
					{
						cout << "       ";
					}
					break;
				}
					//******************
					//Displays row 10
					//******************
				case 10:
				{
					if (faceDown > 0) // for a face down card
					{
						cout << "       ";
						faceDown--;
					}
					else if (hand[handIndex]->num > 10) // card is face card
					{
						cout << "     " << hand[handIndex]->getDisplayNum() << hand[handIndex]->pSuit << "";
					}
					else // card is a number card 2 - 10
					{
						cout << "     ";
						cout.width(2);
						cout << right << (int)hand[handIndex]->num << "";
					}
					break;
				}
				default:
				{
					cout << "       ";
					break;
				}
				}
				handIndex++; //move to next card
				cout << DISPLAY_CLEAR;
				cout << DISPLAY_BACK_WHITE << DISPLAY_BLACK;
				cout << "|";
				cout << DISPLAY_CLEAR;
				cout << " ";
			}
			// moves down a line and back to the first card in the hand
			cout << endl;
			handIndex = handIndex - currentRowSize;
			faceDown = numLeftFaceDown;
		}

		//Display Bottom Card Edge
		for (int col = 0; col < currentRowSize; col++)
		{
			cout << DISPLAY_BLACK;
			cout << "---------";
			cout << DISPLAY_CLEAR;
			cout << " ";

			if (numLeftFaceDown > 0)
			{
				numLeftFaceDown--;
			}
		}
		faceDown = numLeftFaceDown;
		cout << endl;

		tmpHandSize = tmpHandSize - 13; // amount left to display
		rowsOfCards--;
		handIndex = handIndex + 13;

	} while (tmpHandSize > 0);
}

/**
 * Suffles the locations of each card in the deck every time the function is called
 */
void CardDeck::shuffleDeck()
{
	srand(time(NULL));
	int ranIndex = 0;
	for (int i = 0; i < (DECK_SIZE * numDecks); i++)
	{
		ranIndex = rand() % (DECK_SIZE * numDecks);
		ACard temp = deck[i];
		deck[i] = deck[ranIndex];
		deck[ranIndex] = temp;
	}
	resetTopCard();
}

/**
 * Resets teh top Card index to 0
 */
void CardDeck::resetTopCard()
{
	topCard = 0;
}

/**
 * Returns the pointer to the deck.
 * 
 * @return The card deck
 */
ACard *CardDeck::getDeck()
{
	return deck;
}

/**
 * Return the top card of the deck and moves the index to the next location.
 * 
 * @return 	ACard pointer to the current to card of the deck. Return Null if no cards left
 * 			in deck.
 */
ACard *CardDeck::removeTopCard()
{
	if (topCard != -1) // Deck still has cards left
	{
		ACard *top = &(deck[topCard]);
		moveTopCard();
		return top;
	}
	else
	{
		return NULL;
	}
}

/**
 * Moves the top card index to the next location while also making sure the next index is still 
 * in range of the max deck size.
 */
int CardDeck::moveTopCard()
{
	if (topCard < (DECK_SIZE * numDecks)) // index is still in range of deck size
	{
		topCard++;
		return 0;
	}
	else // set top card to -1 it no more cards in deck.
	{
		topCard = -1;
		return -1;
	}
}

/** 
 * Get the size of the playable deck. Includes multiple decks
 * 
 * @return The number of playable cards.
 */
int CardDeck::getDeckSize()
{
	return (DECK_SIZE * numDecks);
}