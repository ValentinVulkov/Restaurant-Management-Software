
#pragma once
#include <iostream>
#include <fstream>;
#include "strUtils.h"

const int MAX_SIZE = 1024;
const char* findLastDate(const char* filename);
const char* CURRENT_DATE = findLastDate("dates.txt");


struct Order {
    char* item;
    int quantity;
};



//DEFINITIONS
//actions
void showAllActionsServer();
void showAllActionsManager();

//menu operations
void showMenu();
void placeOrder();
void cancelOrder();
void showMenuRemaining();
void addMenuItem(const char* filename);
void removeMenuItem(const char* filename);


//order operations
void seePreviousOrders();
void seePreviousOrdersSorted();

//warehouse operations
void showWarehouseStock();
void removeFromWarehouseStock();
void addProductToWarehouse();
void updateWarehouse(const char* item, int quantity);

//financial operations
double getPrice(const char* itemName);
void turnoverFromDate(const char* filename);
void turnoverToday(const char* filename);

//date
void addNextDate(const char* CURRENT_DATE);




int checkRole()
{
    unsigned role = 0;
    std::cout << CURRENT_DATE << "\n";
    std::cout << "Please enter your role: " << "\n";
    std::cout << "             1. Server" << "\n";
    std::cout << "             2. Manager" << "\n";

    std::cin >> role;

    system("cls");

    if (role == 1) {
        std::cout << "Greetings, Server!" << "\n";
        return 1;
    }
    else if (role == 2) {
        std::cout << "Greetings, Manager!" << "\n";
        return 2;
    }
    else {
        std::cout << "Invalid role! Please enter 1 for Server or 2 for Manager."<< "\n";
        return -1;
    }
}
void serverOptions()
{
    while (true)
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
        case 6: seePreviousOrdersSorted(); break;
        case 7: turnoverToday("dates.txt"); break;
        case 8: exit(0); break;
        default: std::cout << "Not an avalable option."; serverOptions(); break;
        }
    }
}
void managerOptions()
{
    while (true)
    {
        int chosenOption = 0;
        std::cout << "Please choose which action you'd like to use, to see all avalable actions type 1:" << "\n";
        std::cin >> chosenOption;
        switch (chosenOption)
        {
        case 1: showAllActionsManager(); break;
        case 2: showMenu(); break;
        case 3: placeOrder(); break;
        case 4: cancelOrder(); break;
        case 5: seePreviousOrdersSorted(); break;
        case 6: seePreviousOrders(); break;
        case 7: showMenuRemaining(); break;
        case 8: showWarehouseStock(); break;
        case 9: removeFromWarehouseStock(); break;
        case 10: addProductToWarehouse(); break;
        case 11: turnoverToday("dates.txt"); break;
        case 12: addNextDate(CURRENT_DATE); break;
        case 13: turnoverFromDate("dates.txt"); break;
        case 14: addMenuItem("dates.txt"); break;
        case 15: removeMenuItem("dates.txt"); break;
        case 16: exit(0); break;
        default: std::cout << "Not an avalable option."; managerOptions(); break;
        }
    }
}       // Show all     // Show all avalable op

