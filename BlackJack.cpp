//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/24/2017
//Source File:                  BlackJack.cpp
//Description:
//  This class will contain all the need info to play a
//  black jack game.
//Editor:                          Emacs
//*******************************************************

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <limits>
#include <sstream>

#include "BlackJack.h"

//Reward ammount multiplier
const double BlackJack::PlAYER_BLACK_JACK = 1.5;
const double BlackJack::PLAYER_WON = 1;
const double BlackJack::PLAYER_LOST = 0;
const double BlackJack::PLAYER_TIE = 0;

const int BlackJack::MAX_BET = -1;

BlackJack::BlackJack() : CardDeck(), DISPLAY_WIDTH(81), MAX_HAND_SIZE(11)
{
    initVar();
    acc = NULL;
}

BlackJack::BlackJack(Account &account) : CardDeck(), DISPLAY_WIDTH(81), MAX_HAND_SIZE(11)
{
    initVar();
    acc = &account;
}

BlackJack::BlackJack(Account &account, int const playableDecks)
    : CardDeck(), DISPLAY_WIDTH(81), MAX_HAND_SIZE(11 * playableDecks)
{
    initVar();
    acc = &account;
}

/**
 * Play one or more games of black jack.
 */
void BlackJack::playGame()
{
    std::string strPlay = "Do You Want to Play? (Y or N) ";
    displayIntro();
    while (yesNo(strPlay, 'Y', 'N'))
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

        if (acc->getBal() == 0) // User has no money left
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
        drawInitHands();

        // Display init dealers hand
        std::cout << "Dealer Hand: " << std::endl;
        CardDeck::displayCards((const ACard **)dealerHand, dealerHandSize, 1);

        // Display init users hand
        std::cout << "Your Hand: " << std::endl;
        CardDeck::displayCards((const ACard **)usrHand, usrHandSize);

        calResult();

        clearHands(); // reset hands
        strPlay = "Play Again? (Y or N) ";
    }
}

/**
 * Determine who won and how much the player won or lost. Also display the 
 * winning results.
 * 
 * @param isOpenAce Is the open dealer card an ACE.
 * 
 */
void BlackJack::calResult()
{
    if (determineInsurance()) // open card is Ace for dealer
    {
        usrHitStay();                 // ask usr to hit stay
        if (dealerHand[0]->num == 10) // dealer got black jack
        {
            dealerHandValue = 21;
            isBust((const ACard **)usrHand, usrHandSize, usrHandValue);
            if (usrHandValue == 21) //user got black jack too
            {
                updateDisplay(0);
                displayResults("Tie, You and Dealer Got BlackJack! ", true, PLAYER_TIE, false);
                return;
            }
            else // dealer won with black jack
            {
                updateDisplay(0);
                if (insurance > 0) // insurance placed
                {
                    displayResults("Insurance Dealer Got Black Jack! ", true, 0, true);
                }
                else // insurance not placed
                {
                    displayResults("Dealer Got Black Jack! ", false, 0, true);
                }
                return;
            }
        }
        else // dealer does not have black jack with ace open
        {
        }
    }
    else
    {
        usrHitStay(); // ask usr to hit stay
    }

    if (usrHandValue <= 21)
    {
        dealerHitStay();

        if (usrHandValue == 21 && usrHandSize == 2) // user got black jack
        {
            if (dealerHandValue == 21 && dealerHandSize == 2) // both user and dealer got black
            {
                displayResults("Tie, You and Dealer Got BlackJack! ", true, PLAYER_TIE, false);
            }
            else // user got black jack but dealer did not
            {
                displayResults("Congradulations, You Got Black Jack! ", true, PlAYER_BLACK_JACK, false);
            }
        }
        else if (dealerHandValue == 21 && dealerHandSize == 2) // user did not get black jack but dealer did with out ace as open card
        {
            displayResults("Dealer Got Black Jack! ", false, PLAYER_LOST, false);
        }
        else if (dealerHandValue > 21) //dealer bust
        {
            displayResults("You Won! Dealer Busted! ", true, PLAYER_WON, false);
        }
        else if (usrHandValue == dealerHandValue) // tie
        {
            displayResults("Tie! ", true, PLAYER_TIE, false);
        }
        else if (usrHandValue > dealerHandValue) // user won
        {
            displayResults("You Won! ", true, PLAYER_WON, false);
        }
        else
        {
            displayResults("You Lost! ", false, PLAYER_LOST, false);
        }
    }
    else // user busted
    {
        updateDisplay(0);
        isBust((const ACard **)dealerHand, dealerHandSize, dealerHandValue);
        displayResults("You Busted! ", false, PLAYER_LOST, false);
    }
}

/**
 * Display the results of the hand.
 * 
 * @param str Message to diplay.
 * @param didWin If the user won or lost.
 * @param winMul Amount to multiply bet by if won.
 */
