#pragma once
#include <string>
#include "Inventory.h"

class Player
{
public:
	Player(const std::string& name);
	void					SavePlayer(const std::string& filename) const;
	void					LoadPlayer(const std::string& filename);
	std::string				GetPlayerName() const;
	void					GetPlayerInventory() const;
	void					AddItemToInventory(const std::string& itemName, int quantity);
	void					RemoveItemFromInventory(const std::string& itemName, int quantity);
	void					EmptyInventory();
	void					SetPlayerName(std::string& name);
private:
	std::string				mName;
	Inventory				mPlayerInventory;
};

