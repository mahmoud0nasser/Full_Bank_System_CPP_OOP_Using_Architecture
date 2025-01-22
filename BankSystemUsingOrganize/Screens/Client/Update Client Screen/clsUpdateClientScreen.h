#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "Enter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "Enter Last Name : ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "Enter Email     : ";
		Client.Email = clsInputValidate::ReadString();
		cout << "Enter Phone     : ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "Enter PinCode   : ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "Enter Balance   : ";
		Client.AccountBalance = clsInputValidate::ReadFltNumber();
	}

public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
			return;

		_DrawScreenHeader("Update Client Screen");

		string AccountNumber = "";

		cout << "Please Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is NOT found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'N';

		cout << "\nAre you sure you want to delete this Client(Y/N)? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {
			cout << "\n\nUpdate Client Info: ";
			cout << "\n_____________________________\n\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;
			SaveResult = Client.Save();

			switch (SaveResult)
			{
				case  clsBankClient::enSaveResults::svSucceeded:
				{
					cout << "\nAccount Updated Successfully :-)\n";
					_PrintClient(Client);
					break;
				}
				case clsBankClient::enSaveResults::svFaildEmptyObject:
				{
					cout << "\nError account was not saved because it's Empty";
					break;
				}
			}
		}
	}

};

