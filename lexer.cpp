#include "lexer.h"
#include <iostream>

std::string showKind(Kind k)
{
    switch(k)
    {
        kind_to_string(NoMoreToken);
        kind_to_string(UnknownCharacter);
        kind_to_string(Identifier);
        kind_to_string(Number);
        kind_to_string(LP);
        kind_to_string(RP);
        kind_to_string(Plus);
        kind_to_string(Dash);
        kind_to_string(Definition);
        kind_to_string(If);
        kind_to_string(LChevron);
        kind_to_string(RChevron);
        kind_to_string(Star);
        kind_to_string(Colon);
        kind_to_string(SemiColon);
    }
    assert(false);
}

std::unordered_map<std::string,Kind> key_map = {{"def", Kind:Definition},
                                                {"if", Kind::If}};

static bool isWhite(char c)
{
    return (c == ' ') || (c == '\n');
}

static bool isNumber(char c)
{
    return (('0'<=c) && (c<='9'));
}

static bool isIdentStart(char c)
{
    return (('a'<=c) && (c<='z')) || (('A'<=c) && (c<='Z')) || (c == '_');
}

static bool isIdentContinue(char c)
{
    return isIdentStart(c) || (('0'<=c) && (c<='9'));
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
                return Token(s, Plus, start, _index-1);
            case '-':
                return Token(s, Plus, start, _index-1);
            case '(':
                return Token(s, LP, start, _index-1);
            case ')':
                return Token(s, RP, start, _index-1);
            case '<':
                return Token(s, LChevron, start, _index-1);
            case '>':
                return Token(s, RChevron, start, _index-1);
            case '*':
                return Token(s, Star, start, _index-1);
            case ':':
                return Token(s, Colon, start, _index-1);
            case ';':
                return Token(s, SemiColon, start, _index-1);
        }
        if (isIdentStart(c))
        {
            while (isIdentContinue(_whole_input[_index]))
            {
                _index++;
            }
            std::string s = _whole_input.substr(start, _index - start);
            if ( key_map.find(s) != key_map.end())
            {
                Kind kind = key_map[s];
                return Token(s, kind, start, _index-1);
            }
            return Token(s, Identifier, start, _index-1);
        }
        if (isNumber(c))
        {
            while (isNumber(_whole_input[_index]))
            {
                _index++;
            }
            std::string s = _whole_input.substr(start, _index - start);
            return Token(s, Number, start, _index-1);
        }
        return Token(s, UnknownCharacter, start, _index-1);
    }
    else
    {
        return Token("", NoMoreToken, _index, _index);
    }
}