
#ifndef __env_h_
#define __env_h_

#include <string>
#include <iostream>
#include <list>
#include "instruction.h"
#include "hash.h"


namespace ast
{
  class decl;
  class type;
  class regprocessor;
  
  
  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////// CLASS ENV
  ////////////////////////////////////////////////////////////////////////////////
  // This is ment to be used as a singleton class, i think, its one design issue
  // in this program I am sketchy on.  The other option is to make it a module
  // in the spirit of c, using the .h/.C to achive data hiding.

  class env 
    {
      
      // ====================================================== \\
      //  ================ SCOPE FUNCTIONS ==================== \\   
      // ====================================================== \\
      
      class scope
	{
	  stringhash<decl*> data;
	  scope* parent;
	  
	  
	public:
	  scope(scope* P) : parent(P) {};
	  scope() : parent(NULL) {};
	  ~scope();
	  
	  scope* branch();
	  scope* get_parent() { return parent; };
	
	  decl* lookup(string &msg);
	  void add_to(decl*);
	  void add_set(vector<decl*> &dset);
	  type get_type_of(string);
	};
      
      scope* curscope;

    public:
      
      void new_scope();
      void release_scope();
      
      void add_to(decl*);
      void add_set(vector<decl*> &dset);
      
      decl* get_decl_of(string msg);
      type  get_type_of(string msg);
      
      // ====================================================== \\
      // ================== OUTPUT FUNCTIONS ================== \\
      // ====================================================== \\
  
    private:

      ostream *dataout;
      ostream *textout;
      ostream *errorout;
      
      list<Astatement*> dribble;
      

    public:
      ostream* tout(); // evetually, theses should be replaced
      ostream* eout();
      
      void push_instruction(Astatement *);
      void push_branch(Astatement *);
      // ====================================================== \\
      // =========== REGISTER PROCESSING FUNCTIONS ============ \\
      // ====================================================== \\
    
    private: 
      regprocessor* roracle; 
     
    public: 
      void set_regprocessor(regprocessor *);
      
      Aarg* get_register(); // maybe these should be private
      void free_register(Aarg*);
      
      
      // ====================================================== \\
      // =========== INIT/FINAL-IZATION FUNCTIONS ============= \\
      // ====================================================== \\
   
      env(
	  ostream *standard_out,
	  ostream *data_out,
	  ostream *error_out,
	  regprocessor *regoracle );

      ~env();

      void finalize();

      
    };

}



#endif

