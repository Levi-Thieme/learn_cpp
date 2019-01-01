#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string maxSubstr(string, string);
string getFileString(string);

int main() {
    string s1 = getFileString("text1.txt");
    string s2 = getFileString("text2.txt");
    cout << "Common Substring: \n" << maxSubstr(s1, s2) << endl;
    return 0;
}

string getFileString(const string filename) {
    ifstream in(filename);
    if (in.fail()) {
        cout << "Could not open " << filename << endl;
        in.close();
        return "";
    }
    stringstream buf;
    buf << in.rdbuf();
    string content = buf.str();
    in.close();
    return content;
}

/*
 * Returns a string containing the maximum common substring of s1 and s2
 */
string maxSubstr(string s1, string s2) {
    if (s1.length() == 0 || s2.length() == 0) {
        return "";
    }
    string common;
    string newCommon;
    //for each character in s1
    for (auto i = s1.begin(); i < s1.end(); i++) {
        size_t first;
        if ((first = s2.find(*i)) != string::npos) {
            newCommon.append(sizeof(*i), *i);
            //get a substring starting after first char match to end of s1
            string sub1 = string(i + 1, s1.end());
            string sub2 = s2.substr(++first);
            for (auto j = sub1.begin(); j < sub1.end(); j++) {
                size_t pos;
                if ((pos = sub2.find(*j)) != string::npos) {
                    newCommon.append(sizeof(*j), *j);
                    sub2 = sub2.substr(++pos);
                }
            }
            if (newCommon.length() > common.length()) {
                common = string(newCommon);
            }
            newCommon.clear();
        }
    }
    return common;
}

/*
 Find the longest contiguous or noncontiguous substrings in two words
 see if a character from s1 is in s2, if so then find all subsequent characters in s1 that are in s2 that are past the location
 of the original character and ordered.
 If not, then go to the next character of s1

 use the shortest string to improve efficiency
 test for empty strings

 helper functions:
    string::find()
    string::substr()
    string::append()
 */