#include "util.h"
#include "clothing.h"
#include <sstream>
using namespace std;

clothing::clothing(const string category, const string name, double price, int qty, const string size, const string brand):
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

clothing::~clothing()
{

}

set<string> clothing::keywords () const
{
    set<string> keys = parseStringToWords(convToLower(name_));
    set<string> bra = parseStringToWords(convToLower(brand_));
    return setUnion(keys, bra);
}

string clothing::displayString() const
{
    //<name>
    //Size: <size> Brand: <brand>
    //<price> <quantity> left.
    ostringstream dis;
    dis << getName() << "\nSize: " << size_ << " Brand: " << brand_
    << "\n" << setprecision(2) << fixed << getPrice() << " " << getQty() << " left.\n";
    return dis.str();
}

void clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << setprecision(2) << fixed << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
