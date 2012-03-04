#ifndef __itos_h_
#define __itos_h_


#include <string>

// this function returns a string from an integer
// i dont know how much it has been tested.
// i "found" it in instruction.C 
// while other files used strstream
// so here it is 
// now in its own header  


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ITOS ()

using std;

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


  
#endif 
