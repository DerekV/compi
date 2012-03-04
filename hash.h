
#ifndef __HASH_H____
#define __HASH_H____

#include<vector>
#include<string>


// this wont behave well at all with 0 legnth strings
// could generalise this to any containers as the key


using namespace std;

template <class _data>
class stringhash
{
  
  struct node
    {
      node* next;
      string key;
      _data data;
    };


 public:

  stringhash();

  stringhash(int tsize);


  _data find(const string &k);

  void add(const string &k, _data d);
  
  vector<_data> get_vector(); // this is a cheap hack, 
  // since I dont really have much time at this point to define an iterator
  // like i should

 private:

  const int tab_size;
  static const int default_tab_size (200);
  
  typedef vector<node*>::iterator nvitor; 

  vector<node*> tab;
 
  nvitor hash(const string &k);
  
  node* getit(const string &k); 
  

};




//template <class _data>
//typedef vector<stringhash<_data>::node*>::iterator stringhash<_data>::nvitor;
// dont know if this is nessisary

template <class _data>
stringhash<_data>::stringhash<_data>(void) 
  : tab_size(default_tab_size), tab(default_tab_size, (node*)NULL)
    {return; }


template <class _data>
stringhash<_data>::stringhash<_data>(int tsize) : tab_size(tsize), tab(tsize, (node*)NULL)
    { }

template <class _data>
_data stringhash<_data>::find(const string &k)
    {
      node* n = getit(k);
      if(n)
	return n->data;

      else return NULL;
    }



template <class _data>
void stringhash<_data>::add(const string &k, _data d)
{
  nvitor tab_location = hash(k);
  node* nw = new node;
  nw->data = d;
  nw->key = k;
  nw->next = *tab_location;
  
  *tab_location = nw;
}


template <class _data>
stringhash<_data>::nvitor stringhash<_data>::hash(const string &k)
{
  // the &tab[] method on vectors is probably bad STL usage style, 
  //  but should work.  the alternitive is tab.begin() + n which looks silly

  return &tab[
	      ( (int)*(k.data())  
		- 20 ) 
	      % tab_size  ];
  
}



template <class _data>
stringhash<_data>::node * stringhash<_data>::getit(const string &k)
{
  node* fst = *(hash(k));
 
  while(fst)
    {
      if( fst->key == k )
	break;
      
      fst = fst->next;
    }
  
  return fst;
}

template< class _data>
vector<_data> stringhash<_data>::get_vector(void)
{
  vector<_data> retval;

  for(vector<node*>::iterator i = tab.begin(); i != tab.end(); i++)
    {
      node* t = *i;
      while(t)
	{
	  retval.push_back(t->data);
	  t = t->next;
	}
      
    }

  return retval;
}

#endif
