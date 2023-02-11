
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string& genre, const std::string& rating) : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {
}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> k_genre = parseStringToWords(genre_);
  std::set<std::string> k_name = parseStringToWords(name_);
  std::set<std::string> output;
  for(const auto& s : k_genre) {
    output.insert(s);
  }
  for(const auto& s : k_name) {
    output.insert(s);
  }
  return output;
}


bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
  auto keys = keywords();
  for(const auto& s : searchTerms) {
    if (keys.find(s) != keys.end()) return true;
  }
  return false;
}

std::string Movie::displayString() const {
 return "<"+name_+">\n" + "Genre <"+genre_+"> Rating: <"+rating_+">\n"+"<"+std::to_string(price_)+"> <"+std::to_string(qty_)+"> left\n";
}

void Movie::dump(std::ostream& os) const {
  os << displayString() << std::endl;
}

