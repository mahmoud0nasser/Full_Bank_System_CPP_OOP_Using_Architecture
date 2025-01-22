#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsString.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static float _ReadAmount()
    {
        float Amount = 0;

        cout << "Enter Amount To Exchange: ";
        Amount = clsInputValidate::ReadFltNumber();

        return Amount;
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card: ")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.GetCountry();
        cout << "\nCode          : " << Currency.GetCurrencyCode();
        cout << "\nName          : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) =    : " << Currency.GetRate();
        cout << "\n_____________________________\n\n";
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string CurrencyCode;

        cout << Message;

        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::isCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        return Currency;
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        if (CurrencyFrom.GetCurrencyCode() == "USD")
        {
            _PrintCurrencyCard(CurrencyFrom, "Convert From: ");
            float AmountInCurrrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

            cout << Amount << " " << CurrencyFrom.GetCurrencyCode()
                << " = " << AmountInCurrrencyTo << " " << CurrencyTo.GetCurrencyCode();

            return;
        }

        _PrintCurrencyCard(CurrencyFrom, "Convert From: ");

        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << Amount << " " << CurrencyFrom.GetCurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (CurrencyTo.GetCurrencyCode() == "USD")
        {
            return;
        }

        _PrintCurrencyCard(CurrencyTo, "Converting from USD to:");

        float AmountInCurrrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

        cout << Amount << " " << CurrencyFrom.GetCurrencyCode()
            << " = " << AmountInCurrrencyTo << " " << CurrencyTo.GetCurrencyCode();
    }


public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'Y';

        while (toupper(Continue) == 'Y')
        {
            system("cls");

            _DrawScreenHeader("\tUpdate Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nEnter Currency Code From: ");
            clsCurrency CurrencyTo = _GetCurrency("\nEnter Currency Code To: ");
            
            cout << endl;

            float Amount = _ReadAmount();

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation(Y/N)? ";
            cin >> Continue;
        }
    }
};



//class clsCurrencyCalculatorScreen : protected clsScreen
//{
//private:
//	static void _PrintCurrency(clsCurrency Currency, string Message = "\nConvert From: \n")
//	{
//		cout << Message;
//		cout << "_________________________________________\n\n";
//		cout << "Country : " << Currency.GetCountry() << endl;
//		cout << "Code    : " << Currency.GetCurrencyCode() << endl;
//		cout << "Name    : " << Currency.GetCurrencyName() << endl;
//		cout << "Rate(1$): " << Currency.GetRate() << endl;
//		cout << "_________________________________________\n";
//	}
//
//public:
//	static void ShowCurrencyCalculatorScreen()
//	{
//		char Answer = 'N';
//		do {
//			system("cls");
//			_DrawScreenHeader("\t  Update Currency Screen");
//
//			string SourceCurrencyCode;
//
//			cout << "\nEnter Source Currency Code: ";
//			SourceCurrencyCode = clsInputValidate::ReadString();
//
//			while (!clsCurrency::isCurrencyExist(SourceCurrencyCode))
//			{
//				cout << "\nCurrency is NOT found, choose another one: ";
//				SourceCurrencyCode = clsInputValidate::ReadString();
//			}
//
//			clsCurrency SourceCurrency = clsCurrency::FindByCode(SourceCurrencyCode);
//
//			string DestinationCurrencyCode;
//
//			cout << "\nEnter Destination Currency Code: ";
//			DestinationCurrencyCode = clsInputValidate::ReadString();
//
//			while (!clsCurrency::isCurrencyExist(DestinationCurrencyCode))
//			{
//				cout << "\nCurrency is NOT found, choose another one: ";
//				DestinationCurrencyCode = clsInputValidate::ReadString();
//			}
//
//			clsCurrency DestinationCurrency = clsCurrency::FindByCode(DestinationCurrencyCode);
//
//			float Amount = 0, AmountAfterExchange = 0;
//
//			cout << "\nEnter Amount to Exchange? ";
//			Amount = clsInputValidate::ReadFltNumber();
//
//			clsCurrency USDCurrency = clsCurrency::FindByCode("USD");
//
//			if (clsString::UpperAllString(DestinationCurrencyCode) == "USD")
//			{
//				AmountAfterExchange = Amount / SourceCurrency.GetRate();
//
//				_PrintCurrency(SourceCurrency);
//				cout << "\n\n" << Amount << " " << clsString::UpperAllString(SourceCurrencyCode) << " = " << AmountAfterExchange << " " << clsString::UpperAllString(DestinationCurrencyCode) << endl;
//			}
//			else {
//				AmountAfterExchange = Amount / SourceCurrency.GetRate();
//
//				_PrintCurrency(SourceCurrency);
//				cout << "\n\n" << Amount << " " << clsString::UpperAllString(SourceCurrencyCode) << " = " << AmountAfterExchange << " " << "USD" << endl;
//
//				AmountAfterExchange *= DestinationCurrency.GetRate();
//
//				_PrintCurrency(DestinationCurrency, "\nConverting From USD To: \n");
//				cout << "\n\n" << Amount << " " << clsString::UpperAllString(SourceCurrencyCode) << " = " << AmountAfterExchange << " " << clsString::UpperAllString(DestinationCurrencyCode) << endl;
//			}
//
//			cout << "\nDo you want to perform another Calculation? ";
//			cin >> Answer;
//
//		} while (toupper(Answer) == 'Y');
//	}
// };

