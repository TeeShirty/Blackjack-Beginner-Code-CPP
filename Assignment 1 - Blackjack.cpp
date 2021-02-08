/*
	Assignment 1 - Blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
	Name: Sharath Ravishankar
	Objective: 
	Create a Blackjack text based card game
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include <cmath>
#include <array>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <windows.h>




class Card 
{
public:
	std::string face;
	std::string suit;
	bool isFaceUp;
	bool hasBeenDealt;
	int value;
	bool inPlayerHand = false;
	bool inDealerHand = false;
	bool belowTen = false;										//checks whether ace needs to be either one or 11
	


	Card(bool x, std::string y, std::string z, int i, bool j)	//creates the format of the card under the class 'Card'
	{
		isFaceUp = x;											//checks if the card is face up
		face = y;												//face of the card
		suit = z;												//suit of the card
		value = i;												//value of the card
		hasBeenDealt = j;										//checks whether if it has already been dealt, if so it will not be dealt again

	};

};

class Player 
{

public:
	int playerPoints{ 0 };										//keeps track of the player's main hand's total
	int splitPoints{ 0 };										//keeps track of hand 2 of player during a split
	int credits{ 1000 };										//money the player starts with
	bool split = false;											//checks if the hand has the same face value of cards
};


class Dealer {

public:
	int dealerPoints{ 0 };

};

void Shuffle(std::array<Card, 52> &deck);						//function to shuffle
void splitCheck(Player &player, std::array<Card, 52>& deck);	//function to check if there is a split
int playerDeal(Player player, std::array<Card, 52> &deck);		//deals cards to the player's main hand
int splitDeal(Player player, std::array<Card, 52>& deck);		//deals cards to the player's second hand, in the event of a split only
int dealerDeal(Dealer dealer, std::array<Card, 52> &deck);		//deals cards to the dealer
int showCredits(int i);											//function to show the remaining credits after each round
int surrender(int i, int j);									//function to show an option for player to surrender

int main()
{
	
	Player player;
	Dealer dealer;
	
	//the rules of the game
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "      WELCOME TO BLACKJACK!" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
	std::cout << "         THE OBJECTIVE" << std::endl;
	std::cout << "         -------------\n" << std::endl;
	std::cout << "Each participant attempts to beat the dealer by getting a count as close to 21 as possible, without going over 21." << std::endl;
	std::cout << "After the Shuffle the dealer will deal 2 cards face up to the player and 2 cards to the dealer. The dealer has only one card face up.\n" << std::endl;
	std::cout << "        THE PLAYER'S TURN" << std::endl;
	std::cout << "         -------------\n" << std::endl;
	std::cout << "The player can choose to:- \n HIT - Add another card to the hand \n STAND - Not ask for another card and resides turn \n DOUBLE DOWN - Another option open to the player is doubling their bet when the original two cards dealt total 9, 10, or 11. When the player's turn comes, they place another bet equal to the original bet. \n SPLIT - If a player's first two cards are of the same denomination, such as two jacks or two sixes, they may choose to treat them as two separate hands when their turn comes around. The amount of the original bet then goes on one of the cards, and an equal amount must be placed as a bet on the other card. THe player plays one hand completely before moving on to the play the second hand.\n" << std::endl;
	std::cout << "          GAME STARTS" << std::endl;
	std::cout << "         -------------\n" << std::endl;

	//the main game loop
	while (player.credits > 0)
	{
		char playerInput = 'z';
		player.playerPoints = 0;
		dealer.dealerPoints = 0;
		bool endGame = false;
		int betAmt = 0;
		player.split = false;
		bool split = false;
		int remainingCredits = 0;

		std::cout << std::endl;

		std::cout << "You have a total of " << player.credits << " credits." << std::endl;
		std::cout << "How much would you like to bet: " << std::endl;

		//check if bet amount is more that the amount of credits
		do
		{
			std::cin >> betAmt;
			if (betAmt > player.credits)
			{
				system("cls");
				std::cout << " Invalid entry. Try again!!" << std::endl;
				std::cout << " You have a total of " << player.credits << " credits." << std::endl;
				std::cout << " How much would you like to bet:" << std::endl;

			}
		
			else if (player.credits <= 0)
			{
				player.credits = 0;
				endGame = true;
				break;
			}
		} while (betAmt > player.credits);

		system("cls");
		std::cout << "Your bet amount is: " << betAmt << std::endl;
		remainingCredits = player.credits - betAmt;
		std::cout << "Remaining credits are: " << remainingCredits << std::endl;
		std::cout << "Shuffling the deck..." << std::endl;
		//showing time taken to shuffle the deck
		Sleep(2000); 
		system("cls");
		std::cout << "Dealing the cards..." << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		std::cout << "Your remaining credits are " << remainingCredits << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

		//seed for randomizer
		srand(time(0));

		//array of all cards
		std::array <Card, 52> deck = { {
		{false, "Ace", "Clubs", 11, false},
		{false, "Ace", "Hearts", 11, false},
		{false, "Ace", "Spades", 11, false},
		{false, "Ace", "Diamonds", 11, false},
		{false, "Two", "Clubs", 2, false},
		{false, "Two", "Hearts", 2, false},
		{false, "Two", "Spades", 2, false},
		{false, "Two", "Diamonds", 2, false},
		{false, "Three", "Clubs", 3, false},
		{false, "Three", "Hearts", 3, false},
		{false, "Three", "Spades", 3, false},
		{false, "Three", "Diamonds", 3, false},
		{false, "Four", "Clubs", 4, false},
		{false, "Four", "Hearts", 4, false},
		{false, "Four", "Spades", 4, false},
		{false, "Four", "Diamonds", 4, false},
		{false, "Five", "Clubs", 5, false},
		{false, "Five", "Hearts", 5, false},
		{false, "Five", "Spades", 5, false},
		{false, "Five", "Diamonds", 5, false},
		{false, "Six", "Clubs", 6, false},
		{false, "Six", "Hearts", 6, false},
		{false, "Six", "Spades", 6, false},
		{false, "Six", "Diamonds", 6, false},
		{false, "Seven", "Clubs", 7, false},
		{false, "Seven", "Hearts", 7, false},
		{false, "Seven", "Spades", 7, false},
		{false, "Seven", "Diamonds", 7, false},
		{false, "Eight", "Clubs", 8, false},
		{false, "Eight", "Hearts", 8, false},
		{false, "Eight", "Spades", 8, false},
		{false, "Eight", "Diamonds", 8, false},
		{false, "Nine", "Clubs", 9, false},
		{false, "Nine", "Hearts", 9, false},
		{false, "Nine", "Spades", 9, false},
		{false, "Nine", "Diamonds", 9, false},
		{false, "Ten", "Clubs", 10, false},
		{false, "Ten", "Hearts", 10, false},
		{false, "Ten", "Spades", 10, false},
		{false, "Ten", "Diamonds", 10, false},
		{false, "Jack", "Clubs", 10, false},
		{false, "Jack", "Hearts", 10, false},
		{false, "Jack", "Spades", 10, false},
		{false, "Jack", "Diamonds", 10, false},
		{false, "Queen", "Clubs", 10, false},
		{false, "Queen", "Hearts", 10, false},
		{false, "Queen", "Spades", 10, false},
		{false, "Queen", "Diamonds", 10, false},
		{false, "King", "Clubs", 10, false},
		{false, "King", "Hearts", 10, false},
		{false, "King", "Spades", 10, false},
		{false, "King", "Diamonds", 10, false}
		}

		};

		Shuffle(deck);

		std::cout << "Player Hand" << std::endl;
		std::cout << "-----------\n" << std::endl;
		player.playerPoints = playerDeal(player, deck); // Adds card to player hand
		player.playerPoints = playerDeal(player, deck); // Adds card to player hand

		splitCheck(player, deck); 
		
		std::cout << "Player total: " << player.playerPoints << std::endl;

		std::cout << std::endl;

		std::cout << "Dealer Hand" << std::endl;
		std::cout << "-----------\n" << std::endl;
		dealer.dealerPoints = dealerDeal(dealer, deck); // Adds card to dealer hand

		std::cout << "Dealer Total: " << dealer.dealerPoints << std::endl;
	
		std::cout << std::endl;
		//game loop checks if player's card values are less than 21
		while (player.playerPoints < 21 && endGame == false)
		{
			//checks if the cards in the player's hand is are of equal value
			if (player.split == true)
			{
				std::cout << "\nPress 'P' to Split, 'H' to Hit, 'S' to Stand, 'D' to Double Down, 'Q' to Surrender.\n" << std::endl;
			}
			if (player.split == false)
			{
				std::cout << "\n'H' to Hit, 'S' to Stand, 'D' to Double Down, 'Q' to Surrender\n" << std::endl;
			}
			
			//checks what the player input is
			std::cin >> playerInput;

			//surrender
			if (playerInput == 'q' || playerInput == 'Q')
			{
				surrender(remainingCredits, betAmt);
			}

			//hit
			if (playerInput == 'h' || playerInput == 'H')
			{
				std::cout << std::endl;
				std::cout << "Player Hits!" << std::endl;
				player.playerPoints = playerDeal(player, deck);
				std::cout << "Player Score = " << player.playerPoints << std::endl;
				std::cout << std::endl;
				std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
			}

			//double down
			else if (playerInput == 'd' || playerInput == 'D')
			{
				std::cout << std::endl;
				betAmt = betAmt * 2;
				
				std::cout << "Player Doubles Down!" << std::endl;
				std::cout << "Total Bet amount " << betAmt << "\n" << std::endl;
				player.playerPoints = playerDeal(player, deck);
				std::cout << "Player Score = " << player.playerPoints << std::endl;
				std::cout << std::endl;
				std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
				dealer.dealerPoints = dealerDeal(dealer, deck);

				if (player.playerPoints > dealer.dealerPoints && player.playerPoints < 21)
				{
					std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
					std::cout << " The Player Wins!!! " << std::endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
					endGame = true;
					player.credits += betAmt;
					showCredits(player.credits);
				}

				else if (player.playerPoints < dealer.dealerPoints)
				{
					std::cout << std::endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
					std::cout << " The Dealer Wins!!! " << std::endl;
					std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
					endGame = true;
					player.credits -= betAmt;
					showCredits(player.credits);

				}

				else if (player.playerPoints == dealer.dealerPoints)
				{
					std::cout << std::endl;
					std::cout << "~~~~~~~~" << std::endl;
					std::cout << " Push!! " << std::endl;
					std::cout << "~~~~~~~~" << std::endl;
					endGame = true;
					player.credits = player.credits;
					showCredits(player.credits);
				}

				else if (player.playerPoints == 21)
				{
					std::cout << std::endl;
					std::cout << "\n~~~~~~~~~~~~~~" << std::endl;
					std::cout << " BLACKJACK!!! " << std::endl;
					std::cout << "~~~~~~~~~~~~~~" << std::endl;
					endGame = true;
					player.credits += (betAmt * 2);
					showCredits(player.credits);
				}
			}

			else if (playerInput == 's' || playerInput == 'S')
			{

				while (dealer.dealerPoints < 17)
				{
					std::cout << std::endl;
					
					std::cout << "Dealer Hits!." << std::endl;
					std::cout << "------------" << std::endl;
					dealer.dealerPoints = dealerDeal(dealer, deck);

					std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
				};

				if (dealer.dealerPoints >= 17)
				{

					if (player.playerPoints > dealer.dealerPoints)
					{
						std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << " The Player Wins!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
						endGame = true;
						player.credits += betAmt;
						showCredits(player.credits);
					}

					else if (dealer.dealerPoints > 21)
					{
						std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << " The Player Wins!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
						endGame = true;
						player.credits += betAmt;
						showCredits(player.credits);
					}

					else if (player.playerPoints < dealer.dealerPoints)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << " The House Wins!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
						endGame = true;
						player.credits -= betAmt;
						showCredits(player.credits);
					}

					else if (player.playerPoints == dealer.dealerPoints)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~" << std::endl;
						std::cout << " Push!! " << std::endl;
						std::cout << "~~~~~~~~" << std::endl;
						endGame = true;
						player.credits = player.credits;
						showCredits(player.credits);
					}
				}
			}
			
			//checks if there is a split opportunity in hand
			while (player.split == true)
			{
				//Split - HAND 1

				if (playerInput == 'p' || playerInput == 'P')
				{
					betAmt += betAmt;
					player.playerPoints = player.playerPoints / 2;
					player.splitPoints = player.playerPoints;
					bool handOne = true;
					std::cout << "Player splits hand!. Playing HAND 1." << std::endl;
					std::cout << "------------------------------------" << std::endl;
					std::cout << "Player Score: " << player.playerPoints << std::endl;
					while (handOne == true && player.playerPoints < 21)
					{
						std::cout << "You are now playing HAND 1." << std::endl;
						std::cout << "------------------------------------" << std::endl;
						std::cout << "'H' to Hit, 'S' to Stand, 'D' to Double Down." << std::endl;
						std::cin >> playerInput;
						
						//Hit
						if (playerInput == 'h' || playerInput == 'H')
						{
							std::cout << std::endl;
							std::cout << "Player Hits!" << std::endl;
							player.playerPoints = playerDeal(player, deck);
							std::cout << "Player Score: " << player.playerPoints << std::endl;
							std::cout << std::endl;
							std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;

							if (player.playerPoints == 21 && endGame == false)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Player Wins HAND 1!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = false;
								player.credits += (betAmt * 2);
								showCredits(player.credits);

								
							}
							else if (player.playerPoints > 21 && endGame == false)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Dealer Wins HAND 1!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = false;
								player.credits -= betAmt;
								showCredits(player.credits);
							}
						}

						//Double Down
						else if (playerInput == 'd' || playerInput == 'D')
						{
							std::cout << std::endl;
							betAmt = betAmt * 2;
							std::cout << "Player Doubles Down!" << std::endl;
							std::cout << betAmt << std::endl;
							player.playerPoints = playerDeal(player, deck);
							std::cout << "Player Score: " << player.playerPoints << std::endl;
							std::cout << std::endl;
							std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;



							if (player.playerPoints > dealer.dealerPoints && player.playerPoints < 21)
							{
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Player Wins HAND 1!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = false;
								player.credits += betAmt;
								showCredits(player.credits);;

							}

							else if (player.playerPoints < dealer.dealerPoints)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Dealer Wins HAND 1!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = false;
								player.credits -= betAmt;
								showCredits(player.credits);
							}

							else if (player.playerPoints == dealer.dealerPoints)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~" << std::endl;
								std::cout << " Push!! " << std::endl;
								std::cout << "~~~~~~~~" << std::endl;
								handOne = false;
								player.credits = player.credits;
								showCredits(player.credits);
							}

							else if (player.playerPoints == 21)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Player Wins HAND 1!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = false;
								player.credits += betAmt;
								showCredits(player.credits);
							}
						}

						//Stand
						else if (playerInput == 's' || playerInput == 'S')
						{

							while (dealer.dealerPoints < 17)
							{
								std::cout << std::endl;
								std::cout << "Dealer Hits!." << std::endl;
								std::cout << "------------" << std::endl;
								dealer.dealerPoints = dealerDeal(dealer, deck);

								std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
							};

							if (dealer.dealerPoints >= 17)
							{

								if (player.playerPoints > dealer.dealerPoints)
								{
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Player Wins HAND 1!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									handOne = false;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (dealer.dealerPoints > 21)
								{
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Player Wins HAND 1!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									handOne = false;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (player.playerPoints < dealer.dealerPoints)
								{
									std::cout << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Dealer Wins HAND 1!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									handOne = false;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (player.playerPoints == dealer.dealerPoints)
								{
									std::cout << std::endl;
									std::cout << "~~~~~~~~" << std::endl;
									std::cout << " Push!! " << std::endl;
									std::cout << "~~~~~~~~" << std::endl;
									handOne = false;
									player.credits = player.credits;
									showCredits(player.credits);
								}
							}
						}
					}
						
				
					if (player.playerPoints == 21 && endGame == false)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << "		BLACKJACK!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						handOne = false;
						player.credits += (betAmt * 2);
						showCredits(player.credits);
					}
					if (player.playerPoints > 21 && endGame == false)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << " The Dealer Wins HAND 1!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						handOne = false;
						player.credits -= betAmt;
						showCredits(player.credits);
					}

					//Split HAND 2

					while (player.split == true && player.splitPoints < 21)
					{
						std::cout << "You are now playing HAND 2." << std::endl;
						std::cout << "'H' to Hit, 'S' to Stand, 'D' to Double Down." << std::endl;
						std::cin >> playerInput;

						//Hit
						if (playerInput == 'h' || playerInput == 'H')
						{
							std::cout << std::endl;
							std::cout << "Player Hits!" << std::endl;
							player.splitPoints = splitDeal(player, deck);
							std::cout << "Player Score: " << player.splitPoints << std::endl;
							std::cout << std::endl;
							std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
						}
						//Double Down
						else if (playerInput == 'd' || playerInput == 'D')
						{
							std::cout << std::endl;
							betAmt = betAmt * 2;
							std::cout << "Player Doubles Down!" << std::endl;
							std::cout << betAmt << std::endl;
							player.splitPoints = splitDeal(player, deck);
							std::cout << "Player Score: " << player.splitPoints << std::endl;
							std::cout << std::endl;
							std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;

							if (player.splitPoints > dealer.dealerPoints && player.splitPoints < 21)
							{
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Player Wins HAND 2!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								endGame = true;
								player.credits += betAmt;
								showCredits(player.credits);

							}

							else if (player.splitPoints < dealer.dealerPoints)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Dealer Wins HAND 2!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								handOne = true;
								player.credits -= betAmt;
								showCredits(player.credits);
							}

							else if (player.splitPoints == dealer.dealerPoints)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~" << std::endl;
								std::cout << " Push!! " << std::endl;
								std::cout << "~~~~~~~~" << std::endl;
								endGame = true;
								player.credits = player.credits;
								showCredits(player.credits);
							}

							else if (player.splitPoints == 21)
							{
								std::cout << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								std::cout << " The Player Wins HAND 2!!! " << std::endl;
								std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
								endGame = true;
								player.credits += betAmt;
								showCredits(player.credits);
							}
						}

						//Stand
						else if (playerInput == 's' || playerInput == 'S')
						{

							while (dealer.dealerPoints < 17)
							{
								std::cout << std::endl;
								std::cout << "Dealer Hits!." << std::endl;
								std::cout << "------------" << std::endl;
								dealer.dealerPoints = dealerDeal(dealer, deck);

								std::cout << "Dealer Score: " << dealer.dealerPoints << std::endl;
							};

							if (dealer.dealerPoints >= 17)
							{

								if (player.splitPoints > dealer.dealerPoints)
								{
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Player Wins HAND 2!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									endGame = true;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (dealer.dealerPoints > 21)
								{
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Player Wins HAND 2!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									endGame = true;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (player.splitPoints < dealer.dealerPoints)
								{
									std::cout << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									std::cout << " The Dealer Wins HAND 2!!! " << std::endl;
									std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
									endGame = true;
									player.credits += betAmt;
									showCredits(player.credits);
								}

								else if (player.splitPoints == dealer.dealerPoints)
								{
									std::cout << std::endl;
									std::cout << "~~~~~~~~" << std::endl;
									std::cout << " Push!! " << std::endl;
									std::cout << "~~~~~~~~" << std::endl;
									endGame = true;
									player.credits = player.credits;
									showCredits(player.credits);
								}
							}
						}
					}


					if (player.splitPoints == 21)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << "		BLACKJACK!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						endGame = true;
						player.credits += (betAmt * 2);
						showCredits(player.credits);
					}
					if (player.splitPoints > 21)
					{
						std::cout << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						std::cout << " The Dealer Wins HAND 2!!! " << std::endl;
						std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
						endGame = true;
						player.credits -= betAmt;
						showCredits(player.credits);
					}
				}
			}
		}
		if (player.playerPoints == 21)
		{
			std::cout << std::endl;
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << "		BLACKJACK!!! " << std::endl;
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			endGame = true;
			player.credits += (betAmt * 2);
			showCredits(player.credits);
		}

		if (player.playerPoints > 21) 
		{
			std::cout << std::endl;
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			std::cout << " The Dealer Wins HAND 2!!! " << std::endl;
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
			endGame = true;
			player.credits -= betAmt;
			showCredits(player.credits);
			
		}
	}
}

void Shuffle(std::array<Card, 52>& deck) 
{
	for (int i = 0; i < 52; ++i) 
	{
		deck[i].hasBeenDealt = false;
	}
}

int playerDeal(Player player, std::array<Card, 52>& deck) 
{
	int i = rand() % 52 - 1;
	do
	{
		int i = rand() % 52 - 1;
	} while (deck[i].hasBeenDealt == true);

	player.playerPoints += deck[i].value;
	deck[i].hasBeenDealt = true;
	deck[i].inPlayerHand = true;
	
	if (deck[0, 1, 2, 3].inPlayerHand == deck[i].inPlayerHand && player.playerPoints > 21)
	{
		player.playerPoints -= 10;
	}

	std::cout << deck[i].face << " of " << deck[i].suit << std::endl;

	return player.playerPoints;

};

int splitDeal(Player player, std::array<Card, 52>& deck)
{
	int i = rand() % 52 - 1;
	do
	{
		int i = rand() % 52 - 1;
	} while (deck[i].hasBeenDealt == true);

	deck[i].hasBeenDealt = true;
	deck[i].inPlayerHand = true;

	player.splitPoints += deck[i].value;

	if (deck[0, 1, 2, 3].inPlayerHand == deck[i].inPlayerHand && player.splitPoints > 21)
	{
		player.splitPoints -= 10;
	}

	std::cout << deck[i].face << " of " << deck[i].suit << std::endl;

	return player.splitPoints;

};

int dealerDeal(Dealer dealer, std::array<Card, 52>& deck) 
{
	int i = rand() % 52 - 1;
	do
	{
		int i = rand() % 52 - 1;
	} while (deck[i].hasBeenDealt == true);


	dealer.dealerPoints += deck[i].value;
	deck[i].hasBeenDealt = true;
	deck[i].inDealerHand = true;
	
	if (deck[0, 1, 2, 3].inDealerHand == deck[i].inDealerHand && dealer.dealerPoints > 21)
	{
		dealer.dealerPoints -= 10;
	}

	std::cout << deck[i].face << " of " << deck[i].suit << std::endl;
	
	return dealer.dealerPoints;
};


void splitCheck (Player &player, std::array<Card, 52>& deck)
{
	
	for (int i = 0; i < 52; i++)
	{
		if (deck[i].inPlayerHand == true)
		{
			for (int j = 0; j < 52; j++)
			{
				if (deck[j].inPlayerHand == true && deck[i].suit != deck[j].suit)
				{
					if (deck[j].face == deck[i].face)
					{
						player.split = true;
					}
				}
			}
		}
	}
}

int showCredits(int i)
{
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Your remaining credits are " << i << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

	return i;
}

int surrender(int i, int j)
{
	std::cout << "You surrendered your bet. You lose half your placed bet" << std::endl;
	i += (j/ 2);
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Your remaining credits are " << i << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

	Sleep(1000);
	return 0;
}

	/*
	THINGS WE NEED TO ADD
		1. total credits and bet amount
		2. double down option
		3. split option
		4. hide the first card of the dealer but include its value
		5. REMOVE DEALER TOTAL
		*/


	// THE PLAN
	// Deck of cards - randomizer
	// Dealer Cards
	// Player Cards
	// Deal the Cards
	// Display the Cards
	// if player_card[0] == player_card[1]
	// Display " 'e' to split or 'd' to continue
	// if 'e' then 

	// While sum(player_cards) < 21
		// Display " 'h' for hit, 'd' for double and 's' for stay
		// if 'h' then add card to player_cards
		// if 'd' then add one card to player_cards and break
		// if 's' then break
	// While sum(dealer_cards) < 17
		// add card to dealer_cards
	// if sum(player_cards) > sum(dealer_cards) && < 21 then display WINNER
	// if sum(player_cards) == 21 then display BLACKJACK
	// if sum(player_cards) > 21 then display loser
	// if sum(player_cards) == sums(dealer_cards) && <= 21 then display DRAW