// Searches for the latest date
const char* findLastDate(const char* filename) {
    static char date[11];
    int i = 0;

    std::fstream file(filename, std::ios::in);
    if (!file) {
        std::cout << "Cannot open the file." << std::endl;
        return nullptr;
    }

    char ch;
    while (file.get(ch)) {
        if (ch == '\n') {
            i = 0;
        }
        else if (i < 10) {
            date[i++] = ch;
        }
    }
    date[10] = '\0';

    file.close();
    return date;
}   
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int daysInMonth(int month, int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}  // Helping function
// Finds the date tommorow
void addNextDate(const char* CURRENT_DATE) { 
    const char* date = CURRENT_DATE;
    int day = myStoi(date);                   
    int month = myStoi(date + 3);              
    int year = myStoi(date + 6);               

   
    day++;
    if (day > daysInMonth(month, year)) {      // If day exceeds the number of days in the month
        day = 1;                              
        month++;                               
        if (month > 12) {                      
            month = 1;
            year++;
        }
    }

   
    char nextDate[25];  
    nextDate[0] = (day / 10) + '0';          
    nextDate[1] = (day % 10) + '0';          
    nextDate[2] = '/';
    nextDate[3] = (month / 10) + '0';        
    nextDate[4] = (month % 10) + '0';        
    nextDate[5] = '/';
    nextDate[6] = (year / 1000) + '0';       
    nextDate[7] = ((year / 100) % 10) + '0'; 
    nextDate[8] = ((year / 10) % 10) + '0'; 
    nextDate[9] = (year % 10) + '0';         
    nextDate[10] = ' ';                      
    nextDate[11] = '\0';                    

   
    const char* timePart = strchr(CURRENT_DATE, ' '); // Find the time part (first space)
    if (timePart != nullptr) {
       
        myStrcpy(nextDate + 11, timePart + 1);  // Skip the space before the time part
    }

    
    std::ofstream file("dates.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open dates.txt.\n";
        return;
    }

    file << nextDate << "\n";  // Write the next date and time to the file
    file.close();

 
    std::ofstream ordersFile("orders.txt", std::ios::trunc);
    if (!ordersFile.is_open()) {
        std::cerr << "Error: Could not open orders.txt to clear it.\n";
        return;
    }

    ordersFile.close();  

    std::cout << "Next date " << nextDate << " added to dates.txt.\n";
    std::cout << "Orders have been cleared from orders.txt.\n";
}
bool isDateGreaterOrEqual(const char* date1, const char* date2) {
    // Compare year, month, and day separately
    int year1 = (date1[6] - '0') * 1000 + (date1[7] - '0') * 100 + (date1[8] - '0') * 10 + (date1[9] - '0');
    int year2 = (date2[6] - '0') * 1000 + (date2[7] - '0') * 100 + (date2[8] - '0') * 10 + (date2[9] - '0');

    if (year1 > year2) return true;
    if (year1 < year2) return false;

    int month1 = (date1[3] - '0') * 10 + (date1[4] - '0');
    int month2 = (date2[3] - '0') * 10 + (date2[4] - '0');

    if (month1 > month2) return true;
    if (month1 < month2) return false;

    int day1 = (date1[0] - '0') * 10 + (date1[1] - '0');
    int day2 = (date2[0] - '0') * 10 + (date2[1] - '0');

    return day1 >= day2;
}



//actions for both roles
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
}
void showAllActionsManager()
{
    system("cls");
    std::cout << "1) See all avalable actions. " << "\n";
    std::cout << "2) See the menu. " << "\n";
    std::cout << "3) Place an order. " << "\n";
    std::cout << "4) Cancel an order. " << "\n";
    std::cout << "5) Look at previous orders. " << "\n";
    std::cout << "6) Look at previous orders in an alphabetical order, as well as the number of items ordered. " << "\n";
    std::cout << "7) Show everything menu item remaining." << "\n";
    std::cout << "8) Show everything contained in the warehouse." << "\n";
    std::cout << "9) Remove an item from the warehouse." << "\n";
    std::cout << "10) Add a product to the warehouse." << "\n";
    std::cout << "11) Show turnover for the day." << "\n";
    std::cout << "12) End the day." << "\n";
    std::cout << "13) Show the turnover from a certain date forward." << "\n";
    std::cout << "14) Add an item to the menu." << "\n";
    std::cout << "15) Remove an item from the menu." << "\n";



    std::cout << "\n";
    managerOptions();
}

//menu operations
void showMenu()
{
    system("cls");  // Clear the console
    std::fstream ofs;

    ofs.open("menu_prices.txt", std::ios::in);
    if (!ofs.is_open())
    {
        std::cout << "Failed to open file for reading.\n";
        return;
    }

    char ch;
    while (ofs.get(ch))
    {
        std::cout << ch;
    }
    ofs.close();
    std::cout << "\n";
}


