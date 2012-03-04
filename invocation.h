

#ifndef __invocation_h_
#define __invocation_h_

#include "expression.h"
#include "statement.h"

namespace ast 

{

  class invocation : public expression, public statement
    {

    public:
      invocation(string *s, vector<expression*>* arglist);
      type check_types(env &E);

    private:
      string* data;
      vector<expression*>* args;

    };
}


#endif
