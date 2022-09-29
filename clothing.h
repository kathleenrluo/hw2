#include "product.h"

class clothing : public Product{
public:
    clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    ~clothing();
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string size_;
    std::string brand_;

};