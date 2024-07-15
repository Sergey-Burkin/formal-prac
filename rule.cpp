#include "rule.h"

const std::string FORMAT = " -> ";
const std::string EPSILON = "ε";

void Rule::pushBack(const Symbol& symbol, bool toLeft) {
	if (toLeft) {
		left = symbol;
	} else {
		right.push_back(symbol);
	}
}

bool Rule::inAlphabet(char c) {
	return isalpha(c) || isdigit(c) || c == '(' || c == ')';
}

Rule::Rule(const std::string& rawString) {
	bool leftSetted = false;
	Symbol current;
	for (char c : rawString) {
		if (!inAlphabet(c)) {
			continue;
		}
		if (!current.isEmpty()) {
			pushBack(current, !leftSetted);
			leftSetted = true;
		}
		current = Symbol(c);
	}

	if (!current.isEmpty()) {
		pushBack(current, !leftSetted);
	}
}

bool Rule::isEpsilon() const {
	if (right.empty()) {
		return true;
	}
	for (auto& symbol : right) {
		if (!symbol.isEmpty()) {
			return false;
		}
	}
	return true;
}

bool Rule::isUnit() const {
	return right.size() == 1 && right.front().isTerminal();
}

bool Rule::operator==(const Rule& other) const {
	if (isEpsilon() && other.isEpsilon()) {
		return true;
	}
	if (left != other.left) {return false;}
	if (right.size() != other.right.size()) {
		return false;
	}
	for (int i = 0; i < right.size(); ++i) {
		if (right[i] != other.right[i]) {
			return false;
		}
	}
	return true;
}

bool Rule::operator<(const Rule& other) const{
	if (left < other.left) {
		return true;
	}
	if (other.left < left) {
		return false;
	}
	for (int i = 0; i < std::min(right.size(), other.right.size()); ++i) {
		if (right[i] < other.right[i]) {
			return true;
		} 
		if (other.right[i] < right[i]) {
			return false;
		}
	}
	return right.size() < other.right.size();
}

std::ostream& operator<<(std::ostream& out, const Rule& rule) {
	out << rule.left << FORMAT;
	if (rule.isEpsilon()) {
		out << EPSILON;
	}
	for (auto& symbol : rule.right) {
		out << symbol;
	}
	return out;
}