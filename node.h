

#ifndef __node_h___
#define __node_h___

#include <string>
#include <vector>
#include <list>

namespace ast {
  using namespace std;
  class env;
  class type;
  class Aarg;

  const string po_arrow("--->");
  const int po_indent = 4;

  class node
    {
    public: 

      
      node();


      // Traversal functions ----
      virtual type check_types(env &E);
      void printout(int I);
      virtual node* resolve(env &E);
      virtual Aarg* process(env &E);
      
      // ------------------------

      string get_short_description();

      //bool is_resolved();
      //bool is_type_ok();
      

    protected:
      

      virtual string poh() const;


      vector<node* > children;
      string po_string;
    };
  
  
}
  
  



#endif
