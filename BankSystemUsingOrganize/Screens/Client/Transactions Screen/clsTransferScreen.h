#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card: \n";
		cout << "_________________________________________\n";
		cout << "\nFull Name  : " << Client.FullName() << endl;
		cout << "Acc. Number: " << Client.AccountNumber() << endl;
		cout << "Balance    : " << Client.AccountBalance << endl;
		cout << "_________________________________________\n";
	}

	static string _ReadAccountNumber(string Type)
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number to Transfer " << Type << "? ";
		AccountNumber = clsInputValidate::ReadString();

		return AccountNumber;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");

		string AccountNumberSender = _ReadAccountNumber("From");

		while (!clsBankClient::IsClientExist(AccountNumberSender))
		{
			cout << "\nClient with [" << AccountNumberSender << "] does NOT Exist.\n";
			AccountNumberSender = _ReadAccountNumber("From");
		}

		clsBankClient ClientSender = clsBankClient::Find(AccountNumberSender);

		_PrintClient(ClientSender);

		string AccountNumberRecienver = _ReadAccountNumber("To");

		while (!clsBankClient::IsClientExist(AccountNumberRecienver))
		{
			cout << "\nClient with [" << AccountNumberRecienver << "] does NOT Exist.\n";
			AccountNumberRecienver = _ReadAccountNumber("To");
		}

		clsBankClient ClientReciever = clsBankClient::Find(AccountNumberRecienver);

		_PrintClient(ClientReciever);

		double TransferAmount;

		cout << "\nEnter Transfer Amount? ";
		cin >> TransferAmount;

		while (TransferAmount > ClientSender.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter Another Amount? ";
			cin >> TransferAmount;
		}

		char Answer = 'N';

		cout << "\nAre you sure you want to perform this Transaction? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (ClientSender.Withdraw(TransferAmount))
			{
				ClientReciever.Deposit(TransferAmount);
				ClientSender.TransferLog(ClientReciever, TransferAmount);
				cout << "\nTransfer Done Successfully.\n";
				_PrintClient(ClientSender);
				_PrintClient(ClientReciever);
			}
		}
	}

};

