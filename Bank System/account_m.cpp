#include "Account.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;

void account::create_account(){
	cout <<"\nEnter The account No.: ";
	cin>>acno;
	cout <<"\n\nEnter the Name of the Account Holder: ";
	cin.ignore();
	cin.getline(name, 50);
	cout <<"\nEnter Type of account (Savings: S, Current: C): ";
	cin >> type;
	type =toupper(type);
	cout <<"\nEnter The Initial(>=500 for Savings and >=1000 for current): ";
	cin >> balance;
	cout <<"\n\nAccount Created Successfully..";
}

void account::show_account() const{
	cout <<"\nAccount No.: " << acno;
	cout <<"\nAccount Holder Name: "<< name;
	cout <<"\nType of Account: "<< type;
	cout <<"\nBalance: "<< balance;
}

void account::modify(){
	cout <<"\nAccount No. : " << acno;
	cout << "\nModify Accout Holder name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account: ";
	cin >> type;
	type = toupper(type);
	cout <<"\nModify Balance: ";
	cin >> balance;
}

void account::dep(int x){
	balance+=x;
}

void account::draw(int x){
	balance-=x;
}

void account::report()const{
	cout <<acno<<setw(10)<<" "<<name<<setw(10)<<" "
	<<type<<setw(10)<<balance<<endl;
}

int account::get_acno() const{
	return acno;
}

int account::get_balance() const{
	return balance;
}

char account::get_type() const{
	return type;
}



