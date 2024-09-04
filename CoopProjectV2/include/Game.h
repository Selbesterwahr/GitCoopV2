#pragma once
#include "GameStates.h"
#include "Player.h"

class Game
{
public:
	Game();

	void					Run();

private:
	Player					mPlayer;
	GameState				mGameState;
	typedef void			(Game::* StateFunction)(); // Defining a type pointer function to state functions
													   // Maps each GameState to a corresponding StateFunction
	void					HandleMainMenu();
	void					HandleCharacterCreation();
	void					HandlePlaying();
	void					HandleMining();
	void					HandleLoading();
	void					HandleInventory();
	void					HandlePause();
};