
#include <iostream>
#include <string>
#include <list>
#include "hash.h"
#include "decl.h"
#include "env.h"
#include "type.h"
#include "instruction.h"
#include "regprocessor.h"


namespace ast {

  using namespace std;
  typedef int reg;
 
  
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////// CLASS ENV
  ////////////////////////////////////////////////////////////////////////////////

  env::scope::~scope()
    {
      /*
      if(parent)
	delete parent;
      */
    }

  env::scope* env::scope::branch()
    {

            #ifdef _ENV_C_DEBUG
      cout << "branched env " << endl;
             #endif
      return new scope(this);
    }
  
  decl* env::scope::lookup(string &s)
    {

      decl* T = data.find(s);
      
      if( T )
	return T;
      else if(parent)
	return parent->lookup(s);
      else
	{
	  cout << "Error : Reference to undeclaired variable _" 
	       << s << "_" << endl;
	  cout << "Error : Declaired variables are as follows: " << endl
	       << "  [";

	  vector<decl*> testlist = data.get_vector();
	  for( vector<decl*>::iterator i = testlist.begin();
	       i != testlist.end(); i++)
	    {
	      cout << "   " << (*i)->get_name();
	    }
	  cout << "  ]" << endl;
	  return NULL;
	  // FAIL FAIL FAIL FAIL FAIL
	}
      
    }
  
  void env::scope::add_to(decl* s)
    {
      

          #ifdef _ENV_C_DEBUG
      cout << "add to about to add _" << s->get_name() 
	   << "_" <<  endl;
          #endif

      if( ! data.find(s->get_name()) )
	data.add(s->get_name(),s);
      else
	cout << "Type error : "
	     << s->get_name() 
	     << " declaired multiple times." << endl;

             #ifdef _ENV_C_DEBUG
      cout << "add to now dbl checking ... "
	   << get_type_of(s->get_name()).get_name()
	   << "was found by addto dbl check" << endl;
               #endif
    }
  

  void env::scope::add_set(vector<decl*> &dset)
    {
      for(vector<decl*>::iterator i  = dset.begin(); i < dset.end(); i++)
	{

           #ifdef _ENV_C_DEBUG
	  cout << "add set added " << (*i)->get_name() << endl;
	     #endif
	  add_to(*i);	
	}

    
    }
      
  
  type env::scope::get_type_of(string s)
    {
      decl* T = lookup(s);
      
      
        #ifdef _ENV_C_DEBUG
      cout << "Entering get_type_of and looking for " << s << endl;
      if(T)
   
	  cout << "Get type of looked for " << s 
	       << " and found " << T->get_name() << endl
	       << "and its a type" << &(T->get_type()) << endl
	       << "which is called a" << flush << T->get_type().get_name();
      else
	cout << "Get type of tried but couldn't find " << s << endl;
      cout << "parent is ";
      if(parent)
	cout << "found";
      else 
	cout << "NOT found";
      cout << endl;     
          #endif
      
      if( T )
	return T->get_type();
      else
	{
	  return tVOID;
	  // FAIL FAIL FAIL FAIL FAIL
	}
    }
  
  

   
  void env::new_scope()   
  { 
    curscope = curscope->branch();
  }
  
  void env::release_scope()
    { 
      scope* temp = curscope->get_parent();
      if(temp)
	{
	  delete curscope;
	  curscope = temp;
	}
      else
	{
	  cout << "INTERNAL ERROR: apperently scope released more then branched " << endl;
	  exit(1);
	}

    }
   
  void env::add_to(decl* d) { curscope->add_to(d); };
  void env::add_set(vector<decl*> &dset) { curscope->add_set(dset); };
  
  decl* env::get_decl_of(string msg) 
  { 
    return curscope->lookup( msg ); 
  } 
  
  type  env::get_type_of(string msg) 
  { 
    return curscope->get_type_of(msg); 
  }
  
   



  // ====================================================== \\
  // ================== OUTPUT FUNCTIONS ================== \\
  // ====================================================== \\
  
  ostream* env::tout() { return textout; } 
  ostream* env::eout() { return errorout; }
  
  void env::push_instruction(Astatement *I)
  {
    dribble.push_back(I);
  }
  
  void env::push_branch(Astatement *I)
  {
    push_instruction(I);
    push_instruction(new Ageneral("      nop"));
  }
		     
  // ====================================================== \\
  // =========== REGISTER PROCESSING FUNCTIONS ============ \\
  // ====================================================== \\
  
    
  Aarg* env::get_register()  
  {
    return roracle->get_reg();
  };
  
  void env::free_register(Aarg* R) 
  {
    if(Alocalreg*Q = dynamic_cast<Alocalreg*> (R) )
      roracle->free_reg(Q);
  };
  
  
      
  // ====================================================== \\
  // ===========     INITIALIZATION FUNCTIONS ============= \\
  // ====================================================== \\
  
  env::env(
      ostream *standard_out,
      ostream *data_out,
      ostream *error_out,
      regprocessor *regoracle )
    : textout(standard_out), dataout(data_out), 
      errorout(error_out)
  {
    roracle = new qdregprocessor;
  }
    
    
 
  
  env::~env()
    {
      // delete curscope;
    }
	    

  void env::finalize()
  {
    roracle->final_pass();
    

    for(list<Astatement*>::iterator i = dribble.begin(); 
	// incorrect way to use stl, really
	i != dribble.end();
	i++)
      {
	(*dataout) << (*i)->stringout() << endl;
      }

    (*textout) << "ENVIROMENT FINISHED AND CLEAN" << endl;
  }
  
}


#ifdef ENV_MAIN

int main()
{
  int a;

  ast::env E((ostream*)&cout,
	(ostream*)&cout,
	(ostream*)&cout,
	new ast::qdregprocessor);

  cout << (a = E.get_register()) << endl;
  cout << E.get_register() << endl;
  E.free_register(a);
  cout << E.get_register() << endl;

  return 0;
}

#endif
