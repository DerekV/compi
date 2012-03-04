
#include "varref.h"
#include "env.h"
#include "decl.h"

namespace ast
{

  Aarg* varref::process(env &E)
  {
    decl* mydecl = E.get_decl_of(*data);

    if(!mydecl)
      {
	cout << *data << " not found. error." << endl;
	exit(1);
      }

    Aarg* myreg = mydecl->put_reg(E);

    return myreg;    
  }  


}
