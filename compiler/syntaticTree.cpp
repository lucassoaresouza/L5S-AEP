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

TreeManage::~TreeManage(){
    clearNodes();
}

void TreeManage::clearNodes(){
    for(int i = 0; i < nodes.size(); i++){
        delete nodes[i];
    }
    nodes.clear();
}

bool TreeManage::existsVariable(const std::string &variable_name){
    return variables.find(variable_name) != variables.end();
}

double TreeManage::getVariable(const std::string &variable_name){
    variablemap_type::const_iterator vi = variables.find(variable_name);
    if(vi == variables.end()){
        std::cout << "Variável não encontrada!" << std::endl;
        return 0;
    } else {
        return vi->second;
    }
}