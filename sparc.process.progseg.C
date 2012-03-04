
#include "progseg.h"
#include "env.h"
#include "instruction.h"

namespace ast
{

  Aarg* programseg::process(env &E)
    {

      E.add_set(*declist);

      for( int i = 0; i < declist->size(); i++)
	  (*declist)[i] ->process(E);

      Aarg* sp = new Aspecial("%sp");

      E.push_instruction(new Ainstruction("sub",sp,sp,new Aimval(-64))); 
      mp->process(E); 

      E.push_instruction(new Ageneral("      ret"));
      E.push_instruction(new Ageneral("      restore"));

      return new Aspecial("VOID");
    }

  Aarg* subprogram::process(env &E)
    {
      Aarg* retR;
      cout << "Processing subprogram " << get_name() << endl;

      // minor bug here:  
      // this will allow you to override parameter names
      E.new_scope();
      E.add_set(*pl);
      E.push_instruction(new Ageneral( "!====start subprogram"));
      E.push_instruction(new Ageneral( get_name() + ":" ));
      
      retR = programseg::process(E);    
      E.push_instruction(new Ageneral( "!====end subprogram"));
      E.release_scope();
      return retR; 
    }
  
  Aarg* program ::process(env &E)
    {
      Aarg* retR;

      cout << "Processing program " << get_name() << endl;

      E.new_scope();      
      E.add_set(  *((vector<decl*>*)splist) );

      E.push_instruction(new Ageneral("!#### start main"));
      E.push_instruction(new Ageneral("main:"));
      retR = programseg::process(E);
      E.push_instruction(new Ageneral("!#### end main"));

      for( int i = 0; i < splist->size(); i++)
	(*splist)[i]->process(E);

      E.release_scope();
      
      return retR;
    }

}
