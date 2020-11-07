#include "./syntaticTree.hpp"

using namespace Compiler;

TreeManage::~TreeManage(){
    clearNodes();
}

void TreeManage::clearNodes(){
    for(int i = 0; i < nodes.size(); i++){
        delete nodes[i];
    }
    variables.clear();
    nodes.clear();
    commands.clear();
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
        std::cout << "Variavel: " << vi->first << " valor: " << vi->second << std::endl;
        return vi->second;
    }
}

command_list TreeManage::getCommands(){
    return commands;
}

void TreeManage::run(){
    std::cout << "Inicializando leitura dos nós" << std::endl;
    for (int i = 0; i < nodes.size(); i++){
        nodes[i]->evaluate();
    }
    std::cout << "Finalizando leitura dos nós" << std::endl;
}
