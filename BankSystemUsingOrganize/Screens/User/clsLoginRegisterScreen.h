#pragma once

#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;

const string LoginRegisterFileName = "LoginRegister.txt";

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintLoginReisterRecordLine(vector<string> vLoginRegister)
    {
        cout << setw(8) << left << "" << "| " << setw(40) << left << vLoginRegister[0];
        cout << "| " << setw(20) << left << vLoginRegister[1];
        cout << "| " << setw(15) << left << vLoginRegister[2];
        cout << "| " << setw(12) << left << vLoginRegister[3];
    }

    static vector<string> _LoadLoginRegisterDataFromFile()
    {
        vector<string> vLoginRegisterList;

        fstream MyFile;
        MyFile.open(LoginRegisterFileName, ios::in);

        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    vLoginRegisterList.push_back(Line);
                }
            }

            MyFile.close();
        }

        return vLoginRegisterList;
    }

public:
    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisterList))
        {
            return; // this will take the function and it will not continue
        }

        vector <string> vLoginRegisters = _LoadLoginRegisterDataFromFile();
        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisters.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(40) << "Date/Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisters.size() == 0)
            cout << "\t\t\t\tNo Login Registers Available In the System!";
        else

            for (string& LoginRegister : vLoginRegisters)
            {
                vector<string> vLoginList = clsString::Split(LoginRegister, "#//#");

                _PrintLoginReisterRecordLine(vLoginList);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }

};
