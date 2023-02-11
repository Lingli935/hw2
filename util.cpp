#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

bool dupSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
// replace punctuations with spaces
  for(size_t i = 0; i < rawWords.size(); ++i)
  {
    char c = ::tolower(rawWords[i]);
    if (c < 'a' && c > 'z') rawWords[i] = ' ';
  }


  // remove repeated spaces
  std::string::iterator new_end = std::unique(rawWords.begin(), rawWords.end(), dupSpaces);
  rawWords.erase(new_end, rawWords.end());

  // tokenize
  std::set<std::string> output;
  stringstream ss(rawWords);
  string s;
  while (getline(ss, s, ' ')) {
    if(s.size() > 1) output.insert(s);
  }
  return output;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
