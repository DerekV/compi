
#include "env.h"
#include "regprocessor.h"
#include "node.h"
#include "decl.h"
#include "progseg.h"
#include "type.h"

int yyparse(void);

namespace ast
{
  extern program *gprog;
}

/* Explination o' dis mojo
   regprocessor is a class that defines a registry allocator.
   qdregprocessor implements this class with a quick-and-dirty solution
     (see the respective files)
    
   the class env (see env.h env.C) basicly stands as a place to puts information
     that would other wise have been global variables, since it may be needed anywhere
     while building the tree.  The advantage of this is that on tree traversals, the env
     is passed instead of reffered to as global, so that, the enviroment can change as the
     tree is decended, without effecting sibling nodes, much like a unix enviroment.

   ast is the namespace for all things relating to the abstract syntax tree

   check types, process, finalize, printout, are all tree traversal functions.

   qprog is a global variable (this might be changed), that represents the root node of the tree.

   all the couts got to go, or move them to a better system, eventually
*/

main()
{	
  ast::qdregprocessor *qd = new ast::qdregprocessor;  // registry processors allocate registers, 
                                                                                        
  ast::env E((ostream *)&cout, (ostream *)&cout, (ostream *)&cout, qd);  
  cout << "PARSING NOW" << endl;
  yyparse();

  if(ast::gprog)
  {
    cout << "PRINTOUT" << endl;
    ast::gprog->printout(0);

    /* Should make this a command line option.
       ALSO! there is an issue with the scope.  since env declairs the first
       scope, check types and process share it, and try to add the same 
       global vars to it twice */
    
    
    cout << endl << "TYPE CHECKING ... " << endl;

    ast::gprog->check_types(E);

    cout << endl << "PROCESSING NOW ... " << endl;
   
    E.new_scope();
    ast::gprog->process(E); // using same E is ok?
    E.release_scope();

    cout << endl << "ASSEMBLY OUTPUT -->>" << endl;
    
    E.finalize();
    
  }

  else  
    {
      cout << "Parse error: aborting" << endl;
      return 1;
    }  

}
