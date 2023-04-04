#include <iostream>;
#include<fstream>;
#include<vector>;
#include<iomanip>;
#include<string>;
#include "Bank.h";
#include"BankUser.h";
using namespace std;
using namespace Allb;
using namespace UsersLib;

void ShowMainMenue();
void ShowTransactionsMenue();
void LoginScreen();
void ShowManageUsersMenue();
void GobackToMainMenue();

void ShowExitScreen() {
	cout << "\n==================================\n";
	cout << "\tEnd Program...(: \n";
	cout << "==================================\n";

}
void ShowClientsScreen() {
	if (!CheckAccessPermission(enPermissions::pLis)) {
		ShowAccessDenied();
		return;
	}
	vector<sclient>Vclient = LoadClientFromFile(FileName);
	printclientsdata(Vclient);
}
void ShowAddClientScreen() {
	if (!CheckAccessPermission(enPermissions::pAdd)) {
		ShowAccessDenied();
		return;
	}
	char Again;
	short Number = 0;
	do {
		system("cls");
		cout << "\n==================================\n";
		cout << "\tAdd Menue Screen \n";
		cout << "==================================\n";
		cout << "\tClient [" << ++Number << "]\n\n";
		AddNewClient();
		cout << "Do You Want Add More Y|N?: ";
		cin >> Again;
	} while (toupper(Again) == 'Y');
	cout << "\n";
}
void ShowDeleteClientScreen() {
	if (!CheckAccessPermission(enPermissions::pDele)) {
		ShowAccessDenied();
		return;
	}
	cout << "\n==================================\n";
	cout << "\tDelete Menue Screen \n";
	cout << "==================================\n\n";
	vector<sclient>Vclient;
	Vclient = LoadClientFromFile(FileName);
	DeleteClientByAccountNumber(Vclient, ReadAccountNumber());
}
void ShowUpdateClientScreen() {
	if (!CheckAccessPermission(enPermissions::pUpda)) {
		ShowAccessDenied();
		return;
	}
	cout << "\n==================================\n";
	cout << "\tUpdate Menue Screen \n";
	cout << "==================================\n\n";
	vector<sclient> Vclient = LoadClientFromFile(FileName);
	UpdateClient(Vclient, ReadAccountNumber());
}
void ShowFindClientScreen() {
	if (!CheckAccessPermission(enPermissions::pFind)) {
		ShowAccessDenied();
		return;
	}
	cout << "\n==================================\n";
	cout << "\tFind Client Screen \n";
	cout << "==================================\n";
	vector<sclient>Vclient = LoadClientFromFile(FileName);
	FindClient(Vclient, ReadAccountNumber());
}

/*Transaction*/
void ShowBalancesScreen() {
	vector<sclient>Vclient = LoadClientFromFile(FileName);
	printBalances(Vclient);
}
void ShowDepositScreen() {
	cout << "\n==============================\n";
	cout << "\tDeposit  Screen \n";
	cout << "===============================\n";
	vector<sclient> Vclient = LoadClientFromFile(FileName);
	Deposit(Vclient, ReadAccountNumber());
}
void ShowDrawScreen() {
	cout << "\n==============================\n";
	cout << "\tWith Draw Screen \n";
	cout << "===============================\n";
	vector<sclient> Vclient = LoadClientFromFile(FileName);
	WithDraw(Vclient, ReadAccountNumber());
}
void GoBackToTransactionMenue() {
	system("pause");
	ShowTransactionsMenue();
}
void PerfromTransactionOption(enTransactionsOption enTransaction) {
	switch (enTransaction)
	{
	case eDeposit: {
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;
	}
	case Withdraw: {
		system("cls");
		ShowDrawScreen();
		GoBackToTransactionMenue();
		break;
	}
	case Totalbalances: {
		system("cls");
		ShowBalancesScreen();
		GoBackToTransactionMenue();
		break;
	}
	case Mainmenue: {
		ShowMainMenue();
		break;
	}
	default: {
		cout << "From 1 To 3 Man [-_-]\n";
		system("pause");
		ShowTransactionsMenue();
		break;
	}
	}
	}
void ShowTransactionsMenue() {
	if (!CheckAccessPermission(enPermissions::pTran)) {
		ShowAccessDenied();
		GobackToMainMenue();
		return;
	}
	system("cls");
	cout << "==================================\n";
	cout << "\tTransactions Menue Screen \n";
	cout << "==================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "==================================\n";
	PerfromTransactionOption( enTransactionsOption(ReadMainMenue()));
}
/*Transaction*/


