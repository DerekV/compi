
#include "invocation.h"
#include "env.h"
#include "type.h"
#include "progseg.h"  // for the quick fix in invocation::check_types()


namespace ast 
{

     invocation::invocation(string *s, vector<expression*>* arglist) 
     {
       data = s;
       args = arglist;
       po_string = "PROCEDURE INV " + *data;
       children.insert(children.end(), args->begin(), args->end());
     }

  type invocation::check_types(env &E)
  {
    // BEGIN QUICK FIX
    // there is an ambiguity in my design which would allow a
    // procedure invocation on a variable name.
    // simularly, you can treat a procedure name as a variable in some cases
    // (see varref.C)
    /*
    subprogram* sp = dynamic_cast<subprogram*> (E.lookup(*data));


    if(!sp)
      {
	cout << "Type error: " << *data << " treated as procedure." << endl;
	// FAIL FAIL FAIL FAIL
	return tVOID;
      } 
       
    return sp->get_type();
    */
    // END QUICK FIX

  

    // this function was previously only the following line 
     return E.get_type_of(*data);
    
   
  }

}
