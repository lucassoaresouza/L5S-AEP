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
            char type(){
                return 'N';
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


    class NodeLogical : public Node {
        private:
            Node* left;
            Node* right;
            std::string operation;

        public:
            NodeLogical(Node* _left, Node* _right, std::string _operation){
                left = _left;
                right = _right;
                operation = _operation;
            };
            double evaluate(){
                if(operation == "=="){
                    return left->evaluate() == right->evaluate();
                } else if (operation == "<"){
                    return left->evaluate() < right->evaluate();
                } else if (operation == ">"){
                    return left->evaluate() > right->evaluate();
                } else if (operation == "<="){
                    return left->evaluate() <= right->evaluate();
                } else if (operation == ">="){
                    return left->evaluate() >= right->evaluate();
                } else if (operation == "||"){
                    return left->evaluate() || right->evaluate();
                } else if (operation == "&&"){
                    return left->evaluate() && right->evaluate();
                } else {
                    return 0;
                }
            }
    };

    class NodeBlock : public Node {
        public:
            std::vector<Node*> nodes;
            int  n = 0;

            NodeBlock(){}
            double evaluate(){
                std::cout << "===============INICIO===============" << std::endl;
                for (int i = 0; i < nodes.size(); i++){
                    std::cout << "\nevaluated: " << nodes[i]->evaluate() << std::endl;
                }
                std::cout << "=================FIM================" << std::endl;
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

    class NodeRepeat : public Node {
        private:
            Node* expr;
            Node* context;

        public:
            NodeRepeat(Node* _expr, Node* _context){
                expr = _expr;
                context = _context;
            }
            double evaluate(){
                for(double i = 0; i < expr->evaluate(); i++){
                    context->evaluate();
                }
                return 0;
            }
    };

    class TreeManage {
        public:
            typedef std::map<std::string, double> variablemap_type;
            typedef std::vector<std::pair<std::string, double>> command_list;
            std::vector<Node*> nodes;
            variablemap_type variables;
            command_list commands;

            ~TreeManage(){
                clearNodes();
            }

            void clearNodes(){
                for(int i = 0; i < nodes.size(); i++){
                    delete nodes[i];
                }
                variables.clear();
                nodes.clear();
                commands.clear();
            }

            bool existsVariable(const std::string &variable_name){
                return variables.find(variable_name) != variables.end();
            }

            double getVariable(const std::string &variable_name){
                variablemap_type::const_iterator vi = variables.find(variable_name);
                if(vi == variables.end()){
                    std::cout << "Variável não encontrada!" << std::endl;
                    return 0;
                } else {
                    std::cout << "Variavel: " << vi->first << " valor: " << vi->second << std::endl;
                    return vi->second;
                }
            }

            command_list getCommands(){
                return commands;
            }

            void run(){
                for (int i = 0; i < nodes.size(); i++){
                    nodes[i]->evaluate();
                }
            }
    };

    class NodeAssignment : public Node {
        private:
            std::string name;
            Node* value;
            TreeManage* manage;

        public:
            NodeAssignment(std::string _name, Node* _value, TreeManage* _manage){
                name = _name;
                value = _value;
                manage = _manage;
            }
            double evaluate(){
                manage->variables[name] = value->evaluate();
                return 0;
            }
    };

    class NodeVariable : public Node {
        private:
            std::string name;
            TreeManage* manage;

        public:
            NodeVariable(std::string _name, TreeManage* _manage){
                name = _name;
                manage = _manage;
            }
            double evaluate(){
                std::cout << "Qtd: " << manage->variables.size() << std::endl;
                if(manage->existsVariable(name)){
                    return manage->getVariable(name);
                } else {
                    return 0;
                }
            }
    };

    class NodeCommand : public Node {
        private:
            Node* atribute;
            std::string type;
            TreeManage* manage;
        public:
            NodeCommand(Node* _atribute, std::string _type, TreeManage* _manage){
                atribute = _atribute;
                type = _type;
                manage = _manage;
            }
            std::string get_type(){
                return type;
            }
            double evaluate(){
                double value = atribute->evaluate();
                std::pair <std::string, double> command(type, value);
                manage->commands.push_back(command);
                std::cout << "|tipo: " << type << " |valor: " << value << std::endl;
                return 0;
            }
    };

}

#endif //SYNTATIC_TREE_H