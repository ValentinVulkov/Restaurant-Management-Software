
#pragma once
#include <iostream>

const int MAX_SIZE = 1024;

void showAllActionsServer();

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
    case 2: showMenu();

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
    std::ifstream file("/mnt/data/updated_restaurant_menu.txt");  // Open the file
    if (!file) 
    {
        std::cerr << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        std::cout << line << "\n";  // Print each menu item
    }

    file.close();  // Close the file
}