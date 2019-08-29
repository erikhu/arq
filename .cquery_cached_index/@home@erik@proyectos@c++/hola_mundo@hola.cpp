// Type your code here, or load an example.
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
  double v = 2.0;
  double r = 1.0;
  asm ("finit\n\t"
       "fld %[v]\n\t"
       "fstp  %[r]"
       : [v] "=r" (v)
       : [r] "r" (r));
  cout << "r";
  cout << "Hoteash";
  return 0;
}
