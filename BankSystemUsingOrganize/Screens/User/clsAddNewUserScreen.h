#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "Enter First Name: ";
		User.FirstName = clsInputValidate::ReadString();
		cout << "Enter Last Name: ";
		User.LastName = clsInputValidate::ReadString();
		cout << "Enter Email: ";
		User.Email = clsInputValidate::ReadString();
		cout << "Enter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		cout << "Enter Password: ";
		User.Password = clsInputValidate::ReadString();
		cout << "Enter Permissions: \n";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'N';

		cout << "Do you give full access(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return -1;
		}
		cout << "\nDo you want to give access to: \n";

		cout << "\nShow Client List(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pLoginRegisterList;
		}

		cout << "\nCurrency Exchange(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pCurrencyExchange;
		}

		return Permissions;
	}

	static string _ReadUsername()
	{
		string Username = "";

		cout << "Enter Username: ";
		Username = clsInputValidate::ReadString();

		return Username;
	}

public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");

		string Username = "";

		cout << "Enter Username: ";
		Username = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			cout << "Username is already Used, Choose another one: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(Username);

		_ReadUserInfo(User);

		clsUser::enSaveResults SaveResults;

		SaveResults = User.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svSucceeded:
			cout << "User Added Successfully :-)\n";
			_PrintUser(User);
			break;

		case clsUser::enSaveResults::svFailedEmptyObject:
		{
			cout << "\nError: Username was not saved because it's Empty\n";
			break;
		}
		case clsUser::enSaveResults::svFailedUsername:
			cout << "\nError: Username is already Used.\n";
			break;
		}
	}

};

