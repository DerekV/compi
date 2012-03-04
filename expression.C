
#include "expression.h"
#include "type.h"

namespace ast
{

  string expression::poh() const
  { return '{' + po_string + '}'; }
  
  monoexpr::monoexpr(expression* ch)
     {
       child = ch;
       po_string = "()";
       children.push_back(child);
     }

  complement::complement(expression* nchild)
    :monoexpr(nchild)

  { 
    po_string += "!"; 
  };

   dualexpr::dualexpr(expression* left, expression* right, string in)
     : lhs(left), rhs(right), instruction_name(in) 
   {
     children.push_back(left);
     children.push_back(right);
   }

  comparison::comparison(expression* left, expression* right, string in) 
    : dualexpr(left,right,in)
  {
  }
  
   lessthan::lessthan(expression* left, expression* right)
     :comparison(left,right,"blt")
   {
     po_string="<";
   }

  greaterthan::greaterthan(expression* left, expression* right)
    : comparison(left,right,"bgt")
  {
    po_string="<";
  }

  equivalence::equivalence(expression* left, expression* right)
    : comparison(left,right,"be")
  { 
      po_string = "=" ;
  }

  mathop::mathop(expression* left, expression* right,string in)
    :dualexpr(left,right,in)
  {
  }
  
  addition::addition(expression* left, expression* right, bool isDifferance)
    : mathop(left,right,"add")
  {
    isNeg = isDifferance;
    isNeg ? po_string = "-" : po_string = "+";
  }  

    multiplication::multiplication(expression* left, expression* right)
      :mathop(left,right,"mult")
    {
      po_string = "*";
    } 

  modulus::modulus(expression* left, expression* right)
    :mathop(left, right,"mod")
  {  
    po_string = "MOD"; 
  } 
  

  logicop::logicop(expression* left, expression* right, string in)
    :dualexpr(left,right,in)
  {
  }
  
   logicaland::logicaland(expression* left, expression* right)
     :logicop(left,right,"and") 
   {
     po_string += "AND";
   }

  logicalor::logicalor(expression* left, expression* right)
    : logicop(left, right,"or")
  {
    po_string += "OR";
  }

}

