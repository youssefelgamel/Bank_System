#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>


using namespace std;



// structures | constants | enums
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool ClientDelete = false;
};

const string ClientsFileName = "Clients.txt";

enum enMainMenueOption { ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, Exit = 7 };

enum enTransactionOption { Deposit = 1, Withdraw = 2, Total_Balance = 3, Main_Menue = 4};



// redefinition functions to fix identification errors
void ShowMainMenue();

void PerformMainMenueOption(enMainMenueOption MainMenueOption);

void PerformTransactionMenueOption(enTransactionOption TransactionMenueOption);



// Functions
vector<string> SplitString(string s, string Delim)
{
	vector<string> vString;

	short pos = 0;
	string sWord;

	while ((pos = s.find(Delim)) != std::string::npos)
	{
		sWord = s.substr(0, pos);

		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		s.erase(0, pos + Delim.length());
	}

	if (s != "")
	{
		vString.push_back(s);
	}

	return vString;
}

string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Please enter Account Number: ";
	cin >> AccountNumber;
	cout << endl;
	return AccountNumber;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
	string DataLine = "";
	DataLine += Client.AccountNumber + Separator;
	DataLine += Client.PinCode + Separator;
	DataLine += Client.Name + Separator;
	DataLine += Client.Phone + Separator;
	DataLine += to_string(Client.AccountBalance);

	return DataLine;
}

sClient ConvertLineToRecord(string Line, string separator = "#//#")
{
	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, separator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stoi(vClientData[4]);

	return Client;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<sClient> vClients;
	fstream File;
	File.open(FileName, ios::in); // read mode
	if (File.is_open())
	{
		string Line;
		sClient Client;

		while (getline(File, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				File.close();
				return true;
			}
			vClients.push_back(Client);
		}
		File.close();
	}
	return false;
}

sClient ReadClientData()
{
	sClient Client;
	cout << "\nEnter Account Number: ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout <<"["<< Client.AccountNumber << "] This account Number is already exists!\n";
		cout << "\nEnter Account Number: ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "\nEnter PinCode: ";
	getline(cin, Client.PinCode);
	cout << "\nEnter Name: ";
	getline(cin, Client.Name);
	cout << "\nEnter Phone: ";
	getline(cin, Client.Phone);
	cout << "\nEnter Account Balance: ";
	cin >> Client.AccountBalance;
	cout << endl;

	return Client;
}

void PrintClientCard(sClient Client)
{
	cout << "\n------This is the Client Card------\n\n";
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code: " << Client.PinCode << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Phone: " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "-------------------------------------\n\n";
}

vector<sClient> LoadClientDataFromFile(string FileName)
{
	vector<sClient> vClients;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line;
		sClient Client;

		while (getline(File, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		File.close();
	}
	return vClients; 
}

void AddDataLineToFile(string FileName, string DataLine)
{
	fstream File;

	File.open(FileName, ios::out | ios::app);

	if (File.is_open())
	{
		File << DataLine << endl;
		File.close();
	}
}

void AddClients()
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "Adding new Clients...\n";
		sClient Client;
		Client = ReadClientData();
		AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
		cout << "\nClient Added successfully, do you want to add more ? [y/n]:  ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

bool MarkClientDelete(string AccountNumber, vector<sClient> &vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.ClientDelete = true;
			return true;
		}
	}
	return false;
}

bool FindClientByAccountNumber(string AccountNumber ,vector<sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

vector<sClient> SaveClientDataToFile(string FileName, vector<sClient> vClients)
{
	fstream File;
	File.open(FileName, ios::out);
	string DataLine;
	if (File.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.ClientDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				File << DataLine << endl;
			}
		}
		File.close();
	}
	return vClients;
}

bool DeleteClientByAccountNumber(vector<sClient> &vClients)
{
	sClient Client;
	char Answer = 'n';

	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "Are you sure you want to delete this client? [y/n]: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkClientDelete(AccountNumber, vClients);
			SaveClientDataToFile(ClientsFileName, vClients);

			vClients = LoadClientDataFromFile(ClientsFileName);
			cout << "\n\nClient is deleted successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
		return false;
	}
}

sClient ChangeClientData(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter Pin Code: ";
	getline(cin >> ws, Client.PinCode);
	cout << "\n\nEnter Name: ";
	getline(cin, Client.Name);
	cout << "\n\nEnter Phone: ";
	getline(cin, Client.Phone);
	cout << "\n\nEnter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientDataByAccountNumber(vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to update this client? [y/n]: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientData(AccountNumber);
					break;
				}
			}
			SaveClientDataToFile(ClientsFileName, vClients);
			cout << "\n\n Client is updated successfully!\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
		return false;
	}
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15)<< left << Client.AccountNumber; //  << left << 
	cout << "| " << setw(10)<< left << Client.PinCode;
	cout << "| " << setw(40)<< left << Client.Name;
	cout << "| " << setw(12)<< left << Client.Phone;
	cout << "| " << setw(12)<< left << Client.AccountBalance;
}

void PrintBalancesRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

double ReadDepositAmount()
{
	double DepositAmount = 0;
	do
	{
		cout << "\nPlease enter deposit amount: ";
		cin >> DepositAmount;

	} while (DepositAmount <= 0);

	return DepositAmount;
}

double ReadWithdrawAmount(sClient Client)
{
	double WithdrawAmount = 0;

	cout << "\nPlease enter withdraw amount: ";
	cin >> WithdrawAmount;

	while (WithdrawAmount > Client.AccountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
		cout << "\nPlease enter another withdraw amount: ";
		cin >> WithdrawAmount;
	}

	return WithdrawAmount;
}

