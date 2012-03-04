

#include "regprocessor.h"
#include "instruction.h"

#ifdef REGPROCESSOR_MAIN
#include <iostream>
#endif 

namespace ast
{

  qdregprocessor::qdregprocessor() 
  { 
    for(int i = 0; i < maxreg; i ++) 
      reglist[i] = false; 
  }
 
  Aarg* qdregprocessor::get_reg()
  {
    int i = 0;
    
    for(i = 0; i < maxreg; i++)
      {
	if(!reglist[i]) 
	  {reglist[i] = true;
	  return new Alocalreg(i);}
      }

    // what do we want to do?
    // make a temporary variable, put it in the sta
    return (Aarg*)(new Aspecialreg("OVERFLOW!"));

  }
  
  
  void qdregprocessor::free_reg(Alocalreg* w)
  {
    int p = w->get_num();
    if( (p < maxreg) && (p >= 0) )
      {
	reglist[p] = false;
      }
    
  }
  
  void qdregprocessor::final_pass() {}
}

#ifdef REGPROCESSOR_MAIN

// i think this is supposed to test it or something...

int funnyfunction(ast::regprocessor *R)
{
  int a, b;
 cout << (a = R->get_reg()) << endl;
  cout << (b = R->get_reg()) << endl;

  R->free_reg(a);
  R->final_pass();
  cout << (b = R->get_reg()) << endl;
  cout << (b = R->get_reg()) << endl;
  R->free_reg(b);
   cout << (b = R->get_reg()) << endl;

  R->final_pass();

  return 0;
}

#ifdef regprocessor_main
int main()
{  
  ast::qdregprocessor* R = new ast::qdregprocessor;
  funnyfunction(R);
  return 0;
}
#endif 

#endif
