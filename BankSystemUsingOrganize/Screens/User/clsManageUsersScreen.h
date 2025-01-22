#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eShowMainMenue = 6
    };

    static int _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do[1 to 6]? ";
        int _Option = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between [1 to 6]? ");

        return _Option;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Manage Users Menu...\n";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen()
    {
        // cout << "\nUsers List Screen Will be here...\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will be here...\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will be here...\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will be here...\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        // cout << "\nFind User Screen Will be here...\n";
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerfromManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOptions)
    {
        switch (ManageUsersMenuOptions)
        {
            case enManageUsersMenuOptions::eListUsers:
            {
                system("cls");
                _ShowListUsersScreen();
                _GoBackToManageUsersMenue();
                break;
            }
            case enManageUsersMenuOptions::eAddNewUser:
                system("cls");
                _ShowAddNewUserScreen();
                _GoBackToManageUsersMenue();
                break;

            case enManageUsersMenuOptions::eDeleteUser:
                system("cls");
                _ShowDeleteUserScreen();
                _GoBackToManageUsersMenue();
                break;

            case enManageUsersMenuOptions::eUpdateUser:
                system("cls");
                _ShowUpdateUserScreen();
                _GoBackToManageUsersMenue();
                break;

            case enManageUsersMenuOptions::eFindUser:
                system("cls");
                _ShowFindUserScreen();
                _GoBackToManageUsersMenue();
                break;

            case enManageUsersMenuOptions::eShowMainMenue:
            {
                // // do nothing here the main screen will handle it :-) ;
            }
        }
    }


public:
    static void ShowManageUsersMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
            return;

        system("cls");
        _DrawScreenHeader("\t\tManage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tManage Users Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    }

};

