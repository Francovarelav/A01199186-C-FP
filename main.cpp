// FRANCO VARELA VILLEGAS
// A01199186
//FINAL PROJECT, furniture
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;


// inventory class

class Item{
private:
    string itemName;
    int itemPrice;
    int itemProfit;
    int itemQuantity;
    bool itemStatus;
    string itemMaterial;
    string itemColor;
public:
    // constructor
    Item(string name, int price, int profit, int quantity, bool status, string material, string color)
    :   itemName(name), itemPrice(price), itemProfit(profit), itemQuantity(quantity), itemStatus(status), itemMaterial(material), itemColor(color){}
    // destructor
    virtual ~Item() = default;
    // display information of the item
    virtual void displayItemInfo() const{
        cout << 
        " // Item Name: " << itemName <<  
        " // Item Price: $" << itemPrice << 
        " // Item Profit: $" << itemProfit <<
        " // Item Quantity: " << itemQuantity <<
        " // Item Status: " << (itemStatus ? "Active" : "Inactive") <<
        " // Item Material: " << itemMaterial <<
        " // Item Color: " << itemColor << endl;
    }
    // check if item is available for an order
    virtual void checkStatus() const{
        if(itemStatus == true || itemQuantity > 0){
            cout << "Item is active for an order" << endl;
        }
        else if (!itemStatus || itemQuantity <= 0){
            cout << "No items left of" << itemName << endl;
        }
    }
    // update item quantity add when adding items to inventory
    virtual void addQuantity(int selectedQuantity) {
        itemQuantity += selectedQuantity;
        if (itemQuantity <= 0){
            itemStatus = false;
        }
        else{
            itemStatus = true;
        }
    }
    // update item quantity remove when adding orders
    virtual void removeQuantity(int selectedQuantity) {
        itemQuantity -= selectedQuantity;
        if (itemQuantity <= 0){
            itemStatus = false;
        }
        else{
            itemStatus = true;
        }
    }
    // GETTERS
    string getItemName() const { return itemName; }
    int getItemPrice() const { return itemPrice; }
    int getItemProfit() const { return itemProfit; }
    int getItemQuantity() const { return itemQuantity; }

};

// chair class =========>
class Chair : public Item{
private:
    int chairHeight;
    bool backSeat;
public:
// constructor
    Chair(string name, int price, int profit, int quantity, bool status, string material, string color, int height, bool seat)
    : Item(name, price, profit, quantity, status, material, color), chairHeight(height), backSeat(seat) {}

    void displayItemInfo(){
        Item::displayItemInfo();
        cout << 
        " //  Chair Height: " << chairHeight <<
        " //  Chair Back Seat: " << (backSeat ? "Yes" : "No") << endl;
    }
};

// SOFA class =========>
class Sofa : public Item{
private:
    string sofaType;
    bool waterProof;
public:
// constructor
    Sofa(string name, int price, int profit, int quantity, bool status, string material, string color, string sofaType, bool waterProof)
    : Item(name, price, profit, quantity, status, material, color), sofaType(sofaType), waterProof(waterProof) {}

    void displayItemInfo(){
        Item::displayItemInfo();
        cout << 
        " //  Sofa Type: " << sofaType <<
        " //  Water Proof?: " << (waterProof ? "Water Proof" : "Not Water Proof") << endl;
    }
};

// TABLE class =========>
class Table : public Item{
private:
    string tableType;
    int tableCapacity;
public:
// constructor
    Table(string name, int price, int profit, int quantity, bool status, string material, string color, string tableType, int capacity)
    : Item(name, price, profit, quantity, status, material, color), tableType(tableType), tableCapacity(capacity) {}

    void displayItemInfo(){
        Item::displayItemInfo();
        cout << 
        " //  Table Type: " << tableType << 
        " //  Table Capacity: " << tableCapacity << endl;
    }
};

