#pragma once
#include<iostream>
#include<string>
#include<fstream>;
using namespace std;
const string FileName = "MyFile.txt";
const string Delim = "#__#";
enum enMainMenueOption { eShowClient = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7,eLogOut=8 };
enum enTransactionsOption{eDeposit=1,Withdraw=2,Totalbalances=3,Mainmenue=4};
struct sclient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	string AccountBalance;
	bool MarkToDeleted =false;
};
namespace Allb {
	vector <string> SplitString(string LineString) {
		vector<string>Vstring;
		short po;
		string sWord;
		while ((po = LineString.find(Delim)) != std::string::npos) {
			sWord = LineString.substr(0, po);
			if (sWord != "") {
				Vstring.push_back(sWord);
			}
			LineString = LineString.erase(0, po + Delim.length());
		}
		if (LineString != "") {
			Vstring.push_back(LineString);
		}
		return Vstring;
	}
	string ConvertRecordToLine(sclient Client) {
		string LineClient = "";
		LineClient += Client.AccountNumber + Delim;
		LineClient += Client.PinCode + Delim;
		LineClient += Client.Name + Delim;
		LineClient += Client.Phone + Delim;
		LineClient += Client.AccountBalance;
		return LineClient;
	}
	sclient ConvertLineToRecord(string LineString) {
		vector<string> Vstring;
		sclient Client;
		Vstring = SplitString(LineString);
		Client.AccountNumber = Vstring[0];
		Client.PinCode = Vstring[1];
		Client.Name = Vstring[2];
		Client.Phone = Vstring[3];
		Client.AccountBalance = Vstring[4];
		return Client;
	}
	vector <sclient> LoadClientFromFile(string FileN) {
		vector<sclient>Vclient;
		fstream MyFile;
		sclient client;
		MyFile.open(FileN, ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				client = ConvertLineToRecord(Line);
				Vclient.push_back(client);
			}
		}
		MyFile.close();
		return Vclient;
	}	
	enMainMenueOption ReadMainMenue() {
		short m;
		cout << "Choice What You Wont To DO : ";
		cin >> m;
		return enMainMenueOption(m);
	}	
	bool ChickAccountNumber(string AccountNumber) {
		vector<sclient>Vclient;
		Vclient = LoadClientFromFile(FileName);
		for (sclient c : Vclient) {
			if (c.AccountNumber == AccountNumber) {
				return true;
			}
		}
		return false;
	}
	sclient ReadClient() {
		sclient Client;
		cout << "Inter Your Account Number! : ";
		getline(cin >> ws, Client.AccountNumber);
		while (ChickAccountNumber(Client.AccountNumber)) {
			cout << "Account Number With [" << Client.AccountNumber << "] Already Exists Read Another Account Number! :";
			getline(cin >> ws, Client.AccountNumber);
		}
		cout << "Inter Your Pin Code :";
		getline(cin, Client.PinCode);
		cout << "Inter Your Name :";
		getline(cin, Client.Name);
		cout << "Inter Your Phone :";
		getline(cin, Client.Phone);
		cout << "Inter Your Account Balance :";
		getline(cin, Client.AccountBalance);
		return Client;
	}
	string ReadAccountNumber() {
		string An;
		cout << "Inter Account Number : ";
		cin >> An;
		return An;
	}
	void printclientdata(sclient cd, bool vertical = false) {
		if (vertical) {
			cout << setw(15) << left << "Account Number " << ":" << cd.AccountNumber << endl;
			cout << setw(15) << "PinCode " << ":" << cd.PinCode << endl;
			cout << setw(15) << "Name" << ":" << cd.Name << endl;
			cout << setw(15) << "Phone" << ":" << cd.Phone << endl;
			cout << setw(15) << "Account Number" << ":" << cd.AccountBalance << "$" << endl;
		}
		else {
			cout << "| " << left << setw(15) << cd.AccountNumber;
			cout << "| " << setw(10) << cd.PinCode;
			cout << "| " << setw(40) << cd.Name;
			cout << "| " << setw(12) << cd.Phone;
			cout << "| " << cd.AccountBalance << setw(30) << "$";
		}

	}
	bool FindClientByAccountNumber(vector <sclient>Vclient, string AccountNumber, sclient& Client) {
		for (sclient c : Vclient) {
			if (c.AccountNumber == AccountNumber) {
				Client = c;
				return true;
			}
		}
		return false;
	}
	void SaveDataToFile(vector<sclient>Vclient) {
		fstream MyFile;
		string Line;
		MyFile.open(FileName, ios::out);
		if (MyFile.is_open()) {
			for (sclient c : Vclient) {
				if (c.MarkToDeleted == false) {
					Line = ConvertRecordToLine(c);
					MyFile << Line << endl;
				}
			}
		}
	}
	void PrintBalance(sclient client) {
		cout << "\nAccount Name    :" << client.Name << endl;
		cout << "Account Balance :" << client.AccountBalance << "$" << endl;
	}

	/*Find Client*/
	void FindClient(vector<sclient>Vclient, string AccountNumber) {
		sclient cd;
		if (FindClientByAccountNumber(Vclient, AccountNumber, cd)) {
			printclientdata(cd, true);
			cout << "\n\n";
		}
		else {
			cout << "client with Account Number [" << AccountNumber << "] Is Not Found ):\n";
			FindClient(Vclient, ReadAccountNumber());
		}
	}
	/*Find Client*/

	/*Update Client*/
	void UpdateClientByUser(sclient& cd) {
		cout << "inter your pincode:";
		getline(cin >> ws, cd.PinCode);
		cout << "inter your name :";
		getline(cin, cd.Name);
		cout << "inter your phone \:";
		getline(cin, cd.Phone);
		cout << "inter your account balance :";
		cin >> cd.AccountBalance;
	}
	void UpdateClient(vector<sclient>Vclient, string AccountNumber) {
		sclient Client;
		char sure;
		if (FindClientByAccountNumber(Vclient, AccountNumber, Client)) {
			printclientdata(Client, true);
			cout << "Are You Sure You Wont Update Data! Y|N :";
			cin >> sure;
			if (toupper(sure) == 'Y') {
				for (sclient& c : Vclient) {
					if (c.AccountNumber == AccountNumber) {
					UpdateClientByUser(c);
					break;
					}
				}
			}
			SaveDataToFile(Vclient);
			cout << "\n\nClient Update Sucessfuly....(: \n";
		}
		else {
			cout << "\nClient With [" << AccountNumber << "] Not Found ): \n";
			UpdateClient(Vclient, ReadAccountNumber());
		}
	}
	/*Update Client*/

	/*Delete Client*/
	void MarkClientToDeleted(vector<sclient>& Vclient, string AccountNumber) {
		for (sclient& c : Vclient) {
			if (c.AccountNumber == AccountNumber) {
				c.MarkToDeleted = true;
				break;
			}
		}
	}
	void DeleteClientByAccountNumber(vector<sclient>& Vclient, string AccountNumber) {
		sclient Client;
		char Sure;
		if (FindClientByAccountNumber(Vclient, AccountNumber, Client)) {
			printclientdata(Client, true);
			cout << "Are You Sure You Want To Delete Y|N :";
			cin >> Sure;
			if (toupper(Sure) == 'Y') {
				MarkClientToDeleted(Vclient, AccountNumber);
				SaveDataToFile(Vclient);
				Vclient = LoadClientFromFile(FileName);
				cout << "\n\nDeleted Sucssfuly...): \n";
			}
		}
		else {
			cout << "\nClient With Account Number [" << AccountNumber << "] Not Found ):!\n";
			DeleteClientByAccountNumber(Vclient, ReadAccountNumber());
		}
	}
	/*Delete Client*/

	/*Print Client*/
	void printclientsdata(vector<sclient>Vclient) {
		cout << "\n\t\t\t\t\tclint list(" << Vclient.size() << ")client(s) .";
		cout << "\n______________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(15) << "Acount Number";
		cout << "| " << setw(10) << "Pin Code";
		cout << "| " << setw(40) << "Client Name";
		cout << "| " << setw(12) << "Phone";
		cout << "| " << setw(40) << "Balance";
		cout << "\n______________________________________________________________________________________________________________\n\n";
		if (Vclient.size() == 0) {
			cout << "\t\t\t\tNo Clients In Systeam!\n";
		}
		else {
			for (sclient& data : Vclient) {
				printclientdata(data);
				cout << endl;
			}

		}
		cout << "______________________________________________________________________________________________________________\n\n";

	}
	/*Print Client*/

	/*Add Client*/
	void AddClientToFile(string NewClient) {
		fstream MyFile;
		MyFile.open(FileName, ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << NewClient << endl;
		}
		MyFile.close();
	}
	void AddNewClient() {
		sclient NewClient;
		NewClient = ReadClient();
		AddClientToFile(ConvertRecordToLine(NewClient));
	}
	/*Add Client*/


	/*Draw*/
	void AddDraw(vector<sclient>& Vclient, string AccountNumber, int DrawN) {
		for (sclient& c : Vclient) {
			if (c.AccountNumber == AccountNumber) {
				if (stoi(c.AccountBalance) >= DrawN) {
				c.AccountBalance = to_string(stoi(c.AccountBalance) + (-1 * DrawN));
				cout << "Balance Is " << c.AccountBalance << endl;
				}
				else {
					cout << "You Dont Have Mony\n";
				}
				break;
			}
		}
	}
	void WithDraw(vector<sclient>Vclient, string AccountNumber) {
		sclient client;
		int DrawN;
		char Sure;
		while (!FindClientByAccountNumber(Vclient, AccountNumber, client)) {
			cout << "Account Number With [" << AccountNumber << "] Not Found ):\n";
			AccountNumber = ReadAccountNumber();
		}
			PrintBalance(client);
			cout << "Inter Draw Account :";
			cin >> DrawN;

			while (DrawN > stoi(client.AccountBalance)) {
				cout << "Amount Exceeds The Balance , You Can WithDraw Up To ."<<client.AccountBalance<<endl;
				cout << "Please Inter Another Amount \n";
				cin >> DrawN;
			}
			cout << "Are You Sure Y|N :";
			cin >> Sure;
			if (toupper(Sure) == 'Y') {
				AddDraw(Vclient, AccountNumber, DrawN);
				SaveDataToFile(Vclient);
			}
		}
	/*Draw*/

	/*Deposit*/
	void AddDeposit(vector<sclient>& Vclient, string AccountNumber, int DepoistN) {
		for (sclient& c : Vclient) {
			if (c.AccountNumber == AccountNumber) {
				c.AccountBalance = to_string(stoi(c.AccountBalance) + DepoistN);
				cout << "Balance Is " << c.AccountBalance << endl;
				break;
			}
		}
	}
	void Deposit(vector<sclient>Vclient, string AccountNumber) {
		sclient client;
		int DepositN;
		char Sure;
		while (!FindClientByAccountNumber(Vclient, AccountNumber, client)) {
			cout << "Account Number With [" << AccountNumber << "] Not Found ):\n";
			AccountNumber = ReadAccountNumber();
		}

			PrintBalance(client);
			cout << "Inter Deposit Account :";
			cin >> DepositN;
			cout << "Are You Sure Y|N :";
			cin >> Sure;
			if (toupper(Sure) == 'Y') {
				AddDeposit(Vclient, AccountNumber, DepositN);
				SaveDataToFile(Vclient);
			}
		}
	/*Deposit*/

	/*Print Balances*/
	void PrintBalanceClient(sclient client) {
		cout << "| " << left << setw(30) << client.AccountNumber;
		cout << "| " << setw(45) << client.Name;
		cout << "| " << client.AccountBalance << setw(50) << "$";

	}
	void printBalances(vector<sclient>Vclient) {
		int total = 0;
		cout << "\n\t\t\t\t\tBalances list(" << Vclient.size() << ")client(s) .";
		cout << "\n______________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(30) << "Acount Number";
		cout << "| " << setw(45) << "Client Name";
		cout << "| " << setw(50) << "Balance";
		cout << "\n______________________________________________________________________________________________________________\n\n";
		if (Vclient.size() == 0) {
			cout << "\t\t\t\tNo Clients In Systeam!";
		}
		else {
			for (sclient& data : Vclient) {
				total += stoi(data.AccountBalance);
				PrintBalanceClient(data);
				cout << endl;
			}

		}
		cout << "______________________________________________________________________________________________________________\n\n";
		cout << "\n\t\t\t\t\tTotal Balances (" << total << ").\n";

	}
	/*Print Balances*/

}

