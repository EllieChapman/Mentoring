#include "lexer.h"
#include <iostream>

std::string showKind(Kind k)
{
    switch(k)
    {
        kind_to_string(NoMoreToken);
        kind_to_string(UnknownCharacter);
        kind_to_string(Identifier);
        kind_to_string(LP);
        kind_to_string(RP);
        kind_to_string(Plus);
    }
    assert(false);
}

static bool isWhite(char c)
{
    return (c == ' ') || (c == '\n');
}

static bool isIdentStart(char c)
{
    return (('a'<=c) && (c<='z')) || (('A'<=c) && (c<='Z')) || (c == '_');
}

static bool isIdentContinue(char c)
{
    return (('a'<=c) && (c<='z')) || (('A'<= c) && (c<='Z')) || (('0'<=c) && (c<='9')) || (c == '_');
}

Token LexState::get_token()
{
    while (isWhite(_whole_input[_index])) _index++;

    if (_whole_input.length() > _index)
    {
        unsigned start = _index;
        char c = _whole_input[_index];
        _index++;
        std::string s = _whole_input.substr(start, _index-start);
        switch(c)
        {
            case '+':
                return Token(s, Plus, start, _index-1); // EBC index -1?
            case '(':
                return Token(s, LP, start, _index-1);
        }
        if (isIdentStart(c))
        {
            while (isIdentContinue(_whole_input[_index]))
            {
                _index++;
            }
            std::string s = _whole_input.substr(start, _index - start);
            return Token(s, Identifier, start, _index-1);
        }
        return Token(s, UnknownCharacter, start, _index-1);
    }
    else
    {
        return Token("", NoMoreToken, _index, _index);
    }
}
