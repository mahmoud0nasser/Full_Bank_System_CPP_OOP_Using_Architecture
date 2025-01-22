#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsTotalBalancesScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferRegisterScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTrancsactionsMenuOptions {
        eDeposit = 1, eWithdraw = 2, 
        eTotalBalances = 3, eTransfer = 4, 
        eTransferLog = 5, eMainMenu = 6
    };

    static int _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do[1 to 6]? ";
        int _Option = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between [1 to 6]? ");

        return _Option;
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\nPress any key to go back to Transactions Menu...\n";
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _ShowDepositScreen()
    {
        // cout << "\nDeposit Screen Will be here...\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        // cout << "\nWithdraw Screen Will be here...\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        // cout << "\nTotal Balances Screen Will be here...\n";
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen()
    {
        // cout << "\nTransfer Screen Will be here...\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferRegisterScreen::ShowTransferRegisterScreen();
    }

    static void _ShowMainMenuScreen()
    {
        // do nothing here the main screen will handle it :-) ;
        // clsMainScreen::ShowMainMenu();
    }

    static void _PerfromTransactionsMenuOption(enTrancsactionsMenuOptions TransactionsMenuOptions)
    {
        switch (TransactionsMenuOptions)
        {
            case enTrancsactionsMenuOptions::eDeposit:
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenue();
                break;

            case enTrancsactionsMenuOptions::eWithdraw:
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenue();
                break;

            case enTrancsactionsMenuOptions::eTotalBalances:
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenue();
                break;

            case enTrancsactionsMenuOptions::eTransfer:
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenue();
                break;

            case enTrancsactionsMenuOptions::eTransferLog:
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenue();
                break;

            case enTrancsactionsMenuOptions::eMainMenu:
                _ShowMainMenuScreen();
        }
    }

public:
	static void ShowTransactionsMenu()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
            return;

        system("cls");

		string Title = "\t  Transactions Screen";

		_DrawScreenHeader(Title);

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionsMenuOption((enTrancsactionsMenuOptions)_ReadTransactionsMenuOption());
	}

};

