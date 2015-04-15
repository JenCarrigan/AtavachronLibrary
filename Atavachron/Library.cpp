#include "Library.h"
#include "Book.h"
#include "Patron.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
using namespace std;

//default constructor
Library::Library()
{
	currentDate = 0;
	holdings.reserve(100);
	members.reserve(100);
}

//constant double set
const double Library::DAILY_FINE = 0.1;

/********************************************************
Add Book function

Create a new Book by asking for ID, title, and author

push_back holdings vector with new book
*********************************************************/
void Library::addBook()
{
	string idc, t, a;
	int uniqueBook = 0;
	size_t count;

	cout << "Please enter the book ID: ";
	cin.ignore();
	getline(cin, idc);
	
	for (count = 0; count < holdings.size(); count++)
	{
		if (idc == holdings[count].getIdCode())
			uniqueBook++;
	}

	if (uniqueBook > 0)
	{
		cout << "I'm sorry, that ID is already in use. Please try again.\n";
		return;
	}
	else
	{
		cout << "Please enter the book title: ";
		getline(cin, t);
		cout << "Please enter the author: ";
		getline(cin, a);

		Book newBook(idc, t, a);
		holdings.push_back(newBook);
		cout << string(100, '\n');
	}
}

/**********************************************
Add Member function

Create a new Patron by asking for ID and name

push_back members vector with new Patron
***********************************************/
void Library::addMember()
{
	string idn, n;
	int uniquePatron = 0;
	size_t count;

	cout << "Please enter the patron ID: ";
	cin.ignore();
	getline(cin, idn);
	
	for (count = 0; count < members.size(); count++)
	{
		if (idn == members[count].getIdNum())
			uniquePatron++;
	}

	if (uniquePatron > 0)
	{
		cout << "I'm sorry, that ID is already in use. Please try again.\n";
		return;
	}
	else
	{
		cout << "Please enter the patron's name: ";
		getline(cin, n);

		Patron newPatron(idn, n);
		members.push_back(newPatron);
		cout << string(100, '\n');
	}
}

/***************************************************************
Check Out Book Function

Allows Patron to check out book so long as Patron is member,
the Book exists in holdings, the book has not been checked out,
or the book is not being held for another Patron
****************************************************************/
void Library::checkOutBook(string patronID, string bookID)
{
	int patronIsNotMember = 0, bookIsNotHolding = 0, bookIsOut = 0, 
		bookIsHeld = 0, samePatronHolding = 0;
	size_t i, j;
	Patron *patron = NULL;

	//loop through members vector
	for (j = 0; j < members.size(); j++)
	{
		if (patronID == members[j].getIdNum())
			patron = &members[j];
		else
			patronIsNotMember++;
	}

	//go through holdings vector
	for (i = 0; i < holdings.size(); i++)
	{
		if (bookID != holdings[i].getIdCode())
			bookIsNotHolding++;

		if (holdings[i].getLocation() == CHECKED_OUT && bookID == holdings[i].getIdCode() && holdings[i].getRequestedBy() != patron && holdings[i].getCheckedOutBy() != patron)
			bookIsOut++;

		if (holdings[i].getLocation() == ON_HOLD && holdings[i].getRequestedBy() == patron && bookID == holdings[i].getIdCode())
			samePatronHolding++;
		
		if (holdings[i].getLocation() == ON_HOLD && holdings[i].getRequestedBy() != patron && bookID == holdings[i].getIdCode())
			bookIsHeld++;

		if (bookID == holdings[i].getIdCode() && patronIsNotMember != members.size())
		{
			if (holdings[i].getLocation() == ON_SHELF || holdings[i].getLocation() == ON_HOLD)
			{
				holdings[i].setCheckedOutBy(patron);
				//set the date checked out with the current date
				holdings[i].setDateCheckedOut(currentDate);

				if (samePatronHolding == 1)
					holdings[i].setRequestedBy(NULL);
			}
		}
	}

	if (patronIsNotMember == members.size())
		cout << "I'm sorry, you are not member here. Please see a librarian for membership information.\n";
	if (bookIsNotHolding == holdings.size())
		cout << "I'm sorry, that is not a book we have. Please see a librarian to request that the library get this book.\n";
	if (bookIsOut == 1)
		cout << "I'm sorry, that book has been checked out by another patron.\n";
	if (bookIsHeld == 1)
		cout << "I'm sorry, another patron has requested that book.\n";

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
}


