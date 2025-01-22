#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
	static void ShowFindUserScreen()
	{
		string Username = "";

		_DrawScreenHeader("\t  Find User Screen");

		cout << "\nEnter Username: ";
		Username = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not found, choose another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);

		_PrintUser(User);
	}

};

