#include "mydatastore.h"
#include "util.h"

    /**
     * Adds a product to the data store
     */
    void MyDataStore::addProduct(Product* p)
		{
			    products_.push_back(p);
		}

    /**
     * Adds a user to the data store
     */
     void MyDataStore:: addUser(User* u)
		 {
			 users_.push_back(u);
		 }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
     std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
		 {
			 std::set<Product*>result;
			 for(int i =0;i<terms.size();i++)
			 {
				 std::set<Product*>current;
				 for(int j =0;j<products_.size();j++)
				 {
					  std::set<std::string>keywords = products_[j]->keywords();
						if(keywords.find(terms[i])!= keywords.end())
							current.insert(products_[j]);
				 }
				 if(type == 0)
				 	 result = setIntersection(result,current);
				 else
				 	 result = setUnion(result,current);
			 }
			 	return std::vector<Product*>(result.begin(),result.end());
		 }

    void MyDataStore::dump(std::ostream& ofile)
		{
	
				 for(int j =0;j<products_.size();j++)
				 {
					  products_[j]->dump(ofile);
				 }
		}

