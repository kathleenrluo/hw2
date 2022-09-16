#include "util.h"
#include "movie.h"
#include <sstream>
using namespace std;

movie::movie(const string category, const string name, double price, int qty, const string genre, const string rating):
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

movie::~movie()
{

}

set<string> movie::keywords () const
{
    set<string> keys = parseStringToWords(name_);
    set<string> gen = parseStringToWords(genre_);
    return setUnion(keys, gen);
}

string movie::displayString() const
{
    //<name>
    //Genre: <genre> Rating: <rating>
    //<price> <quantity> left.
    ostringstream dis;
    dis << getName() << "\nGenre: " << genre_ << " Rating: " << rating_
    << "\n" << getPrice() << " " << getQty() << " left.\n";
    return dis.str();
}

void movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}