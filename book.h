#include "product.h"

class book : public Product{
public:
    book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
    ~book();
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string author_;
    std::string isbn_;

};