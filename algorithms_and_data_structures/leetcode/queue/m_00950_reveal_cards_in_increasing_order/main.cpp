#include <iostream>
#include <deque>
#include <vector>
#include "input.h"
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<int> deckRevealedIncreasing(vector<int> &deck)
    {
        sort(deck.rbegin(), deck.rend());

        deque<int> que;

        for (int i = 0; i < deck.size() - 1; i++)
        {
            que.push_back(deck[i]);
            que.push_back(que.front());
            que.pop_front();
        }
        que.push_back(deck[deck.size() - 1]);

        for (int i = 0; i < deck.size(); i++)
        {
            deck[i] = que.back();
            que.pop_back();
        }

        return deck;
    }
};

int main()
{
    vector<vector<int>> decks = {
        {17, 13, 11, 2, 3, 5, 7}, // 2,13,3,11,5,17,7
        {1, 1000},                // 1,1000
    };

    int g = getGroup();
    Solution s;
    vector<int> result = s.deckRevealedIncreasing(decks[g]);
    output(result);

    return 0;
}
