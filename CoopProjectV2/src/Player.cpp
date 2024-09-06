#include "Player.h"
#include <fstream>
#include <iostream>


Player::Player(const std::string& name)
	:mName{ name }
{
}

bool Player::SavePlayer(const std::string& filename) const
{
	std::ofstream outFile(filename);
	if (outFile.is_open())
	{
		outFile << mName << "\n";
		mPlayerInventory.SaveInventory(outFile);
		outFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::LoadPlayer(const std::string& filename)
{
	std::ifstream inFile(filename);
	if (inFile.is_open())
	{
		std::getline(inFile, mName);
		mPlayerInventory.LoadInventory(inFile);
		inFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

std::string Player::GetPlayerName() const
{
	return mName;
}

void Player::GetPlayerInventory() const
{
	if (mPlayerInventory.GetInventorySize() == 0)
	{
		std::cout << "Your inventory is empty." << std::endl;
	}
	else
	{
		std::cout << "You have: "; mPlayerInventory.DisplayItems();
	}
}

void Player::AddItemToInventory(const std::string& itemName, int quantity)
{
	mPlayerInventory.AddItem(itemName, quantity);
}

void Player::RemoveItemFromInventory(const std::string& itemName, int quantity)
{
	mPlayerInventory.RemoveItem(itemName, quantity);
}

void Player::EmptyInventory()
{
	mPlayerInventory.RemoveAllItems();
}

void Player::SetPlayerName(std::string& name)
{
	mName = name;
}
