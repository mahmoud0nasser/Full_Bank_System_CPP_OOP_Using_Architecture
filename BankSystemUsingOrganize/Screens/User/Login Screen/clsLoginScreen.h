#pragma once

#include <iostream>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	// static int _Trials;

	static bool _Login()
	{
		bool LoginFailed = false;
		short FailedLoginCount = 0;

		string Username, Password;

		do {
			if (LoginFailed)
			{
				FailedLoginCount++;

				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << (3 - FailedLoginCount) << " Trial(s) to login.\n\n";
			}

			if (FailedLoginCount == 3)
			{
				cout << "\nYou are locked after " << FailedLoginCount << " failed trials\n\n";
				return false;
			}

			cout << "Enter Username: ";
			// cin >> Username;
			Username = clsInputValidate::ReadString();

			cout << "Enter Password: ";
			// cin >> Password;
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.isEmpty();

		} while (LoginFailed);

		// clsUser::AddToLoginRegisterFile(CurrentUser);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenu();

		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");

		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}

};