bool updateBalanceAfterDeposit(vector<sClient>& vClients)
{
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	char Answer = 'y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		double DepositAmount = ReadDepositAmount();

		cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance += DepositAmount;
					cout << "Account Balance after transaction = " << C.AccountBalance << endl;
					break;
				}
			}
			SaveClientDataToFile(ClientsFileName, vClients);
			cout << "\n\n Client is updated successfully!\n";
			return true;
		}
		else
		{
			cout << "Transactions is canceled!\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
		return false;
	}
}

bool updateBalanceAfterWithDraw(vector<sClient>& vClients)
{
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	char Answer = 'y';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		double WithdrawAmount = ReadWithdrawAmount(Client);

		cout << "\nAre you sure you want to perform this transaction? [y/n]: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance -= WithdrawAmount;
					cout << "Account Balance after transaction = " << C.AccountBalance << endl;
					break;
				}
			}
			SaveClientDataToFile(ClientsFileName, vClients);
			cout << "\n\n Client is updated successfully!\n";
			return true;
		}
		else
		{
			cout << "Transactions is canceled!\n";
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
		return false;
	}
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1-7]: ";
	short choice = 0;
	cin >> choice;
	return choice;
}

short ReadTransactionMenueOption()
{
	cout << "Choose what do you want to do? [1-4]: ";
	short choice = 0;
	cin >> choice;
	return choice;
}



// Main Screen
void ShowMainMenue()
{
	system("cls");
	cout << "========================================\n";
	cout << "             Main Menue Screen          \n";
	cout << "========================================\n";
	cout << "      [1] Show Client List.             \n";
	cout << "      [2] Add New Client.               \n";
	cout << "      [3] Delete Client.                \n";
	cout << "      [4] Update Client Info.           \n";
	cout << "      [5] Find Client.                  \n";
	cout << "      [6] Transactions.                 \n";
	cout << "      [7] Exit.                         \n";
	cout << "========================================\n";

	PerformMainMenueOption((enMainMenueOption)ReadMainMenueOption());
}

void ShowAllClientsScreen()
{
	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients.";
	cout << "\n________________________________________________________________________________________________________";
	cout << "\n________________________________________________________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "Pin Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n________________________________________________________________________________________________________";
	cout << "\n________________________________________________________________________________________________________\n" << endl;

	if (vClients.size() == 0)
	{
		cout << "\t\t\tNO Clients Avaliable In the system!";
	}
	else
	{
		for (sClient Client : vClients)
		{
			PrintClientRecord(Client);
			cout << endl;
		}
	}

	cout << "\n_________________________________________________________________________________________________________";
	cout << "\n_________________________________________________________________________________________________________\n" << endl;
}

void ShowAddNewClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tAdd new clients screen";
	cout << "-------------------------------------------\n";

	AddClients();
}

void ShowDeleteClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tDelete client screen\n";
	cout << "-------------------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	DeleteClientByAccountNumber(vClients);
}

void ShowUpdateClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tUpdate client screen\n";
	cout << "-------------------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	UpdateClientDataByAccountNumber(vClients);
}

void ShowFindClientScreen()
{
	cout << "-------------------------------------------\n";
	cout << "\tFind client screen\n";
	cout << "-------------------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";
	}

}

void ShowEndScreen()
{
	cout << "\n--------------------------------------\n";
	cout << "\tProgram Ends :)\n";
	cout << "\n--------------------------------------\n";
}



// Transaction Screen
void ShowTransactionsScreen()
{
	system("cls");
	cout << "-------------------------------------------\n";
	cout << "\tTransactions screen\n";
	cout << "-------------------------------------------\n";
	cout << "\t [1] Deposit.\n";
	cout << "\t [2] Withdraw.\n";
	cout << "\t [3] Total Balances.\n";
	cout << "\t [4] Main Menue.\n";
	cout << "-------------------------------------------\n";

	PerformTransactionMenueOption((enTransactionOption)ReadTransactionMenueOption());
}

void ShowDepositScreen()
{
	cout << "-------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	updateBalanceAfterDeposit(vClients);
}

void ShowWithdrawScreen()
{
	cout << "-------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------\n";

	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	updateBalanceAfterWithDraw(vClients);
}

void ShowTotalBalancesScreen()
{
	vector<sClient> vClients = LoadClientDataFromFile(ClientsFileName);
	double TotalBalances = 0;

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Clients.";
	cout << "\n________________________________________________________________________________________________________";
	cout << "\n________________________________________________________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n________________________________________________________________________________________________________";
	cout << "\n________________________________________________________________________________________________________\n" << endl;

	if (vClients.size() == 0)
	{
		cout << "\t\t\tNO Clients Avaliable In the system!";
	}
	else
	{
		for (sClient Client : vClients)
		{
			TotalBalances += Client.AccountBalance;

			PrintBalancesRecord(Client);
			cout << endl;
		}
	}

	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "\t\t\t\t\t\t Total Balances = " << TotalBalances << endl;
}



// Link Screens
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue.....";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionMenue()
{
	cout << "\n\nPress any key to go back to Transaction Menue.....";
	system("pause>0");
	ShowTransactionsScreen();
}

void PerformMainMenueOption(enMainMenueOption MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOption::ShowClientList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::AddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::DeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::UpdateClientInfo:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::FindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::Transactions:
		system("cls");
		ShowTransactionsScreen();
		break;

	case enMainMenueOption::Exit:
		ShowEndScreen();
		break;

	}
}

void PerformTransactionMenueOption(enTransactionOption TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionOption::Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionOption::Withdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionOption::Total_Balance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionOption::Main_Menue:
		system("cls");
		ShowMainMenue();
		break;
	}
}



int main() {


	ShowMainMenue();

	system("pause");
	return 0;
}


