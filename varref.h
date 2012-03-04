// contains : varrefs as well as subscripts

#ifndef __varref_h_
#define __varref_h_

#include"expression.h"
#include"instruction.h"  // only here for the VOID constant in get_offs dummy function
#include "node.h"

namespace ast
{
  class Aimval;  // why am I here?

  class varref : public expression
    {
      // temp. a dummy class of sorts
    public:
      varref(); //removeme

     varref(string *s) : data(s) 
       {po_string = "VAR REF on " + *data;};
     string get_name() const;

     virtual type check_types(env &E);
     virtual Aarg* process(env &E);
     Aarg* get_offs(env &E) { return new Aimval(02222); };

    private:
     string* data;

    };
  

  // this could be worked to inherit from dual expression
  // not sure what the advatages of that would be, in VOID anyways
  // anyways void.y expects it to inherit from varref 
  class subscript : public varref
    {
    public:
      subscript(varref* var, expression* exp);
      
      type check_types(env &E);

    private:
	varref* v;
	expression* index;
    };

}

#endif
