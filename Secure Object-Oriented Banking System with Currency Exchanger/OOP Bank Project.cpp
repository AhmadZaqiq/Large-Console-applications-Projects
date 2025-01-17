//Ahmad JR
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsCurrency.h"
#include "clsLoginScreen.h"

using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}

	system("pause>0");
}
