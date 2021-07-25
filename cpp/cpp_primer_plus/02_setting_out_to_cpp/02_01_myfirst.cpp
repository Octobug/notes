#include <iostream>


int main()
{
  // modern practice regards this as a bit lazy and potentially a problem in
  //  large projects. The preferred approaches are to use std::qualifier or to
  //  use something called a using declaration to make just particular names
  //  available:
  //    using std::cout;
  //    using std::endl;
  //    using std::cin;
  //  but not:
  //    using namespace std;
  using namespace std;      // lazy approach, all names available

  cout << "Come up and C++ me some time.";
  cout << endl;
  cout << "You won't regret it!" << endl;
  return 0;
}
