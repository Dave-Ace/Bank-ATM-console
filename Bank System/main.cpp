#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "Account.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main(int argc, char** argv) {
	char ch;
	int num;
	intro();
	do{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT";
		cout << "\n\n\t03. WITHDRAW";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNR";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option(1-8): ";
		cin >> ch;
		system("cls");
		switch(ch){
			case '1': write_account();
				break;
			case '2': cout << "\n\n\tEnter The account NO.: "; cin >> num;
					  deposit_withdraw(num, 1);
				break;
			case '3': cout << "\n\n\tEnter The account NO.: "; cin >> num;
					  deposit_withdraw(num, 2);
				break;
			case '4': cout << "\n\n\tEnter The account NO.: "; cin >> num;
					  display_sp(num);
				break;
			case '5': display_all();
				break;
			case '6': cout << "\n\n\tEnter The account NO.: "; cin >> num;
					  delete_account(num);
				break;
			case '7': cout << "\n\n\tEnter The account NO.: "; cin >> num;
					  modify_account(num);
				break;
			case '8': cout << "\n\n\tThanks for Using Daivy Bank Management System";
				break;
			default: cout <<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

void write_account(){
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
		outFile.close();
}

void display_sp(int n){
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile){
		cout << "File could not be open !! Press any key...";
			return;
	}
	cout << "\nBALANCE DETAILS\n";
	while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
	{
		if(ac.get_acno()==n){
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
	cout << "\n\nAccount Number does not exist";
}

void modify_account(int n){
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
		if(!File){
			cout <<"File could not be open !! Press any key...";
			return;
		}
		while(!File.eof() && found==false){
			cout <<"entered"
			File.read(reinterpret_cast<char*> (&ac), sizeof(account));
			if(ac.get_acno()==n){
				ac.show_account();
				cout<<"\nEnter The New Details of account"<<endl;
				ac.modify();
//				int pos=(-1)*static_cast<int>(sizeof(account));
//				File.write(reinterpret_cast<char*>(&ac), sizeof(account));
				cout<<"\n\n\tRecord Updated";
				found=true;
			}
		}
		File.close();
		if(found==false)
		cout <<"\n\nRecord not Found";
}

void delete_account(int n){
	account ac;
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("account.dat", ios::binary);
	if(!inFile){
		cout<<"File could not be open !! Press any key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
		inFile.seekg(0,ios::beg);
		while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))){
			if(ac.get_acno()!=n){
				outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
			}
		}
		inFile.close();
		outFile.close();
		remove("account.dat");
		rename("Temp.dat", "account.dat");
		cout<<"\n\n\tRecord Deleted..";
}

void display_all(){
	account ac;
	ifstream inFile;
	
	inFile.open("account.dat", ios::binary);
	if(!inFile){
		cout <<"File could not be open !! Pres any key...";
		return;
	}
	cout <<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "======================================================\n";
	cout << "A/c no.     \t   NAME	\t\t\t TYPE	BALANCE\n";
	cout << "======================================================\n";
	while(inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))){
			ac.report();
		}
		inFile.close();
}

void deposit_withdraw(int n, int option){
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File){
		cout <<"File could not be open !! Press any key...";
		return;
	}
	while(!File.eof() && found == false){
		File.read(reinterpret_cast<char*>(&ac), sizeof(account));
		if(ac.get_acno()==n){
			ac.show_account();
			if(option==1){
				cout<<"\n\nTO DEPOSIT AMOUNT";
				cout <<"\n\nEnter The Amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2){
				cout<<"\n\nTO WITHDRAW AMOUNT";
				cout <<"\n\nEnter The Amount to be withdraw: ";
				cin>>amt;
				int bal=ac.get_balance()-amt;
				if((bal<500 && ac.get_type()=='S') || (bal<1000 && ac.get_type()=='C'))
				cout <<"Insufficient Fund";
				else
				ac.draw(amt);
			}
		int pos=(-1)*static_cast<int>(sizeof(ac));
		File.seekp(pos,ios::cur);
		File.write(reinterpret_cast<char*>(&ac), sizeof(account));
		cout <<"\n\n\tRecord Updated";
		found = true;
		}
	}
	File.close();
	if(found==false)
	cout<<"\n\nRecord Not Found..";
}

void intro(){
	cout<<"\n\n\n\t\t=========================================================";
	cout<<"\n\t\t***************\t     DAIVY     BANK\t*****************";
	cout<<"\n\t\t****************       MANAGEMENT      ******************";
	cout<<"\n\t\t*****************\tSYSTEM\t      *******************";
	cout<<"\n\t\t=========================================================";
	cin.get();
	
}
