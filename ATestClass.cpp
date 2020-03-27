#include "ATestClass.h"
#include <format>
#include <iostream>
using namespace std;
ATestClass::ATestClass() {
  cout << format("ATestClass is {}.", "constructing") << endl;
}
ATestClass::~ATestClass() {
  cout << format("ATestClass is {}.", "destructing") << endl;
}