void BlackJack::displayResults(std::string const str, bool const didWin, double const winMul, bool const didDealerBJ)
{
    std::string strDidWin;
    if (didWin)
    {
        strDidWin = "You Won";
    }
    else
    {
        strDidWin = "You Lost";
    }

    std::cout << str << std::endl
              << std::endl;
    std::cout << "Your Hand Total: " << usrHandValue << std::endl;
    std::cout << "Dealers Hand Total: " << dealerHandValue << std::endl;

    std::cout << std::endl;

    std::cout.imbue(std::locale(""));
    int balance = acc->getBal(); // inital balance
    int bet = acc->getBet();     // get bet
    std::cout << "Your Initial Balance was: "
              << "$" << std::fixed << balance << std::endl;

    acc->didWinLose(didWin, winMul); // update account balance

    std::cout << "Your Bet: "
              << "$" << std::fixed << bet << std::endl;
    if (insurance > 0) // insurance needed
    {
        std::cout << "Your Insurance: "
                  << "$" << std::fixed << insurance << std::endl;
        acc->addToBal(-insurance);
    }

    balance = acc->getBal(); // curret balance
    std::cout << "Your Current Balance is: "
              << "$" << std::fixed << balance << std::endl;

    if (insurance > 0)
    {
        if (!didDealerBJ)
        {
            std::cout << "You Lost Insurance: "
                      << "$" << std::fixed << insurance << std::endl;
            std::cout << strDidWin << ": "
                      << "$" << std::fixed << (int)(bet) << std::endl;
        }
        else
        {
            std::cout << "You Lost Insurance: "
                      << "$" << std::fixed << insurance << std::endl;
            std::cout << strDidWin << ": "
                      << "$" << std::fixed << (int)(bet * winMul) << std::endl;
        }
    }
    else if (winMul == PlAYER_BLACK_JACK) // player got black jack
    {
        std::cout << strDidWin << ": "
                  << "$" << std::fixed << (int)(bet * winMul) << std::endl;
    }
    else
    {
        std::cout << strDidWin << ": "
                  << "$" << std::fixed << (int)(bet * winMul) << std::endl;
    }
}

/**
 * Determines if the dealer needs to hit or stay.
 * 
 * Dealer must hit if less then 16.
 * Delaer stays if equal to or greater then 17.
 */
void BlackJack::dealerHitStay()
{
    isBust((const ACard **)dealerHand, dealerHandSize, dealerHandValue);
    updateDisplay(0);
    while (dealerHandValue < 17) // while the delers total value if < 17
    {
        dealerHand[dealerHandSize] = drawCard();
        dealerHandSize++;
        isBust((const ACard **)dealerHand, dealerHandSize, dealerHandValue);
        updateDisplay(0);
    }
}

/**
 * Determine if the user needs to bet insurance. Needed if teh dealers visable 
 * card is an Ace. If dealer got black jack, then give user back amount bet.
 */
bool BlackJack::determineInsurance()
{
    if (dealerHand[1]->num == ACE)
    {
        std::string str = "Dealers open card is an Ace.\nWould you like to buy insurance for \%50 of bet placed? (Y or N) ";
        if (yesNo(str, 'y', 'n'))
        {
            insurance = acc->getBet() / 2;
        }
        return true;
    }
    return false; // open card not ACE
}

/**
 * Keep asking the user if he would like to hit or stay.
 * Stop if user gets 21, busts or asks to stop. After each hit, check
 * the hand to make sure the user has not busted.
 */
void BlackJack::usrHitStay()
{
    std::string strMessage = "Hit or stay? (H or S) ";
    bool didBust = isBust((const ACard **)usrHand, usrHandSize, usrHandValue);
    while (!didBust && yesNo(strMessage, 'H', 'S')) // While user wants a hit and did not bust
    {
        usrHand[usrHandSize] = drawCard();
        usrHandSize++;
        if (isBust((const ACard **)usrHand, usrHandSize, usrHandValue))
        {
            didBust = true;
        }
        updateDisplay(1);
    }
}

/**
 * refreshes the display with the current info.
 */
void BlackJack::updateDisplay(int const numDealerFaceDown)
{
    displayIntro();
    acc->displayAccount();
    std::cout << std::endl;

    // Display init dealers hand
    std::cout << "Dealer Hand: " << std::endl;
    CardDeck::displayCards((const ACard **)dealerHand, dealerHandSize, numDealerFaceDown);

    // Display int users hand
    std::cout << "Your Hand: " << std::endl;
    CardDeck::displayCards((const ACard **)usrHand, usrHandSize);
}

/**
 * Determine if the hand is still under 21.
 * 
 * @retrun True if busted, Flase if under 21.
 */
