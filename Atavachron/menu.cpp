#include "Book.h"
#include "Library.h"
#include "Patron.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void printFun();

int main()
{
	Library atavachron;
	int choice;
	string patronID, bookID;

	do
	{
		cout << "*********************" << endl;
		cout << "Welcome to ATAVACHRON" << endl;
		cout << "*********************" << endl << endl;
		cout << "What would you like to do?\n";
		cout << "1. Add Book\n";
		cout << "2. Add Member\n";
		cout << "3. Checkout Book\n";
		cout << "4. Return Book\n";
		cout << "5. Request Book for Hold\n";
		cout << "6. Pay Fine\n";
		cout << "7. Increment Date\n";
		cout << "8. View Patron Information\n";
		cout << "9. View Book Information\n";
		cout << "10. Return to Sarpeidon Past\n";
		cout << "11. Quit\n\n";
		cout << "Please enter your choice: ";
		cin >> choice;

		switch (choice)
		{
			case 1:	atavachron.addBook();
					break;

			case 2: atavachron.addMember();
					break;

			case 3: cout << "Please enter your ID: ";
					cin >> patronID;
					cout << "Please enter the book ID: ";
					cin >> bookID;
					atavachron.checkOutBook(patronID, bookID);
					break;

			case 4: cout << "Please enter the book ID: ";
					cin >> bookID;
					atavachron.returnBook(bookID);
					break;

			case 5: cout << "Please enter your ID: ";
					cin >> patronID;
					cout << "Please enter the book ID: ";
					cin >> bookID;
					atavachron.requestBook(patronID, bookID);
					break;

			case 6: cout << "Please enter your ID: ";
					cin >> patronID;
					atavachron.payFine(patronID);
					break;

			case 7: atavachron.incrementCurrentDate();
					break;

			case 8: cout << "Please enter your ID: ";
					cin >> patronID;
					atavachron.viewPatronInfo(patronID);
					break;

			case 9: cout << "Please enter the book ID: ";
					cin >> bookID;
					atavachron.viewBookInfo(bookID);
					break;

			case 10: printFun();
					break;

		}
	} while (choice != 11);
}

void printFun()
{
	cout << endl << endl << endl;
	cout << "  ___________________          _-_             \n"
		<<	"  \\__(==========/_=_/ ____.---'---`---.____      \n"
		<<	"              \\_ \\    \\----._________.----/   \n"
		<<	"                \\ \\   /  /    `-_-'              \n"
		<<	"            __,--`.`-'..'-_                           \n"
		<<	"           /____          ||                         \n"
		<<	"                `--.____,-'  \n";

	cout << "To go where no one has gone before, press any key...";
	cin.ignore(100, '\n');
	cin.get();
}