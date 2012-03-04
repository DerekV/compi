
#include "expression.h"
#include "type.h"
#include "env.h"

namespace ast
{

  type monoexpr::check_types(env &E)
  {
  

    return
      child->check_types(E);
  }

  type complement::check_types(env &E)
  {
    return
      ( child->check_types(E) == tINTEGER ) ? tINTEGER : tVOID;
  }
  
  type comparison::check_types(env &E)
  {
    // this will break if language is extended to
    // include user defined types
    if ( lhs->check_types(E) == rhs->check_types(E) )
      return tINTEGER;
    else
      {
	cout << "Type error : comparison between " 
	     << (lhs->check_types(E)).get_name() << " and "
	     << (rhs->check_types(E)).get_name()
	     << ", are different types." << endl; 

	// FAIL FAIL FAIL FAIL FAIL !!!
	return tVOID;
      }
  }
  
  type mathop::check_types(env &E)
  {
    if (!lhs || !rhs)
      {

	cout << "INTERNAL ERROR: incomplete tree on mathop." << endl;
	exit(1);
      }

    type lhs_type = (lhs->check_types(E));
    type rhs_type = (rhs->check_types(E));
    
    if( (lhs_type == tFLOAT) && (rhs_type == tFLOAT) 
	||  ((lhs_type == tFLOAT) && (rhs_type == tINTEGER))
	||  ((lhs_type == tINTEGER) && (rhs_type == tFLOAT)))
      return tFLOAT;
    
    else if( (lhs_type == tINTEGER) && (rhs_type == tINTEGER) )
      return tINTEGER;
    
    else 
      {
	// FAIL FAIL FAIL FAIL !!!!
	cout << "Type error :  math op " << flush 
	     << get_short_description() << flush
	     << " between "  << flush
	     << lhs->get_short_description() << flush
	     << " (" << lhs_type.get_name() << flush
	     << ") and " << flush
	     <<  rhs->get_short_description()  << flush 
	     << " (" << flush
	     << rhs_type.get_name() << flush
 	     << ") not allowed." << endl;
	return tVOID;
      }

  }
  
  type modulus::check_types(env &E)
  {
       // lang definition ambigious...
       // assuming only ints make sence
	  // later I could cause anything in modulo to be cast to int
       
       if(( lhs->check_types(E) == tINTEGER )&& 
	  ( rhs->check_types(E) == tINTEGER ))
	 return tINTEGER;
       else
       {
	 //FAIL FAIL FAIL FAIL FAIL !!!
	      return tVOID;
       }
     };

   type logicop::check_types(env &E)
	{
	  type lhs_type = lhs->check_types(E);
	  type rhs_type = rhs->check_types(E);
	    
	  
	  if( lhs_type == rhs_type )
	    return lhs_type;              // check this !!
	  else if( (lhs_type == tINTEGER) &&
		   (rhs_type == tINTEGER) )
	    return tINTEGER;
	  else
	    {
	      cout << "Type error : "
		   << get_short_description()
		   << " between "
		   << lhs->get_short_description()
		   << " (" 
		   << lhs_type.get_name()
		   << ") and "
		   << rhs->get_short_description()
		   << " ("
		   << rhs_type.get_name()
		   << ") is not allowed."
		   << endl;

	      // FAIL FAIL FAIL FAIL FAIL !!!!
	      return tVOID;
	    }
	}

}
