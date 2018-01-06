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

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <limits>
#include <sstream>

#include "Poker.h"
#include "InsertionSort.h"

//Reward ammount multiplier
const int Poker::JACK_BETTER = 1;
const int Poker::TWO_PAIR = 2;
const int Poker::THREE_KIND = 4;
const int Poker::STRAIGHT = 6;
const int Poker::FLUSH = 8;
const int Poker::FULL_HOUSE = 10;
const int Poker::FOUR_KIND = 20;
const int Poker::STRAIGHT_FLUSH = 1000;
const int Poker::ROYAL_STRAIGHT_FLUSH = 10000;

const int Poker::MAX_BET = -1;  // max allowed bet.
const int Poker::HAND_SIZE = 5; // max size for a hand

/**
 * Default constructor.
 */
Poker::Poker() : CardDeck(), DISPLAY_WIDTH(81)
{
    //acc = NULL;
    hand = new ACard *[HAND_SIZE];
}

/**
 * Contructor for a account being passed.
 * 
 * @param account Bank account of the user.
 */
Poker::Poker(Account &account) : CardDeck(), DISPLAY_WIDTH(81)
{
    acc = &account;
    hand = new ACard *[HAND_SIZE];
}

/**
 * Play hands of Poker until the user decides to stop
 */
void Poker::playGame()
{
    std::string strPlay = "Do You Want to Play? (Y or N) ";
    displayIntro();
    while (yesNo(strPlay))
    {
        // For users bet choice
        displayIntro();
        if (acc == NULL) // no account set
        {
            std::cout << "Error: no account\n";
            break;
        }
        acc->displayAccount();
        std::cout << std::endl;
        if (acc->getBal() == 0)
        {
            std::string temp;
            std::cout << "Your do not have any money left to play (Enter any key to continue) ";
            std::cin >> temp;
            break;
        }
        placeBet();

        // Once bet set
        displayIntro();
        acc->displayAccount();
        std::cout << std::endl;
        CardDeck::shuffleDeck();
        drawHand();

        std::cout << "Your Hand: " << std::endl;

        // Display users cards and ask if they wnat to exchange any
        CardDeck::displayCards((const ACard **)hand, HAND_SIZE);
        stayOrRedraw();
        updateDisplay(); // show exchanged cards
        calResult();     // determine if they won and display winning cards
        clearHand();     // reset users hand
        strPlay = "Play Again? (Y or N) ";
        //TODO: Finish *******************************
    }
}

/**
 * Play hands of Poker until the user decides to stop
 */
void Poker::playGameAdmin()
{
    std::string strPlay = "Do You Want to Play? (Y or N) ";
    displayIntro();
    while (yesNo(strPlay))
    {
        // For users bet choice
        displayIntro();
        if (acc == NULL) // no account set
        {
            std::cout << "Error: no account\n";
            break;
        }
        acc->displayAccount();
        std::cout << std::endl;
        if (acc->getBal() == 0)
        {
            std::string temp;
            std::cout << "Your do not have any money left to play (Enter any key to continue) ";
            std::cin >> temp;
            break;
        }
        placeBet();

        // Once bet set
        displayIntro();
        acc->displayAccount();
        std::cout << std::endl;
        CardDeck::shuffleDeck();
        drawHand();

        std::cout << "Your Hand: " << std::endl;

        // Display users cards and ask if they wnat to exchange any
        CardDeck::displayCards((const ACard **)hand, HAND_SIZE);
        stayOrRedrawAdmin();
        updateDisplay(); // show exchanged cards
        calResult();     // determine if they won and display winning cards
        clearHand();     // reset users hand
        strPlay = "Play Again? (Y or N) ";
        //TODO: Finish *******************************
    }
}

/**
 * Display the intro to the Poker game
 */
void Poker::displayIntro()
{
    std::string welcomeMessage = "Welcome to Poker - Five Card Draw";
    int messSize = welcomeMessage.length();
    int messBlankSpaceWidth = DISPLAY_WIDTH / 2 - messSize / 2;
    system("clear");

    // Display top line //*******************************\\ etc..
    std::cout << "//";
    for (int i = 2; i < DISPLAY_WIDTH - 2; i++)
    {
        std::cout << "*";
    }
    std::cout << "\\\\" << std::endl;

    // Dsipaly Welcome message
    std::cout << std::setw(messBlankSpaceWidth) << std::left << "||" << welcomeMessage << std::setw(messBlankSpaceWidth) << std::right << "||" << std::endl;

    // Dsipaly bottom line \\**********************// etc...
    std::cout << "\\\\";
    for (int i = 2; i < DISPLAY_WIDTH - 2; i++)
    {
        std::cout << "*";
    }
    std::cout << "//" << std::endl;
}

