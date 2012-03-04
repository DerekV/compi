#include "hash.h"
#include <iostream>

class retard { 
  public:
  void goku() { cout << "goku!!" << endl;};
};

int main()

{
  const string foo("x");
  const string foo2("x");
  
  retard *fee = new retard;
  stringhash<retard*> newhash;

  newhash.add(foo,fee);

  

  (newhash.find(foo2)) -> goku();
  
}
