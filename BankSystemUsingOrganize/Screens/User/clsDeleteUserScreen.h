#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card: \n";
		cout << "_________________________________________\n";
		cout << "First Name : " << User.FirstName << endl;
		cout << "Last Name  : " << User.LastName << endl;
		cout << "Full Name  : " << User.FullName() << endl;
		cout << "Email      : " << User.Email << endl;
		cout << "Phone      : " << User.Phone << endl;
		cout << "Password   : " << User.Password << endl;
		cout << "Permissions: " << User.Permissions << endl;
		cout << "_________________________________________\n";
	}

public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");

		string Username = "";

		cout << "\nEnter Username: ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not found, choose another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		_PrintUser(User);

		cout << "\nAre you sure you want to delete this User(Y/N)? ";

		char Answer = 'N';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (User.Delete()) {
				cout << "\nUser Deleted Successfully -)\n";
				_PrintUser(User);
			}
			else {
				cout << "\nError: User was NOT Deleted.\n";
			}
		}
	}

};