/*************************************************************
Return Book Function

Allows Patron to return Book so long as Book is not on shelf
or on hold and that the Book exists in the library.
**************************************************************/
void Library::returnBook(string bookID)
{
	Book *book = NULL;
	size_t i, j;
	string patronID;
	int bookIsHolding = 0, bookIsOut = 0;

	for (i = 0; i < holdings.size(); i++)
	{
		if (bookID != holdings[i].getIdCode())
			bookIsHolding++;

		if (holdings[i].getLocation() == ON_SHELF || holdings[i].getLocation() == ON_HOLD)
			if (holdings[i].getLocation() != CHECKED_OUT && holdings[i].getIdCode() == bookID)
				bookIsOut++;
	}

	if (bookIsHolding == holdings.size())
		cout << "I'm sorry, that is not a book we have. Please see a librarian to request that the library get this book.\n";
	else if (bookIsOut == 1)
		cout << "I'm sorry, that book has not been checked out.\n";

	else
	{
		for (j = 0; j < holdings.size(); j++)
		{
			if (bookID == holdings[j].getIdCode())
			{
				book = &holdings[j];
			}
		}

		book->getCheckedOutBy()->removeBook(book);
		book->setCheckedOutBy(NULL);

		cout << "Thank you for returning the book!\n";

		book->setLocation(ON_SHELF);

		if (book->getRequestedBy() != NULL)
		{
			book->setLocation(ON_HOLD);
		}
	}

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
	//if Book is not in Library, print out such
	//if Book is not checked out, print out such
	//create Book variable
	//loop through holdings and set Book that matches bookId to Book var
	//send Book var into setCheckedOutBook(Book var)
	//if another Patron has requested Book, change location to ON HOLD
}

/******************************************************************************
Request Book Function

Allows Patron to place a Book that is not on hold for another Patron on hold
******************************************************************************/
void Library::requestBook(string patronID, string bookID)
{
	int patronIsMember = 0, bookIsHolding = 0, bookIsHeld = 0, bookIsOutAndHeld = 0;
	size_t i, j;
	Patron *x = NULL;
	string name, title;

	//loop through holdings
	for (i = 0; i < holdings.size(); i++)
	{
		if (bookID != holdings[i].getIdCode())
			bookIsHolding++;
		if (holdings[i].getLocation() == ON_HOLD && bookID == holdings[i].getIdCode())
			bookIsHeld++;
	}

	for (j = 0; j < members.size(); j++)
	{
		if (patronID == members[j].getIdNum())
		{
			x = &members[j];
			name = members[j].getName();

			for (i = 0; i < holdings.size(); i++)
			{
				if (bookID == holdings[i].getIdCode() && holdings[i].getLocation() != ON_HOLD
					&& holdings[i].getRequestedBy() == NULL)
				{
					title = holdings[i].getTitle();
					holdings[i].setRequestedBy(x);
					cout << title << " has been requested by " << name << ".\n";
				}
				if (bookID == holdings[i].getIdCode() && holdings[i].getLocation() == CHECKED_OUT
					&& holdings[i].getRequestedBy() != x)
				{
					bookIsOutAndHeld++;
				}
			}
		}

		else
			patronIsMember++;
	}

	if (patronIsMember == members.size())
		cout << "I'm sorry, you are not member of this library. Please see a librarian for membership information.\n";
	if (bookIsHolding == holdings.size())
		cout << "I'm sorry, that is not a book we have. Please see a librarian to request that the library get this book.\n";
	if (bookIsHeld == 1 || bookIsOutAndHeld == 1)
		cout << "I'm sorry, another patron has requested that book.\n";

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
}

/***********************************
Increment Current Date Function

Adds 1 to currentDate variable

If Book is overdue, increase fine
***********************************/
void Library::incrementCurrentDate()
{
	size_t i;
	int x, temp;
	Patron *patron = NULL;

	for (i = 0; i < holdings.size(); i++)
	{
		if (holdings[i].getLocation() == CHECKED_OUT)
		{
			temp = holdings[i].getDateCheckedOut();
			x = temp + 1;
			holdings[i].setDateCheckedOut(x);
			patron = holdings[i].getCheckedOutBy();

			//cout << holdings[i].getDateCheckedOut();

			if (holdings[i].getDateCheckedOut() > 20)
				patron->amendFine(DAILY_FINE);
		}
	}
}

