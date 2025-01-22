#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
			return;

		_DrawScreenHeader("Find Client Screen");

		string AccountNumber = "";

		cout << "Please Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is NOT found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientInfo = clsBankClient::Find(AccountNumber);
		if (!ClientInfo.IsEmpty()) {
			cout << "\nClient Found :-)\n";
		}
		else {
			cout << "\nClient was NOT Found :-(\n";
		}

		_PrintClient(ClientInfo);
	}

};

