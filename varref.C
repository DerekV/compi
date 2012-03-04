#include "varref.h"



namespace ast 
{


  varref::varref() {};
   
  subscript::subscript(varref* var, expression* exp)
    :varref(new string("subscripter"))
  {
    v = var;
    index = exp;
    po_string = "{subscript}";
    children.push_back(v);
    children.push_back(index);
  }
    
  
  string varref::get_name() const
    {return *data;}


  /*  HERE IS THAT MYSTERIOUS put_to AGAIN
  void varref::put_to(env &E, Aarg* a)
  {
    decl* mydecl = E.get_decl_of(*data);
    if(!mydecl)
      {
	// fail
      }

       mydecl->put_to(E, a);

  }
  */

}
