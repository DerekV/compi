
#include "type.h"
#include "statement.h"
#include "node.h"
#include "env.h"





namespace ast
{

  string statement::poh()
    { return "[" + po_string + "]"; }


  assignment::assignment(varref* left, expression* right)
  { 
    lval = left;
    rval = right;
    po_string = ":="; 
    children.push_back(lval);
    children.push_back(rval);
  }



  ifstatement::ifstatement(expression* condition,
		  statement* then_statement,
		  statement* else_statement = NULL)
  {
    cond = condition;
    ts = then_statement;
    es = else_statement;
    po_string = "IF";
    children.push_back(cond);
    children.push_back(ts);
    if(es) children.push_back(es);
  }

  whilestatement::whilestatement(expression* condition, statement* content)
  { 
    cond = condition;
    cont = content;
    po_string = "WHILE"; 
    children.push_back(cond);
    children.push_back(cont);
  };

  

   caseelement::caseelement(vector<constant*>* labels, statement* contents)
   { 
     lab = labels;
     cont = contents;
     po_string = "[CASE]"; 
     children.insert(children.end(), lab->begin(), lab->end());
     children.push_back(cont);  // this will function for now
   }

  casestatement::casestatement(expression* condition, vector<caseelement*>* _cases)
    : cond(condition), cases(_cases)
  {
    cond = condition;
    cases = _cases;
    po_string = "C.S.>";
    children.push_back(cond);
    children.insert(children.end(), cases->begin(), cases->end());
  }

  
  writestring::writestring::writestring(string* stringconst)
  {
    str = stringconst;
    po_string = "WRITE STRING CONSTANT (" + *str + ")";
  }

   write::write(expression* expr)
   {     
     val = expr;
     po_string = "WRITE ";   
     children.push_back(val);
   }
      
  read::read(varref* v)
  { 
    var = v;
    po_string = "READ"; 
    children.push_back(var);
  }

  returnstatement::returnstatement(expression* return_value)	
  { 
    val = return_value;
    po_string = "RETURN"; 
    children.push_back(val);
  }

  
  compound::compound(vector<statement*>* statements)
  { 
     slist = statements;
     po_string = "COMPOUND";
     children.insert(children.end(), slist->begin(), slist->end());
  }
  
  
  // =====================================================    check types
  

}
