
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string& author, const std::string& isbn) : Product(category, name, price, qty), author_(author), isbn_(isbn) {}

Book::~Book() {
}

std::set<std::string> Book::keywords() const {
  std::set<std::string> k_auth = parseStringToWords(author_);
  std::set<std::string> k_name = parseStringToWords(name_);
  std::set<std::string> output;
  output.insert(isbn_);
  for(const auto& s : k_auth) {
    output.insert(s);
  }
  for(const auto& s : k_name) {
    output.insert(s);
  }
  return output;
}


bool Book::isMatch(std::vector<std::string>& searchTerms) const {
  auto keys = keywords();
  for(const auto& s : searchTerms) {
    if (keys.find(s) != keys.end()) return true;
  }
  return false;
}

std::string Book::displayString() const {
  return name_+"\n" + "Author: "+author_+" ISBN: "+isbn_+"\n"+std::to_string(price_)+" "+std::to_string(qty_)+" left\n";
}

//
void Book::dump(std::ostream& os) const {

	//call dump for the product (book)
	Product::dump(os);
	//os each data member (isbn, author etc.)
	//based on the database.txt for it 
	os<<isbn_<<"\n"<<author_<<"\n";

}

