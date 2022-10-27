#include "parser.h"
#include "ast.h"
#include <iostream>

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


Kind peek_token(LexState ls) { // **no '&'; state unchanged
  Token tok = ls.get_token();
  return tok.kind();
}


// EBC need to add if then else, will also have to add them as token types to be lexed
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
                case Dash:
                {
                    exp eright = parse_expression(lx);
                    Token t = lx.get_token();
                    if (t.kind() != RP)
                    {
                        parse_crash("expected RP ", t);
                    }
                    return sub(eleft, eright);
                }
                case Star:
                {
                    exp eright = parse_expression(lx);
                    Token t = lx.get_token();
                    if (t.kind() != RP)
                    {
                        parse_crash("expected RP ", t);
                    }
                    return mul(eleft, eright);
                }
                // EBC really need to add div to whole thing at some point
                default:
                    parse_crash("Expected binop: ", t);
            }
        }
        // add case if here
        // "if" expression "then" expression "else" expression
        case If:
        {
            exp e1 = parse_expression(lx);
            Token t = lx.get_token();
            if (t.kind() != Then)
            {
                parse_crash("expected Then ", t);
            }
            exp e2 = parse_expression(lx);
            t = lx.get_token();
            if (t.kind() != Else)
            {
                parse_crash("expected Else ", t);
            }
            exp e3 = parse_expression(lx);
            return ite(e1, e2, e3);
        }
        default:
            parse_crash("EXP: ", t);

    }

    crash("undefined parse_expression!");
    return 0;
}


// EBC switch up for program level, uses parser for expressions
// EBC probs want expect_token(Kind k) utility funciton
// EBC want peek_token whihc is lik eget_token but dowsnst take referece
program parse_program(LexState &lx)
{
    // when starting to parse program we either have a definition, or an expression.
    // peek to see if next token if type Def
        // if so parse def
    // else remaining if exp, so call parse_exp
    crash("undefined parse_program!");
    return 0;
}