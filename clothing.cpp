
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string& brand, const std::string& size) : Product(category, name, price, qty), brand_(brand), size_(size) {}

Clothing::~Clothing() {
}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> k_brand = parseStringToWords(brand_);
  std::set<std::string> k_name = parseStringToWords(name_);
  std::set<std::string> output;
  for(const auto& s : k_brand) {
    output.insert(s);
  }
  for(const auto& s : k_name) {
    output.insert(s);
  }
  return output;
}


bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
  auto keys = keywords();
  for(const auto& s : searchTerms) {
    if (keys.find(s) != keys.end()) return true;
  }
  return false;
}

std::string Clothing::displayString() const {
  return "<"+name_+">\n" + "Size: <"+size_+"> Brand: <"+brand_+">\n"+"<"+std::to_string(price_)+"> <"+std::to_string(qty_)+"> left\n";
}

void Clothing::dump(std::ostream& os) const {
  os << displayString() << std::endl;
}

