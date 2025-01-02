
#pragma once
#include <iostream>
#include <fstream>;

const int MAX_SIZE = 1024;

void showAllActionsServer();
void showMenu();

void placeOrder();
void cancelOrder();
void seePreviousOrders();

int checkRole()
{
    char role[MAX_SIZE] = {};
    char c;
    int i = 0;
    std::cout << "Please enter your role: ";
    while (std::cin.get(c) && c != '\n') { // Input the array
        role[i++] = c;
    }
    role[i] = '\0';

    const char server[] = "Server";
    const char manager[] = "Manager";

    bool isServer = true;
    bool isManager = true;

    // Check for "Server"
    i = 0;
    while (server[i]) 
    {
        if ((i == 0) && (server[i] != role[i]) && (server[i] != role[i] + ('A' - 'a')))
        {
            isServer = false;
        }
        else if ((i > 0) && (server[i] != role[i])) {
            isServer = false;
        }
        i++;
    }
    if (isServer)
    {
        system("cls");  // Clear the console
        std::cout << "Greetins, Server!" << "\n";
        return 1;
    }
        

    // Check for "Manager"
    i = 0;
    while (manager[i]) 
    {
        if ((i == 0) && (manager[i] != role[i]) && (manager[i] != role[i] + ('A' - 'a')))
        {
            isManager = false;
        }
        else if ((i > 0) && (manager[i] != role[i])) {
            isManager = false;
        }
        i++;
    }

    if (isManager)
    {
        system("cls");  // Clear the console
        std::cout << "Greetins, Manager!" << "\n";
        return 2;
    }


    return -1;
}


void serverOptions()
{
    int chosenOption = 0;   
    std::cout << "Please choose which action you'd like to use, to see all avalable actions type 1:" << "\n";
    std::cin >> chosenOption;
    switch (chosenOption)
    {
    case 1: showAllActionsServer(); break;
    case 2: showMenu(); break;
    case 3: placeOrder(); break;
    case 4: cancelOrder(); break;
    case 5: seePreviousOrders(); break;
    }
}

void showAllActionsServer()
{
    system("cls");
    std::cout << "1) See all avalable actions. " << "\n";
    std::cout << "2) See the menu. " << "\n";
    std::cout << "3) Place an order. " << "\n";
    std::cout << "4) Cancel an order. " << "\n";
    std::cout << "5) Look at previous orders. " << "\n";
    std::cout << "6) Look at previous orders in an alphabetical order, as well as the number of items ordered. " << "\n";
    std::cout << "7) See the turnover for the day." << "\n";
    std::cout << "\n";
    serverOptions();
}

void showMenu()
{
   system("cls");  // Clear the console
   std::fstream ofs;

   ofs.open("restaurant_menu.txt", std::ios::in);
   if (!ofs.is_open()) 
   {
       std::cerr << "Failed to open file for reading.\n";
       return;
   }
  
   char ch;
   while (ofs.get(ch)) 
   {
       std::cout << ch;
   }
   ofs.close();
   std::cout << "\n";
   serverOptions();
}

bool compareStrings(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

void placeOrder() {
    std::ifstream menuFile("restaurant_menu.txt", std::ios::in);
    if (!menuFile) {
        std::cout << "Error: cannot open the Menu file!" << std::endl;
        return;
    }

    char menuItem[256];
    char orderItem[256];
    bool itemFound = false;

    std::cin.ignore(); // Clear the leftover newline from previous input.
    std::cout << "Enter the name of the item: ";
    std::cin.getline(orderItem, 256);

    while (menuFile.getline(menuItem, 256)) { // Check if the item is on the menu
        if (compareStrings(menuItem, orderItem)) {
            itemFound = true;
            break;
        }
    }
    menuFile.close();

    if (!itemFound) {
        std::cout << "This item cannot be found on the menu!" << std::endl;
        return;
    }

    int quantity = 0;
    std::cout << "Enter quantity: "; // If the item is found, the quantity of it is asked.
    std::cin >> quantity;

    std::ofstream orderFile("orders.txt", std::ios::app); // Writing the data to a separate file only for orders on the current day.
    if (!orderFile) {
        std::cout << "Error: cannot open the Orders file!" << std::endl;
        return;
    }

    orderFile << orderItem << " " << quantity << std::endl;
    orderFile.close();

    std::cout << "The order was successful!" << std::endl;
    serverOptions();
}

void cancelOrder() {
    std::ifstream orderFile("orders.txt", std::ios::in);
    if (!orderFile) {
        std::cerr << "Error: cannot find the file for orders!" << std::endl;
        return;
    }

   
    struct Order {
        char name[256];
        int quantity;
    };

    Order orders[100]; 
    int orderCount = 0;

    while (orderFile >> orders[orderCount].name >> orders[orderCount].quantity) {
        orderFile.ignore(); 
        orderCount++;
    }
    orderFile.close();

  
    char cancelItem[256];
    std::cin.ignore(); // Clear the input buffer
    std::cout << "Enter the name of the item to cancel: ";
    std::cin.getline(cancelItem, 256);

   
    bool itemFound = false;
    for (int i = 0; i < orderCount; i++) {
        if (compareStrings(orders[i].name, cancelItem)) {
            itemFound = true;

            
            int cancelQuantity;
            std::cout << "Enter the quantity to cancel: ";
            std::cin >> cancelQuantity;

            if (cancelQuantity > orders[i].quantity) {
                std::cerr << "Error: Cannot cancel more than the existing quantity!" << std::endl;
                return;
            }

         
            if (cancelQuantity == orders[i].quantity) {
                orders[i].quantity = 0; // 
            }
            else {
                orders[i].quantity -= cancelQuantity;
            }
            break;
        }
    }

    if (!itemFound) {
        std::cerr << "Error: Item not found in the orders!" << std::endl;
        return;
    }

    
    std::ofstream outFile("orders.txt", std::ios::out | std::ios::trunc);               // Rewrite the file with updated orders
    if (!outFile) {
        std::cerr << "Error: Cannot open the Orders file for writing!" << std::endl;
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].quantity > 0) { // Only write non-deleted orders
            outFile << orders[i].name << " " << orders[i].quantity << std::endl;
        }
    }
    outFile.close();

    std::cout << "The order was successfully canceled!" << std::endl;
}


void seePreviousOrders() {
    std::ifstream orderFile("orders.txt", std::ios::in);
    if (!orderFile) {
        std::cerr << "Error: cannot find the file for orders!" << std::endl;
        return;
    }

    char orderLine[256];
    std::cout << "Previous orders:\n";

    while (orderFile.getline(orderLine, 256)) {
        std::cout << orderLine << std::endl;
    }

    orderFile.close();
    serverOptions();
}
