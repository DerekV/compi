// just bunches everything together, for what purpose, i dunno

#ifndef __AST_H
#define  __AST_H

#include<string>
#include<sstream>
#include<vector> 
#include<iostream>


#include"node.h"
#include"expression.h"
#include"statement.h"
#include"invocation.h"
#include"env.h"
#include"progseg.h"
#include"decl.h"
#include"type.h"
#include"const.h"
#include"varref.h"
#include"regprocessor.h"


namespace ast
{
  
  program* gprog;
  
}  

#endif
