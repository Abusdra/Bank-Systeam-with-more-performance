#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include"Bank.h";
using namespace std;
using namespace Allb;
const string UsersFiletxt = "Users.txt";

enum enManageUsers { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6 };
enum enPermissions{pAll=-1,pLis=1,pAdd=2,pDele=4,pUpda=8,pFind=16,pTran=32,pMangU=64};

struct stUsers {
	string UserName;
	string Password;
	int Permissions;
	bool MarkUserToDelete = false;
};
stUsers CurrentUser;

namespace UsersLib {
stUsers ConvertLineUserToRecordUser(string LineString) {
	vector<string> Vstring;
	stUsers User;
	Vstring = SplitString(LineString);
	User.UserName = Vstring[0];
	User.Password = Vstring[1];
	User.Permissions = stoi(Vstring[2]);
	return User;
}
string ConvertRecordUserToLineUser(stUsers User) {
	string Line = "";
	Line += User.UserName + Delim;
	Line += User.Password+Delim;
	Line += to_string(User.Permissions);

	return Line;

}
vector <stUsers> LoadUsersFromFile(string Users) {
	vector<stUsers>VUsers;
	fstream MyFile;
	stUsers User;
	MyFile.open(Users, ios::in);
	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {
			User = ConvertLineUserToRecordUser(Line);
			VUsers.push_back(User);
		}
	}
	MyFile.close();
	return VUsers;
}
enManageUsers ReadMangeUsers() {
	short MU;
	cout << "Choose What You Want To Do : [1(TO)6] ";
	cin >> MU;
	return enManageUsers(MU);
}
bool FindUserByUserName(vector<stUsers>& Vusers, string UserName, stUsers& Userstruc) {
	for (stUsers& User : Vusers) {
		if (User.UserName == UserName) {
			Userstruc = User;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameAndPassword(string UserName,string Password,stUsers& User) {
	vector<stUsers>Vusers = LoadUsersFromFile(UsersFiletxt);
	for (stUsers U : Vusers) {
		if (U.UserName == UserName && U.Password==Password) {
			User = U;
			return true;
		}
	}
	return false;
}
bool CheckUserAndPassword(string UserName,string Password,stUsers& CurrentUser) {
	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser)) {
		return true;
	}
	else
		return false;
}
bool CheckAccessPermission(enPermissions Permission) {
	if (CurrentUser.Permissions == enPermissions::pAll)
		return true;
	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}
string ReadUserName() {
	string UserName;
	cout << "Inter User Name ";
	cin >> UserName;
	return UserName;
}
void ShowAccessDenied() {
	cout << "==================================\n";
	cout << "AccessDenied, \n";
	cout << "You Dont Have Permission To Do This,\n";
	cout << "Please Conact With Admin\n";
	cout << "==================================\n";
}

/*Show Users*/
void PrintUserData(stUsers User, bool vertical = false) {
	if (vertical) {
		cout << setw(15) << left << "User Name " << ":" << User.UserName << endl;
		cout << setw(15) << "Password " << ":" << User.Password << endl;
		cout << setw(15) << "Permissions " << ":" << User.Permissions << endl;

	}
	else {
		cout << "| " << left << setw(15) << User.UserName;
		cout << "| " << setw(10) << User.Password;
		cout << "| " << setw(10) << User.Permissions;
	}

}
void PrintUsersData(vector<stUsers>Vusers) {
	cout << "\n\t\t\t\t\tUsers list(" << Vusers.size() << ")User(s) .";
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << setw(10) << "Password";
	cout << "| " << setw(10) << "Permissions";
	cout << "\n______________________________________________________________________________________________________________\n\n";
	if (Vusers.size() == 0) {
		cout << "\t\t\t\tNo Users In Systeam!";
	}
	else {
		for (stUsers& data : Vusers) {
			PrintUserData(data);
			cout << endl;
		}
	}
	cout << "______________________________________________________________________________________________________________\n\n";

}
/*Show Users*/

/*Add User*/
bool CheckUserName(string UserName) {
	vector<stUsers> Vusers = LoadUsersFromFile(UsersFiletxt);
	for (stUsers User : Vusers) {
		if (User.UserName == UserName)
			return true;
	}
	return false;
}
int ReadPermissionsToSet() {
	char Access;
	int Permissions=0;
	cout << "Do You Want Ton Give Full Access Y|N ";
	cin >> Access;

	if (toupper(Access) == 'Y')
		return enPermissions::pAll;

	else {
		cout << "Do You Want To Give Access To :\n";

		cout << "Show Client List Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pLis;

		cout << "Add New Client Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pAdd;

		cout << "Delete Client Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pDele;

		cout << "Update Client Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pUpda;

		cout << "Find Client Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pFind;

		cout << "Transactions Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pTran;

		cout << "Manage Users Y|N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			Permissions += enPermissions::pTran;

		return Permissions;
	}
}
stUsers ReadNewUser() {
	stUsers User;
	cout << "Inter User Name : ";
	getline(cin >> ws, User.UserName);
	while (CheckUserName(User.UserName)) {
		cout << "User Name  [" << User.UserName << "] Already Exists Read Another User Name :";
		getline(cin >> ws, User.UserName);
	}

	cout << "Inter Your Password :";
	getline(cin, User.Password);

	User.Permissions = ReadPermissionsToSet();
	return User;
}
void AddUserToFile(string NewClient) {
	fstream MyFile;
	MyFile.open(UsersFiletxt, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << NewClient << endl;
	}
	MyFile.close();
}
void AddNewUser() {
	stUsers NewUser;
	NewUser = ReadNewUser();
	AddUserToFile(ConvertRecordUserToLineUser(NewUser));
}
/*Add User*/

/*Delete User*/
void SaveDataUserToFile(vector<stUsers>Vusers) {
	fstream MyFile;
	string Line;
	MyFile.open(UsersFiletxt, ios::out);
	if (MyFile.is_open()) {
		for (stUsers User : Vusers) {
			if (User.MarkUserToDelete == false) {
				Line = ConvertRecordUserToLineUser(User);
				MyFile << Line << endl;
			}
		}
	}
}
void MarkUserToDeleted(vector<stUsers>& Vusers, string UserName) {
	for (stUsers& User : Vusers) {
		if (User.UserName == UserName) {
			User.MarkUserToDelete = true;
			break;
		}
	}
}
void DeleteUserByUserName(vector<stUsers>& Vusers, string UserName) {
	stUsers Userstruc;
	char Sure;
	if (FindUserByUserName(Vusers, UserName, Userstruc)&&(Userstruc.Permissions!=-1)) {
		PrintUserData(Userstruc, true);
		cout << "Are You Sure You Want To Delete Y|N :";
		cin >> Sure;
		if (toupper(Sure) == 'Y') {
			MarkUserToDeleted(Vusers, UserName);
			SaveDataUserToFile(Vusers);
			cout << "\n\nDeleted Sucssfuly...): \n";
		}
	}
	else if (Userstruc.Permissions == -1) {
		cout << "Canot Deleted Admin User (:\n";
		system("pause>0");
	}
	else {
		cout << "\nUser With User Name [" << UserName << "] Not Found ):!\n";
		DeleteUserByUserName(Vusers, ReadAccountNumber());
	}
}
/*Delete User*/

/*Update User*/
void UpdateDataByUser(stUsers& User) {
	cout << "Inter Your Password :";
	getline(cin>>ws, User.Password);
	User.Permissions = ReadPermissionsToSet();
}
void UpdateUser(vector<stUsers>& Vusers, string UserName) {
	stUsers Userstruc;
	char Sure;
	if (FindUserByUserName(Vusers, UserName, Userstruc)) {
		PrintUserData(Userstruc, true);
		cout << "Are You Sure You Want To Update Data Y|N :";
		cin >> Sure;
		if (toupper(Sure) == 'Y') {
			for (stUsers& User : Vusers) {
				if (User.UserName == Userstruc.UserName) {
					UpdateDataByUser(User);
					break;
				}
			}
			SaveDataUserToFile(Vusers);
			cout << "\n\nUpdate Sucssfuly...): \n";
		}
	}
	else {
		cout << "\nUser With User Name [" << UserName << "] Not Found ):!\n";
		UpdateUser(Vusers, ReadAccountNumber());
	}
}
/*Update User*/

/*Find User*/
void FindUser(vector<stUsers>Vusers, string UserName) {
	stUsers User;
	if (FindUserByUserName(Vusers, UserName, User)) {
		PrintUserData(User, true);
	}
	else {
		cout << "User Not Found \n";
	}
}
/*Find User*/

}
