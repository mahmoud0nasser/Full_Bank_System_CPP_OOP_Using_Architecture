#pragma once

#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsUser.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";


        cout << "\t\t\t\t\tUser: " << CurrentUser.Username << endl;
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";

        /*clsDate now = clsDate::GetSystemDate();
        cout << "\t\t\t\t\tDate: " << now.Day << "/" << now.Month << "/" << now.Year << "\n\n";*/
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }
    }
};

//class clsScreen
//{
//protected:
//	static void _DrawScreenHeader(string Title)
//	{
//		cout << setw(37) << left << "" << "\t______________________________________________________\n\n";
//		cout << setw(37) << left << "" << "\t\t\t" << Title << endl;
//		cout << setw(37) << left << "" << "\t______________________________________________________\n\n";
//	}
//};