// Function to place an order
void placeOrder() {
    char menuItem[256], searchItem[256];
    bool found = false;
    int quantity;

    // Open the menu file
    std::ifstream menuFile("menu_prices.txt");
    if (!menuFile) {
        std::cout << "Error: cannot open the menu file.\n";
        return;
    }

    std::cin.ignore();

    // Ask for the item
    std::cout << "Please enter the name of the item you wish to order: ";
    std::cin.getline(searchItem, sizeof(searchItem));

    // Check if the item exists in the menu
    while (menuFile.getline(menuItem, sizeof(menuItem))) {
        char itemName[256];
        int i = 0;
        while (menuItem[i] != '\0' && menuItem[i] != ' ') {
            itemName[i] = menuItem[i];
            i++;
        }
        itemName[i] = '\0';

        if (strcmp(searchItem, itemName) == 0) {
            found = true;
            break;
        }
    }
    menuFile.close();

    // If the item is found, ask for quantity and write to orders.txt
    if (found) {
        std::cout << "The item \"" << searchItem << "\" is available.\n";
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        std::ofstream ordersFile("orders.txt", std::ios::app);
        if (!ordersFile) {
            std::cout << "Error: cannot open the file with orders!\n";
            return;
        }

        ordersFile << searchItem << " " << quantity << "\n";
        ordersFile.close();

        std::cout << "The order has been successfully added.\n";

        // Update the warehouse file
        updateWarehouse(searchItem, quantity);
    } else {
        std::cout << "The item \"" << searchItem << "\" is not available in the menu.\n";
    }
}



