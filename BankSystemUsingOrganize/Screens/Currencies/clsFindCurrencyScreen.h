#pragma once

#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
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

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.isEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country? ";

		short Answer = 1;
		cin >> Answer;

		if (Answer == 1)
		{
			string CurrencyCode;
			cout << "\nPlease Enter CurrencyCode: ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else {
			string Country;
			cout << "\nPlease Enter Country: ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}

};









//class clsFindCurrencyScreen : protected clsScreen
//{
//private:
//
//	static int _ReadFindCurrencyOption()
//	{
//		cout << "\nFind By: [1] Code or [2] Country? ";
//		int _Option = clsInputValidate::ReadShortNumberBetween(1, 2, "Find By: [1] Code or [2] Country? ");
//
//		return _Option;
//	}
//
//	enum enChoice;
//	static string _PerformUserChoice(enChoice Choice)
//	{
//		string UserInput = "";
//
//		switch (Choice)
//		{
//		case enChoice::eCode:
//			cout << "\nEnter Currency Code: ";
//			UserInput = clsInputValidate::ReadString();
//			return UserInput;
//
//		case enChoice::eCountry:
//			cout << "\nEnter Country: ";
//			UserInput = clsInputValidate::ReadString();
//			return UserInput;
//
//		}
//	}
//
//	static void _PrintCurrency(clsCurrency Currency)
//	{
//		cout << "\nCurrency Card: \n";
//		cout << "_________________________________________\n\n";
//		cout << "Country : " << Currency.GetCountry() << endl;
//		cout << "Code    : " << Currency.GetCurrencyCode() << endl;
//		cout << "Name    : " << Currency.GetCurrencyName() << endl;
//		cout << "Rate(1$): " << Currency.GetRate() << endl;
//		cout << "_________________________________________\n";
//	}
//
//public:
//	enum enChoice {
//		eCode = 1,
//		eCountry = 2
//	};
//
//	static void ShowFindCurrencyScreen()
//	{
//		string UserInput = "";
//
//		_DrawScreenHeader("\t  Find Currency Screen");
//
//		enChoice Choice = (enChoice)_ReadFindCurrencyOption();
//		UserInput = _PerformUserChoice(Choice);
//
//		clsCurrency Currency;
//
//		switch (Choice)
//		{
//			case enChoice::eCode:
//				while (!clsCurrency::isCurrencyExist(UserInput))
//				{
//					cout << "\nCurrency is NOT found, choose another one: ";
//					UserInput = clsInputValidate::ReadString();
//				}
//
//				Currency = clsCurrency::FindByCode(UserInput);
//				break;
//
//			case enChoice::eCountry:
//				while (!clsCurrency::isCountryExist(UserInput))
//				{
//					cout << "\nCurrency is NOT found, choose another one: ";
//					UserInput = clsInputValidate::ReadString();
//				}
//
//				Currency = clsCurrency::FindByCountry(UserInput);
//				break;
//		}
//		
//		cout << "\nCurrency Found -:)\n";
//		_PrintCurrency(Currency);
//	}
//
//};