bool BlackJack::isBust(ACard const **hand, int const size, int &value)
{
    int num_of_A = 0;
    for (int i = 0; i < size; i++) // get number of ace in hand
    {
        if (hand[i]->num == ACE)
        {
            num_of_A++;
        }
    }
    int num_to_make_1 = 0;  // number of aces to try and make 1
    int handValue = 0;      // hand value
    int temp_num_to_make_1; // numebr of aces curently made 1
    int tempCardNum;        // card number
    bool checkAgain;        // check again if bust and ace's can be made 1

    do // while ace's ca be made into 1 value
    {
        checkAgain = false;
        temp_num_to_make_1 = num_to_make_1;
        for (int i = 0; i < size; i++) // determines value of hand
        {
            tempCardNum = hand[i]->num;
            if (tempCardNum <= 10) // Card number is 2 - 10
            {
                handValue = handValue + tempCardNum;
            }
            else if (tempCardNum > 10 && tempCardNum < 14) // Card is face card
            {
                handValue = handValue + 10;
            }
            else // Card is Ace
            {
                if (temp_num_to_make_1 > 0) // make a Ace value 1 instead of 11
                {
                    handValue = handValue + 1;
                    temp_num_to_make_1--;
                }
                else // ace used as 11
                {
                    handValue = handValue + 11;
                }
            }
        }

        // hand under 21
        if (handValue <= 21)
        {
            value = handValue;
            return false;
        }
        else if (num_to_make_1 < num_of_A) // bust but still can check ace as 1
        {
            checkAgain = true;
            num_to_make_1++;
            handValue = 0; // reset hand value
        }
        else // hand busted
        {
            value = handValue;
            return true;
        }
    } while (checkAgain);

    return false; //default something went wrong
}

/**
 * Draw the init four cards two for the dealer and two for the user.
 * Users get first.
 * Dealers gets second.
 * User gets third.
 * Dealer gets Fourth.
 */
void BlackJack::drawInitHands()
{
    usrHand[0] = drawCard();
    usrHandSize++;
    dealerHand[0] = drawCard();
    dealerHandSize++;

    usrHand[1] = drawCard();
    usrHandSize++;
    dealerHand[1] = drawCard();
    dealerHandSize++;

    /**************************Test****************************************/
    /*
    ACard *card1 = new ACard();
    card1->num = 8;
    card1->pSuit = "\xe2\x99\xa0";

    ACard *card2 = new ACard();
    card2->num = ACE;
    card2->pSuit = "\xe2\x99\xa0";

    ACard *card3 = new ACard();
    card3->num = 7;
    card3->pSuit = "\xe2\x99\xa0";

    ACard *card4 = new ACard();
    card4->num = 13;
    card4->pSuit = "\xe2\x99\xa0";

    dealerHand[0] = card1;
    dealerHand[1] = card2;

    usrHand[0] = card3;
    usrHand[1] = card4;
    */
}

/**
 * Draw one card from the deck.
 * 
 * @return Return a pointer to the card drawn.
 */
ACard *BlackJack::drawCard()
{
    return CardDeck::removeTopCard();
}

/**
 * Asks the user to place a bet for Poker while also makeing sure hte user only enters
 * ints and less then MAX_BET.
 */
void BlackJack::placeBet()
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
        strMaxBet = MAX_BET;
    }
    do
    {
        std::cout << "Place Bet (Max bet = "
                  << "$" << std::fixed << std::stoi(strMaxBet) << "): ";
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
 * Display the intro to the Poker game
 */
void BlackJack::displayIntro()
{
    std::string welcomeMessage = "Welcome to Black Jack";
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
 * Only allow the user to enter Y or N forom keyboard.
 * Case does not matter.
 * 
 * @param str Message to display to the user for entry.
 * @param yes Charater to enter for yes
 * @param no charater to enter for no
 * 
 * @return True if enter Y and False if enter N.
 */
bool BlackJack::yesNo(std::string const str, char const yes, char const no)
{
    char input;
    do // only allow user to enter n or y
    {
        std::cout << str;
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input = tolower(input);
        if (input == tolower(yes))
        {
            return true;
        }
        else if (input == tolower(no))
        {
            return false;
        }
        else
        {
            std::cout << "Only Enter " << yes << " or " << no << "!" << std::endl;
        }
    } while (true);
}

/**
 * Clears the hands
 */
void BlackJack::clearHands()
{

    //Clear users hand
    for (int i = 0; i < usrHandSize; i++)
    {
        usrHand[i] = NULL;
    }
    usrHandSize = 0;

    //Clear dealers hand
    for (int i = 0; i < dealerHandSize; i++)
    {
        dealerHand[i] = NULL;
    }
    dealerHandSize = 0;

    insurance = 0;
}

/**
 * init all vars
 */
void BlackJack::initVar()
{
    usrHand = new ACard *[MAX_HAND_SIZE];
    dealerHand = new ACard *[MAX_HAND_SIZE];
    dealerHandSize = 0;
    usrHandSize = 0;
    insurance = 0;
}
