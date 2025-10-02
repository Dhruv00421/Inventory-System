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

void Inventory::viewInventory(const int windowWidth, const int windowHeight)
{
	if (!showViewInventoryWindow) return;

	ImGui::Begin("View Inventory", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);

	int column = 4;
	int emptySlots = column - (items.size() % column);

	if (ImGui::BeginTable("InventoryTable", column))
	{
		for (size_t i = 0; i < emptySlots; i++)
		{
			ImGui::TableNextColumn();
			ImGui::PushID(static_cast<int>(i));

			if (i < items.size()) {
				ImGui::BeginChild("Panel", ImVec2(200, 200), true);
				ImGui::Text("Name: %s", items[i].productName.c_str());
				ImGui::Text("Qty: %d", items[i].productQuantity);
				ImGui::Text("Price: %.2f", items[i].productPrice);
				if (ImGui::IsItemHovered()) {
					ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(100, 100, 250, 50));
				}

				if (ImGui::Button("update")) {
					showUpdateItemWindow = true;
					updatingIndex = i;
					updatingName = items[i].productName;
					updatingQuantity = items[i].productQuantity;
					updatingPrice = items[i].productPrice;
					Inventory::updateItem();
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete")) {
					deleteItem(i);
				}

				ImGui::EndChild();
			}
			else {
				ImGui::BeginChild("EmptySlots", ImVec2(200, 200), true);
				ImGui::Text("Add Item");
				if (ImGui::IsItemHovered()) {
					ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(100, 100, 250, 50));
				}

				if (ImGui::Button("Add Item")) {
					showAddItemWindow = true;
				}
				ImGui::SameLine();
				ImGui::EndChild();
			}


			ImGui::PopID();
		}

		ImGui::EndTable();
	}


	ImGui::End();
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
			newItemQuantity = 0;
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
			newItemQuantity = 0;
			newItemPrice = 0.0f;
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Cancel")) {
		showAddItemWindow = false;
		newItemName.clear();
		newItemQuantity = 0;
		newItemPrice = 0.0f;
	}

	ImGui::End();


}


void Inventory::updateItem()
{
	if (!showUpdateItemWindow) return;

	ImGui::Begin("Adding Item", &showUpdateItemWindow);

	ImGui::InputText("Item name", &updatingName);
	ImGui::InputInt("Item quantity", &updatingQuantity);
	ImGui::InputFloat("Item price", &updatingPrice);

	if (ImGui::Button("Update")) {
		if (updatingName.empty()) {
			std::cout << "Item filed needed!" << std::endl;
		}
		else {
			items[updatingIndex].productName = updatingName;
			items[updatingIndex].productQuantity = updatingQuantity;
			items[updatingIndex].productPrice = updatingPrice;

			showUpdateItemWindow = false;
			updatingName.clear();
			updatingIndex = -1;
			updatingPrice = 0;
			updatingQuantity = 0.0f;
		}

		
	}

	ImGui::SameLine();
	if (ImGui::Button("Cancel")) {
		showUpdateItemWindow = false;
		updatingName.clear();
		updatingIndex = -1;
		updatingPrice = 0;
		updatingQuantity = 0.0f;
	}

	ImGui::End();

	
}

void Inventory::deleteItem(int deletingIndex)
{

	if(deletingIndex < items.size())
		items.erase(items.begin() + deletingIndex);

	/*auto it = std::find_if(items.begin(), items.end(), [&](InventoryItems& items) {
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
	std::cout << "Item deleted " << std::endl;*/
}
