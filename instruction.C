
#include <iostream>
#include "instruction.h"
#include <cstdlib>
#include <cmath>

namespace ast
{
  using namespace std;



  
  Aarg* Aarg::VOID = new Aspecial("VOID");
  Aarg* Aarg::temp1 = new Aspecialreg("g", 1);
  Aarg* Aarg::temp2 = new Aspecialreg("g", 2);
  Aarg* Aarg::temp3 = new Aspecialreg("g", 3);
  Aarg* Aarg::zero = new Aspecialreg("g", 0);
  
  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aLOCALREG //
  ////////////////////////////////////////////////////////////////////////////


  string Alocalreg::stringout()
  {
    return ("%r" + itos(get_num() + 16  ));
  }

  
  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aIMVAL    //
  ////////////////////////////////////////////////////////////////////////////

  string Aimval::stringout()
  {
    return itos(n);
  }


  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aMACRONAME//
  ////////////////////////////////////////////////////////////////////////////


  string Amacroname::stringout()
  {
    return w;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aSPECIAL  //
  ////////////////////////////////////////////////////////////////////////////

  string Aspecial::stringout()
  {
    return w;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////// CLASS aSPECIALREG//
  ////////////////////////////////////////////////////////////////////////////

  string Aspecialreg::stringout()
  {
    return ("%" + w + ( hasnum ? (itos(get_num())) : ("") ));
  }


  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aSTATMENT //
  ////////////////////////////////////////////////////////////////////////////

  inline bool Astatement::is_final()
  {
    return final;
  }

  inline void Astatement::set_final()
  {
    final = true;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aDIVIDER  //
  ////////////////////////////////////////////////////////////////////////////

  
  string Ageneral::stringout()
  {
    return (w);
  }

 

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aINSTRUCT //
  ////////////////////////////////////////////////////////////////////////////

  Ainstruction::Ainstruction(string inst, Aarg* res, Aarg* lhs, Aarg* rhs = NULL)
    : cmd(inst), left(lhs), right(rhs), result(res), Astatement()
  {}
  
  inline Aarg* Ainstruction::get_left()   {return left;}
  inline Aarg* Ainstruction::get_right()  {return right;}
  inline Aarg* Ainstruction::get_result() {return result;}


  // yet more function i wrote but will never use.
  // these set instructions would be a great place to use exceptions

  inline Aarg* Ainstruction::set_left(Aarg* real) 
  { if(!is_final()) left = real; /* else throw something */  }
  
  inline Aarg* Ainstruction::set_right(Aarg* real ) 
  { if(!is_final()) right = real; /* else throw something */}
  

  inline Aarg* Ainstruction::set_result(Aarg* real ) 
  { if(!is_final()) result = real; /* else throw something */} 



  string Ainstruction::stringout() 
  { 

    
    string s;

    /*
    s = cmd;
    s += "      r";
    s += itos(get_left());
    if(right >= -1)
      {
	s+= ",    r";
	s+= itos(get_right());
      }
    s += ",    r";
    s += itos( get_result() );
    */


    s = "      " + cmd + "      " 
      + get_left()->stringout();

    if(get_right())
      s += ",      " + get_right()->stringout();

    s += ",      " + get_result()->stringout();
      
    return s;
  } 
  
  string Ainstruction::get_cmd()
  { return cmd;}
  
  /////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aIMINST  //
  ///////////////////////////////////////////////////////////////////////////

  Aiminst::Aiminst(string inst, Aarg* result, Aimval* lhs, Aarg* rhs = NULL)
    : Ainstruction(inst, result, lhs, rhs) {};
  
  string Aiminst::stringout()
  {
    string s;
    s = "      " + get_cmd() + "      " + get_left()->stringout();
    if(get_right())
      {
	s+= ",      " + get_right()->stringout();
      }
    s += ",      " + get_result()->stringout();

    return s;
  }



  /////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////CLASS aDEFINE  //
  ///////////////////////////////////////////////////////////////////////////

  string Adefine::stringout()
  {
    return ("define(" + macro + ", " + target);

  }


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ITOS ()


  string itos(int num)
  {
    
    if(num < 0)
      {
	string s;
	s = "-";
	s += itos( abs(num) );
	return s;
      }
    else if (num < 10)
      {
	switch(num)
	  {
	  case 0: return "0"; 
	  case 1: return "1"; 
	  case 2: return "2";
	  case 3: return "3";
	  case 4: return "4";
	  case 5: return "5";
	  case 6: return "6";
	  case 7: return "7";
	  case 8: return "8"; 
	  case 9: return "9"; 
	  }
      }
    else 
      {
	string s;
	s = itos( (int) floor(num / 10) ) + itos( (int)(num % 10));
	return s;
      }
  }


  
}
