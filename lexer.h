#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include <cassert>
#include <unordered_map>

enum Kind { NoMoreToken,
            UnknownCharacter,
            Identifier,
            Number,
            Plus,
            Dash,
            LP,
            RP,
            Definition,
            If,
            Then,
            Else,
            LChevron,
            RChevron,
            Star,
            Colon,
            SemiColon};

#define kind_to_string(E) case E: return #E

std::string showKind(Kind k);

class Token {
private:
  std::string _text;
  Kind _kind;
  unsigned int _start_pos;
  unsigned int _end_pos;
public:
  Token(std::string text, Kind kind, unsigned int start_pos, unsigned int end_pos) : _text(text), _kind(kind), _start_pos(start_pos), _end_pos(end_pos) {}
  std::string text() { return _text; };
  Kind kind() { return _kind; };
  unsigned int start_pos() { return _start_pos; };
  unsigned int end_pos() { return _end_pos; };
};

class LexState {
private:
  std::string _whole_input;
  unsigned _index;
public:
  LexState(std::string input) : _whole_input(input), _index(0) {};
  Token get_token();
};

#endif