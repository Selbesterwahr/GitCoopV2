#include "Game.h"
#include "RandomNum.h"
#include <iostream>
#include <string>

Game::Game()
	: mCurrentGameState{GameState::NullState }
	, mNextGameState{ GameState::MainMenu }
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
	while (mCurrentGameState != GameState::GameOver)
	{
		if (mNextGameState != GameState::NullState)
		{
			system("cls");
			mCurrentGameState = mNextGameState;
			mNextGameState = GameState::NullState;
			RenderGame();
		}

		(this->*stateFunctions[static_cast<int>(mCurrentGameState)])();
	}
}

// Game state logic functions, potential to refactor input

void Game::RenderGame()
{
	switch (mCurrentGameState)
	{
	case GameState::MainMenu: RenderMainMenu(); break;
	case GameState::CharacterCreation: RenderCharacterCreation(); break;
	case GameState::Playing: RenderPlaying(); break;
	case GameState::Mining: RenderMining(); break;
	case GameState::Loading: break;
	case GameState::Inventory: RenderInventory(); break;
	case GameState::Paused: RenderPause(); break;
	case GameState::GameOver: break;
	default: std::cout << "Huh!? This shouldn't happen... \n";
	}								
}

void Game::RenderMainMenu()
{
	std::cout << "\033[34m"
	<< "===================================\n"
		<< "   *                            *  \n"
		<< "    Pointer Function State Game    \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *    Start: s    *         \n"
		<< "        *     Load: l    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
}

void Game::HandleMainMenu()
{
	std::string input;
	std::getline(std::cin, input);
	if (input == "s") { mNextGameState = GameState::CharacterCreation; }
	else if (input == "l") { LoadGame(); }
	else if (input == "q") { mNextGameState = GameState::GameOver; }
}

void Game::RenderCharacterCreation()
{
	std::cout << "\033[34m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        Create New Character       \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "    Character Name: ";
}

void Game::HandleCharacterCreation()
{
	std::string name;
	std::getline(std::cin, name);
	mPlayer.SetPlayerName(name);
	mPlayer.EmptyInventory();
	mNextGameState = GameState::Playing;
}

void Game::RenderPlaying()
{
	std::string name = mPlayer.GetPlayerName();
	std::cout << "\033[32m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "        Playing as: " << name << "\n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *     Mine: m    *         \n"
		<< "        *    Pause: p    *         \n"
		<< "        *Main Menu: r    *         \n"
		<< "        *     Save: s    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
}

void Game::HandlePlaying()
{
	std::string input;
	std::string name = mPlayer.GetPlayerName();
	
	std::getline(std::cin, input);
	if (input == "m") { mNextGameState = GameState::Loading; }
	else if (input == "p") { mNextGameState = GameState::Paused; }
	else if (input == "r") { mNextGameState = GameState::MainMenu; }
	else if (input == "s") { SaveGame(); }
	else if (input == "q") { mNextGameState = GameState::GameOver; }
}

void Game::RenderMining()
{
	std::cout << "\033[35m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "         Congratulations           \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "    You found some gold pieces     \n"
		<< "===================================\n"
		<< "        *     Mine: m    *         \n"
		<< "        *Inventory: i    *         \n"
		<< "        *   Return: r    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m";
}

void Game::HandleMining()
{
	
	int gold = GetRandomNum();
	mPlayer.AddItemToInventory("Gold", gold);

	std::cout << "\033[35m" << gold << " pieces of gold added to inventory.\n" << "\033[0m";
	std::cout << "             Input: ";
	std::string input;
	while (true)
	{
		std::getline(std::cin, input);
		if (input == "m") { mNextGameState = GameState::Loading; break; }
		else if (input == "i") { mNextGameState = GameState::Inventory; break; }
		else if (input == "r") { mNextGameState = GameState::Playing; break; }
		else if (input == "q") { mNextGameState = GameState::GameOver; break; }
		else { std::cout << "That is not a valid input, try again.\n"; continue; }
		
	}
	
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
	mNextGameState = GameState::Mining;
}

void Game::RenderInventory()
{
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
}

void Game::HandleInventory()
{
	std::string input;
	std::string name = mPlayer.GetPlayerName();
	
	std::getline(std::cin, input);
	if (input == "c") { mNextGameState = GameState::Playing; }
}

void Game::RenderPause()
{
	std::cout << "\033[35m"
		<< "===================================\n"
		<< "   *                            *  \n"
		<< "            Game Paused            \n"
		<< "   *                            *  \n"
		<< "===================================\n"
		<< "        *   Resume: r    *         \n"
		<< "        *Main Menu: m    *         \n"
		<< "        *     Save: s    *         \n"
		<< "        *     Quit: q    *         \n"
		<< "===================================\n"
		<< "\033[0m"
		<< "             Input: ";
}

void Game::HandlePause()
{
	std::string input;
	
	std::getline(std::cin, input);
	if (input == "r") { mNextGameState = GameState::Playing; }
	else if (input == "m") { mNextGameState = GameState::MainMenu; }
	else if (input == "s") { SaveGame(); }
	else if (input == "q") { mNextGameState = GameState::GameOver; }
}

void Game::LoadGame()
{
	while (true)
	{
		std::cout << "Enter a character name to load:" << '\n';
		std::string name;
		std::getline(std::cin, name);
		std::string path{ "saves/" + name + ".txt" };
		if (mPlayer.LoadPlayer(path))
		{
			mNextGameState = GameState::Playing;
			return;
		}
		else
		{
			// Stay in load menu to try again / or return to main menu
			system("cls");
			RenderMainMenu();
			std::cout << "\nFailed to load\n";
			continue;
		}
	}
}

void Game::SaveGame()
{
	std::string saveFilePath{ "saves/" + mPlayer.GetPlayerName() + ".txt" };
	if (mPlayer.SavePlayer(saveFilePath))
	{
		std::cout << "Saved succesfully!\n";
	}
	else
	{
		std::cout << "Failed to save. \n";
	}
	
}
