#include <iostream>

// interface...
class Exp;

typedef Exp* exp; // wont compile
typedef int value;
static value eval(exp);
static exp num(int);
static exp add(exp,exp);
static exp sub(exp,exp);

// testing...
void test(void) {
  exp example1 = add(num(42),num(3));
  exp example2 = sub(sub(num(42),num(3)), num(5));
  exp example3 = sub(num(42), sub(num(3),num(5)));
//   exp example2 = num(3);
  int result = eval(example1);
  printf("result: %d\n", result);

  int result2 = eval(example2);
  printf("result: %d\n", result2);

  int result3 = eval(example3);
  printf("result: %d\n", result3);
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
};

class Num : public Exp
{
public:
    Num(int n) : _num(n) {}

    value eval()
    {
        return _num;
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
private:
    exp _a;
    exp _b;
};

static value eval(exp e)
{
    return e->eval();
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



// EBC add sub node, mode onm add, 2 examples 42 -5 -7 with two types pf bracketing