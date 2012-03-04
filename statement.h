#ifndef __statement_h___
#define __statement_h___

#include "node.h"
#include "const.h"
#include "varref.h"
#include <vector>
#include <string>

namespace ast 
{
  class env;
  class type;
  class Aarg;

  class statement : public virtual node
    {
    protected:
      virtual string poh();
    };
  
  class assignment : public statement
    {
    public:
      assignment(varref* left, expression* right);
      
      virtual type check_types(env &E);
      virtual Aarg* process(env &E);

    private:
      varref* lval;
      expression* rval;
    };


  // maybe make an ifstatement and an ifelse statement seperate??
  class ifstatement : public statement
    {
    public:
      ifstatement(expression* condition,
		  statement* then_statement,
		  statement* else_statement = NULL);

      type check_types(env &E);
      Aarg* process(env &E);
	   
    private:

      static int iflabel;
      expression* cond;
      statement* ts;
      statement* es;	    
    };


  class whilestatement : public statement
    {
    public:
      whilestatement(expression* condition, statement* content);

      Aarg* process(env &E);

    private:
      expression* cond;
      statement* cont;
      static int wlabel;
    };


  class caseelement : public node // maybe it should inherit from node
    {
    public:
      caseelement(vector<constant*>* labels, statement* contents);
      
      // ADD A REAL TYPE CHECK FUNCTION!  dont know if this is graded(?)
      // thought is to have caseelement.check_types() resolve to type of constants
      // in label, i think

    private:
      vector<constant*>* lab;
      statement* cont;
    };


  class casestatement : public statement
    {
    public:
      casestatement(expression* condition, vector<caseelement*>* _cases);
		    
    private:
      vector<caseelement*>* cases;
      expression* cond;
      
    };

  

  class writestring : public statement
    {
    public:
      writestring(string* stringconst);


    private:
      string* str;
    };

  class write : public statement
    {
    public:
      write(expression* expr);
  
    private:
      expression* val;
    };

  class read : public statement
    {
    public:
      read(varref* v);

    private:
      varref* var;
    };


  class returnstatement : public statement
    {
    public:
      returnstatement(expression* return_value);

      type check_types(env &E);
      Aarg* process(env &E);
    private:
      expression* val;
    };


  class compound : public statement
    {
    public:
      compound(vector<statement*>* statements);

    private: 
      vector<statement*>* slist;
      
    };

}

#endif
