#include <iostream>

void askAndConvert();

int main()
{
    askAndConvert();
    return 0;
}

void askAndConvert()
{
    using namespace std;
    cout << "Enter your age: ";
    int age;
    cin >> age;
    int ageInM = age * 12;

    cout << "Your age in months is " << ageInM << "." << endl;
}