/**
 * Draw a certain number of hand size.
 * 
 * @param handSize The size of the hand to draw.
 */
void Poker::drawHand()
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        hand[i] = drawCard();
    }
}

/**
 * Draw the next avaible card from the deck
 * 
 * @return Retruns the next card if the current top card is less then deck size. NUll if no cards in deck
 */
ACard *Poker::drawCard()
{
    return CardDeck::removeTopCard();
}

/**
 * Ask the user if he would like to change any of the cards in his hand.
 * Make the change if user selects yes.
 */

void Poker::stayOrRedraw()
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        std::stringstream ss;
        ss << hand[i]->getDisplayNum() << hand[i]->pSuit << ": Redraw (Y or N)? ";

        if (yesNo(ss.str())) // exchange card
        {
            hand[i] = CardDeck::removeTopCard();
        }
    }
}

/**
 * Ask the user if he would like to change any of the cards in his hand.
 * Make the change if user selects yes.
 */

void Poker::stayOrRedrawAdmin()
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        std::stringstream ss;
        ss << hand[i]->getDisplayNum() << hand[i]->pSuit << ": Redraw (Y or N)? ";

        if (yesNo(ss.str())) // exchange card
        {
            ACard *temp = new ACard();
            int input;
            std::cout << "Enter card num 2-14 :";
            std::cin >> input;
            temp->num = input;

            char inputChar;
            bool suit = false;
            while (!suit)
            {
                std::cout << "enter suit S, C, H or D: ";
                std::cin >> inputChar;
                std::cin.clear();
                std::cin.ignore(256, '\n');

                switch (tolower(inputChar))
                {
                case 's':
                {
                    temp->pSuit = CardDeck::suits[INDEX_SPADE];
                    suit = true;
                    break;
                }
                case 'c':
                {
                    temp->pSuit = CardDeck::suits[INDEX_CLUB];
                    suit = true;
                    break;
                }
                case 'h':
                {
                    temp->pSuit = CardDeck::suits[INDEX_HEART];
                    suit = true;
                    break;
                }
                case 'd':
                {
                    temp->pSuit = CardDeck::suits[INDEX_DIAMOND];
                    suit = true;
                    break;
                }
                default:
                {
                    std::cout << "Error entry!";
                    break;
                }
                }
            }
            hand[i] = temp;
        }
    }
}

/**
 * Update the cards dispalyed after user made exchange choices.
 */
void Poker::updateDisplay()
{
    system("clear");
    displayIntro();
    acc->displayAccount();
    std::cout << std::endl;

    std::cout << "Your New Hand: " << std::endl;
    CardDeck::displayCards((const ACard **)hand, HAND_SIZE);
}

/**
 * Determine the Result of the game.
 *  1) Short a temp hand in order.
 *  2) Determine what the users hand was.
 *  3) Determine amount won.
 *  4) Display results.
 */
void Poker::calResult()
{
    int winMul = 0;     // amount of reward for winning hand
    int numDisplay = 0; // number of winning cards to display
    std::string strWin; // winning hand type
    ACard **copyHand = new ACard *[HAND_SIZE];

    // copy hand into temp arr
    for (int i = 0; i < HAND_SIZE; i++)
    {
        copyHand[i] = hand[i];
    }

    insertionSort(copyHand, HAND_SIZE); // sort the hand

    determineHand(copyHand, winMul, numDisplay, strWin);

    if (numDisplay != 0) // means you won
    {
        std::cout << "You Won!" << std::endl;
        std::cout << "Hand: " << strWin << std::endl;
        CardDeck::displayCards((const ACard **)copyHand, numDisplay);
        std::cout << std::endl;

        std::cout.imbue(std::locale(""));
        int balance = acc->getBal(); // inital balance
        int bet = acc->getBet();     // get bet
        std::cout << "Your Initial Balance was: "
                  << "$" << std::fixed << balance << std::endl;

        acc->didWinLose(true, winMul); // update account balance

        balance = acc->getBal(); // inital balance
        std::cout << "Your Current Balance is: "
                  << "$" << std::fixed << balance << std::endl;
        std::cout << "Your Bet: "
                  << "$" << std::fixed << bet << std::endl;
        std::cout << "You Won: "
                  << "$" << std::fixed << (bet * winMul) << std::endl;
    }
    else
    {
        std::cout << "You Lost!" << std::endl;
        std::cout << std::endl;

        std::cout.imbue(std::locale(""));
        int balance = acc->getBal(); // inital balance
        int bet = acc->getBet();     // get bet
        std::cout << "Your Initial Balance was: "
                  << "$" << std::fixed << balance << std::endl;

        acc->didWinLose(false, winMul); // update account balance

        balance = acc->getBal(); // inital balance
        std::cout << "Your Current Balance is: "
                  << "$" << std::fixed << balance << std::endl;
        std::cout << "Your Bet: "
                  << "$" << std::fixed << bet << std::endl;
        std::cout << "You Lost: "
                  << "$" << std::fixed << bet << std::endl;
    }

    delete[] copyHand;
}

