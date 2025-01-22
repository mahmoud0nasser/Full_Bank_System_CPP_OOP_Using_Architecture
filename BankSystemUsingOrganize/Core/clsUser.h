#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>
#include "clsUtil.h"

using namespace std;

const string _UsersFileName = "Users.txt";

class clsUser : public clsPerson
{
private:
	enum enMode {
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		string Password = clsUtil::DecryptText(vUserData[5]);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], Password, stoi(vUserData[6]));
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];

		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);

		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string Line = "";

		Line += User.FirstName + Separator;
		Line += User.LastName + Separator;
		Line += User.Email + Separator;
		Line += User.Phone + Separator;
		Line += User._Username + Separator;

		User.Password = clsUtil::EncryptText(User.Password);

		Line += User._Password + Separator;
		Line += to_string(User._Permissions);

		return Line;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open(_UsersFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);

				if (Line != "")
				{
					vUsers.push_back(User);
				}
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open(_UsersFileName, ios::out);

		if (MyFile.is_open())
		{
			string Line = "";

			for (clsUser& User : vUsers)
			{
				if (User._MarkedForDelete == false) {
					Line = _ConvertUserObjectToLine(User);

					if (Line != "")
						MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == _Username)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open(_UsersFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			if (stDataLine != "")
				MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static string _ConvertCurrentUserToString(clsUser User, string Separator = "#//#")
	{
		string DataLine = "";

		time_t t = time(0);
		tm* now = localtime(&t);

		string Hour = to_string(now->tm_hour);
		string Minute = to_string(now->tm_min);
		string Seconds = to_string(now->tm_sec);

		string TimeAsString = Hour + ":" + Minute + ":" + Seconds;

		DataLine += clsDate::DateToString(clsDate()) + " - ";
		DataLine += TimeAsString + Separator;
		DataLine += User.Username + Separator;

		User.Password = clsUtil::EncryptText(User.Password);

		DataLine += User.Password + Separator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	string _PrepareLogInRecord(string Separator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += Username + Separator;

		Password = clsUtil::EncryptText(Password, 2);

		LoginRecord += Password + Separator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		pLoginRegisterList = 128, pCurrencyExchange = 256
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, 
		string Username, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;

		// _Password = clsUtil::DecryptText(Password, 2);

		_Password = Password;
		_Permissions = Permissions;
	}

	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	void SetUsername(string Username)
	{
		_Username = Username;
	}

	string GetUsername()
	{
		return _Username;
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string Username)
	{
		fstream MyFile;
		MyFile.open(_UsersFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);

				if (User.Username == Username)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;
		MyFile.open(_UsersFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);

				// User.Password = clsUtil::DecryptText(Password, 2);

				if (User.Username == Username && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string Username)
	{
		clsUser User = clsUser::Find(Username);

		return (!User.isEmpty());
	}

	enum enSaveResults {
		svFailedEmptyObject = 0, svSucceeded = 1, svFailedUsername = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
				if (isEmpty()) {
					return enSaveResults::svFailedEmptyObject;
				}

			case enMode::UpdateMode:
				_Update();
				return enSaveResults::svSucceeded;

			case enMode::AddNewMode:
				if (IsUserExist(_Username))
				{
					return enSaveResults::svFailedUsername;
				}
				else {
					_AddNew();

					_Mode = enMode::UpdateMode;

					return enSaveResults::svSucceeded;
				}

		}
	}

	static clsUser GetAddNewUserObject(string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers) {
			if (User.Username == _Username)
			{
				User._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((this->Permissions & Permission) == Permission)
			return true;
		else
			return false;
	}

	static void AddToLoginRegisterFile(clsUser User)
	{
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string Line = "";
			Line = _ConvertCurrentUserToString(User);

			if (Line != "")
				MyFile << Line << endl;

			MyFile.close();
		}
	}

	void RegisterLogIn()
	{
		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {
			MyFile << stDataLine << endl;
			
			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}
};

