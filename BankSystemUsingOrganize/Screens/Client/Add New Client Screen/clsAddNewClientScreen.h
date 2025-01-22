#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
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
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
			return;

		_DrawScreenHeader("\t  Add New Client Screen");

		string AccountNumber = "";

		cout << "Please Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is already Used, Choose another one: \n";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Updated Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError: Account was not saved because it's Empty\n";
			break;
		}
		case clsBankClient::enSaveResults::svFailedAccountNumberExists:
			cout << "\nError: Account Number is already Used.\n";
			break;
		}
	}
};