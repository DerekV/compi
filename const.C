
#include "const.h"
#include "env.h"
#include "type.h"
#include <strstream> // how ugly ... used by floatconstant::floatconstant only

namespace ast
{

  int intconstant::get_int()
  { return data; }

  string stringconstant::get_string()
  { return *data; }

  floatconstant::floatconstant(string *s)
  {
    strstream ss;
    ss << *s;
    ss >> data;
  }

  float floatconstant::get_float()
  { return data; }

}
