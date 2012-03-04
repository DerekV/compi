#include "statement.h"
#include "instruction.h"
#include "env.h"

namespace ast
{

  Aarg* assignment::process(env &E)
  {
    Aarg* rreg = rval->process(E);
    
    // this is ____REALLY____ ghetto
    Aimval* offs = (Aimval*) lval->get_offs(E);

    E.push_instruction(new Ageneral("!  assignment to var " + lval->get_name()));
    // some stuff to do with floats here

    Aarg* addr = E.get_register();

    E.push_instruction(new Aiminst("set", addr, offs));
    E.push_instruction(new Ainstruction("add", addr, addr, 
					new Aspecial("%fp")) );
    
    E.push_instruction(new Ainstruction("st", addr, rreg));
    
    // free registers, since statements 
    // dont evaluate to anything
    E.free_register(addr);
    E.free_register(rreg);
    
    return Aarg::VOID;
  }

  int ifstatement::iflabel = 1000;

  Aarg* ifstatement::process(env &E)
  {
    Aarg* cval = cond->process(E);
    int label = iflabel++;
    
    E.push_instruction( new Ainstruction("set", Aarg::temp1, new Aimval(0)));
    E.push_instruction( new Ainstruction("cmp", Aarg::temp1, cval));
    E.push_branch( new Ageneral("be       ifelse", label));  // ghetto
    E.free_register(cval);
    
    ts->process(E);
    E.push_instruction( new Ageneral(".ifelse", label) );
    if(es) es->process(E);
    
    return Aarg::VOID;
  }


  int whilestatement::wlabel = 1000;

  Aarg* whilestatement::process(env &E)
  {
    Aarg* cvar;
    int label = wlabel++;

    E.push_instruction(new Ageneral(".wtop", label));
    cvar = cond->process(E);
    E.push_instruction(new Ainstruction("set", Aarg::temp1, new Aimval(0)));
    E.push_instruction(new Ainstruction("cmp", Aarg::temp1, cvar));
    E.push_branch(new Ageneral("      be      wend", label ));
    cont->process(E);
    E.push_branch(new Ageneral("      ba      wtop", label));
    E.push_instruction(new Ageneral(".wend", label));
    E.free_register(cvar);

    return Aarg::VOID;
  }

  Aarg* returnstatement::process(env &E)
  {
    Aarg* retR; 

    E.push_instruction(new Ageneral("! return statement"));
    retR = val->process(E);
    E.push_instruction(new Ainstruction("mov", retR, new Aspecialreg("o", 1)));
    E.push_instruction(new Ageneral("      ret"));
    E.push_instruction(new Ageneral("      restore"));
    return Aarg::VOID;
  }

}
