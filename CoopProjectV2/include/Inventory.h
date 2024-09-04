#pragma once
#include <unordered_map>
#include <string>

class Inventory
{
public:
	Inventory() = default;
	void				SaveInventory(std::ofstream& outFile) const;
	void				LoadInventory(std::ifstream& inFile);
	void				DisplayItems() const;
	size_t				GetInventorySize() const;
	void				AddItem(const std::string& itemName, int quantity);
	void				RemoveItem(const std::string& itemName, int quantity);
	void				RemoveAllItems();
private:
	std::unordered_map<std::string, int> mInventory;
};

