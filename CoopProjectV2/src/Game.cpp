#include "Game.h"
#include "RandomNum.h"
#include <iostream>
#include <string>


Game::Game()
	: mGameState{GameState::MainMenu}
    , mPlayer{ "" }
{
}

void Game::Run()
{
	// An array of function pointers that point to the specific game state
	StateFunction stateFunctions[] =
	{
		&Game::HandleMainMenu,
		&Game::HandleCharacterCreation,
		&Game::HandlePlaying,
		&Game::HandleMining,
		&Game::HandleLoading,
		&Game::HandleInventory,
		&Game::HandlePause
	};
	while (mGameState != GameState::GameOver)
	{
		(this->*stateFunctions[static_cast<int>(mGameState)])(); // Calls the function that corresponds to the current game state, super weird syntax
		system("cls");
	}
}

// Game state logic functions, potential to refactor input

void Game::HandleMainMenu()
{
	std::string input;
	std::cout << "\033[34m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "    Pointer Function State Game    \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *    Start: s    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
	std::getline(std::cin, input);
	if (input == "s") { mGameState = GameState::CharacterCreation; }
	else if (input == "q") { mGameState = GameState::GameOver; }
}

void Game::HandleCharacterCreation()
{
	std::string name;
	std::cout << "\033[34m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        Create New Character       \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "    Character Name: ";
	std::getline(std::cin, name);
	mPlayer.SetPlayerName(name);
	mPlayer.EmptyInventory();
	mGameState = GameState::Playing;
}

void Game::HandlePlaying()
{
	std::string input;
	std::string name = mPlayer.GetPlayerName();
	std::cout << "\033[32m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        Playing as: " << name <<  "\n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *     Mine: m    *         \n"
		<< "        *    Pause: p    *         \n"
		<< "        *Main Menu: r    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
	std::getline(std::cin, input);
	if (input == "m") { mGameState = GameState::Loading; }  
	else if (input == "p") { mGameState = GameState::Paused; }
	else if (input == "r") { mGameState = GameState::MainMenu; }
	else if (input == "q") { mGameState = GameState::GameOver; }
}

void Game::HandleMining()
{
	std::string input;
	int gold = GetRandomNum();
	std::cout << "\033[35m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "         Congratulations           \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "    You found "<< gold <<" gold pieces\n"
		<< "===================================\n"
		<< "        *     Mine: m    *         \n"
		<< "        *Inventory: i    *         \n"
		<< "        *   Return: r    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
	std::getline(std::cin, input);
	mPlayer.AddItemToInventory("Gold", gold);
	if (input == "m") { mGameState = GameState::Loading; }
	else if (input == "i") { mGameState = GameState::Inventory; }
	else if (input == "r") { mGameState = GameState::Playing; }
	else if (input == "q") { mGameState = GameState::GameOver; }
}

void Game::HandleLoading()
{
	std::string name = mPlayer.GetPlayerName();
	std::cout << "\033[33m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        " << name << " is mining   \n"
		<< "   *                            *  \n"
		<< "===================================\n";  Wait(1); std::cout
		<< "   Tink..."; Wait(1); std::cout << " Schwack..."; Wait(1); std::cout << " Tchwink!"
		<< "\033[0m";
	Wait(2);
	mGameState = GameState::Mining;
}

void Game::HandleInventory()
{
	std::string input;
	std::string name = mPlayer.GetPlayerName();
	std::cout << "\033[33m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        " << name << "'s Inventory \n"
		<< "   *                            *  \n"
		<< "===================================\n"; std::cout 
		<< "     "; mPlayer.GetPlayerInventory(); std::cout << "\n"
		<< "===================================\n"
		<< "        *    Close: c    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
	std::getline(std::cin, input);
	if (input == "c") { mGameState = GameState::Playing; }
}

void Game::HandlePause()
{
	std::string input;
	std::cout << "\033[35m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "            Game Paused            \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *   Resume: r    *         \n"
		<< "        *Main Menu: m    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
	std::getline(std::cin, input);
	if (input == "r") { mGameState = GameState::Playing; }
	else if (input == "m") { mGameState = GameState::MainMenu; }
	else if (input == "q") { mGameState = GameState::GameOver; }
}
