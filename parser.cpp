#include "parser.h"
#include "ast.h"

static void crash(std::string mes)
{
  printf("CRASH: %s\n", mes.c_str());
  fflush(stdout);
  abort();
}

static void parse_crash(std::string tag, Token token)
{
    crash(tag + "   Token: " + "   Start: " + std::to_string(token.start_pos()) + "   End: " + std::to_string(token.end_pos()) + "   Kind: " + showKind(token.kind()) + "   Text: '" + token.text() + "'");
}

program parse_program(LexState&)
{
    crash("undefined parse_program!");
    return 0;
}

Kind peek_token(LexState ls) { // **no '&'; state unchanged
  Token tok = ls.get_token();
  return tok.kind();
}


// EBC do opther binop
// EBC switch up for program level, uses parser for expressions
// EBC probs want expect_token(Kind k) utility funciton
// EBC want peek_token whihc is lik eget_token but dowsnst take referece
exp parse_expression(LexState &lx)
{
    Token t = lx.get_token();

    switch(t.kind())
    {
        case Identifier:
            return var(t.text());
        case Number:
            int i;
            sscanf(t.text().c_str(), "%d", &i);
            return num(i);
        case LP:
        {
            exp eleft = parse_expression(lx);
            Token t = lx.get_token();
            switch (t.kind())
            {
                case Plus:
                {
                    exp eright = parse_expression(lx);
                    Token t = lx.get_token();
                    if (t.kind() != RP)
                    {
                        parse_crash("expected RP ", t);
                    }
                    return add(eleft, eright);
                }
                default:
                    parse_crash("Expected binop: ", t);
            }
        }
        default:
            parse_crash("EXP: ", t);

    }

    crash("undefined parse_expression!");
    return 0;
}

