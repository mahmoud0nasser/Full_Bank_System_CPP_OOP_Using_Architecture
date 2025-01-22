#pragma once

#include <iostream>
#include "clsPerson.h"
#include <vector>
#include "clsString.h"
#include <string>
#include <fstream>
#include "Global.h"

using namespace std;

const string _ClientsFileName = "Clients.txt";
const string _TransferFileName = "TransferLog.txt";

class clsBankClient : public clsPerson
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClientDate;
		vClientDate = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2],
			vClientDate[3], vClientDate[4], vClientDate[5], stof(vClientDate[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string Line = "";

		Line += Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client._AccountNumber + Separator;
		Line += Client.PinCode + Separator;
		Line += to_string(Client.AccountBalance);

		return Line;
	}

	struct stTransferRegisterRecord;
	static stTransferRegisterRecord _ConvertTransferRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		vector<string> vTransferRegisterDataLine = clsString::Split(Line, Separator);
		stTransferRegisterRecord TransferRegisterRecord;

		TransferRegisterRecord.DateTime = vTransferRegisterDataLine[0];
		TransferRegisterRecord.S_AccountNumber = vTransferRegisterDataLine[1];
		TransferRegisterRecord.D_AccountNumber = vTransferRegisterDataLine[2];
		TransferRegisterRecord.Amount = stod(vTransferRegisterDataLine[3]);
		TransferRegisterRecord.S_AcountBalance = stod(vTransferRegisterDataLine[4]);
		TransferRegisterRecord.D_AccountBalance = stod(vTransferRegisterDataLine[5]);
		TransferRegisterRecord.Username = vTransferRegisterDataLine[6];

		return TransferRegisterRecord;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open(_ClientsFileName, ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}
		return vClients;
	}

	static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open(_ClientsFileName, ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C._MarkForDelete == false) {
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open(_ClientsFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			if (stDataLine != "")
				MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	string _PrepareTransferRecord(clsBankClient DestinationClient, double Amount, string Separator = "#//#")
	{
		string TransferRecord = "";

		TransferRecord += clsDate::GetSystemDateTimeString() + Separator;
		TransferRecord += AccountNumber() + Separator;
		TransferRecord += DestinationClient.AccountNumber() + Separator;
		TransferRecord += to_string(Amount) + Separator;
		TransferRecord += to_string(AccountBalance) + Separator;
		TransferRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TransferRecord += CurrentUser.Username;

		return TransferRecord;
	}

public:

	struct stTransferRegisterRecord {
		string DateTime;
		string S_AccountNumber;
		string D_AccountNumber;
		double Amount;
		double S_AcountBalance;
		double D_AccountBalance;
		string Username;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	/*
	// No UI Related code aside object.
	void Print()
	{
		cout << "\nClient Card: \n";
		cout << "_________________________________________\n";
		cout << "First Name : " << FirstName << endl;
		cout << "Last Name  : " << LastName << endl;
		cout << "Full Name  : " << FullName() << endl;
		cout << "Email      : " << Email << endl;
		cout << "Phone      : " << Phone << endl;
		cout << "Acc. Number: " << _AccountNumber << endl;
		cout << "Password   : " << _PinCode << endl;
		cout << "Balance    : " << _AccountBalance << endl;
		cout << "_________________________________________\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open(_ClientsFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open(_ClientsFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if(IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddMode:
			if(clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFailedAccountNumberExists;
			}
			else {
				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveCleintsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> _vClients;
		_vClients = GetClientsList();
		// _vClients = _LoadClientsDataFromFile();

		double TotalBalances = 0;

		for (clsBankClient& C : _vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
		}
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		return true;
	}

	void TransferLog(clsBankClient DestinationClient, double Amount)
	{
		string Line = _PrepareTransferRecord(DestinationClient, Amount);

		fstream MyFile;
		MyFile.open(_TransferFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	static vector<stTransferRegisterRecord> GetTransferRegisterList()
	{
		vector<stTransferRegisterRecord> vTransferRegisterRecord;

		fstream MyFile;
		MyFile.open(_TransferFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				stTransferRegisterRecord TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(Line);
				vTransferRegisterRecord.push_back(TransferRegisterRecord);
			}

			MyFile.close();
		}

		return vTransferRegisterRecord;
	}
};

