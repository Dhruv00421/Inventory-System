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

	int updatingIndex;
	std::string updatingName;
	int updatingQuantity = 0;
	float updatingPrice = 0.0f;

public:

	bool showAddItemWindow = false;
	bool showViewInventoryWindow = false;
	bool showUpdateItemWindow = false;
	bool showdeleteItemWindow = false;

	std::string newItemName;
	int newItemQuantity = 0;
	float newItemPrice = 0.0f;

	Inventory();
	~Inventory();

	bool productExists(const std::string& name) const;
	void viewInventory(const int windowWidth, const int windowHeight);
	void addItem();
	void updateItem();
	void deleteItem(int deletingIndex);

};
