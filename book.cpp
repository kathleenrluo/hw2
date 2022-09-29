#include "util.h"
#include "book.h"
#include <sstream>
using namespace std;

book::book(const string category, const string name, double price, int qty, const string isbn, const string author):
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
    /*string all = convToLower(name_)+" "+convToLower(author_);
    set<string> keys = parseStringToWords(all);*/
    set<string> nam = parseStringToWords(convToLower(name_));
    set<string> auth = parseStringToWords(convToLower(author_));
    set<string> keys = setUnion(nam, auth);
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
    << "\n" << setprecision(2) << fixed << getPrice() << " " << getQty() << " left.\n";
    return dis.str();
}

void book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << setprecision(2) << fixed << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