//function that cancels an order
void cancelOrder() {
    char item[100];
    int cancelQuantity;
    double price = 0.0;

    // Ask for the item to cancel
    std::cout << "Enter the item you want to cancel: ";
    std::cin.ignore();
    std::cin.getline(item, 100);

    
    std::ifstream menuFile("menu_prices.txt");
    if (!menuFile) {
        std::cout << "Error opening menu_prices.txt.\n";
        return;
    }

    char menuItem[100];
    double menuPrice;
    bool itemFound = false;

    while (menuFile >> menuItem >> menuPrice) {
        // Check for an exact match between input item and menu item
        int i = 0;
        bool match = true;
        while (menuItem[i] != '\0' || item[i] != '\0') {
            if (menuItem[i] != item[i]) {
                match = false;
                break;
            }
            i++;
        }

        if (match) {
            price = menuPrice;
            itemFound = true;
            break;
        }
    }
    menuFile.close();

    if (!itemFound) {
        std::cout << "Item not found in menu.\n";
        return;
    }

    // Ask for the quantity to cancel
    std::cout << "Enter the quantity to cancel: ";
    std::cin >> cancelQuantity;

    // Read orders.txt to find and update the item
    std::ifstream ordersFile("orders.txt");
    std::ofstream tempOrdersFile("temp_orders.txt");
    if (!ordersFile || !tempOrdersFile) {
        std::cout << "Error opening orders.txt or creating temp_orders.txt.\n";
        return;
    }

    char line[200];
    bool quantityUpdated = false;

    while (ordersFile.getline(line, 200)) {
        char orderItem[100];
        int orderQuantity = 0;
        int i = 0, j = 0;


        while (line[i] != ' ' && line[i] != '\0') {
            orderItem[j++] = line[i++];
        }
        orderItem[j] = '\0';

        // Skip space and extract quantity
        if (line[i] == ' ') {
            i++;
            orderQuantity = 0;
            while (line[i] >= '0' && line[i] <= '9') {
                orderQuantity = orderQuantity * 10 + (line[i] - '0');
                i++;
            }
        }

  
        bool match = true;
        j = 0;
        while (orderItem[j] != '\0' || item[j] != '\0') {
            if (orderItem[j] != item[j]) {
                match = false;
                break;
            }
            j++;
        }

        // Update the quantity if it matches
        if (match) {
            if (orderQuantity >= cancelQuantity) {
                orderQuantity -= cancelQuantity;
                quantityUpdated = true;
            }
            else {
                std::cout << "Cancel quantity exceeds ordered quantity.\n";
                tempOrdersFile.close();
                ordersFile.close();
                return;
            }
        }

        // Write back updated or original line to temp file
        if (orderQuantity > 0) {
            tempOrdersFile << orderItem << " " << orderQuantity << "\n";
        }
    }
    ordersFile.close();
    tempOrdersFile.close();

    if (!quantityUpdated) {
        std::cout << "Item not found in orders or invalid cancel quantity.\n";
        return;
    }

    // Replace orders.txt with updated temp_orders.txt
    std::remove("orders.txt");
    std::rename("temp_orders.txt", "orders.txt");


    std::ifstream datesFile("dates.txt");
    std::ofstream tempDatesFile("temp_dates.txt");
    if (!datesFile || !tempDatesFile) {
        std::cout << "Error opening dates.txt or creating temp_dates.txt.\n";
        return;
    }

    char date[20];
    double totalSum;
    if (datesFile >> date >> totalSum) {
        totalSum -= cancelQuantity * price;
        tempDatesFile << date << " " << totalSum << "\n";
    }
    datesFile.close();
    tempDatesFile.close();


    std::remove("dates.txt");
    std::rename("temp_dates.txt", "dates.txt");

    std::cout << "Order canceled successfully.\n";
}
//show all remaining quantities of menu items
void showMenuRemaining()
{
    system("cls");  // Clear the console
    std::fstream ofs;

    ofs.open("menu_remaining.txt", std::ios::in);
    if (!ofs.is_open())
    {
        std::cout << "Failed to open file for reading.\n";
        return;
    }

    char ch;
    while (ofs.get(ch))
    {
        std::cout << ch;
    }
    ofs.close();
    std::cout << "\n";

}
//add/remove an item to the menu
void addMenuItem(const char* filename) {
    char itemName[256];
    double price;

    // Input for the new menu item
    std::cout << "Enter the name of the menu item: ";
    std::cin.ignore();
    std::cin.getline(itemName, sizeof(itemName));

    std::cout << "Enter the price of the menu item: ";
    std::cin >> price;

    if (price < 0) {
        std::cout << "Error: Price cannot be negative.\n";
        return;
    }


    std::ofstream menuFile(filename, std::ios::app);
    if (!menuFile) {
        std::cout << "Error: Cannot open the menu file!" << std::endl;
        return;
    }

    menuFile << itemName << " " << price << "\n";
    menuFile.close();

    std::cout << "Menu item added successfully!\n";
}
void removeMenuItem(const char* filename) {
    char itemNameToRemove[256];

    // Input for the item to remove
    std::cout << "Enter the name of the menu item to remove: ";
    std::cin.ignore(); // Clear input buffer
    std::cin.getline(itemNameToRemove, sizeof(itemNameToRemove));

    std::ifstream menuFile(filename, std::ios::in);
    if (!menuFile) {
        std::cout << "Error: Cannot open the menu file!" << std::endl;
        return;
    }

    std::ofstream tempFile("temp_menu.txt", std::ios::out);
    if (!tempFile) {
        std::cout << "Error: Cannot create a temporary file!" << std::endl;
        menuFile.close();
        return;
    }

    char line[256];
    bool itemFound = false;

    // Process the file line by line
    while (menuFile.getline(line, sizeof(line))) {
        char itemName[256];
        int i = 0;

        // Extract the item name from the line
        while (line[i] != '\0' && line[i] != ' ') {
            itemName[i] = line[i];
            i++;
        }
        itemName[i] = '\0';

        // Compare the item name with the one to remove
        if (strcmp(itemName, itemNameToRemove) == 0) {
            itemFound = true; // Mark item as found
        }
        else {
            tempFile << line << "\n"; // Copy other lines to the temp file
        }
    }

    menuFile.close();
    tempFile.close();

    if (itemFound) {
        // Replace the original file with the temp file
        remove(filename);
        rename("temp_menu.txt", filename);
        std::cout << "Menu item removed successfully!\n";
    }
    else {
        // Cleanup temp file and notify the user
        remove("temp_menu.txt");
        std::cout << "Menu item not found!\n";
    }
}

