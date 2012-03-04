
#ifndef __type_h_
#define __type_h_

#include<string>


namespace ast
{

  class type
    {
    public:
     
      type(string n, int type_int, bool is_const); 
     
      
      // constructor should be private, if that can be done somehow, 
      // really only the
      // copy constructer needs to be used outside the ast context
      
       string get_name() const;
      
      bool numberp()    const;
       bool floatp()     const;
       bool integerp()   const;
       bool arrayp()     const;
       bool charp()      const;
       bool stringp()    const;
       bool constp()     const;

      void set_subtype(type);
      inline const type get_subtype() const;

      inline int get_begin() const;
      inline int get_end() const;
      const type get_dimtype() const;

      void set_dim( int begin, int end, type dimtype );
	
      bool operator==(const type &lhs) const;
	      
      static type* new_array(type array_of, int begin, int end, type dimtype);

    private:
      const string name;
      int ty;
      type* subtype;
      type* dtype;
      int dbegin;
      int dend;
      bool cnst;
    };

  
  const type tSTRING("STRING", 5, false);
  const type tCHARCONST("CHARACTER", 3, true);
  const type tCHAR("CHARACTER", 3, false);
  const type tFLOATCONST("FLOAT", 2, true);
  const type tFLOAT("FLOAT", 2, false);
  const type tINTCONST("INTEGER", 1, true);
  const type tINTEGER("INTEGER", 1, false);
  const type tVOID("VOID", 0, false);
  const type tARRAYMODEL("ARRAY", 4, false);

}



#endif
