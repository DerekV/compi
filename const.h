#ifndef __const_h_
#define __const_h_

#include "expression.h"
#include <string>


namespace ast
{

  class constant : public expression
    {  	 
	  
    };

  class stringconstant : public constant
    {
      // temporarily a dummy class of sorts
    public:
      stringconstant(string *s) :  data(s) 
	{po_string = "STRING CONSTANT" + *data;};
      
      virtual type check_types(env &E);

      string get_string();

    private:
      string* data;
    };

  class intconstant : public constant
    {
    public:
	intconstant(int i) : data(i) 
	  { po_string = "INT CONSTANT"; };

	virtual type check_types(env &E);
	virtual Aarg* process(env &E);

	int get_int();

	  
     private:
	int data;
    };


  // double check that floatconstant is being used
  class floatconstant : public constant
    {
    public:
      floatconstant(float f) : data(f) 
	{ po_string = "FLOAT CONSTANT"; };

      floatconstant(string *s);

      virtual type check_types(env &E);
      
      float get_float();

    private:
      float data;
    };

}


#endif
