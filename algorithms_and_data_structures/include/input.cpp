#include <iostream>
#include "input.h"

using namespace std;

int getGroup()
{
    cout << "Please enter group: ";
    int group;
    cin >> group;
    return group - 1;
};
