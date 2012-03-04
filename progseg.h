

#ifndef __progseg_h_
#define __progseg_h_

#include "node.h"
#include "statement.h"
#include "decl.h"
#include <vector>
#include <string>


namespace ast
{

  class type;
  class env;


  class programseg : public decl
    {
    public:
      programseg(string *n, vector<decl*>* dl, compound* mn);
      virtual type check_types(env &E);
      virtual Aarg* process(env &e);

    protected:  // not great
      vector<decl*>* declist;

    private:
      compound* mp;
    };
  
  
  class subprogram : public programseg
    {
    public:
      subprogram(string *n, vector<decl*>* dl, compound* mn, 
		 vector<decl*>* parameter_list,
		 type* ret_type);
      
      
      virtual type check_types(env &E);
      type get_type() const;
      virtual Aarg* process(env &e);


    private:
      type* rt;
      vector<decl*>* pl;
    };


  class program : public programseg
    {
    public:
      program(string *n, vector<decl*>* dl, vector<subprogram*>* spl, 
	      compound* mn);
      
      type get_type() const; // just to make it non virtual
      
      virtual type check_types(env &E);
      virtual Aarg* process(env &e);

    private:
      vector<subprogram*>* splist;
    
    };
 

}


#endif
