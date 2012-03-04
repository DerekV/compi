
#ifndef __expression_h_
#define __expression_h_

#include "node.h"


namespace ast
{
  class expression : public virtual node
    {

    protected:
      virtual string poh() const;
           
    public:
      

    };

  class monoexpr : public expression
    {
    public:
      monoexpr(expression* ch);
      virtual type check_types(env &E);

      virtual Aarg* process(env &E);

    protected:
      expression* child;
     
    };


  class complement : public monoexpr
    {
    public:
      complement(expression* nchild);
      
      virtual Aarg* process(env &E);
      virtual type check_types(env &E);
    };

      
  class dualexpr : public expression
    {
    protected:
      string instruction_name;

    public:
      dualexpr(expression* left, expression* right, string instruction_name);
   
      virtual Aarg* process(env &E);

    protected:
      expression* lhs;
      expression* rhs;
    };


  // what i would like to do later is extend this to include
  //  an actuall "negitive" operator

  class comparison : public dualexpr
    { 
     

    public:
      comparison(expression* left, expression* right, string inst_name);
      
      type check_types(env &E);
      Aarg* process(env &E);

    };

  class lessthan : public comparison
    {
    public:
      lessthan(expression* left, expression* right);
     
    };

  class greaterthan : public comparison
    {
    public:
      greaterthan(expression* left, expression* right);
     
    };

  class equivalence : public comparison
    {
    public:
      equivalence(expression* left, expression* right);
     
    };


  class mathop : public dualexpr
    {
    public:
      mathop(expression* left, expression* right,string in);
      virtual type check_types(env &E);
    };


  class addition : public mathop
    {
    public:
      addition(expression* left, expression* right, bool isDifferance);     
 
    private:
      bool isNeg;
    };


  class multiplication : public mathop
    {
    public:
      multiplication(expression* left, expression* right);  
      Aarg *process(env &E);

    };


  class modulus : public mathop
    {
    public:
      modulus(expression* left, expression* right); 
      
      virtual type check_types(env &E);
    };


  class logicop : public dualexpr
    {
    public:
      logicop(expression* left, expression* right, string in);

      type check_types(env &E); 

    };


  class logicaland : public logicop
    {
    public:
      logicaland(expression* left, expression* right);
      //  Aarg* process(env &E);

    };

  class logicalor : public logicop
    {
      static int labeln;
    public:
      logicalor(expression* left, expression* right);
      // Aarg* process(env &E);
    };

      

}

#endif
