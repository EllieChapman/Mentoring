#include <iostream>

// interface...
class Exp;
class Env;

typedef Exp* exp;
typedef int value;
typedef std::string name;
typedef Env* env;

static value eval(exp, env);
static std::string pp(exp);
static exp num(int);
static exp add(exp,exp);
static exp sub(exp,exp);
static exp less(exp,exp);
static exp ite(exp,exp,exp);
static exp var(name);
static env empty();
static env extend(env, name, value);
static value lookup(env, name);
static exp let(name bound, exp rhs, exp body);


void t_env(exp example, int expected, env env) {
  printf("[%s] ", pp(example).c_str());
  int actual = eval(example, env); // EBC todo, need to test woth multip envs
  bool pass = actual == expected;
  if (pass) {
    printf("%d\n", actual);
  } else {
    printf("%d [expect:%d] FAIL\n", actual, expected);
  }
  if (!pass) std::abort();
}

void t(exp example, int expected)
{
    return t_env(example, expected, empty());
}

// testing...
void test(void) {
    t ( let("x", add(num(39),num(3)), add(num(100),var("x"))), 142 );
    t ( let ("x", num(3), let("x", add(var("x"),var("x")), add(var("x"),var("x")))), 12);
    t ( let ("x", let("x", num(4), add(var("x"),var("x"))), let("x", add(var("x"),var("x")), add(var("x"),var("x")))), 32);
    exp e1 = add(num(1), var("x"));
    exp e2 = add(var("x"), var("y"));
    env env1 = extend(empty(), "x", 5);
    env env2 = extend(empty(), "x", 6);
    env env3 = extend(env2, "y", 10);
    env env4 = extend(env3, "x", 500);
    t_env(e1, 6, env1);
    t_env(e1, 7, env2);
    t_env(e2, 16, env3);
    t_env(e2, 510, env4);
    t(add(num(42),num(3)), 45);
    t(sub(sub(num(42),num(3)), num(5)), 34);
    t(sub(num(42), sub(num(3),num(5))), 44);
    t(less(num(5), num(4)), 0);
    t(ite(num(10), num(6), num(5)), 6);
    t(add(num(1), ite(less(num(4), num(3)), num(2), num(4))), 5);
}

int main()
{
    std::cout << "c-interpreter" << std::endl;
    test();
    return 0;
}

class Exp
{
public:
    virtual value eval(env) = 0;
    virtual std::string pp() = 0;
};

class Num : public Exp
{
public:
    Num(int n) : _num(n) {}

    value eval(env)
    {
        return _num;
    }

    std::string pp()
    {
        return std::to_string(_num);
    }
private:
    int _num;
};

class Var : public Exp
{
public:
    Var(std::string s) : _name(s) {}

    value eval(env env)
    {
        return lookup(env, _name);
    }

    std::string pp()
    {
        return _name;
    }
private:
    std::string _name;
};

class Add : public Exp
{
public:
    Add(exp a, exp b) : _a(a), _b(b) {}

    value eval(env env)
    {
        return _a->eval(env) + _b->eval(env);
    }

    std::string pp()
    {
        return "(" + _a->pp() + " + " + _b->pp() + ")";
    }
private:
    exp _a;
    exp _b;
};

class Sub : public Exp
{
public:
    Sub(exp a, exp b) : _a(a), _b(b) {}

    value eval(env env)
    {
        return _a->eval(env) - _b->eval(env);
    }

    std::string pp()
    {
        return "(" + _a->pp() + " - " + _b->pp() + ")";
    }
private:
    exp _a;
    exp _b;
};

class Less : public Exp
{
public:
    Less(exp a, exp b) : _a(a), _b(b) {}

    value eval(env env)
    {
        return _a->eval(env) < _b->eval(env);
    }

    std::string pp()
    {
        return "(" + _a->pp() + " < " + _b->pp() + ")";
    }
private:
    exp _a;
    exp _b;
};

class Ite : public Exp
{
public:
    Ite(exp a, exp b, exp c) : _a(a), _b(b), _c(c) {}

    value eval(env env)
    {
        if (_a->eval(env))
        {
            return _b->eval(env);
        }
        else
        {
            return _c->eval(env);
        }
    }

    std::string pp()
    {
        return "( if(" + _a->pp() + ") then(" + _b->pp() + ") else(" + _c->pp() + ") )";
    }
private:
    exp _a;
    exp _b;
    exp _c;
};

class Let : public Exp
{
public:
    Let(name x, exp rhs, exp body) : _x(x), _rhs(rhs), _body(body) {}

    value eval(env env1)
    {
        value v = _rhs->eval(env1);
        env env2 = extend(env1, _x, v);
        return _body->eval(env2);
    }

    std::string pp()
    {
        return "let " + _x + " = " + _rhs->pp() + " in " + _body->pp();
    }
private:
    name _x;
    exp _rhs;
    exp _body;
};

static value eval(exp e, env env)
{
    return e->eval(env);
}
static std::string pp(exp e)
{
    return e->pp();
}
static exp num(int n)
{
    return new Num(n);
}
static exp var(std::string s)
{
    return new Var(s);
}
// EBC genrlaie binary operator stuff, only need to extend enum
exp add(exp a,exp b)
{
    return new Add(a, b);
    // return new binop(a,b,+)
}
exp sub(exp a, exp b)
{
    return new Sub(a, b);
}
exp less(exp a, exp b)
{
    return new Less(a, b);
}
exp ite(exp a, exp b, exp c)
{
    return new Ite(a, b, c);
}
exp let(name bound, exp rhs, exp body)
{
    return new Let(bound, rhs, body);
}


class Env
{
public:
    virtual value lookup(name) = 0;
};

class ExtendedEnv : public Env
{
public:
    ExtendedEnv(env env, name name, value value) : _env(env), _name(name), _value(value) {}

    value lookup(name key)
    {
        if(_name == key)
        {
            return _value;
        }
        else
        {
            return _env->lookup(key);
        }
    }
private:
    env _env;
    name _name;
    value _value;
};

class EmptyEnv : public Env
{
public:
    EmptyEnv() {}

    value lookup(name key)
    {
        std::cout << "Attemt to look up variable '" << key << "' in empty environment failed!" << std::endl;
        std::abort();
    }
};

env empty()
{
    return new EmptyEnv();
}
env extend(env env, name name, value value)
{
    return new ExtendedEnv(env, name, value);
}
value lookup(env env, name name)
{
    return env->lookup(name);
}
