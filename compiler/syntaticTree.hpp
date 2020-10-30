#ifndef SYNTATIC_TREE_H
#define SYNTATIC_TREE_H

#include <map>
#include <vector>
#include <cmath>

namespace Compiler {
    class Node {
        public:
            virtual ~Node(){};
            virtual double evaluate(){
                return 0;
            };
    };

    class NodeConst : public Node {
        private:
            double value = 0;
        public:
            NodeConst(double _value){
                value = _value;
            }
            ~NodeConst(){};
            double evaluate(){
                return value;
            }
    };

    class NodeBool : public Node {
        private:
            bool value = false;
        public:
            NodeBool(bool _value){
                value = _value;
            }
            ~NodeBool(){};
            double evaluate(){
                if(value){
                    return 1;
                } else {
                    return 0;
                }
            }
    };

    class NodeNegate : public Node {
        private:
            Node* node;
        public:
            NodeNegate(Node* _node){
                node = _node;
            }
            ~NodeNegate(){
                delete node;
            }
            double evaluate(){
                double result = - node->evaluate();
                return - node->evaluate();
            }
    };

    class NodeCalc : public Node {
        private:
            Node* left;
            Node* right;
            char operation;

        public:
            NodeCalc(Node* _left, Node* _right, char _operation){
                left = _left;
                right = _right;
                operation = _operation;
            };
            ~NodeCalc(){
                delete left;
                delete right;
            };
            double evaluate(){
                switch (operation){
                    case '+':
                        return left->evaluate() + right->evaluate();
                        break;
                    case '-':
                        return left->evaluate() - right->evaluate();
                        break;
                    case '*':
                        return left->evaluate() * right->evaluate();
                        break;
                    case '/':
                        return left->evaluate() / right->evaluate();
                        break;
                    case '^':
                        return std::pow(left->evaluate(), right->evaluate());
                        break;                
                    default:
                        return 0;
                        break;
                }
            };
    };

    class TreeManage {
        public:
            typedef std::map<std::string, double> numeric_variablemap;
            typedef std::map<std::string, bool> boolean_variablemap;
            boolean_variablemap boolean_variables;
            numeric_variablemap numeric_variables;
            std::vector<Node*> nodes;

            ~TreeManage(){
                clearNodes();
            }
            void clearNodes(){
                for(int i = 0; i < nodes.size(); i++){
                    delete nodes[i];
                }
                boolean_variables.clear();
                numeric_variables.clear();
                nodes.clear();
            }
            char existsVariable(std::string &variable_name){
                if(numeric_variables.find(variable_name) != numeric_variables.end()){
                    return 'N';
                } else if (boolean_variables.find(variable_name) != boolean_variables.end()) {
                    return 'B';
                } else {
                    return '0';
                }
            }

            double getVariable(char type, std::string &variable_name){
                switch (type){
                    case 'N':
                        return getNumericVariable(variable_name);
                        break;
                    case 'B':
                        return getBooleanVariable(variable_name);
                    default:
                        return 0;
                        break;
                }
            }

            double getNumericVariable(std::string &variable_name){
                numeric_variablemap::const_iterator vi = numeric_variables.find(variable_name);
                if(vi == numeric_variables.end()){
                    std::cout << "Variável não encontrada!" << std::endl;
                    return 0;
                } else {
                    return vi->second;
                }
            }

            double getBooleanVariable(std::string &variable_name){
                boolean_variablemap::const_iterator vi = boolean_variables.find(variable_name);
                if(vi == boolean_variables.end()){
                    std::cout << "Variável não encontrada!" << std::endl;
                    return 0;
                } else {
                    return vi->second;
                }
            }

            void run(){
                for (int i = 0; i < nodes.size(); i++){
                    std::cout << "evaluated: " << nodes[i]->evaluate() << std::endl;
                }
            }
    };
}

#endif //SYNTATIC_TREE_H