/**
 * Determine the users hand type and set each varibale
 * 
 * @param copyHand users hand.
 * @param winMul amount to multiple bet by.
 * @param numDisplay number of winning cards in hand.
 * @param strWin String of the winning hand type name.
 */
void Poker::determineHand(ACard **copyHand, int &winMul, int &numDisplay, std::string &strWin)
{
    // Flush
    if (copyHand[0]->pSuit == copyHand[1]->pSuit && copyHand[0]->pSuit == copyHand[2]->pSuit &&
        copyHand[0]->pSuit == copyHand[3]->pSuit && copyHand[0]->pSuit == copyHand[4]->pSuit)
    {
        // Striaght Flush
        if (copyHand[1]->num == copyHand[0]->num + 1 && copyHand[2]->num == copyHand[1]->num + 1 &&
            copyHand[3]->num == copyHand[2]->num + 1 && copyHand[4]->num == copyHand[3]->num + 1)
        {
            if (copyHand[0]->num == 10) // Royal straight flush
            {
                winMul = ROYAL_STRAIGHT_FLUSH;
                strWin = "Royal Straight Flush";
                numDisplay = 5;
            }
            else // Straight flush
            {
                winMul = STRAIGHT_FLUSH;
                strWin = "Straight Flush";
                numDisplay = 5;
            }
        }
        else // Flush
        {
            winMul = FLUSH;
            strWin = "Flush";
            numDisplay = 5;
        }
    }
    // straight
    else if (copyHand[1]->num == copyHand[0]->num + 1 && copyHand[2]->num == copyHand[1]->num + 1 &&
             copyHand[3]->num == copyHand[2]->num + 1 && copyHand[4]->num == copyHand[3]->num + 1)
    {
        winMul = STRAIGHT;
        strWin = "Straight";
        numDisplay = 5;
    }
    else if (copyHand[0]->num == copyHand[3]->num) // Four Card (front 4)
    {
        winMul = FOUR_KIND;
        strWin = "Four Card";
        numDisplay = 4;
    }
    else if (copyHand[1]->num == copyHand[4]->num) // Four Card (back 4)
    {
        winMul = FOUR_KIND;
        copyHand[0] = copyHand[1];
        copyHand[1] = copyHand[2];
        copyHand[2] = copyHand[3];
        copyHand[3] = copyHand[4];
        strWin = "Four of a Kind";
        numDisplay = 4;
    }
    else if (copyHand[0]->num == copyHand[2]->num) // 1 and 3 same
    {
        if (copyHand[3]->num == copyHand[4]->num) // Full house 1 2  and 4 5
        {
            winMul = FULL_HOUSE;
            strWin = "Full House";
            numDisplay = 5;
        }
        else // three of a kind 1 2 3 (Front 3)
        {
            winMul = THREE_KIND;
            strWin = "Three of a Kind";
            numDisplay = 3;
        }
    }
    else if (copyHand[1]->num == copyHand[3]->num) // three kind 2 3 4 (middle)
    {
        winMul = THREE_KIND;
        copyHand[0] = copyHand[1];
        copyHand[1] = copyHand[2];
        copyHand[2] = copyHand[3];
        strWin = "Three of a Kind";
        numDisplay = 3;
    }
    else if (copyHand[0]->num == copyHand[1]->num) // 1 2 same
    {
        if (copyHand[2]->num == copyHand[4]->num) // Full house
        {
            winMul = FULL_HOUSE;
            strWin = "Full House";
            numDisplay = 5;
        }
        else if (copyHand[3]->num == copyHand[4]->num) // two pair 1 2 && 4 5
        {
            winMul = TWO_PAIR;
            copyHand[2] = copyHand[3];
            copyHand[3] = copyHand[4];
            strWin = "Two Pair";
            numDisplay = 4;
        }
        else if (copyHand[2]->num == copyHand[3]->num) // two pair 1 2 && 3 4
        {
            winMul = TWO_PAIR;
            strWin = "Two Pair";
            numDisplay = 4;
        }
        else // pair 1 2
        {
            winMul = JACK_BETTER;
            strWin = "Pair";
            numDisplay = 2;
        }
    }
    else if (copyHand[2]->num == copyHand[4]->num) // thre of a kind 3 4 5 (back)
    {
        winMul = THREE_KIND;
        copyHand[0] = copyHand[2];
        copyHand[1] = copyHand[3];
        copyHand[2] = copyHand[4];
        strWin = "Three of a Kind";
        numDisplay = 3;
    }
    else if (copyHand[1]->num == copyHand[2]->num) // 2 3 same
    {
        if (copyHand[3]->num == copyHand[4]->num) // Two pair 2 3 && 4 5
        {
            winMul = TWO_PAIR;
            copyHand[0] = copyHand[1];
            copyHand[1] = copyHand[2];
            copyHand[2] = copyHand[3];
            copyHand[3] = copyHand[4];
            strWin = "Two Pair";
            numDisplay = 4;
        }
        else // Pair 2 3
        {
            winMul = JACK_BETTER;
            copyHand[0] = copyHand[1];
            copyHand[1] = copyHand[2];
            strWin = "Pair";
            numDisplay = 2;
        }
    }
    else if (copyHand[2]->num == copyHand[3]->num) // pair 3 4
    {
        winMul = JACK_BETTER;
        copyHand[0] = copyHand[2];
        copyHand[1] = copyHand[3];
        strWin = "Pair";
        numDisplay = 2;
    }
    else if (copyHand[3]->num == copyHand[4]->num) // pair 4 5
    {
        winMul = JACK_BETTER;
        copyHand[0] = copyHand[3];
        copyHand[1] = copyHand[4];
        strWin = "Pair";
        numDisplay = 2;
    }
    else if (copyHand[4]->num >= JACK) // High card jack or better
    {
        winMul = JACK_BETTER;
        copyHand[0] = copyHand[4];
        strWin = "High Card";
        numDisplay = 1;
    }
    else // high card lower than jack, did not win
    {
        copyHand[0] = copyHand[4];
        strWin = "High Card lower than Jack";
        numDisplay = 0;
    }
}

