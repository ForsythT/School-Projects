#include <iostream>
#include <map>

extern int yylex();
extern bool _error;
extern std::map<std::string, float> symbols;

int main() {
  if (!yylex()) {
    if (!_error) {
    	
    }
    return 0;
  } else {
    return 1;
  }
}
