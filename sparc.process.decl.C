#include "decl.h"
#include "instruction.h"
#include "env.h"

namespace ast
{

  Aarg* decl::put_reg(env &E)  // decl incorrect place to implement
  {
    return new Aimval(42);
  }

  Aarg* vardecl::put_reg(env &E)
  {
    Aarg* addr = E.get_register();
    // put stuff for floats here
    E.push_instruction(new Ageneral("!  load var " + get_name() ));
    E.push_instruction(new Ainstruction("set", addr, Aarg::VOID)); 
    E.push_instruction(new Ainstruction("add", addr, addr, 
					new Aspecial("%fp")) );
    E.push_instruction(new Ainstruction("ld", addr, addr));
    return addr;
  }


  Aarg* vardecl::process(env &E)
  {
    
    E.push_instruction(new Ageneral(".align 4"));
    E.push_instruction(new Ageneral( mylabel ));  

    // maybe there should be an accessor function for my_label, for consistancy,	      
    // do some sort of memory map thing here
    return Aarg::VOID;
  }

  Aarg* paramdecl::process(env &E)
  {
    return Aarg::VOID;
  }



}
