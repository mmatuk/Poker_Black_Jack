//*******************************************************
//Author:                       Matt Matuk
//Created:                      11/15/2017
//Source File:                  Main.h
//Description:
//  Casino Game to play Poker or Black Jack
//
//Editor:                          Emacs
//*******************************************************
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <limits>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>

#include "Poker.h"
#include "BlackJack.h"
#include "Account.h"

using namespace std;

//Function Header
void displayIntro();
int pickGame();
void displayGameChoice();
void displayEnd();
Account *enterAccount();
int openAccountFile(char const *file);
void saveAccount(Account &);
void exitGame(Account *);
bool createAccount(Account &);
bool yesNo(std::string const, char const, char const, char const);
void writeToFile(int const, Account &);
void addMoney(Account &);
void act(int);
Account *admin();
Account *readFromFile(int const);

// Displays error message and exits with error 1.
void err_sys(char *str)
{
	printf("%s\n", str);
	exit(1);
}

const int DISPLAY_WIDTH = 81;
int numGames = 2;

int main()
{
	// TEST ********************************************
	Account *acc = new Account();

	displayIntro();

	//**************************************************
	signal(SIGINT, act);

	acc = enterAccount();
	Poker poker = Poker(*acc);
	BlackJack blackJack = BlackJack(*acc);

	int choice = -1;
	do
	{
		displayIntro();
		acc->displayAccount();
		cout << endl;
		displayGameChoice();
		choice = pickGame();
		switch (choice)
		{
		case -1:
		{
			addMoney(*acc);
			break;
		}
		case 1:
		{
			if (acc->getUname().compare("admin") == 0)
			{
				poker.playGameAdmin();
			}
			else
			{
				poker.playGame();
			}
			break;
		}
		case 2:
		{
			blackJack.playGame();
			break;
		}
		default:
		{
			break;
		}
		}
	} while (choice); // not 0

	exitGame(acc);
}

/**
 * Add money to the users account. User can add any positive ammount.
 * 
 * @param acc Account to add money to.
 */
void addMoney(Account &acc)
{
	int input;
	bool done = false;
	while (!done) // enter amount 0 - 1 mill.
	{
		cout << "Enter amount: ";
		cin >> input;
		while (cin.fail()) // User did not enter a Integer
		{
			cout << "Error: Please only enter only Integers" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl
				 << "Enter Amount: ";
			cin >> input;
		}

		if (input >= 0)
		{
			acc.addToBal(input);
			done = true;
		}
		else
		{
			cout << "Please only enter positive numbers less than $1,000,000!" << endl;
		}
	}
	while (!done)
		;
}

/**
 * Display the intro to the Casino game
 */
