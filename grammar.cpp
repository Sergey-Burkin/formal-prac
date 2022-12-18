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

void Grammar::dfsUnit(const Symbol current, const std::map<Symbol, std::vector<Symbol>>& graph,
		std::map<Symbol, bool>& visited) {
	if (visited[current]) {
		return;
	}
	visited[current] = true;
	for ( auto symbol : graph.at(current)) {
		dfsUnit(symbol, graph, visited);
	}
}

void Grammar::removeUnitRules() {
	std::map<Symbol, std::vector<Symbol>> graph;
	std::map<Symbol, bool> visited;
	std::map<Symbol, std::vector<std::set<Rule>::iterator>> nonUnitRules;
	std::set<Rule> newRules;

	for (auto it = rules.begin(); it != rules.end(); ++it) {
		if (it->isUnit()) {
			graph[it->left].push_back(it->right.front());
			graph[it->right.front()];
			visited[it->left] = false;
			visited[it->right.front()] = false;
		} else {
			nonUnitRules[it->left].push_back(it);
		}
	}
	for (auto& pair : graph) {
		for (auto& pairBool : visited) {
			pairBool.second = false;
		}
		Symbol current = pair.first;
		dfsUnit(current, graph, visited);
		for (auto& pairBool : visited) {
			if (pairBool.second == false) {
				continue;
			}
			Symbol otherSymbol = pairBool.first;
			if (otherSymbol == current) {continue;}
			for (auto iterator : nonUnitRules[otherSymbol]) {
				Rule newRule = *iterator;
				newRule.left = current;
				newRules.insert(newRule);
			}
		}
	}
	for (auto it = rules.begin(); it != rules.end();) {
		if (it->isUnit()) {
			rules.erase(it++);
			continue;
		}
		++it;
	} 
	rules.insert(newRules.begin(), newRules.end());
	
}

void Grammar::makeChomskyForm() { 
	if (isInChomskyForm) {
		return;
	}
	removeMixedRules();
	removeLongRules();
	removeEpsilonRules();
	removeUnitRules();
	isInChomskyForm = true;

}

bool Grammar::runCYK(const std::string& word) {
	makeChomskyForm();
	int n = word.size();
	std::vector<std::vector<bool>> zero(n + 1, std::vector<bool>(n + 1, false));
	std::map<Symbol, std::vector<std::vector<bool>>> dp;
	for (auto& rule: rules) {
		if (dp.find(rule.left) == dp.end() ) {
			dp[rule.left] = zero;
		}
		if (!rule.right.empty() && !rule.right.front().isTerminal()) {
			for (int i = 0; i < n; ++i) {
				if (Symbol(word[i]) == rule.right.front()){
					dp[rule.left][i][i + 1] = true;
				}
			}
		} else {
			for (int i = 0; i <= n; ++i) {
				dp[rule.left][i][i] = true;
			}
		}
	}
	for (int length = 2; length <= n; ++length) {
		for (auto& rule : rules) { //A -> BC
			if (rule.right.size() != 2) {
				continue;
			}
			Symbol a = rule.left;
			Symbol b = rule.right[0];
			Symbol c = rule.right[1];
			for (int i = 0; i + length <= n; ++ i) {
				for (int k = i; k <= i + length; ++ k) {
					if (dp[b][i][k] && dp[c][k][i + length]) {
						dp[a][i][i + length] = true;
					}
				}
			}
		}
	}
	return dp[start][0][n];
}
