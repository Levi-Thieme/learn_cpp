#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string maxSubstr(const string&, const string&);
string getFileString(const string&);

int main() {
    string s1 = getFileString("text1.txt");
    string s2 = getFileString("text2.txt");
    cout << "Common Substring: \n" << maxSubstr(s1, s2) << endl;
    return 0;
}

/*
 * Returns a string containing the contents of the file.
 */
string getFileString(const string &filename) {
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
string maxSubstr(const string &s1, const string &s2) {
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