#include "mydatastore.h"
#include "util.h"

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product *p)
{
	products_.push_back(p);
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User *u)
{
	users_.push_back(u);
	std::vector<Product *> v1;
	userCarts.insert(make_pair(u, v1)); // map is users' cart
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
	std::set<Product *> result;
	bool first = true;
	for (unsigned i = 0; i < terms.size(); i++)
	{
		std::set<Product *> current;
		for (unsigned j = 0; j < products_.size(); j++)
		{
			std::set<std::string> keywords = products_[j]->keywords();
			if (keywords.find(terms[i]) != keywords.end())
				current.insert(products_[j]);
		}
		if (type == 0) {
			if (first){
				result = setUnion(result, current);
				first = false;
			} else {
				result = setIntersection(result, current);
			}
		} else
			result = setUnion(result, current);
	}
	return std::vector<Product *>(result.begin(), result.end());
}

void MyDataStore::dump(std::ostream &ofile)
{
	ofile << "<products>" << std::endl;
	for (unsigned j = 0; j < products_.size(); j++)
	{
		products_[j]->dump(ofile);
	}
	ofile << "</products>" << std::endl;

	ofile << "<users>" << std::endl;
	for (unsigned j = 0; j < users_.size(); j++)
	{
		users_[j]->dump(ofile);
	}
	ofile << "</users>" << std::endl;
}

void MyDataStore::addCart(User *u, Product *p) // check insert the
{
	// first check if the users exit,if they have a cart, add to cart
	// if they don't have car, create a cart  for them , then add item to the cart
	if (u != NULL)
	{
		std::map<User *, std::vector<Product *>>::iterator it = userCarts.find(u);
		if (it != userCarts.end())
		{
			it->second.push_back(p);
		}
		else
		{
			std::vector<Product *> v;
			v.push_back(p);
			userCarts.insert(std::make_pair(u, v));
		}
	}
	else
	{
		std::cout << "The user doesn't exist\n";
		return;
	}
}

// check if the user has money , if the hace remove the balance in their cart
void MyDataStore::buyCart(User *u)
{
	if (u != NULL)
	{
		// get user's cart vector<Product *>
		std::map<User *, std::vector<Product *>>::iterator it = userCarts.find(u);
		if (it != userCarts.end())
		{
			// if user has a cart
			// iterate through the cart
			std::vector<Product *> u_cart = it->second;
			std::vector<Product *> newCart;
			for (unsigned i = 0; i < u_cart.size(); i++)
			{
				// if product is in stock and user balance >= product price
				// then buy the product
				Product *prod = u_cart[i];
				if (prod->getQty() > 0 && u->getBalance() >= prod->getPrice())
				{
					u->deductAmount(prod->getPrice());
					prod->subtractQty(1);
				}
				else if (u->getBalance() <= prod->getPrice())
				{
					// user exist, lack of credit
				  //	std::cout << "The user does not have enough credit,\n";
					newCart.push_back(prod);
				  continue;
				}
				else // user exist , item is not in stock
				{
				  //	std::cout << "The item is not in stock\n";
					newCart.push_back(prod);
					continue;
				}
			}
			it->second = newCart;
		}
	}
	else
	{
		std::cout << "The user dosen't exist\n";
	}
}

bool isValid(std::string str)
{

	// If first character is invalid
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return false;

	// Traverse the string for the rest of the characters
	for (int i = 1; i < str.length(); i++)
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return false;
	}
}

// see if the user name exist, print it
void MyDataStore::viewCart(User *u)
{
	if (u != NULL) // user exist
	{
		// check if the user has a cart
		std::map<User *, std::vector<Product *>>::iterator iit = userCarts.find(u);
		if (iit != userCarts.end()) // user has a cart
		{
			// iterate through the cart
			std::vector<Product *> u_cart = iit->second;
			for (int i = 0; i < u_cart.size(); i++)
			{
				Product *prod = u_cart[i];
				// if (isValid(prod->getName()))
				{
					std::cout<<"Item "<<i+1<<std::endl;
					// user has car, vector product
					std::cout << prod->displayString() << std::endl;
				}
			}
		}
		else // user dosen't have a cart
		{
			std::cout << "Invalid username\n";
		}
	}
	else // user dosen't exist
	{
		std::cout << "The user dosen't exist\n";
	}
}

MyDataStore::~MyDataStore()
{
	for(auto p : products_) {
		delete p;
	}
	for(auto u : users_) {
		delete u;
	}
}


User* MyDataStore::getUser(const std::string& username) {
	for(auto u : users_) {
		//std::cout << u->getName() <<std::endl;
		if(u->getName() ==  username) {
			return u;
		}
	}
	return nullptr;
}