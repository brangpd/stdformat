#include "ATestClass.h"
#include <format>
using namespace std;
ATestClass::ATestClass() {
  cout << format("ATestClass is {}.", "constructing") << endl;
}
ATestClass::~ATestClass() {
  cout << format("ATestClass is {}.", "destructing") << endl;
}
