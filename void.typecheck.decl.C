#include "decl.h"
#include "type.h"

namespace ast 
{
// DECL 
//    use default (parent)

// VARDECL   
  type vardecl::get_type() const
    {return *ty;}
}
