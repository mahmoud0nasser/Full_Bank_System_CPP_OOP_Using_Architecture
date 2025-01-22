#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card: \n";
		cout << "_________________________________________\n\n";
		cout << "Country : " << Currency.GetCountry() << endl;
		cout << "Code    : " << Currency.GetCurrencyCode() << endl;
		cout << "Name    : " << Currency.GetCurrencyName() << endl;
		cout << "Rate(1$): " << Currency.GetRate() << endl;
		cout << "_________________________________________\n";
	}

	static float _ReadRate()
	{
		float NewRate = 0;
		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadFltNumber();

		return NewRate;
	}

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\t  Update Currency Screen");

		string CurrencyCode;

		cout << "Enter Currency Code? ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is NOT found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		_PrintCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this currency(Y/N)? ";

		char Answer = 'N';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";

			float NewRate = 0;

			/*cout << "\nEnter New Rate: ";
			NewRate = clsInputValidate::ReadFltNumber();

			Currency.SetRate(NewRate);*/

			Currency.SetRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully -:)\n";

			_PrintCurrency(Currency);
		}
	}

};