//look at all previous orders
void seePreviousOrders() {
    system("cls");
    std::ifstream orderFile("orders.txt", std::ios::in);
    if (!orderFile) {
        std::cout << "Error: cannot find the file for orders!" << std::endl;
        return;
    }

    char orderLine[256];
    std::cout << "Previous orders:\n";

    while (orderFile.getline(orderLine, 256)) {
        std::cout << orderLine << std::endl;
    }

    orderFile.close();
    std::cout << "\n";

}
void seePreviousOrdersSorted() {
    system("cls");
    std::ifstream orderFile("orders.txt", std::ios::in);
    if (!orderFile) {
        std::cout << "Error: cannot find the file for orders!" << std::endl;
        return;
    }

    char orderLine[256];
    std::string orders[100];  // 100 orders max
    int orderCount = 0;

    while (orderFile.getline(orderLine, 256) && orderCount < 100) {
        orders[orderCount] = orderLine;
        orderCount++;
    }

    orderFile.close();

    // Bubble Sort
    for (int i = 0; i < orderCount - 1; i++) {
        for (int j = 0; j < orderCount - i - 1; j++) {
            if (orders[j] > orders[j + 1]) {

                std::string temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }


    std::cout << "Previous orders (sorted):\n";
    for (int i = 0; i < orderCount; i++) {
        std::cout << orders[i] << std::endl;
    }

    std::cout << "\n";

}


//see all avalable items in the warehouse
void showWarehouseStock()
{
    system("cls");  // Clear the console
    std::fstream ofs;

    ofs.open("warehouse_products.txt", std::ios::in);
    if (!ofs.is_open())
    {
        std::cout << "Failed to open file for reading.\n";
        return;
    }

    char ch;
    while (ofs.get(ch))
    {
        std::cout << ch;
    }
    ofs.close();
    std::cout << "\n" << "\n";

}
//add a new product to the warehouse
void addProductToWarehouse() {
    system("cls");  // Clear the console
    std::cout << "Adding a new product to the warehouse." << std::endl;


    char productName[256];
    std::cout << "Enter the name of the product: ";
    std::cin.ignore();
    std::cin.getline(productName, 256);


    int quantity = 0;
    std::cout << "Enter the quantity (in grams): ";
    std::cin >> quantity;


    std::ofstream warehouseFile("warehouse_products.txt", std::ios::app);
    if (!warehouseFile) {
        std::cerr << "Error: cannot open the warehouse products file for writing!" << std::endl;
        return;
    }


    warehouseFile << productName << " " << quantity << std::endl;

    warehouseFile.close();

    std::cout << "The product was successfully added!" << std::endl;

}
//remove a product from the warehouse
void removeFromWarehouseStock() {
    system("cls");

    std::ifstream warehouseFile("warehouse_products.txt", std::ios::in);
    if (!warehouseFile.is_open()) {
        std::cout << "Error: cannot open warehouse_products.txt for reading!" << std::endl;
        return;
    }

    char products[100][50]; // Product names (up to 100 products, each name up to 50 characters)
    int quantities[100];    // Quantities of the products
    int productCount = 0;


    while (warehouseFile >> products[productCount] >> quantities[productCount]) {
        productCount++;
    }

    warehouseFile.close();

    char productName[50];
    int quantityToRemove;

    std::cin.ignore();
    std::cout << "Enter the product name to remove quantity from: ";
    std::cin.getline(productName, 50);

    int foundIndex = -1;
    for (int i = 0; i < productCount; ++i) {
        if (compareStrings(products[i], productName)) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        std::cout << "Error: Product not found in the warehouse!" << std::endl;
        return;
    }


    std::cout << "Enter the quantity to remove: ";
    std::cin >> quantityToRemove;

    if (quantityToRemove <= 0 || quantityToRemove > quantities[foundIndex]) {
        std::cout << "Error: Invalid quantity to remove!" << std::endl;
        return;
    }


    quantities[foundIndex] -= quantityToRemove;
    std::cout << "Removed " << quantityToRemove << " from " << products[foundIndex]
        << ". Remaining quantity: " << quantities[foundIndex] << std::endl;

    std::ofstream updatedWarehouseFile("warehouse_products.txt", std::ios::out);
    if (!updatedWarehouseFile.is_open()) {
        std::cout << "Error: cannot open warehouse_products.txt for writing!" << std::endl;
        return;
    }

    for (int i = 0; i < productCount; ++i) {
        if (quantities[i] > 0) {
            updatedWarehouseFile << products[i] << " " << quantities[i] << std::endl;
        }
    }

    updatedWarehouseFile.close();

    std::cout << "Warehouse stock updated successfully!" << std::endl;
    managerOptions();
}



double getPrice(const char* itemName) {
    std::ifstream priceFile("menu_prices.txt", std::ios::in);
    if (!priceFile) {
        std::cout << "Error: cannot open the price file!" << std::endl;
        return -1.0;
    }

    char menuItem[256];
    while (priceFile.getline(menuItem, 256)) {
        char itemNameInFile[256];
        int i = 0, j = 0;

        // Extract item name
        while (menuItem[i] != '\0' && menuItem[i] != ' ') {
            itemNameInFile[j++] = menuItem[i++];
        }
        itemNameInFile[j] = '\0';

        if (compareStrings(itemName, itemNameInFile)) {
            // Skip spaces to find the price
            while (menuItem[i] == ' ') {
                i++;
            }

            double price = 0.0;
            bool decimal = false;
            double factor = 0.1;

            while (menuItem[i] != '\0') {
                if (menuItem[i] == '.') {
                    decimal = true;
                }
                else if (menuItem[i] >= '0' && menuItem[i] <= '9') {
                    if (!decimal) {
                        price = price * 10 + (menuItem[i] - '0');
                    }
                    else {
                        price += (menuItem[i] - '0') * factor;
                        factor /= 10;
                    }
                }
                i++;
            }

            priceFile.close();
            return price;
        }
    }

    priceFile.close();
    return -1.0; // Return -1 if the item is not found
}
//show previous turnovers
void turnoverFromDate(const char* filename) {
    char fromDate[11];
    std::cout << "Enter the starting date (dd/mm/yyyy): ";
    std::cin.getline(fromDate, sizeof(fromDate));

    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cout << "Error: Cannot open the file!" << std::endl;
        return;
    }

    char line[256];

    std::cout << "Revenues from " << fromDate << " onward:\n";
    bool found = false;

    while (file.getline(line, sizeof(line))) {
        char currentDate[11];
        int i = 0;

        // Extract the date from the current line
        while (line[i] != ' ' && line[i] != '\0') {
            currentDate[i] = line[i];
            i++;
        }
        currentDate[i] = '\0';

        if (isDateGreaterOrEqual(currentDate, fromDate)) {
            found = true;
            std::cout << line << "\n";
        }
    }

    file.close();

    if (!found) {
        std::cout << "No revenues found from the given date onward.\n";
    }
}
//show the turnover for today
void turnoverToday(const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cout << "Error: Cannot open the file!" << std::endl;
        return;
    }

    char currentLine[256];
    char lastLine[256];

    // Read the file line by line and store the last read line
    while (file.getline(currentLine, sizeof(currentLine))) {
        for (int i = 0; i < 256; ++i) {
            lastLine[i] = currentLine[i];
            if (currentLine[i] == '\0') break;
        }
    }

    file.close();

    // Extract date and sum from the last line
    char date[11];
    double sum = 0.0;
    int i = 0, j = 0;

    // Extract date
    while (lastLine[i] != ' ' && lastLine[i] != '\0') {
        date[j++] = lastLine[i++];
    }
    date[j] = '\0';

    // Skip spaces
    while (lastLine[i] == ' ') {
        i++;
    }

    // Extract sum
    double factor = 1.0, fraction = 0.1;
    bool decimal = false;
    while (lastLine[i] != '\0') {
        if (lastLine[i] == '.') {
            decimal = true;
        }
        else if (lastLine[i] >= '0' && lastLine[i] <= '9') {
            if (!decimal) {
                sum = sum * 10 + (lastLine[i] - '0');
            }
            else {
                sum += (lastLine[i] - '0') * fraction;
                fraction *= 0.1;
            }
        }
        i++;
    }

    // Print the results
    std::cout << "Todays date: " << date << "\n";
    std::cout << "Turnover: " << sum << "\n";
}

