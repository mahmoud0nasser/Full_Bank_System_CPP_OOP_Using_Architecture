#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "Please Enter Account Number? ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does NOT Exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;

		cout << "Enter Withdraw Amount? ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'N';

		cout << "\nAre you sure you want to perform this Transaction? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (Client.Withdraw(Amount)) {
				cout << "\nAmount Withdrawed Successfully.\n";
				cout << "New Balance is: " << Client.AccountBalance << endl;
			}
			else {
				cout << "\nCann't withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to Withdraw is: " << Amount << endl;
				cout << "Your balance is: " << Client.AccountBalance << endl;
			}
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}
	}

};

