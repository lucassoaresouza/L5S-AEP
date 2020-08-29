#include <iostream>
#include "scanner.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

using namespace Compiler;
using namespace std;

int main(int argc, char **argv){
    Interpreter i;
    int res = i.parse();
    cout << "Parser finalizado! res: " << res << endl;
    return res;
}