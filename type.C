
#include "type.h"
#include "decl.h"



namespace ast
{
    type::type(string n, int type_int, bool is_const) 
      : name(n), dbegin(0), dend(0), ty(type_int), 
	subtype(NULL), dtype(NULL), cnst(false)
    { }

  /*
  type::type(const ast::type &cloneme)
    : name(cloneme.name), dbegin(cloneme.dbegin),
      dend(cloneme.dend), dtype(cloneme.dtype),
      ty(cloneme.ty), subtype(cloneme.subtype),
      cnst(cloneme.cnst)
  {};
  */
  
  string type::get_name() const
  {
    
    if(name.empty())
      {
	cout << "INTERNAL ERROR: bad type name." << endl;
	exit(1);
      }

    string s(name);
   
    if( ty == 4 )
      {
	s += " [" ;
	s +=   dbegin;
	s += "..";
	s +=  dend;
	s += "] of ";
	s += subtype->get_name();
      }

    return s; 
    
  }
  
  
  bool type::numberp()        const { return ((ty == 1) || (ty == 2));}
  bool type::floatp()         const { return (ty == 2);}
  bool type::integerp()       const { return (ty == 1);}
  bool type::arrayp()         const { return (ty == 4);}
  bool type::charp()          const { return (ty == 3);}
  bool type::stringp()        const { return (ty == 5);}
  bool type::constp()            const { return cnst; }
  const type type::get_subtype() const { return *subtype; }
  int  type::get_begin()         const { return dbegin; }
  int  type::get_end()           const { return dend; }
  const type type::get_dimtype() const { return *dtype; }
  
  
  void type::set_dim( int begin, int end, type dimtype )
  { 
    dbegin = begin;
    dend = end;
    dtype = &dimtype;
  }
  
  void type::set_subtype(type t)
  {
    subtype = &t;
  }
  
  bool type::operator==(const type &lhs) const 
  { 
    if( ty == lhs.ty )
      {
	if( ty == 4 )
	  {
	    if( !subtype )
	      if( !lhs.subtype )
		if( get_subtype() == lhs.get_subtype() )
		  return true;
	  }
	else return true;  // types are equal, and not arrays
      }
  
    return false;
  }

  type* type::new_array(type array_of, int begin, int end, type dimtype)
  { 
    type* t = new type(tARRAYMODEL); 
    t->set_subtype(array_of);
    t->set_dim( begin, end, dimtype);
    return t;
  }

}


