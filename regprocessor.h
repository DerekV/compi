#ifndef __regprocessor__h__
#define __regprocessor__h__


namespace ast
{
  const int maxreg = 6;


  class Alocalreg;
  class Aarg;

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////// CLASS REGPROCESSOR
  ////////////////////////////////////////////////////////////////////////////////
  class regprocessor
    {
    public:
      virtual Aarg* get_reg() = 0;
      virtual void free_reg(Alocalreg* w) = 0;
      virtual void final_pass() = 0;
  };
  
  class qdregprocessor : public regprocessor
  { 
    bool reglist[maxreg];
    
  public:
    qdregprocessor();
    
    Aarg* get_reg();      
    void free_reg(Alocalreg* w);
    void final_pass();
  };

}
#endif
