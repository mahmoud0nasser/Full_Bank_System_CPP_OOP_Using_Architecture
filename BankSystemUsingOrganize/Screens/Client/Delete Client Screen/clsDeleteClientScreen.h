#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card: \n";
		cout << "_________________________________________\n";
		cout << "First Name : " << Client.FirstName << endl;
		cout << "Last Name  : " << Client.LastName << endl;
		cout << "Full Name  : " << Client.FullName() << endl;
		cout << "Email      : " << Client.Email << endl;
		cout << "Phone      : " << Client.Phone << endl;
		cout << "Acc. Number: " << Client.AccountNumber() << endl;
		cout << "Password   : " << Client.PinCode << endl;
		cout << "Balance    : " << Client.AccountBalance << endl;
		cout << "_________________________________________\n";
	}

public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
			return;

		_DrawScreenHeader("Delete Client Screen");

		string AccountNumber = "";

		cout << "Please Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is NOT found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientInfo = clsBankClient::Find(AccountNumber);
		_PrintClient(ClientInfo);

		char Answer = 'N';

		cout << "\nAre you sure you want to delete this Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (ClientInfo.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";

				_PrintClient(ClientInfo);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}
};

