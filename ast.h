#ifndef _AST_H
#define _AST_H

#include <string.h>

class Exp;
class Env;

typedef Exp* exp;
typedef int value;
typedef std::string name;
typedef Env* env;

value eval(exp, env);
std::string pp(exp);
exp num(int);
exp add(exp,exp);
exp sub(exp,exp);
exp mul(exp,exp);
exp less(exp,exp);
exp ite(exp,exp,exp);
exp var(name);
env empty();
env extend(env, name, value);
value lookup(env, name);
exp let(name bound, exp rhs, exp body);
exp call1(name f,exp arg); // f(arg)


class Program;
typedef Program* program;
class Defs;
typedef Defs* defs;
class Def;
typedef Def* def;


program makeProgram(defs, exp main);
defs nilDefs();
defs consDefs(def,defs);
def def1(name func_name, name arg, exp body);
value execute(program);



#endif