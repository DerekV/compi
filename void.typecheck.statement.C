
#include "statement.h"
#include "type.h"
#include "env.h"

namespace ast
{

  type assignment::check_types(env &E)
    {
      // this is a bit more complex...
      // this should go ahead and cast stuff
      // but for now lets just check to see if it is possible
      //   and later add the ability to cast
      
      // DOES NOT DETECT ASSIGMENT TO NON-LVALS (like invocations)
      // part of this this problem should go away 
      // once invocation checks its parameters...
      // it will still be a problem.  maybe, if the docs dont explicity
      // say its illeagle, then we'll let it slide as stupid (assiment to
      // the temporary value returned from the function i think
      type ltype = lval->check_types( E);      
      type rtype = rval->check_types( E);
      
      if( ( ((ltype.charp())||(rtype.charp())) && !(rtype == ltype))
	  || (ltype.arrayp()) 
	  || (rtype.arrayp()
	      )
	  )
	// check on symantics for array assigment 
	 	  
      {
	// FAIL FAIL FAIL FAIL FAIL !!!!!!!!
	cout << "Type error : " 
	     << "Assignment between "
	     << lval->get_short_description()
	     << " ("
	     << ltype.get_name()
	     << ") and "
	     << rval->get_short_description()
	     << " ("
	     << rtype.get_name()
	     << ") not allowed."
	     <<	  endl;
      }
      
      return tVOID;
      
    }

  
  type ifstatement::check_types(env &E)
    {
      ts->check_types(E);
      if(es) es->check_types(E);
      
      if( !(cond->check_types(E)).integerp() )
      {
	//FAIL FAIL FAIL FAIL FAIL FAIL !!!
	cout << "Type error: "
	     << "IF condition "
	     << cond->get_short_description() 
	     << " ("
	     << cond->check_types(E).get_name()
	     << ") failed to be int. " << endl;
      }
      
      return tVOID;
    }

  type returnstatement::check_types(env &E)
    {
      // this has to wait untill the symbol table is implemented
      return tVOID; 
    }; 

}
