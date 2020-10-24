#ifndef SYNTATIC_TREE_H
#define SYNTATIC_TREE_H

#include <map>
#include <vector>

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
            NodeConst(double _value);
            ~NodeConst(){};
            double evaluate();
    };

    class NodeBool : public Node {
        private:
            bool value = false;
        public:
            NodeBool(bool _value);
            ~NodeBool(){};
            double evaluate();
    };

    class TreeManage {
        private:
            typedef std::map<std::string, double> variablemap_type;
            variablemap_type variables;
            std::vector<Node*> nodes;

        public:
            ~TreeManage();
            void clearNodes();
            bool existsVariable(const std::string &variable_name);
            double getVariable(const std::string &variable_name);
    };
}

#endif //SYNTATIC_TREE_H