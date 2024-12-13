#include "BalancedTrees.hpp"

int main(){
    BTrees<int> tree;
    tree.add(1);
    tree.add(5);
    tree.printDot();
    tree.remove(5);
    tree.printDot();
}