#include <iostream>
#include <math.h>
#include <vector>
#include "array.h"

using namespace std;

class Solution
{
public:
    vector<double> convertTemperature(double celsius)
    {
        double ten_k = 100000.0;
        double kelvin = (celsius + 273.15) * ten_k / ten_k;
        double fahrenheit = (celsius * 1.8 + 32) * ten_k / ten_k;
        return {kelvin, fahrenheit};
    }
};

int main()
{
    double celsius;
    cout << "Please input celsius: ";
    cin >> celsius;

    Solution s;
    vector<double> ans = s.convertTemperature(celsius);
    output(ans);

    return 0;
}