/**
 * Sets all hand cards pointing back to NULL.
 */
void Poker::clearHand()
{
    //for (int i = 0; i < HAND_SIZE; i++)
    //{
    //    hand[i] = NULL;
    //}
}

/**
 * Asks the user to place a bet for Poker while also makeing sure hte user only enters
 * ints and less then MAX_BET.
 */
void Poker::placeBet()
{
    int bet = -1;
    std::string strMaxBet;
    std::cout.imbue(std::locale("")); // set cout to local curreny

    if (MAX_BET == -1)
    {
        strMaxBet = std::to_string(acc->getBal());
    }
    else
    {
        strMaxBet = std::to_string(MAX_BET);
    }
    do
    {
        std::cout << "Place Bet (Max bet = " << "$" << std::fixed << std::stoi(strMaxBet) << "): ";
        std::cin >> bet;
        while (std::cin.fail()) // User did not enter int
        {
            std::cout << "Only Enter Integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Place Bet: ";
            std::cin >> bet;
        }
        if (bet <= 0)
        {
            std::cout << "Please enter correct bet amount! (Max Bet = "
                      << "$" << std::fixed << std::stoi(strMaxBet) << "): " << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            bet = -1;
        }
        else if (bet > MAX_BET && MAX_BET != -1)
        {
            std::cout << "Please enter correct bet amount! (Max Bet = "
                      << "$" << std::fixed << std::stoi(strMaxBet) << "): " << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            bet = -1;
        }
        else if (acc->setBet(bet) == -1)
        {
            std::cout << "You do not have enough money in your account! Account Balance = "
                      << "$" << std::fixed << acc->getBal() << " Bet Amount = "
                      << "$" << std::fixed << bet << std::endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            bet = -1;
        }
    } while (bet == -1);
}

/**
 * Only allow the user to enter Y or N forom keyboard.
 * Case does not matter.
 * 
 * @param str Message to display to the user for entry.
 * 
 * @return True if enter Y and False if enter N.
 */
bool Poker::yesNo(std::string const str)
{
    char input;
    do // only allow user to enter n or y
    {
        std::cout << str;
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = tolower(input);
        if (input == 'n')
        {
            return false;
        }
        else if (input == 'y')
        {
            return true;
        }
        else
        {
            std::cout << "Only Enter Y or N!" << std::endl;
        }
    } while (true);
}