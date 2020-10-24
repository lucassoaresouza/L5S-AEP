#ifndef SYNTATIC_TREE_H
#define SYNTATIC_TREE_H

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

}

#endif //SYNTATIC_TREE_H