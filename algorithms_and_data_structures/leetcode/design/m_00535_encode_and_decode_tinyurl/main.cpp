#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    unordered_map<string, string> db;
    unsigned int id = 0;

    // Encodes a URL to a shortened URL.
    string encode(string longUrl)
    {
        string shortURL = "http://tinyurl.com/" + to_string(id);
        id++;
        db[shortURL] = longUrl;
        return shortURL;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl)
    {
        return db[shortUrl];
    }
};

int main()
{
    Solution solution;
    string url = "https://leetcode.com/problems/design-tinyurl";
    cout << solution.decode(solution.encode(url)) << endl;

    return 0;
}