void displayIntro()
{
	std::string welcomeMessage = "Welcome to the Casino";
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
 * Display the differnt games avabl
 */
void displayGameChoice()
{
	cout << "What Game Would You Like to Play?" << endl;
	cout << " 1 - Poker" << endl;
	cout << " 2 - Black Jack" << endl;
	cout << endl;
	cout << "-1 - Add Money" << endl;
	cout << " 0 - EXIT" << endl;
}

/**
 * Display the ending to the Casino game
 */
void displayEnd()
{
	cout << endl
		 << "Thank you for playing! " << endl;
	cout << "BYE!" << endl;
}

/**
 * Allows the user to pick from one of the games displayed
 */
int pickGame()
{
	int input = -1;
	bool choiceMade = false;
	while (!choiceMade)
	{
		cout << endl
			 << "Choice: ";
		std::cin >> input;
		while (cin.fail()) // User did not enter a Integer
		{
			cout << "Error: Please only enter only Integers" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl
				 << "Choice: ";
			cin >> input;
		}

		if (input < -1 || input > numGames)
		{
			cout << "Error: Please only enter only 0-" << numGames << endl;
		}
		else
		{
			choiceMade = true;
		}
	}
	return input;
}

/**
 * 
 * User enters account info
 */
Account *enterAccount()
{
	string strName;
	Account *acc = new Account();
	Account *temp = new Account();
	string str = "acc";
	const char *c;
	int fd;

	c = str.c_str();
	fd = openAccountFile(c);

	while (true)
	{
		lseek(fd, 0, SEEK_SET);
		cout << "Please Enter Account Infomation" << endl;
		cout << "Username: ";
		cin >> strName;

		if (strName.compare("admin") == 0) // admin enterd
		{
			return admin();
		}

		while ((acc = readFromFile(fd)) != NULL) // while there r account to read
		{
			if (acc->getUname().compare(strName) == 0) // account found
			{
				cout << "Welcome " << strName << endl;
				delete temp;
				return acc;
			}
		}

		// User not found
		cout << "Username not found." << endl;
		if (createAccount(*temp))
		{
			delete acc;
			return temp;
		}
	}
	return NULL;
}

/**
 * create admin test account
 * 
 * @return The admin Account created.
 */
Account *admin()
{
	Account *admin = new Account();
	admin->addToBal(1000000);
	admin->setUname("admin");
	return admin;
}

/**
 * Read an account from the file.
 * 
 * @param fd File fd.
 * 
 * @return Return the account pointer or NULL if end of file.
 */
Account *readFromFile(int const fd)
{
	Account *temp = new Account();
	char *name;
	name = (char *)malloc(sizeof(string) + 1);
	memset(name, '\0', 33);
	int bal;	  // blance of bank account
	int bet;	  // current bet
	int totalWin; // total winning of current game
	int nbyte;
	int seek, seekEnd;

	seek = lseek(fd, 0, SEEK_CUR);
	seekEnd = lseek(fd, 0, SEEK_END);
	if (seekEnd == seek) // end of file
	{
		delete temp;
		return NULL;
	}
	else // set back to current
	{
		lseek(fd, seek, SEEK_SET);
	}

	nbyte = read(fd, name, sizeof(string));
	if (nbyte == -1)
	{
		perror("Error read: ");
		exit(1);
	}

	nbyte = read(fd, &bal, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error read: ");
		exit(1);
	}

	nbyte = read(fd, &bet, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error read: ");
		exit(1);
	}

	nbyte = read(fd, &totalWin, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error read: ");
		exit(1);
	}

	temp->setUname(name);
	temp->addToBal(bal);
	temp->setBet(bet);
	temp->addToWin(totalWin);
	return temp;
}

/**
 * Write to a file.
 */
void writeToFile(int const fd, Account &acc)
{
	int nbyte;
	const char *name = acc.getUname().c_str();
	int bal = acc.getBal();
	int bet = acc.getBet();
	int win = acc.getWin();
	nbyte = write(fd, name, sizeof(string));
	if (nbyte == -1)
	{
		perror("Error write: ");
		exit(1);
	}

	nbyte = write(fd, &bal, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error write: ");
		exit(1);
	}

	nbyte = write(fd, &bet, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error write: ");
		exit(1);
	}

	nbyte = write(fd, &win, sizeof(int));
	if (nbyte == -1)
	{
		perror("Error write: ");
		exit(1);
	}
}

/**
 * Ask the user to enter account infomation
 * 
 * @param acc Account to save info into.
 * 
 * @return ture if account made, else false if account not made.
 */
bool createAccount(Account &acc)
{
	string name;
	int bal;
	string strMessage = "Would you like to create an Account? (Y or N) (0 to exit) ";
	if (yesNo(strMessage, 'Y', 'N', '0'))
	{
		cout << "Enter Username: ";
		cin >> name;
		acc.setUname(name);
		cout << "Enter Starting Balance: ";
		cin >> bal;
		while (cin.fail()) // User did not enter int
		{
			cout << "Only Enter Integer!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Enter Starting Balance: ";
			cin >> bal;
		}
		acc.addToBal(bal);
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Saves users account info on exit
 */
void exitGame(Account *acc)
{
	displayEnd();
	saveAccount(*acc);
	exit(0);
}

/**
 * Saves the users Account infomation
 */
void saveAccount(Account &acc)
{
	if (&acc == NULL)
	{
		return;
	}
	Account *temp = new Account();
	string str = "acc";
	string strTemp = "accTemp";
	const char *c;
	const char *cT;
	bool found = false;

	string name;
	int fd, fdT;

	c = str.c_str();
	cT = strTemp.c_str();

	fd = openAccountFile(c);
	fdT = open(cT, O_CREAT | O_TRUNC | O_WRONLY, 0500);

	name = acc.getUname();

	while ((temp = readFromFile(fd)) != NULL)
	{
		if (temp->getUname().compare(name) == 0)
		{
			temp = &acc;
			found = true;
		}
		writeToFile(fdT, *temp);
	}

	if (!found && acc.getUname().compare("admin") != 0)
	{
		writeToFile(fdT, acc);
	}

	remove(c);
	rename(cT, c);

	close(fd);
	close(fdT);
	delete temp;
}

/**
 * opens account file
 * 
 * @param Name of file
 * 
 * @return file descriptor.
 */
int openAccountFile(char const *file)
{
	int fd = -1;
	if ((fd = open(file, O_CREAT | O_RDONLY)) < 0)
	{
		perror("Error File Open: ");
		//exit(1);
	}

	return fd;
}

/**
 * Only allow the user to enter Y or N forom keyboard.
 * Case does not matter.
 * 
 * @param str Message to display to the user for entry.
 * @param yes Charater to enter for yes.
 * @param no charater to enter for no.
 * @param exit Charater to exit.
 * 
 * @return True if enter Y and False if enter N.
 */
bool yesNo(std::string const str, char const yes, char const no, char const ex)
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
		else if (input == tolower(ex))
		{
			exitGame(NULL);
		}
		else
		{
			std::cout << "Only Enter " << yes << ", " << no << " or " << ex << "!" << std::endl;
		}
	} while (true);
}

/**
 * User can not use crt-c to exit
 */
void act(int sig)
{
	if (sig == SIGINT)
	{
		cout << "Please finish game before exit" << endl;
	}
}