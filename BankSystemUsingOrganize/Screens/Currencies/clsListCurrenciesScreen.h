#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsListCurrenciesScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
		cout << "| " << setw(8) << left << Currency.GetCurrencyCode();
		cout << "| " << setw(40) << left << Currency.GetCurrencyName();
		cout << "| " << setw(15) << left << Currency.GetRate();
	}

public:
	static void ShowCurrenciesList()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Title = "\t  Currencies List Screen";
		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(15) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\t\t\t\tNo Currencies Available In the System!";
		}
		else {
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyRecordLine(Currency);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;
	}

};

