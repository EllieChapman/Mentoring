#include <iostream>

// interface...
class Exp;

typedef Exp* exp; // wont compile
typedef int value;
static value eval(exp);
static std::string pp(exp);
static exp num(int);
static exp add(exp,exp);
static exp sub(exp,exp);
static exp less(exp,exp);
static exp ite(exp,exp,exp);
// EBC two new ways to constrict, binary < or >, and an if then else
// when done the exp below whould cmpile
// make eval and pp for two new exp

// add(num(1), ite(less(num(4), num(3)), num(2), num(4)))

void t(exp example, int expected) {
  printf("[%s] ", pp(example).c_str());
  int actual = eval(example);
  bool pass = actual == expected;
  if (pass) {
    printf("%d\n", actual);
  } else {
    printf("%d [expect:%d] FAIL\n", actual, expected);
  }
  if (!pass) std::abort();
}


// testing...
void test(void) {
  t(add(num(42),num(3)), 45);
  t(sub(sub(num(42),num(3)), num(5)), 34);
  t(sub(num(42), sub(num(3),num(5))), 44);
  t(less(num(5), num(4)), 0);
  t(ite(num(10), num(6), num(5)), 6);
  t(add(num(1), ite(less(num(4), num(3)), num(2), num(4))), 6);
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
    virtual value eval() = 0;
    virtual std::string pp() = 0;
};

class Num : public Exp
{
public:
    Num(int n) : _num(n) {}

    value eval()
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

class Add : public Exp
{
public:
    Add(exp a, exp b) : _a(a), _b(b) {}

    value eval()
    {
        return _a->eval() + _b->eval();
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

    value eval()
    {
        return _a->eval() - _b->eval();
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

    value eval()
    {
        return _a->eval() < _b->eval();
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

    value eval()
    {
        if (_a->eval())
        {
            return _b->eval();
        }
        else
        {
            return _c->eval();
        }
    }

    std::string pp()
    {
        // return "(" + _a->pp() + " < " + _b->pp() + ")";
        return "( if(" + _a->pp() + ") then(" + _b->pp() + ") else(" + _c->pp() + ") )";
        // return "ite";
    }
private:
    exp _a;
    exp _b;
    exp _c;
};

static value eval(exp e)
{
    return e->eval();
}
static std::string pp(exp e)
{
    return e->pp();
}
static exp num(int n)
{
    return new Num(n);
}
exp add(exp a,exp b)
{
    return new Add(a, b);
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



// EBC add sub node, mode onm add, 2 examples 42 -5 -7 with two types pf bracketing
