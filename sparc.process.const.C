#include "const.h"
#include "instruction.h"
#include "env.h"

namespace ast
{

  Aarg* intconstant::process(env &E)
  {
    Ainstruction *n = new Aiminst("set", E.get_register(),
				  new Aimval(data));
    E.push_instruction(n);
    return n->get_result();
  }

  // FLOATS
  //  uses default (right now)

  // strings
  //  uses defaults (right now)

}
