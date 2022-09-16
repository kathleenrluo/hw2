#include "util.h"
#include "book.h"
#include <sstream>
using namespace std;

book::book(const string category, const string name, double price, int qty, const string author, const string isbn):
    Product(category, name, price, qty),
    author_(author),
    isbn_(isbn)
{

}

book::~book()
{

}

set<string> book::keywords () const
{
    set<string> keys = parseStringToWords(name_);
    set<string> auth = parseStringToWords(author_);
    keys = setUnion(keys, auth);
    keys.insert(isbn_);
    return keys;
}

string book::displayString() const
{
    //<name>
    //Author: <author> ISBN: <isbn>
    //<price> <quantity> left.
    ostringstream dis;
    dis << getName() << "\nAuthor: " << author_ << " ISBN: " << isbn_
    << "\n" << getPrice() << " " << getQty() << " left.\n";
    return dis.str();
}

void book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
