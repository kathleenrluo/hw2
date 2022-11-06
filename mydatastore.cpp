#include "util.h"
#include "mydatastore.h"
#include <sstream>
using namespace std;

MyDataStore::MyDataStore() 
{

}

MyDataStore::~MyDataStore()
{
    for (map<std::string, Product*>::iterator it = items.begin() ; it != items.end(); ++it)
    {
        delete (it->second);
    }
    for (map<std::string, User*>::iterator it2 = people.begin() ; it2 != people.end(); ++it2)
    {
        delete (it2->second);
    }
    items.clear();
    people.clear();
    cart.clear();
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    items.insert(make_pair(p->getName(), p));
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    people.insert(make_pair(convToLower(u->getName()), u));
    deque<Product*> userCart;
    cart.insert(make_pair(convToLower(u->getName()), userCart));
}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<Product*> temp;
    set<string> setTerms;
    if(terms.empty())
    {
        cout<< "No search terms.\n";
        return temp;
    }
    for (string x : terms) 
    {
        setTerms.insert(x);
    }
    for (map<std::string, Product*>::iterator it = items.begin() ; it != items.end(); ++it)
    {
        set<string> keys = it->second->keywords();
        set<string> overlap = setIntersection(keys, setTerms);
        //for an or search
        if (!overlap.empty() && type==1)
        {
            temp.push_back(it->second);
        }
        //for an and search
        if(overlap==setTerms && type==0)
        {
            temp.push_back(it->second);
        }
        keys.clear();
        overlap.clear();
    }
    setTerms.clear();
    return temp;

}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>\n";
    for(map<string, Product*>::iterator itP = items.begin(); itP!=items.end(); ++itP)
    {
        (itP->second->dump(ofile));
    }
    ofile << "</products>\n<users>\n";
    for(map<string, User*>::iterator itU = people.begin(); itU!=people.end(); itU++)
    {
        (itU->second->dump(ofile));
    }
    ofile << "</users>";

}

void MyDataStore::addToCart(std::string username, int hit, std::vector<Product*>& hits)
{
    username=convToLower(username);
    if(hit>int(hits.size()) || hit<1)
    {
        cout <<"Invalid Request\n";
    }
    else if(cart.find(username)!=cart.end())
    {
        cart.find(username)->second.push_back(hits[hit-1]);
    }
    else{
        cout<<"Invalid Request\n";
    }
}

void MyDataStore::viewCart(std::string username)
{
    username=convToLower(username);
    if(cart.find(username)!=cart.end())
    {
        int count=1;
        deque<Product*> temp = cart.find(username)->second;
        for(deque<Product*>::iterator it=temp.begin(); it!=temp.end(); ++it)
        {
            cout<<count<<": "<< (*it)->displayString();
            ++count;
        }
    }
    else{
        cout<<"Invalid Username\n";
    }
}

void MyDataStore::buyCart(std::string username)
{
    username=convToLower(username);
    User* temp = people.find(username)->second;
    deque<Product*> newCart;
    if(cart.find(username)!=cart.end())
    {
        for(deque<Product*>::iterator it=(cart.find(username)->second).begin(); it!=(cart.find(username)->second).end(); ++it)
        {
            double price = (*it)->getPrice();
            //if user has enough money and there is product in stock, it is purchased
            //if not, it's added to new cart
            if((price<=(temp->getBalance())) && ((*it)->getQty())>0)
            {
                temp->deductAmount(price);
                (*it)->subtractQty(1);
            }
            else
            {
                newCart.push_back(*it);
            }
        }
        //new cart with unbought products are left in the user's cart
        cart.find(username)->second.clear();
        cart.find(username)->second=newCart;

    }
    else{
        cout<<"Invalid Username\n";
    }
}