/*Manage Users */
void ShowUsersScreen() {
	vector<stUsers>Vusers = LoadUsersFromFile(UsersFiletxt);
	PrintUsersData(Vusers);
}
void ShowAddUserScreen() {
		cout << "\n==================================\n";
		cout << "\tAdd Users Screen \n";
		cout << "==================================\n";
		AddNewUser();
}
void ShowDeleteUserScreen() {

	cout << "\n==================================\n";
	cout << "\tDelete User Screen \n";
	cout << "==================================\n\n";
	vector<stUsers>Vusers;
	Vusers = LoadUsersFromFile(UsersFiletxt);
	DeleteUserByUserName(Vusers, ReadUserName());
}
void ShowUpdateUserScreen() {
	cout << "\n==================================\n";
	cout << "\tUpdate Users Screen \n";
	cout << "==================================\n\n";
	vector<stUsers> Vusers = LoadUsersFromFile(UsersFiletxt);
	UpdateUser(Vusers,ReadUserName());
}
void ShowFindUserScreen() {
	cout << "\n==================================\n";
	cout << "\tFind User Screen \n";
	cout << "==================================\n";
	vector<stUsers>Vusers = LoadUsersFromFile(UsersFiletxt);
	FindUser(Vusers, ReadUserName());
}

void GobackToMangeUsers() {
	system("pause");
	ShowManageUsersMenue();
}
void PerformManageUsersOption(enManageUsers ManageUser) {
	switch (ManageUser)
	{
	case eListUsers: {
		system("cls");
		ShowUsersScreen();
		GobackToMangeUsers();
		break;
	}
	case eAddNewUser: {
		system("cls");
		ShowAddUserScreen();
		GobackToMangeUsers();
		break;
	}
	case eDeleteUser: {
		system("cls");
		ShowDeleteUserScreen();
		GobackToMangeUsers();
		break;
	}
	case eUpdateUser: {
		system("cls");
		ShowUpdateUserScreen();
		GobackToMangeUsers();
		break;
	}
	case eFindUser: {
		system("cls");
		ShowFindUserScreen();
		GobackToMangeUsers();
		break;
	}
	case eMainMenue: {
		ShowMainMenue();
		break;
	}
	}
}
void ShowManageUsersMenue() {
	if (!CheckAccessPermission(enPermissions::pMangU)) {
		ShowAccessDenied();
		GobackToMainMenue();
		return;
	}
	system("cls");
	cout << "==================================\n";
	cout << "Manage Users Menue Screen \n";
	cout << "==================================\n";
	cout << "\t[1] .List Users\n";
	cout << "\t[2] .Add New User\n";
	cout << "\t[3] .DeleteUser\n";
	cout << "\t[4] .UpdateUser\n";
	cout << "\t[5] .FindUser\n";
	cout << "\t[6] .MainMenuen\n";
	cout << "==================================\n";
	PerformManageUsersOption(ReadMangeUsers());
}
/*Manage Users */

void GobackToMainMenue() {
	system("pause");
	ShowMainMenue();
}
void PerfromMainMenueOption(enMainMenueOption MainMenueOption ) {
	switch (MainMenueOption) {
	case eShowClient: {
		system("cls");
		ShowClientsScreen();
		GobackToMainMenue();
		break;
	}
	case eAddClient: {
		system("cls");
		ShowAddClientScreen();
		GobackToMainMenue();
			break;
	}
	case eDeleteClient: {
		system("cls");
			ShowDeleteClientScreen();			
			GobackToMainMenue();
			break;
	}
	case eUpdateClient: {
		system("cls");
			ShowUpdateClientScreen();
			GobackToMainMenue();
			break;
	}
	case eFindClient: {
		system("cls");
			ShowFindClientScreen();
			GobackToMainMenue();
			break;
	}	
	case eTransactions: {
		system("cls");
			ShowTransactionsMenue();
			break;
	}
	case eManageUsers: {		
		system("cls");
			ShowManageUsersMenue();
			break;
		}
	case eLogOut: {
		system("cls");
		LoginScreen();
		break;
	}
	 default: {
		 cout << "From 1 To 7 Maan ..[-_-]\n";
		 system("pause>0");
		 ShowMainMenue();
	}
	}
}
void ShowMainMenue() {
	system("cls");
	cout << "==================================\n";
	cout << "\tMain Menue Screen \n";
	cout << "==================================\n";
	cout << "\t[1] Show Client Data.\n";
	cout << "\t[2] Add Client Data.\n";
	cout << "\t[3] Delete Client Data.\n";
	cout << "\t[4] Update Client Data.\n";
	cout << "\t[5] Find Client Data.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Log Out.\n";
	cout << "==================================\n";
	PerfromMainMenueOption(ReadMainMenue());
}
void ShowLogInScreen() {
	cout << "\n==============================\n";
	cout << "\tLogInScreen \n";
	cout << "===============================\n";

}
void LoginScreen() {
	bool LoginFaild = false;
	string UserName, Password;

	do {
		system("cls");
		ShowLogInScreen();

		if (LoginFaild) {
			cout << "Invalid UserName/Password \n";
		}

		cout << "Ineter Username :";
		cin >> UserName;
		cout << "Inter Password :";
		cin >> Password;

		LoginFaild = !CheckUserAndPassword(UserName, Password, CurrentUser);

	} while (LoginFaild);
	ShowMainMenue();
}
int main()
{
	LoginScreen();
}