/****************************************************************
Pay Fine Function

Allows Patron to pay any fines they've incurred at the library
****************************************************************/
void Library::payFine(string patronID)
{
	int patronIsMember = 0;
	size_t i, j;
	double toPay, currentFine, newCurrentFine;

	//loop through members vector
	for (j = 0; j < members.size(); j++)
	{
		if (members[j].getIdNum() == patronID)
		{
			currentFine = members[j].getFineAmount();

			if (currentFine == 0.00)
			{
				cout << "You do not have any fines.\n";
			}

			else
			{
				cout << "CURRENT FINE: " << currentFine << endl << endl;
				cout << "How much would you like to pay toward your fine?\n";
				cin >> toPay;
				toPay *= -1;

				members[j].amendFine(toPay);

				//get new fine amount
				for (i = 0; i < members.size(); i++)
					if (members[i].getIdNum() == patronID)
						newCurrentFine = members[i].getFineAmount();

				if (newCurrentFine < 0.0)
				{
					cout << "You overpaid by $" << 0 - newCurrentFine << ". Please see a librarian for a refund.\n";
					newCurrentFine *= -1;

					for (i = 0; i < members.size(); i++)
						if (members[i].getIdNum() == patronID)
							members[i].amendFine(newCurrentFine);
				}

				else if (newCurrentFine == 0.0)
				{
					cout << "You have paid off your fines. Thank you!\n";
				}
				else
				{
					cout << "CURRENT FINE: " << newCurrentFine << ".\n\n";
				}
			}
		}
		
		else
			patronIsMember++;
	}

	if (patronIsMember == members.size())
		cout << "I'm sorry, you are not member here. Please see a librarian for membership information.\n";

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
}

/**********************************************
View Patron Function

Allows a user to view a Patron with a patronID
**********************************************/
void Library::viewPatronInfo(string patronID)
{
	int patronIsMember = 0;
	size_t i, j;
	Patron *patron = NULL;

	for (i = 0; i < members.size(); i++)
	{
		if (patronID == members[i].getIdNum())
		{
			patron = &members[i];
			cout << endl << endl << endl;
			cout << fixed << showpoint << setprecision(2);
			cout << "PATRON INFORMATION\n" << endl
				<< "Name: " << members[i].getName() << endl
				<< "Checked Out Books: ";
			for (j = 0; j < holdings.size(); j++)
			{
				if (patron == holdings[j].getCheckedOutBy())
				{
					cout << holdings[j].getTitle() << "  ||  ";
				}
			}
			cout << endl << "Late Fines: " << members[i].getFineAmount() << endl;
			cout << endl << endl << endl;
		}
		else
			patronIsMember++;
	}

	if (patronIsMember == members.size())
		cout << "I'm sorry, you are not member here. Please see a librarian for membership information.\n";

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
}

/****************************************
View Book Function

Allows user to view a Book with a bookID
****************************************/
void Library::viewBookInfo(string bookID)
{
	size_t j;
	int count = 0;

	for (j = 0; j < holdings.size(); j++)
	{
		if (holdings[j].getIdCode() == bookID)
		{
			cout << endl << endl << endl;
			cout << "BOOK INFORMATION\n\n";
			cout << "Title: " << holdings[j].getTitle() << endl;
			cout << "Author: " << holdings[j].getAuthor() << endl;
			cout << "Location: ";

			if (holdings[j].getLocation() == 0)
			{
				cout << "Shelf.\n";
			}
			else if (holdings[j].getLocation() == 1)
			{
				cout << "Holds.\n";
			}
			else
			{
				cout << "Checked out.\n";
			}
			cout << endl << endl << endl;
		}
		else
			count++;
	}

	if (count == holdings.size())
		cout << "I'm sorry, that is not a book we have. Please see a librarian to request that the library get this book.\n";

	cout << "Press any key to return to the main menu: ";
	cin.ignore(100, '\n');
	cin.get();
}
