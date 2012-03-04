
#include "progseg.h"
#include "env.h"
#include "type.h"

namespace ast
{

  type programseg::check_types(env &E)
    {
      E.add_set(*declist);
      return node::check_types(E);
    }

  type subprogram::check_types(env &E)
    {
      cout << "Type checking subprogram " << get_name() << endl;
      E.new_scope();
      E.add_set(*pl);
      programseg::check_types(E);      
      E.release_scope();
      return *rt;  // nessisary for anything?
    }
  
  type program ::check_types(env &E)
    {
      cout << "Type checking program " << get_name() << endl;
      E.new_scope();
      E.add_set(  *((vector<decl*>*)splist) );
      E.release_scope();
    } 

}
