#ifndef _ACCOUNT_
#define _ACCOUNT_

class account{
	private: // Sheltered members:
		int acno;  // Account number
		char name[50]; // Account holder
		int balance;
		char type; // State of the account
	public: // Public interface:
		void create_account();
		void show_account() const;
		void modify();
		void dep(int);
		void draw(int);
		void report() const;
		int get_acno() const;
		int get_balance() const;
		char get_type() const;
};
#endif // _ACCOUNT_

