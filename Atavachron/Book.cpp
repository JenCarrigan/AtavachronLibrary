#include "Book.h"
#include <string>

//default constructor
Book::Book()
{
	idCode = "******";
	title = "*******";
	author = "******";
	location = ON_SHELF;
	checkedOutBy = NULL;
	requestedBy = NULL;
	dateCheckedOut = 0;
}

//initialize class parameters
Book::Book(string idc, string t, string a)
{
	idCode = idc;
	title = t;
	author = a;
	location = ON_SHELF;
	checkedOutBy = NULL;
	requestedBy = NULL;
	dateCheckedOut = 0;
}

//read input data and set idcode
string Book::getIdCode()
{
	return idCode;
}

string Book::getTitle()
{
	return title;
}

string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

void Book::setLocation(Locale lo)
{
	location = lo;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

void Book::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
	setLocation(CHECKED_OUT);
}

Patron* Book::getRequestedBy()
{
	return requestedBy;
}

void Book::setRequestedBy(Patron* p)
{
	requestedBy = p;
	if (p != NULL && getLocation() == ON_SHELF)
		setLocation(ON_HOLD);
	else if (p == NULL)
		setLocation(CHECKED_OUT);
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}
