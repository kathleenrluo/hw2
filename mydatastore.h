#pragma once
#include "datastore.h"
#include <map>
#include <deque>

class MyDataStore : public DataStore {
public:

    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    //add product to a user's cart
    void addToCart(std::string username, int hit, std::vector<Product*>& hits);

    //shows items in a user's cart
    void viewCart(std::string username);

    //buy the cart
    void buyCart(std::string username);

private:
    std::map<std::string, Product*> items;
    std::map<std::string, User*> people;
    std::map<std::string, std::deque<Product*>> cart;

};