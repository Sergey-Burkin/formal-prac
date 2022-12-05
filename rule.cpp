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

Rule::Rule(const std::string& rawString) {
	bool leftSetted = false;
	Symbol current;
	for (char c : rawString) {
		if (!(isalpha(c) || isdigit(c))) {
			continue;
		}
		if (isalpha(c)) {
			if (!current.isEmpty()) {
				pushBack(current, !leftSetted);
				leftSetted = true;
			}
			current = Symbol(c);
		} else {
			current.pushBack(c);
		}
	}

	if (!current.isEmpty()) {
		pushBack(current, !leftSetted);
	}
}

bool Rule::isEps() const {
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

bool Rule::operator==(const Rule& other) {
	if (isEps() && other.isEps()) {
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

std::ostream& operator<<(std::ostream& out, const Rule& rule) {
	out << rule.left << FORMAT;
	if (rule.isEps()) {
		out << EPSILON;
	}
	for (auto& symbol : rule.right) {
		out << symbol;
	}
	return out;
}