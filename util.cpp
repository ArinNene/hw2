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

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{ 
	std::set<string> keyWords;
	unsigned int i = 0;
	int letterCount = 0;
	while (i <= rawWords.length()) {
			if ((rawWords[i] == '+' || rawWords[i] == '&' || rawWords[i] == '\'' || rawWords[i] == ';' || rawWords[i] == ',' || rawWords[i] == ' ' || rawWords[i] == '.' || rawWords[i] == '\0')) { //check delims
			    letterCount > 1 ? rawWords[i] = '\0', keyWords.insert(&rawWords[i-letterCount]), letterCount = -1 : rawWords[i] = '\0', letterCount = -1; //if substring is longer than 1 character, add it to the set of keywords. otherwise, move on.
			}
			letterCount++;
			i++;
	}
	return keyWords;
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
