
#include "progseg.h"
#include "env.h"
#include "type.h"


namespace ast

{
  
  programseg::programseg(string *n, vector<decl*>* dl, compound* mn): decl(*n)
  {  
    declist = dl;
    mp = mn;
    children.insert(children.end(), declist->begin(), declist->end());
    children.insert(children.end(), mp);
    po_string = "(SUB)PROGRAM : " + get_name();
  }

  subprogram::subprogram(string *n, vector<decl*>* dl, compound* mn, 
			 vector<decl*>* parameter_list,
			 type* ret_type)
    : programseg(n, dl, mn), rt(ret_type), pl(parameter_list)
  {
    children.insert(children.end(), pl->begin(), pl->end());
    po_string = "SUBPROGRAM : " + get_name();
  }
  
   program::program(string *n, vector<decl*>* dl, vector<subprogram*>* spl, 
	      compound* mn) 
     : programseg(n, dl, mn), splist(spl)
   {
     children.insert(children.end(), spl->begin(), spl->end());  
     po_string = "MAIN PROGRAM : " + get_name();
   };
  
  type subprogram::get_type() const
    {return *rt;};
  
  type program::get_type() const
    { return tVOID; };

   

}
