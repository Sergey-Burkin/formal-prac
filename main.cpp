#include<iostream>
#include "CYK.h"

int main () {
    std::string alpha;
    std::string u;
   // Grammar g;
    std::cout << "Hello!\nEnter n:";
    Symbol c('A');
    Symbol c2('B');
    Symbol c3('A');
    Rule rule("S   -> a32Sb;;;$");
    Rule rule2("S ->");
    Grammar g;
    g.addRule(rule);
    g.addRule(rule2);
    g.addRule(std::string("B -> A"));
    g.addRule("B -> abcderfgg");
    g.removeMixedRules();
    g.print();
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string rule;
        std::cin >> rule;

    }
    std::cin >> alpha;
    std::cout << "Enter u:";
    std::cin >> u;
    return 0;
}
