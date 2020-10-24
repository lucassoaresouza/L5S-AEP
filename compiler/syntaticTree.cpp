#include "./syntaticTree.hpp"
#include <iostream>

using namespace Compiler;

NodeConst::NodeConst(double _value){
    value = _value;
}

double NodeConst::evaluate(){
    return value;
}

NodeBool::NodeBool(bool _value){
    value = _value;
}

double NodeBool::evaluate(){
    if(value){
        return 1;
    } else {
        return 0;
    }
}