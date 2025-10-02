#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>


class InventoryItems
{
public:
	std::string productName;
	int productQuantity;
	float productPrice;

	InventoryItems(std::string name, int quantity, float price)
		: productName(name), productQuantity(quantity), productPrice(price) {
	}
};

class Inventory
{
private:
	std::vector<InventoryItems> items;

public:
	Inventory();
	~Inventory();

	bool productExists(const std::string& name) const;
	void addItem(std::string Name, int Quantity, float price);
	void viewInventory();
	void updateItem(std::string& updatingName);
	void deleteItem(std::string& deletingName);

};
