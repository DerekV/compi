#include "const.h"
#include "env.h"
#include "type.h"

namespace ast 
{

  // INT 
  type intconstant::check_types(env &E)
    { return tINTCONST; }

  // FLOAT
  type floatconstant::check_types(env &E)
    { return tFLOATCONST; }

  // STRING
  type stringconstant::check_types(env &E)
    { return tSTRING; }
}
