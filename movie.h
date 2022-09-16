#include "product.h"

class movie : public Product{
public:
    movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    ~movie();
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string genre_;
    std::string rating_;

};