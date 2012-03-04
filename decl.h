
#ifndef __decl_h_
#define __decl_h_

#include <string>
#include "node.h"


namespace ast
{
  class type;
  typedef int reg;
  class Aimval;

  class decl : public node
    {
    public:
      decl(string s);
      
      virtual type   get_type() const = 0;
      virtual string get_name() const;

      // i dont know what this is.  i hope it isn't important.
      //           virtual void put_to(env &E, Aarg* a) = 0;

      virtual Aarg* put_reg(env &E);
       
    private:
      string name;
    };
  
  class vardecl : public decl 
    {
    public:
      vardecl(string* variable, type * itstype);
      
      virtual Aarg* put_reg(env &E);
      type get_type() const; 
      virtual string poh() const;
      
      virtual Aarg* process(env &E);
      //    virtual void put_to(env &E, Aarg* a);

    private:

      string mylabel;
      type* ty;
    };


  class paramdecl : public vardecl
    {

    public:
      
      paramdecl(string* v, type *t) : vardecl(v,t) {};
      Aarg* process(env &E);

      // Aarg* put_reg(env &E);
      // void put_to(env &E, Aarg* a);
    };
}


#endif
