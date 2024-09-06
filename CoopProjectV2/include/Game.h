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
	GameState				mCurrentGameState;
	GameState				mNextGameState;
	typedef void			(Game::* StateFunction)(); // Defining a type pointer function to state functions
													   // Maps each GameState to a corresponding StateFunction
	void					RenderGame();
	void					RenderMainMenu();
	void					HandleMainMenu();
	void					RenderCharacterCreation();
	void					HandleCharacterCreation();
	void					RenderPlaying();
	void					HandlePlaying();
	void					RenderMining();
	void					HandleMining();
	void					HandleLoading();
	void					RenderInventory();
	void					HandleInventory();
	void					RenderPause();
	void					HandlePause();
	void					LoadGame();
	void					SaveGame();
};