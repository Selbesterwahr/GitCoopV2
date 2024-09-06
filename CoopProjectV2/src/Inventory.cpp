#include "Inventory.h"
#include <fstream>
#include <iostream>

void Inventory::SaveInventory(std::ofstream& outFile) const
{
	for (const auto& item : mInventory)
	{
		outFile << item.first << " " << item.second << "\n";
	}
}

void Inventory::LoadInventory(std::ifstream& inFile)
{
	mInventory.clear();
	std::string itemName;
	int quantity;
	while (inFile >> itemName >> quantity)
	{
		mInventory[itemName] = quantity;
	}
}

void Inventory::DisplayItems() const
{
	for (const auto& item : mInventory)
	{
		if (item.second > 1)
		{
			std::cout << item.second << " " << item.first << " pieces.\n";
		}
		else { std::cout << item.second << " " << item.first << " piece\n"; }
	}
}

size_t Inventory::GetInventorySize() const
{
	return mInventory.size();
}

void Inventory::AddItem(const std::string& itemName, int quantity)
{
	if (mInventory.find(itemName) != mInventory.end())
	{
		mInventory[itemName] += quantity;
	}
	else
	{
		mInventory[itemName] = quantity;
	}
}

void Inventory::RemoveItem(const std::string& itemName, int quantity)
{
	auto it = mInventory.find(itemName);

	if (it != mInventory.end()) // Check if the item was found
	{
		if (quantity >= it->second) { mInventory.erase(it); std::cout << "Dropped " << it->first << ".\n"; }
		else { it->second -= quantity; std::cout << "Dropped " << quantity << " " << it->first << ".\n"; }
	}
	else { std::cout << itemName << " is not in your inventory.\n"; } // If the item ID was not found
}

void Inventory::RemoveAllItems()
{
	mInventory.clear();
}