// class INVENTORY =========>
class Inventory{
    public:
        vector <Item*> inventoryArray;
        Inventory(){
            //3 of each one with different quantities
            inventoryArray.push_back(new Chair("Oxford", 1000, 500, 15, true, "Wood", "Brown", 3, true));
            inventoryArray.push_back(new Chair("Zinus", 700, 450, 12, true, "Steel", "Black", 2, true));
            inventoryArray.push_back(new Chair("Aidan", 500, 200, 8, true, "Plastic", "Red", 1.2, false));

            inventoryArray.push_back(new Sofa("Iron Man", 10000, 8000, 22, true, "American Steel", "White", "L type", true));
            inventoryArray.push_back(new Sofa("Superman", 12000, 6000, 11, true, "Woord", "Yellow", "Sofa Cama", true));
            inventoryArray.push_back(new Sofa("Batman", 20000, 14000, 6, true, "Rock", "Black", "Movie Sofa", false));

            inventoryArray.push_back(new Table("Spider Man", 9000, 4500, 19, true, "Web", "Red", "Dinning room", 8));
            inventoryArray.push_back(new Table("Hullk", 13000, 9000, 2, true, "Adamantium", "Green", "Outdoors", 10));
            inventoryArray.push_back(new Table("Gambler", 30000, 22000, 40, true, "Magnets", "Brown", "Poker Table", 9));
        };
        //display Inventory
        void displayInventory(){
            for(const Item* item: inventoryArray){
                item->displayItemInfo();
                cout << "-------------" << endl;
            }
            if(inventoryArray.size() == 0){
                cout << "No items in the inventory" << endl;
            }
        }

        // ADDING ITEM
       void editInventory(Inventory& inventory) {
        cout << "You can only add or remove quantity for existing items in the inventory." << endl;
        string nametoEdit;
        int quantityToEdit;
        cout << "Please enter the name of the item to edit: ";
        cin >> nametoEdit;

        bool itemFound = false;
        for (Item* item : inventory.inventoryArray) {
            if (item->getItemName() == nametoEdit) {
                itemFound = true;

                cout << "Enter the quantity to adjust (positive to add, negative to remove): ";
                cin >> quantityToEdit;
                int totalQuantity = item->getItemQuantity();
                // negative cases
                if(quantityToEdit < 0){
                    // cannot edit
                    if(totalQuantity + quantityToEdit < 0){
                        cout << "You cannot remove more items than you have in stock." << endl;
                    }
                    // can edit
                    else{
                        quantityToEdit = quantityToEdit*-1;
                        item->removeQuantity(quantityToEdit);
                        cout << "Successfully removed " << quantityToEdit << " items from" << nametoEdit << endl;
                        cout << "New stock of" << nametoEdit << "is " << item->getItemQuantity() << endl;
                    }
                }
                // positive cases
                else{
                    item->addQuantity(quantityToEdit);    
                    cout << "Successfully added " << quantityToEdit << " items from " << nametoEdit << endl;
                    cout << "New stock of " << nametoEdit << " is: " << item->getItemQuantity() << endl;
                }
            }
        }

        if (!itemFound) {
            cout << "Error: Item '" << nametoEdit << "' not found in the inventory." << endl;
        }
    }

};


class Order{
private:
    int orderNumber;
    int totalProfit;
    int totalPrice;
    vector<Item*> orderItems;

public:
    Order(int number) : orderNumber(number), totalProfit(0), totalPrice(0) {}

    
    void addItemToOrder(Item* item, int quantity) {
        orderItems.push_back(item);
        totalPrice += item->getItemPrice() * quantity;
        totalProfit += item->getItemProfit() * quantity;
    }

    void displayOrderSummary() const {
        cout << "Order Number: " << orderNumber << endl;
        cout << "Total Price: $" << totalPrice << endl;
        cout << "Total Profit: $" << totalProfit << endl;
    }

    int getTotalPrice() const { return totalPrice; }
    int getTotalProfit() const { return totalProfit; }

};

class OrderRegister{
    public:
    vector<Order*> orderArray;
    ~OrderRegister() {
        for (Order* order : orderArray) {
            delete order;
        }
    }

    void addOrder(Order* order) {
        orderArray.push_back(order);
    }

    void displayAllOrders() const {
        for (const Order* order : orderArray) {
            order->displayOrderSummary();
            cout << "-------------" << endl;
        }
        if(orderArray.size() == 0){
            cout << "No orders to display." << endl;
            cout << "Make an order pressing 1." << endl;
        }
    }

};

// staff main class
class Staff {
private:
    string staffName;
    string staffPassword;

public:
    // Constructor with parameters
    Staff(string name, string password) : staffName(name), staffPassword(password) {}
    // Default constructor
    Staff() : staffName(""), staffPassword("") {}
    // Destructor
    ~Staff() = default;
    // Get name
    string getName() const { return staffName; }

    // Set staff information
    void setStaffInfo(string providedName, string providedPassword) {
        staffName = providedName;
        staffPassword = providedPassword;
    }

    // Display staff info
    void displayStaffInfo() const {
        cout << "Staff Name: " << staffName << endl;
    }

    void staffLogin(string guessedPassword){
        while (staffPassword != guessedPassword){
            cout << "Incorrect password, please try again." << endl;
            cout << "Enter password: ";
            cin >> guessedPassword;
            if(guessedPassword == staffPassword){
                cout << "Welcome, " << staffName << endl;
                break; 
            }
        }
    }

