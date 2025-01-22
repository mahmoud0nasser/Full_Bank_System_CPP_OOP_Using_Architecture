#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeMenuOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eMainMenu = 5
    };

    static int _ReadCurrencyMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do[1 to 5]? ";
        int _Option = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between [1 to 5]? ");

        return _Option;
    }

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Currency Exchange Menu...\n";
        system("pause>0");
        ShowCurrencyExchangeMenu();
    }

    static void _ShowAllCurrenciesScreen()
    {
        // cout << "\nClient List Screen Will be here...\n";
        clsListCurrenciesScreen::ShowCurrenciesList();
    }

    static void _ShowFindCurrencyScreen()
    {
        // cout << "\nFind Currency Screen Will be here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        // cout << "\nUpdate Rate Screen Will be here...\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        // cout << "\nCurrency Calculator Screen Will be here...\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerfromCurrencyExchangeMenuOption(enCurrencyExchangeMenuOptions CurrencyExchangeMenuOptions)
    {
        switch (CurrencyExchangeMenuOptions)
        {
        case enCurrencyExchangeMenuOptions::eListCurrencies:
        {
            system("cls");
            _ShowAllCurrenciesScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case enCurrencyExchangeMenuOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeMenuOptions::eMainMenu:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
	static void ShowCurrencyExchangeMenu()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            return;

        system("cls");
        _DrawScreenHeader("\tCurrency Exchange Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyExchangeMenuOption((enCurrencyExchangeMenuOptions)_ReadCurrencyMenuOption());
	}

};

