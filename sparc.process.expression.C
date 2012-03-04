#include "expression.h"
#include "env.h"

namespace ast
{

  Aarg* monoexpr::process(env &E)
  {
    return child->process(E);
  }

  Aarg* complement::process(env &E)
  {
    Aarg* result = E.get_register();
    Aarg* incoming = monoexpr::process(E);
    Astatement *I = new Ainstruction("not", result, incoming);
    E.push_instruction(I);

       
    Alocalreg* Q = dynamic_cast<Alocalreg*>(incoming);
    if(Q)
      E.free_register(Q);

    return result;
  }

  Aarg* dualexpr::process(env &E)
  {
    Aarg* lrr = lhs->process(E);
    Aarg* rrr = rhs->process(E);
    Astatement *I = new Ainstruction(instruction_name, lrr, rrr, lrr);
    E.push_instruction(I);
    if(Alocalreg* Q = dynamic_cast<Alocalreg*>(rrr))
      E.free_register(Q);

    return lrr;
  }
    
  Aarg* comparison::process(env &E)
  {
    static int label = 1000;
    Aarg* retR, * lrr, * rrr;
    
    label++;

    lrr = lhs->process(E);
    rrr = rhs->process(E);
    
    retR= E.get_register();
    // assume true, check for falsehood
    E.push_instruction(new Ainstruction("set", retR, new Aimval(1)));
    E.push_instruction(new Ainstruction("cmp", lrr, rrr));
    E.push_branch(new Ageneral("      " + instruction_name + "   c", label));
    E.push_instruction(new Ainstruction("set", retR, new Aimval(0)));
    E.push_instruction(new Ageneral(".c", label));
    
    E.free_register(lrr);
    E.free_register(rrr);

    return retR;
  }

  Aarg* multiplication::process(env &E)
  {
    static int label = 1000;
    label++;

    Aarg* lrr = lhs->process(E);
    Aarg* rrr = rhs->process(E);
    Aarg* cntr = Aarg::temp1;
    Aarg* retR = E.get_register();

    E.push_instruction(new Ainstruction("set", retR, new Aimval(0)));
    E.push_instruction(new Ainstruction("set", cntr, new Aimval(0)));
    E.push_instruction(new Ageneral(" .mulstart", label));
    E.push_instruction(new Ainstruction("cmp", rrr, cntr));
    E.push_branch(new Ageneral("      bge mulend", label));
    E.push_instruction(new Ainstruction("add", retR, rrr, retR));
    E.push_instruction(new Ainstruction("add", cntr, new Aimval(1), cntr));
    E.push_branch(new Ageneral("      ba mulstart", label));
    E.push_instruction(new Ageneral(" .mulend", label));

    E.free_register(lrr);
    E.free_register(rrr);

    return retR;
		       
  }
}
