#include "Patron.h"
#include "Book.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//default constructor
Patron::Patron()
{
	name = "name";
	idNum = "00000";
	fineAmount = 0.0;
	checkedOutBooks.push_back(NULL);
	checkedOutBooks.reserve(100);
}
	

//initialize variables
Patron::Patron(string idn, string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0.0;
	checkedOutBooks.reserve(100);
}

string Patron::getName()
{
	return name;
}

string Patron::getIdNum()
{
	return idNum;
}

vector <Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

void Patron::addBook(Book *b)
{
	checkedOutBooks.push_back(b);
}

void Patron::removeBook(Book *b)
{
	size_t i;
	for (i = 0; i < checkedOutBooks.size(); i++)
	{
		if (checkedOutBooks[i]->getIdCode() == b->getIdCode())
			checkedOutBooks.erase(checkedOutBooks.begin() + i);
	}
}

double Patron::getFineAmount()
{
	return fineAmount;
}

void Patron::amendFine(double amount)
{
	fineAmount = fineAmount + amount;
}
