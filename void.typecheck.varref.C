
#include "varref.h"
#include "type.h"
#include "env.h"


namespace ast
{
  type subscript::check_types(env &E)
  {
    type vtype = v->check_types(E);
    type itype = index->check_types(E);

    if (vtype.arrayp())
      {
	if (itype != vtype.get_dimtype())
	  {
	    // FAIL FAIL FAIL FAIL
	    cout << "Type error : "
		 << "Subscript index of "
		 << v->get_name() 
		 << " ("
		 << vtype.get_name()
		 << ") is of type "
		 << itype.get_name()
		 << " and does not match declaration of type "
		 << vtype.get_dimtype().get_name()
		 << endl;
	    return tVOID;
	  }
	else if(itype.constp() )
	  {
	    // put bounds checking here 
	  }
	
	
	return vtype.get_subtype();
      }
    else
      {
	// FAIL FAIL FAIL FAIL
	cout << "Type error : "
	     << "Subscript on non array type variable "
	     << v->get_name() 
	     << " ("
	     << vtype.get_name()
	     << ")"
	     << " not allowed."
	     << endl;
      

	return tVOID;
      }

    return tVOID;
  }

  type varref::check_types(env &E)
  { 
    return E.get_type_of( *data );
  }


}
