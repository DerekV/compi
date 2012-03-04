


// This defines two classes for assembly instructions,
// Astatment, which uses the other class Aarg,
// both have stringout function, but are both toplevel parent classes

#ifndef __inStRuction_h__
#define __inStRuction_h__

#include <string>

namespace ast
{

  string itos(int);


  /////////////////////////////////////////////////////////////////////////
  class Aarg
    {
    public:
      virtual string stringout() = 0;
      
      static Aarg* VOID;
      static Aarg* temp1;
      static Aarg* temp2;
      static Aarg* temp3;
      static Aarg* zero;
    };
  
  class Areg : public Aarg
    {

      int n;
    public:
      Areg(int N) : n(N) {};
      int get_num() {return n;};
      void set_num(int N) {n = N;};

    };

  class Alocalreg : public Areg
    {
    public:
      Alocalreg(int N) : Areg(N) {};

      virtual string stringout();
      bool operator==(Alocalreg rhs) { return get_num() == rhs.get_num(); };
    };

  class Aspecial : public Aarg
    {
      string w;
      
    public:
      Aspecial(string W) : w(W) {};
      Aspecial(string W, int N) { w = W + itos(N); }
      Aspecial(int N) { w = itos(N);}

      virtual string stringout();
    };

  class Aspecialreg : public Areg
    {
      string w;
      bool hasnum;
      
    public:
      Aspecialreg(string W, int N) : w(W), Areg(N), hasnum(true) {};
      Aspecialreg(string W) : w(W), Areg(-1), hasnum(false) {};

      
      virtual string stringout();
    };

  class Aimval : public Aarg
    {
      int n;

    public:
      Aimval(int N) : n(N) {};
      virtual string stringout();
    };

  class Amacroname : public Aarg
    {
      string w;
    public:
      Amacroname(string W) : w(W) {};
      virtual string stringout();
    };
  
  /////////////////////////////////////////////////////////////////////////////
  class Astatement
    {
      bool final;

    public:
      Astatement() {final = false;};
      
      virtual string stringout() = 0;
      
      virtual bool is_final();
      virtual void set_final();
    };

  class Ageneral : public Astatement
    {
      string w;

    public:
      Ageneral(string W) : w(W), Astatement() {};
      Ageneral(string W, int N) { w = W + itos(N) ;};
      Ageneral( int N) { w = itos(N); };
      virtual string stringout();
     
    };

  class Ainstruction : public Astatement
    {
      Aarg* left;
      Aarg* right;
      Aarg* result;
      string cmd;
            
    public:
      Ainstruction(string inst, Aarg* result, Aarg* lhs, Aarg* rhs = NULL);
      
      
      virtual Aarg* get_left();
      virtual Aarg* get_right();
      virtual Aarg* get_result();
      virtual string get_cmd();

      virtual Aarg* set_left( Aarg* );
      virtual Aarg* set_right( Aarg* );
      virtual Aarg* set_result( Aarg* );
      virtual string stringout();
    };

  class Aiminst : public Ainstruction
    {
    public:
      Aiminst(string inst, Aarg* result, Aimval* lhs, Aarg* rhs = NULL);      
      virtual string stringout();

    };


  class Adefine : public Astatement
    {
      string macro;
      string target;

    public:
      Adefine(string M, string T) : macro(M), target(T) {};
      
      virtual string stringout();
    };

  
}




#endif
