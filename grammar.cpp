#include "grammar.h"
#include <iostream>
void Grammar::addRule(const Rule& rule) {
	rules.insert(rule);
	isInChomskyForm = false;
}

void Grammar::addRule(const char* rule) {
	rules.insert(Rule(rule));
	isInChomskyForm = false;
}



void Grammar::print() const {
	for (auto& rule : rules) {
		std::cout << rule << '\n';
	}
}

void Grammar::print(const std::string& sep) const {
	for (auto& rule : rules) {
		std::cout << rule << sep;
	}
}

void Grammar::removeMixedRules() {
	std::set<Symbol> letters;
	for (auto& rule: rules) {
		if (rule.right.size() <= 1) {
			continue;
		}
		for (auto& symbol: rule.right) {
			if (!symbol.isTerminal()) {
				letters.insert(symbol);
			}
		}
		Rule newRule = rule;
		for (auto& symbol: newRule.right) {
			if (!symbol.isTerminal()) {
				Symbol oldSymbol = symbol;
				symbol.setTerminal(true);
				symbol.setRepresentation("TERM_" + symbol.getRepresentation());
				Rule newRule;
				newRule.left = symbol;
				newRule.right.push_back(oldSymbol);
				rules.insert(newRule);
			}
		}
		rules.insert(newRule);
	}
	for (auto it = rules.begin(); it != rules.end();) {
		if (it->right.size() <= 1) {
			++it;
			continue;
		}
		bool flag = true;
		for (auto& symbol: it->right) {
			if (!symbol.isTerminal()) {
				rules.erase(it++);
				flag = false;
				break;
			}
		}
		if (flag) {
			++it;
		}
	}
}

void Grammar::removeLongRules() {
	int numberAuxiliary = 0;
	for (auto it = rules.begin(); it != rules.end();) {
		if (it->right.size() <= 2) {
			++it;
			continue;
		}
		Rule newRule;
		newRule.left = it->left;
		newRule.right.push_back(it->right[0]);
		Symbol newSymbol = "LONG_" + std::to_string(numberAuxiliary++);
		newRule.right.push_back(newSymbol);
		rules.insert(newRule);
		for (int i = 1; i < it->right.size() - 2; ++i) {
			newRule.left = newSymbol;
			newRule.right[0] = it->right[i];
			newSymbol = "LONG_" + std::to_string(numberAuxiliary++);
			newRule.right[1] = newSymbol;
			rules.insert(newRule);
		}
		newRule.left = newSymbol;
		int n = it->right.size();
		newRule.right[0] = it->right[n - 2];
		newRule.right[1] = it->right[n - 1];
		rules.insert(newRule);
		rules.erase(it++);
	} 
}

void Grammar::removeEpsilonRules() {
	std::set<Symbol> epsilonSymbols;
	for (auto it = rules.begin(); it != rules.end(); ++it) {
		if (it->isEpsilon()) {
			epsilonSymbols.insert(it->left);
		}
	}
	for (auto it = rules.begin(); it != rules.end(); ++it) {
		bool isCurrentRuleEpsilon = true;
		for (auto& symbol : it->right) {
			if (epsilonSymbols.find(symbol) == epsilonSymbols.end()) {
				isCurrentRuleEpsilon = false;
				break;
			}
		}
		if (isCurrentRuleEpsilon) {
			if (epsilonSymbols.find(it->left) == epsilonSymbols.end()) {
				epsilonSymbols.insert(it->left);
				it = rules.begin();
			}
		}
	}
	for (auto it = rules.begin(); it!= rules.end(); ++it) {
		if (it->right.size() <= 1) {
			continue;
		}
		Symbol left = it->left;
		Symbol right[2];
		right[0] = it->right[0];
		right[1] = it->right[1];
		for (int i = 0; i < 2; ++i) {
			if (epsilonSymbols.find(right[i]) != epsilonSymbols.end()) {
				Rule newRule;
				newRule.left = left;
				newRule.right.push_back(right[(i + 1) % 2]);
				rules.insert(newRule);
			}
		}
	}
	for (auto it = rules.begin(); it != rules.end();) {
		if (it->isEpsilon()) {
			rules.erase(it++);
			continue;
		}
		++it;
	} 
	if (epsilonSymbols.find(start) != epsilonSymbols.end()) {
		Symbol newSymbol = start;
		newSymbol.setRepresentation(start.getRepresentation() + "_EPS");
		rules.insert(Rule(newSymbol, start));
		rules.insert(newSymbol); 
		start = newSymbol;
	}
}

void Grammar::removeUnitRules() {
	
}

void Grammar::makeChomskyForm() { 
	if (isInChomskyForm) {
		return;
	}
	removeMixedRules();
	removeLongRules();
	removeEpsilonRules();

}