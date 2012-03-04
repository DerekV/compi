

#include "node.h"
#include "env.h"
#include "type.h"
#include "instruction.h"

/* The premis is that an abstract syntax tree will be made up of nodes.
   This sets up the interface for a node and some basic default virtual
   functions.  Several of these work in a tree search fasion.  Generally,
   you reimplement these functions in your child class, then call the 
   node version, to get the default behavior, which is, to go down the 
   tree.  It all depends on what your doing.

   A better way to seperate node types from passes would be cool,
   so adding passes would look cleaner in the code, if nothing
   else.

   Passes: (as they stand at the moment.  not enough thought has been put into
            these with respect to the overall goals of the project.)

   check_types : performs type checking
   printout : prints the AST out to stdout in a human readable (sorta) format.
   resolve : prep the tree for the final translation stages
   process : final translation back into a flat form, in the new language

   string related functions, mostly for the printout functionality
*/ 


namespace ast 
{

  node::node() { };
 
  type node::check_types(env &E) 
  {
    for( int i = 0; i < children.size(); i++)
      children[i]->check_types(E); 
    return tVOID;      
  }
  
  string node::poh() const 
  {
    if(!po_string.empty())
      return po_string;
    
    cout << "INTERNAL ERROR: BAD PO STRING!" << endl;	

    exit(1);
  }
  
  void node::printout(int indent )
  { 
    string s;
    s.append(indent, ' ');
    cout << s << po_arrow;
    cout << poh();
    cout << endl;
    
    for( int i = 0; i < children.size(); i++)
      children[i]->printout(indent + po_indent);
  }
  
  node* node::resolve(env &E) 
  {
    for( int i = 0; i < children.size(); i++) 
	children[i]->resolve(E);
  }

  string node::get_short_description() 
  {
    return poh();
  }
  
  Aarg* node::process(env &E)
  {
    for( int i = 0; i < children.size(); i++)
      {
	children[i]->process(E);
      }
    return new Aspecial("VOID");
  }
    
}



/* ************* node.c test "main" function
int main ( )
{
  ast::node nnode;
  ast::env E;

  nnode.printout(3);
  cout << endl;
  cout << (nnode.check_types(E)).get_name();
  cout << endl;
  cout << ast::tVOID.get_name() << endl;

}
*/
