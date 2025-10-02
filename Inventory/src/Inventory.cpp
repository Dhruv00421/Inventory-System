#include "Inventory.h"
#include "Vendors/Imgui/imgui.h"
#include "Vendors/Imgui/imgui_stdlib.h"

Inventory::Inventory() {
	std::cout << "Inventory created " << std::endl;
}
Inventory::~Inventory() {}

bool Inventory::productExists(const std::string& name) const {
	return std::find_if(items.begin(), items.end(),
		[&](const InventoryItems& item) {
			return item.productName == name;
		}) != items.end();
}

void Inventory::addItem()
{
	if (!showAddItemWindow) return;

	ImGui::Begin("Adding Item", &showAddItemWindow );

	ImGui::InputText("Item name", &newItemName);
	ImGui::InputInt("Item quantity", &newItemQuantity);
	ImGui::InputFloat("Item price", &newItemPrice);

	if (ImGui::Button("Add")) {
		if (newItemName.empty()) {
			std::cout << "Item filed needed!" << std::endl;
		}
		else if (!productExists(newItemName)) {
			InventoryItems newItem(newItemName, newItemQuantity, newItemPrice);
			items.push_back(newItem);
			std::cout << "Item added " << std::endl;
			showAddItemWindow = false;
			newItemName.clear();
			newItemQuantity = 1;
			newItemPrice = 0.0f;
		}
		else {
			std::cout << "The product is already exists" << std::endl;
			auto it = std::find_if(items.begin(), items.end(), [&](InventoryItems& items) {return items.productName == newItemName; });
			if (it != items.end()) {
				it->productQuantity++;
			}
			showAddItemWindow = false;
			newItemName.clear();
			newItemQuantity = 1;
			newItemPrice = 0.0f;
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Cancel")) {
		showAddItemWindow = false;
		newItemName.clear();
		newItemQuantity = 1;
		newItemPrice = 0.0f;
	}

	ImGui::End();


}

void Inventory::viewInventory()
{
	for (const InventoryItems& item : items) {
		std::cout << "Name: " << item.productName << ", Quantity: " << item.productQuantity << ", Price: " << item.productPrice << std::endl;
	}
	std::cout << "Item viewed " << std::endl;
}

void Inventory::updateItem(std::string& updatingName)
{
	if (productExists(updatingName)) {
		// find_if(begin iterator, ending iterator, predicate(lambda func which checks if the name is equal to the given from begin to ending, predicate returns bool value)also "&" taking reference not copying the value)
		auto it = std::find_if(items.begin(), items.end(), [&](InventoryItems& items) {
			return items.productName == updatingName;
			});
		if (it != items.end()) {
			std::cout << it->productName << std::endl << it->productQuantity << std::endl << it->productPrice << std::endl;
			std::cout << "Which field do you want to change?" << std::endl << "1. Name" << std::endl << "2. quantity" << std::endl << "3. Price" << std::endl;
			int updatingChoice;
			std::cin >> updatingChoice;
			std::string updatingName;
			int updatingQuantity;
			float updatingPrice;
			switch (updatingChoice)
			{
			case 1:
				std::cout << "Enter the name to update: " << std::endl;
				std::cin >> updatingName;
				it->productName = updatingName;
				break;
			case 2:
				std::cout << "Enter the quantity to update: " << std::endl;
				std::cin >> updatingQuantity;
				it->productQuantity = updatingQuantity;
				break;
			case 3:
				std::cout << "Enter the Price to update: " << std::endl;
				std::cin >> updatingPrice;
				it->productPrice = updatingPrice;
				break;

			default:
				break;
			}
		}
	}
	std::cout << "Item updated " << std::endl;
}

void Inventory::deleteItem(std::string& deletingName)
{
	auto it = std::find_if(items.begin(), items.end(), [&](InventoryItems& items) {
		return items.productName == deletingName;
		});
	if (it != items.end()) {
		items.erase(
			std::remove_if(items.begin(), items.end(), [&](InventoryItems& items) {
				return items.productName == deletingName;
				}),
			items.end()
		);
	}
	else {
		std::cout << "Product is not exist!" << std::endl;
	}
	// items.erase(std::remove(items.begin(), items.end(), deletingName), items.end());
	std::cout << "Item deleted " << std::endl;
}
