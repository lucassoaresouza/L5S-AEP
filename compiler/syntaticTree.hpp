#ifndef SYNTATIC_TREE_H
#define SYNTATIC_TREE_H

#include <map>
#include <vector>
#include <cmath>

namespace Compiler {
    class Node {
        public:
            virtual ~Node(){};
            virtual char type(){
                return '0';
            }
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
            char type(){
                return 'N';
            }
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
            char type(){
                return 'B';
            }
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
            char type(){
                return 'N';
            }
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

    class NodeBlock : public Node {
        public:
            std::vector<Node*> nodes;
            int  n = 0;

            NodeBlock(){}
            double evaluate(){
                std::cout << "IN BLOCK" << std::endl;
                for (int i = 0; i < nodes.size(); i++){
                    std::cout << "evaluated: " << nodes[i]->evaluate() << std::endl;
                }
                std::cout << "OUT BLOCK" << std::endl;
                return 0;
            }
    };


    class NodeIf : public Node {
        private:
            Node* boolexp;
            Node* ifblock;

        public:
            NodeIf(Node* _boolexp, Node* _ifblock){
                boolexp = _boolexp;
                ifblock = _ifblock;
            }
            double evaluate(){
                if(boolexp->evaluate()){
                    return ifblock->evaluate();
                }
                return 0;
            }
    };

    class TreeManage : public Node {
        public:
            typedef std::map<std::string, Node*> variablemap_type;
            std::vector<Node*> nodes;
            variablemap_type variables;

            ~TreeManage(){
                clearNodes();
            }

            void clearNodes(){
                for(int i = 0; i < nodes.size(); i++){
                    delete nodes[i];
                }
                variables.clear();
                nodes.clear();
            }

            bool existsVariable(const std::string &variable_name){
                return variables.find(variable_name) != variables.end();
            }

            Node* getVariable(const std::string &variable_name){
                variablemap_type::const_iterator vi = variables.find(variable_name);
                if(vi == variables.end()){
                    std::cout << "Variável não encontrada!" << std::endl;
                    return 0;
                } else {
                    return vi->second;
                }
            }

            void run(){
                std::cout << "Nodes: " << nodes.size() << std::endl;
                for (int i = 0; i < nodes.size(); i++){
                    std::cout << "tree:" << std::endl;
                    std::cout << "evaluated: " << nodes[i]->evaluate() << std::endl;
                }
            }
    };
}

#endif //SYNTATIC_TREE_H