        // Crear orden (actualización dentro de Staff)
    void createOrder(Inventory& inventory, OrderRegister& orderRegister, int orderNumber) {
        Order* newOrder = new Order(orderNumber);
        cout << "In order to make an order, follow these steps:" << endl;
        cout << "1. Enter the number of items you want to add." << endl;
        cout << "2. Enter the name of each item." << endl;
        cout << "3. Enter the quantity of each item." << endl;
        cout << "==============================" << endl;
        cout << "Available furniture:" << endl;
        inventory.displayInventory();

        int itemsOrder;
        cout << "How many different items do you want to order? ";
        cin >> itemsOrder;

        for (int i = 0; i < itemsOrder; i++) {
            string itemName;
            int userItemQuantity;

            cout << "Enter the name of item " << (i + 1) << ": ";
            cin.ignore();
            getline(cin, itemName);

            // search for article
            bool itemFound = false;
            for (Item* item : inventory.inventoryArray) {
                if (item->getItemName() == itemName) {
                    itemFound = true;

                    cout << "Enter the quantity of " << itemName << ": ";
                    cin >> userItemQuantity;
                    // VERIFY IS THE QUANTITY ADDED IS AVAILABLE
                    if (userItemQuantity > 0 && userItemQuantity <= item->getItemQuantity()) {
                        item->removeQuantity(userItemQuantity); // Actualizar inventario
                        newOrder -> addItemToOrder(item, userItemQuantity);
                        cout << userItemQuantity << " of "<< itemName <<" successfully added to the order." << endl;
                    } else {
                        cout << "Insufficient quantity available for " << itemName <<"" << endl;
                        i --;
                    }
                    break;
                }
            }

            if (!itemFound) {
                cout << "Item "<< itemName << " not found in the inventory." << endl;
                i --;
            }
        }
        orderRegister.addOrder(newOrder);
        cout << "Order creation complete!" << endl;
    }

};


int main() {
    Inventory furnitureInventory;
    OrderRegister orderRegister;

    // Selección inicial
    int initialSelection;
    cout << "Hello! If you are junior, press 1. If you are senior, press 2: ";
    cin >> initialSelection;

    if (initialSelection == 1) {
        Staff juniorStaff("Junior", "Junior");
        string guessPassword;
        cout << "Enter the password: ";
        cin >> guessPassword;

        juniorStaff.staffLogin(guessPassword);

        // Junior Staff Menu
        int selectionMenu;
        do {
            cout << "\nJunior Staff Menu:\n"
                 << "1. Add Order\n"
                 << "2. Display Inventory\n"
                 << "4. Display Orders\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            cin >> selectionMenu;

            switch (selectionMenu) {
                case 1: {
                    static int orderCount = 1; // Keeps track of the order number
                    juniorStaff.createOrder(furnitureInventory, orderRegister, orderCount++);
                    break;
                }
                case 2:
                    furnitureInventory.displayInventory();
                    break;
                case 4:
                    orderRegister.displayAllOrders();
                    break;
                case 5:
                    cout << "Exiting Junior Staff Menu..." << endl;
                    break;
                default:
                    cout << "Invalid selection. Please try again." << endl;
                    break;
            }
        } while (selectionMenu != 4);
    } 

    else if (initialSelection == 2) {
        Staff seniorStaff("Senior", "Admin");
        string guessPassword;
        cout << "Enter the password: ";
        cin >> guessPassword;

        seniorStaff.staffLogin(guessPassword);

        // Senior Staff Menu
        int selectionMenu;
        do {
            cout << "\nSenior Staff Menu:\n"
                 << "1. Add Order\n"
                 << "2. Display Inventory\n"
                 << "3. Display Orders\n"
                 << "4. Edit Inventory\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            cin >> selectionMenu;

            switch (selectionMenu) {
                case 1:
                    static int orderCount = 1; // Keeps track of the order number
                    seniorStaff.createOrder(furnitureInventory, orderRegister, orderCount++);
                    break;
                case 2:
                    furnitureInventory.displayInventory();
                    break;
                case 3:
                    orderRegister.displayAllOrders();
                    break;
                case 4:
                    furnitureInventory.editInventory(furnitureInventory);
                    break;
                case 5:
                    cout << "Exiting Senior Staff Menu..." << endl;
                    break;
                default:
                    cout << "Invalid selection. Please try again." << endl;
                    break;
            }
        } while (selectionMenu != 4);
    } 

    else {
        cout << "Invalid selection. Exiting program." << endl;
    }

    return 0;
}