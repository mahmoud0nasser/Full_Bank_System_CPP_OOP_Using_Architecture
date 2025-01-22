#pragma once

#include <iostream>
#include "clsString.h"
#include <vector>
#include "clsUtil.h"
#include <fstream>

using namespace std;

const string _CurrenciesFileName = "Currencies.txt";

class clsCurrency
{
private:
	enum enMode {
		EmptyMode = 0, UpdateMode = 1
	};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Separator = "#//#")
	{
		vector<string> vCurrencyRecord = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyRecord[0], vCurrencyRecord[1],
			vCurrencyRecord[2], stof(vCurrencyRecord[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency CurrencyObject, string Separator = "#//#")
	{
		string Line = "";

		Line += CurrencyObject.GetCountry() + Separator;
		Line += CurrencyObject.GetCurrencyCode() + Separator;
		Line += CurrencyObject.GetCurrencyName() + Separator;
		Line += to_string(CurrencyObject.GetRate());

		return Line;
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector<clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open(_CurrenciesFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open(_CurrenciesFileName, ios::out);

		if (MyFile.is_open())
		{
			string Line = "";

			for (clsCurrency& Currency : vCurrencies)
			{
				Line = _ConvertCurrencyObjectToLine(Currency);

				if (Line != "")
					MyFile << Line << endl;
			}
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	void _Update()
	{
		vector<clsCurrency> _vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& Currency : _vCurrencies)
		{
			if (Currency.GetCurrencyCode() == GetCurrencyCode())
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(_vCurrencies);
	}

public:

	clsCurrency()
	{

	}

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string GetCountry()
	{
		return _Country;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	void SetRate(float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float GetRate()
	{
		return _Rate;
	}

	// __declspec(property(get = GetRate, put = SetRate)) string Rate;

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open(_CurrenciesFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open(_CurrenciesFileName, ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.GetCountry()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return (!Currency.isEmpty());
	}

	static bool isCountryExist(string Country)
	{
		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		return (!Currency.isEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		return vCurrencies;
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / GetRate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency.GetCurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency.GetRate());
	}

};