// Function to update the warehouse after an order
void updateWarehouse(const char* item, int quantity) {
    std::ifstream ingredientsFile("menu_ingredients.txt");
    if (!ingredientsFile) {
        std::cout << "Error: cannot open the ingredients file.\n";
        return;
    }

    char line[256];
    bool foundItem = false;
    char ingredients[100][100];  // Array to store ingredient names
    int amounts[100];            // Array to store ingredient amounts
    int ingredientCount = 0;

    // Find the ingredients for the ordered item
    while (ingredientsFile.getline(line, sizeof(line))) {
        if (strcmp(line, item) == 0) {
            foundItem = true;
            continue;
        }

        if (foundItem && line[0] == '\0') {  // Empty line indicates end of ingredients
            break;
        }

        if (foundItem) {
            // Extract ingredient name and amount manually
            int i = 0;
            while (line[i] != ' ' && line[i] != '\0') {
                ingredients[ingredientCount][i] = line[i];
                i++;
            }
            ingredients[ingredientCount][i] = '\0';

            // Skip the space and extract the amount
            i++;
            char amountStr[20];
            int j = 0;
            while (line[i] != '\0') {
                amountStr[j++] = line[i++];
            }
            amountStr[j] = '\0';

            amounts[ingredientCount] = myStoi(amountStr) * quantity;
            ingredientCount++;
        }
    }

    ingredientsFile.close();

    if (!foundItem) {
        std::cout << "Error: item not found in ingredients file.\n";
        return;
    }

    // Update the warehouse
    std::ifstream warehouseFile("warehouse_products.txt");
    if (!warehouseFile) {
        std::cout << "Error: cannot open the warehouse file.\n";
        return;
    }

    char warehouseLines[1000][256];  // Array to store warehouse lines
    int warehouseCount = 0;

    while (warehouseFile.getline(warehouseLines[warehouseCount], sizeof(warehouseLines[warehouseCount]))) {
        warehouseCount++;
    }

    warehouseFile.close();

    // Reduce the quantities in the warehouse
    for (int i = 0; i < ingredientCount; i++) {
        for (int j = 0; j < warehouseCount; j++) {
            char product[100];
            int k = 0;
            while (warehouseLines[j][k] != ' ' && warehouseLines[j][k] != '\0') {
                product[k] = warehouseLines[j][k];
                k++;
            }
            product[k] = '\0';

            if (strcmp(product, ingredients[i]) == 0) {
                // Extract the current stock
                k++;
                char stockStr[20];
                int l = 0;
                while (warehouseLines[j][k] != '\0') {
                    stockStr[l++] = warehouseLines[j][k++];
                }
                stockStr[l] = '\0';

                int stock = myStoi(stockStr);
                stock -= amounts[i];
                if (stock < 0) stock = 0;

                // Convert the new stock to a string
                char newStockStr[20];
                intToString(stock, newStockStr);

                // Update the warehouse line
                myStrcpy(warehouseLines[j], product);
                myStrCat(warehouseLines[j], " ");
                myStrCat(warehouseLines[j], newStockStr);
                break;
            }
        }
    }

    // Write the updated warehouse back to the file
    std::ofstream updatedWarehouseFile("warehouse_products.txt");
    if (!updatedWarehouseFile) {
        std::cout << "Error: cannot update the warehouse file.\n";
        return;
    }

    for (int i = 0; i < warehouseCount; i++) {
        updatedWarehouseFile << warehouseLines[i] << "\n";
    }

    updatedWarehouseFile.close();
}
