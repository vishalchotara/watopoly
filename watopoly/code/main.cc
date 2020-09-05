#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
#include "board.h"
#include "exception.h"
#include <algorithm>
int main(int argc, char *argv[])
{
	std::cin.exceptions(std::ios::failbit | std::ios::eofbit);
	try
	{
		bool testing = false;
		std::string infile = "";

		for (int i = 0; i < argc; ++i)
		{
			std::string arg = argv[i];
			if (arg == "-testing")
			{
				testing = true;
			}
			if (arg == "-load")
			{
				if (i + 1 < argc)
					infile = argv[i + 1];
				else
					std::cerr << "No input file given" << std::endl;
			}
		}

		Board b;
		std::vector<std::shared_ptr<Player>> players;
		int playersnum = 0;

		if (infile != "")
		{
			std::ifstream ifs;
			ifs.open(infile);
			playersnum = ifs.peek() - '0';
			ifs >> b;
		}
		else
		{
			std::cout << "Please enter the number of players (Minimum of 2 players required): ";
			std::string input;
			while (1)
			{
				try
				{
					std::cin >> input;
					playersnum = std::stoi(input);
					if (playersnum < 2)
					{
						std::cout << "Please enter a number greater than 1: ";
					}
					else
					{
						break;
					}
				}
				catch (...)
				{
					std::cout << "Please enter a number greater than 1: ";
				}
			}
			std::string name;
			std::string c;

			std::vector<char> pieces;
			std::vector<std::string> names;
			for (int i = 1; i <= playersnum; ++i)
			{
				std::cout << "Player" << i << ", please enter your name: ";

				while (1)
				{
					std::string temp;
					std::cin >> name;
					for (auto i : name)
					{
						temp += std::tolower(i);
					}
					if (name == "bank")
					{
						std::cout << "You cannot name yourself " << name << std::endl;
					}
					else
					{
						int counter = count(names.begin(), names.end(), name);
						if (counter == 0)
						{
							names.emplace_back(name);
							break;
						}
						else
						{
							std::cout << "This name is already being used, please select a new one!" << std::endl;
						}
					}
				}
				std::cout << "\n";
				std::cout << "Please choose your character from the following:" << std::endl;
				std::cout << "	Goose | GRT Bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink Tie:" << std::endl;
				std::cin.ignore();
				while (1)
				{
					getline(std::cin, c);
					char piece;
					piece = b.getPiece(c);
					if (piece == '0')
					{
						std::cout << "Please choose a valid character: ";
					}
					else
					{
						int counter = count(pieces.begin(), pieces.end(), piece);
						if (counter == 0)
						{
							pieces.emplace_back(piece);
							players.emplace_back(new Player(name, piece));
							break;
						}
						else
						{
							std::cout << "This piece is already being used, please select a new one!" << std::endl;
						}
					}
				}
				std::cout << "\n";
			}
			b.newBoard(players);
			displayBoard(b);
		}

		int currPlayer = 0;
		while (playersnum > 1)
		{
			bool rolled = false;
			bool rentToPlayer = false;
			std::shared_ptr<Player> owedTo = nullptr;
			bool moneyOwed = false;
			bool saved = true;
			int amtOwed;
			int amtremain;
			bool jailMoney = false;
			std::cout << "It is " << b.currentPlayer()->getName() << "'s turn\n";
			displayStrip(b, b.currentPlayer().get());
			std::cout << "You currently have $" << b.currentPlayer()->getMoney() << '\n';
			std::cout << "Enter 'help' for a list of commands\n";
			std::string arg;
			outOfMoney object{nullptr, 50};
			// JAIL
			if (b.currentPlayer()->inTims())
			{
				std::cout << "You are in the DC Tim's Line! You can either\n(a) try to roll doubles,\n(b) pay $50, or\n(c) use a Roll Up the Rim Cup to get out!\n";
				std::string answer;
				while (1)
				{
					std::cin >> answer;
					if (answer == "a")
					{
						int first = rand() % 6 + 1;
						int second = rand() % 6 + 1;
						std::cout << "First die: " << first << "\nSecond die: " << second << '\n';
						if (first == second)
						{
							std::cout << "You have rolled doubles and are now out of the Tim's line!\nYou may continue with your turn.\n";
							b.currentPlayer()->resetTims();
						}
						else
						{
							std::cout << "You did not roll doubles.\n";
							if (b.currentPlayer()->turnsinTims() == 3)
							{
								std::cout << "This is your third turn in Tim's. You must (a) pay $50 or (b) use a Roll Up the Rim cup to get out\n";
								std::string option;
								while (1)
								{
									std::cin >> option;
									if (option == "a")
									{
										if (b.currentPlayer()->getCups() > 0 && b.currentPlayer()->getMoney() < 50)
										{ // forces them to use a cup if they have one and not enough cash
											std::cout << "You do not have enough money for this. You must use a cup instead\n You are now out of Tim's and may continue with your turn";
											b.currentPlayer()->useCup();
											b.useCup();
											b.currentPlayer()->resetTims();
											break;
										}
										else
										{
											try
											{
												b.currentPlayer()->withdrawMoney(50);
												b.currentPlayer()->resetTims();
												std::cout << "Congrats! You are now out of the Tim's Line!\nYou may continue with your turn.\n";
												break;
											}
											catch (outOfMoney o)
											{
												moneyOwed = true;
												amtOwed = 50;
												std::cout << "You are not able to pay your $50 to get out of the Tims Line. You can declare bankruptcy or try to raise money.\n";
												jailMoney = true;
											}
											break;
										}
									}
									else if (option == "b")
									{
										try
										{
											b.currentPlayer()->useCup();
											b.useCup();
											b.currentPlayer()->resetTims();
											std::cout << "Congrats! You are now out of the Tim's Line!\nYou may continue with your turn.\n";
											break;
										}
										catch (outOfMoney o)
										{
											moneyOwed = true;
											amtOwed = 50;
											std::cout << "You are not able to pay your $50 to get out of the Tims Line. You can declare bankruptcy or try to raise money.\n";
											jailMoney = true;
										}
										break;
									}
									else
									{
										std::cout << "Invalid input. Please enter either 'a', 'b', or 'c': ";
									}
								}
							}
							else
							{
								std::cout << "You may continue with your turn.\n";
								b.currentPlayer()->stayinTims();
							}
						}
						break;
					}
					else if (answer == "b")
					{
						if (b.currentPlayer()->getMoney() < 50)
						{
							std::cout << "You do not have enough money for this! Please try another option\n";
						}
						else
						{
							b.currentPlayer()->withdrawMoney(50);
							b.currentPlayer()->resetTims();
							std::cout << "Congrats! You are now out of the Tim's Line!\nYou may continue with your turn.\n";
							break;
						}
					}
					else if (answer == "c")
					{
						if (b.currentPlayer()->getCups() <= 0)
						{
							std::cout << "You do not have enough cups for this. Try another option\n";
						}
						else
						{
							b.currentPlayer()->useCup();
							b.useCup();
							b.currentPlayer()->resetTims();
							std::cout << "Congrats! You are now out of the Tim's Line!\nYou may continue with your turn.\n";
							break;
						}
					}
					else
					{
						std::cout << "Invalid input. Please enter either 'a', 'b', or 'c': ";
					}
				}
			}

			while (1)
			{
				std::cin >> arg;
				if (arg == "roll")
				{
					if (!b.currentPlayer()->inTims() && !rolled)
					{ // if player is not in jail
						int roll = 0;
						int d1;
						int d2;
						if (testing)
						{
							try
							{
								std::cin >> arg;
								d1 = stoi(arg);
								std::cin >> arg;
								d2 = stoi(arg);
							}
							catch (std::invalid_argument)
							{
								std::cerr << "Invalid roll numbers. Rolling from scratch\n";
							}
						}
						else
						{
							d1 = rand() % 6 + 1;
							d2 = rand() % 6 + 1;
						}
						for (int i = 0; i < 3; ++i)
						{
							if (d1 != d2)
							{
								roll = d1 + d2;
								break;
							}
							else if (i == 2)
							{
								std::cout << "You have rolled doubles three times in a row and are being sent to the Tim's Line!\n";
								displayStrip(b, b.currentPlayer().get());
								b.currentPlayer()->setInTims(true);
							}
							else
							{
								std::cout << "You roll double " << d1 << "'s and roll again.\n";
							}
							d1 = rand() % 6 + 1;
							d2 = rand() % 6 + 1;
						}
						if (b.currentPlayer()->inTims())
							continue;
						std::cout << "You have rolled a " << roll << '\n';

						rolled = true;
						try
						{
							b.move(roll);
						}
						catch (Auction p)
						{
							b.startAuction(p.p);
						}
						catch (outOfMoney p)
						{
							amtOwed = p.amountowed;
							if (p.playerowed != nullptr)
							{
								rentToPlayer = true;
								owedTo = p.playerowed;
								std::cout << b.currentPlayer()->getName() << ", you owe $" << amtOwed << " to " << p.playerowed->getName() << std::endl;
							}
							else
							{
								std::cout << b.currentPlayer()->getName() << ", you owe $" << amtOwed << " to the bank." << std::endl;
							}
							moneyOwed = true;
							std::cout << "\n";
							std::cout << "You can choose to delcare bankruptcy by calling the bankrupt command. You can also choose to mortgage/sell your properties to raise enough money to pay the money you owe." << std::endl;
							std::cout << "Note: If you choose to raise money, once it has been raised it will automatically be deducted from your balance." << std::endl;
							std::cout << "You can only use the following commands while you owe money:" << std::endl;
							std::cout << "  improve (sell only)\n  trade\n  mortgage\n  bankrupt\n  assets\n  all" << std::endl;
						}
					}
					else
					{
						if (b.currentPlayer()->inTims())
						{
							std::cout << "You are in the DC Tim's Line and cannot roll!\n";
						}
						else
						{
							std::cout << "You have already rolled!" << std::endl;
						}
					}
				}
				else if (arg == "display")
				{
					displayBoard(b);
				}
				else if (arg == "help")
				{
					std::cout << "List of Commands:\n";
					std::cout << "\troll : rolls two dice and moves the player that many squares\n";
					std::cout << "\tnext : gives control to next player\n";
					std::cout << "\ttrade <name> <give> <receive> : offers a trade to name where give and recieve can be amount of money or a property name\n";
					std::cout << "\timprove <property> buy/sell : attempts to buy or sell an improvement for property\n";
					std::cout << "\tmortgage <property> : attempts to mortgage property\n";
					std::cout << "\tunmortgage <property> : attempts to unmortgage property\n";
					std::cout << "\tbankrupt : declare bankruptcy\n";
					std::cout << "\tassets : displays assets of current player\n";
					std::cout << "\tall : displays assets of all players\n";
					std::cout << "\tsave <filename> : saves game to given file\n";
					std::cout << "\tdisplay : displays the full board\n";
					std::cout << "\tquit : exits the game\n";
					std::cout << "\thelp : prints the list of commands\n";
				}
				else if (arg == "next")
				{
					if (rolled == false && !b.currentPlayer()->inTims())
					{
						std::cout << "You haven't rolled yet! Roll first then end your turn." << std::endl;
						continue;
					}
					else if (moneyOwed == true)
					{
						amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
						std::cout << "You still owe $" << amtremain << " to ";
						if (owedTo != nullptr)
						{
							std::cout << owedTo->getName();
						}
						else
						{
							std::cout << "the Bank";
						}
						std::cout << ","
								  << " you can declare bankruptcy or raise more money before ending your turn." << std::endl;
					}
					else
					{
						b.endturn();
						break;
					}
				}
				else if (arg == "trade")
				{
					std::string name;
					std::cin >> name;
					std::string give;
					std::cin >> give;
					std::string receive;
					std::cin >> receive;
					b.trade(b.currentPlayer()->getName(), name, give, receive);
				}
				else if (arg == "improve")
				{
					std::string prop;
					std::cin >> prop;
					std::string option;
					std::cin >> option;
					if (option == "buy")
					{
						if (moneyOwed == true)
						{
							amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
							std::cout << "You still owe $" << amtremain << " to ";
							if (owedTo != nullptr)
							{
								std::cout << owedTo->getName();
							}
							else
							{
								std::cout << "the Bank";
							}
							std::cout << ","
									  << " you can declare bankruptcy or raise more money before buy any improvements." << std::endl;
							continue;
						}
						try
						{
							auto property = b.findProperty(prop);
							b.currentPlayer()->buyImprovement(property.get());
							std::cout << "You have upgraded " << prop << " to level " << property->getImprovements() << '\n';
							std::cout << "Your updated balance is $" << b.currentPlayer()->getMoney() << '\n';
						}
						catch (Exception e)
						{
							std::cout << e.getMessage() << std::endl;
						}
					}
					else if (option == "sell")
					{
						try
						{
							auto property = b.findProperty(prop);
							b.currentPlayer()->sellImprovement(property.get());
							std::cout << "You have downgraded " << prop << " to level " << property->getImprovements() << '\n';
							std::cout << "Your updated balance is $" << b.currentPlayer()->getMoney() << '\n';
						}
						catch (Exception e)
						{
							std::cout << e.getMessage() << std::endl;
						}
					}
					else
						std::cout << "Invalid command\n";
				}
				else if (arg == "mortgage")
				{
					std::string prop;
					std::cin >> prop;
					try
					{
						auto property = b.findProperty(prop);
						b.currentPlayer()->getMortgage(property.get());
						std::cout << "You have mortgaged " << prop << " for $" << property->getMortgage() << '\n';
						std::cout << "Your updated balance is $" << b.currentPlayer()->getMoney() << '\n';
					}
					catch (Exception e)
					{
						std::cout << e.getMessage() << std::endl;
					}
				}
				else if (arg == "unmortgage")
				{
					if (moneyOwed == true)
					{
						amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
						std::cout << "You still owe $" << amtremain << " to ";
						if (owedTo != nullptr)
						{
							std::cout << owedTo->getName();
						}
						else
						{
							std::cout << "the Bank";
						}
						std::cout << ","
								  << " you can declare bankruptcy or raise more money before unmortgaging." << std::endl;
						continue;
					}
					std::string prop;
					std::cin >> prop;
					try
					{
						auto property = b.findProperty(prop);
						b.currentPlayer()->getUnmortgage(property.get());
					}
					catch (Exception e)
					{
						std::cout << e.getMessage() << std::endl;
					}
				}
				else if (arg == "bankrupt")
				{
					if (moneyOwed == true)
					{
						amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
						std::cout << "You owe $" << amtremain << " to ";
						if (owedTo != nullptr)
						{
							std::cout << owedTo->getName() << "." << std::endl;
						}
						else
						{
							std::cout << "the bank." << std::endl;
						}
						std::cout << "You can (a) declare bankruptcy, or (b) try and raise money: ";
						std::string input;
						bool droppedOut = false;
						std::string name = b.currentPlayer()->getName();
						while (1)
						{
							std::cin >> input;
							if (input == "a" || input == "A")
							{
								if (owedTo != nullptr)
								{
									b.transferAssets(b.currentPlayer(), owedTo);
									--playersnum;
								}
								else
								{
									b.dropout();
									--playersnum;
								}
								droppedOut = true;
								std::cout << "Thanks for playing, " << name << "!" << std::endl;
								break;
							}
							else if (input == "b" || input == "B")
							{
								break;
							}
							else
							{
								std::cout << "This is an invalid answer, please enter either 'a' or 'b':";
							}
						}
						if (droppedOut == true)
						{
							break;
						}
					}
					else
					{
						std::cout << "You don't owe anyone money, you cannot call bankrupt!" << std::endl;
					}
				}
				else if (arg == "assets")
				{
					if (b.currentPlayer()->getPos() == 4 && moneyOwed == true)
					{
						std::cout << "You cannot use access assets if you have to still pay tuition!" << std::endl;
						continue;
					}
					b.printAssets(b.currentPlayer());
				}
				else if (arg == "all")
				{
					if (b.currentPlayer()->getPos() == 4 && moneyOwed == true)
					{
						std::cout << "You cannot use access assets if you have to still pay tuition!" << std::endl;
						continue;
					}
					b.getAllAssets();
				}
				else if (arg == "save")
				{
					if (moneyOwed == true)
					{
						amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
						std::cout << "You still owe $" << amtremain << " to ";
						if (owedTo != nullptr)
						{
							std::cout << owedTo->getName();
						}
						else
						{
							std::cout << "the Bank";
						}
						std::cout << ","
								  << " you can declare bankruptcy or raise more money before saving." << std::endl;
					}
					else
					{
						if (rolled)
						{
							b.endturn();
						}
						std::ofstream outFile;
						std::string file;
						std::cin >> file;
						outFile.open(file);
						outFile << b;
						std::cout << "Your game has been saved to the following file: " << file << std::endl;
						std::cout << "The game will now exit!" << std::endl;
						return 0;
					}
				}
				else if (arg == "quit")
				{
					std::cout << "You will be quitting without saving! Are you sure?: ";
					std::string input;
					while (1)
					{
						std::cin >> input;
						if (input == "yes" || input == "Yes")
						{
							std::cout << "Thanks for playing!" << std::endl;
							return 0;
						}
						else if (input == "no" || input == "No")
						{
							std::cout << "You have chosen not to quit without saving." << std::endl;
							break;
						}
						else
						{
							std::cout << "Incorrect input, please enter Yes or No: ";
						}
					}
				}
				else
				{
					std::cout << "That's not a valid command. Type in \"help\" to list the possible commands\n";
				}
				if (moneyOwed == true)
				{
					if (b.currentPlayer()->getMoney() >= amtOwed)
					{
						b.currentPlayer()->withdrawMoney(amtOwed);
						if (rentToPlayer == true)
						{
							owedTo->addMoney(amtOwed);
						}
						if (jailMoney == true)
						{
							b.currentPlayer()->resetTims();
							std::cout << "You are now out of jail!" << std::endl;
						}
						else
						{
							std::cout << "Your amount owed has been paid!" << std::endl;
							std::cout << "Your new balance is: $" << b.currentPlayer()->getMoney() << std::endl;
						}
						jailMoney = false;
						moneyOwed = false;
					}
					else
					{
						amtremain = abs(amtOwed - b.currentPlayer()->getMoney());
						std::cout << "Your balance is: $" << b.currentPlayer()->getMoney() << std::endl;
						std::cout << "You still owe $" << amtremain << " to ";
						if (owedTo != nullptr)
						{
							std::cout << owedTo->getName();
						}
						else
						{
							std::cout << "the Bank";
						}
						std::cout << ","
								  << " you can declare bankruptcy or raise more money." << std::endl;
					}
				}
			}
			if (playersnum == 1)
			{
				auto remainingPlayers = b.allPlayers();
				std::cout << remainingPlayers[0]->getName() << " is the winner!\nCongratulations, you win bragging rights and eternal glory!\n";
				std::cout << "Thanks for playing! :D\n";
				return 0;
			}
		}
	}
	catch (std::ios::failure)
	{
		std::cout << "ERROR: Abrupt end of game (possibly with EOF signal (crtl-d))\n";
	}
}
