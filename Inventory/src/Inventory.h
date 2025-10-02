#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>

//#include "Vendors/Imgui/imgui_stdlib.h"

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
	void addItem();
	void viewInventory();
	void updateItem(std::string& updatingName);
	void deleteItem(std::string& deletingName);

};
