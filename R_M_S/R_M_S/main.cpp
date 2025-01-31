/*
Solution to course project # 1
Introduction to programming course
Faculty of Mathematics and Informatics of Sofia University
Winter semester 2023/2024

@author Valentin Valkov
@idNumebr 9MI0600516
@compiler VS

<file with functions>
*/


#include <iostream>
#include <fstream>
#include "roleFunctions.h"

int main()
{
	int role = checkRole();
	if (role == 1)
	{
		waiterOptions();
	}
	else if (role == 2)
	{
		managerOptions();
	}
}