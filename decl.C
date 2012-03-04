

#include "decl.h"
#include "type.h"
#include <cstdio>  // for sprintf

namespace ast
{

  decl::decl(string s) 
    : name (s)
  {
    if(name.length() == 0)
      {
	cout << "INTERNAL ERROR!  DECL WITHOUT NAME!" << endl;
	exit(1);
      }
	
    children.clear();
  }

  
  vardecl::vardecl(string* variable, type * itstype)
        : ty(itstype), decl(*variable)
  { 
    static int id = 100;
    po_string = "DECL";
    char numberstring[6];  // we'll give it 5 digits, plus one for the null terminator, for now.  better ideas may come...
    snprintf(numberstring,6,"%d",id++);
    mylabel = "_" + get_name() + numberstring;
  }
  
  
  string decl::get_name() const
    {return name;}

  string vardecl::poh() const 
    {return po_string + get_name() + " : " + ty->get_name();}

}
