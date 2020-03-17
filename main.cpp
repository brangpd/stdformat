#include "ATestClass.h"
#include <format>
using namespace std;

int main(int argc, char *argv[]) {
  ATestClass aClass;
  cout << format("{}, {}!", "Hello", "World") << endl;
  return 0;
}
