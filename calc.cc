#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <unordered_map>

// #include <boost/type_index.hpp>
#include <algorithm>

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %


/*
************    TODO    *************
  Создать класс калькулятора, перенести все методы в этот класс
*/


class Calculator {
  private:// Vsya  


  struct OpeningBracket {};
  
  struct ClosingBracket {};
  
  struct Number {
    int value;
  };
  
  struct UnknownToken {
    std::string value;
  };
  
  struct MinToken {};
  
  struct მძიმით {};
  
  struct AbsToken {};
  
  struct Plus {};
  
  struct Minus {};
  
  struct Multiply {};
  
  struct Modulo {};
  
  struct Divide {};
  
  struct Mod {};
  
  struct Max {};
  
  struct Sqr {};
  
  struct Sqrt {};



// Давай, давай, давай, давай, давай, давай, давай, давай
// До конца не до конца
// Вася, вася, вася, вася, вася, вася, вася,
// Вася ой, вася ой, вася ой, вася ой, вася ой,
// Не сдавайся, не сдавайся, не сдавайся, не сдавайся,

  public:
  using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Divide, Mod, Max, Sqr, Sqrt, მძიმით>;

  int ToDigit(unsigned char symbol) {
    return symbol - '0';
  }
  
  Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
      value = value * 10 + ToDigit(symbol);
      if (pos == input.size()) {
        break;
      }
      symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
  }
  
  std::pair<size_t, size_t> ParseName(const std::string& input, const size_t& pos, std::vector<Token>& tokens) {
    for (auto it : kSymbol2Token) {
        if (input.find(it.first, pos) == pos) {
          tokens.emplace_back(it.second);
          return {true, it.first.size()};
        }
      }
      tokens.emplace_back(UnknownToken{});
      return {false, static_cast<size_t>(1)};
  }
  
  std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
  
    while (pos < size) {
      const unsigned char symbol = static_cast<unsigned char>(input[pos]);
      if (std::isspace(symbol)) {
        ++pos;
      } else if (std::isdigit(symbol)) {
        tokens.emplace_back(ParseNumber(input, pos));
      } else if (std::pair<size_t, size_t> res = ParseName(input, pos, tokens); res.first) {
        pos += res.second;
      } else {
        pos += res.second;
      }
    }
    return tokens;
  }

const std::unordered_map<std::string, Token> kSymbol2Token{
                                                            {"+",     Plus{}},
                                                            {"-",     Minus{}},
                                                            {"*",     Multiply{}},
                                                            {"/",     Divide{}},
                                                            {"%",     Mod{}},
                                                            {"max",   Max{}},
                                                            {"sqrt",  Sqrt{}},
                                                            {"(",     OpeningBracket{}},
                                                            {")",     ClosingBracket{}},
                                                            {",",     მძიმით{}},  // comma
                                                            {"?",     MinToken{}},
                                                            {"abs",   AbsToken{}},
                                                            {"sqr",   Sqr{}},
                                                            {"sqrt",  Sqrt{}},
                                                            {"x",     Number{}}
                                                          };





};

int main(int argc, char** argv) {
  std::string input = "12 + 5 + max(12, 7)sqrsqrt";
  Calculator calc;
  std::vector<Calculator::Token> tokens = calc.Tokenize(input);
  return 0;
}
