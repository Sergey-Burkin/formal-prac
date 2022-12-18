#include "symbol.h"
#include <vector>
struct Rule {
private:
	Symbol left;
	std::vector<Symbol> right;
	static const std::string FORMAT;
	static const std::string EPSILON;
	bool inAlphabet(char c);
public:
	Rule() = default;
	Rule(const Symbol& symbol) : left(symbol) {}
	Rule(const Symbol& symbolLeft, const Symbol& symbolRight) : left(symbolLeft), right(1, symbolRight) {}
	Rule(const std::string& rawString);
	void pushBack(const Symbol& symbol, bool toLeft);
	bool isEpsilon() const;
	bool isUnit() const;
	bool operator==(const Rule& other) const;
	bool operator<(const Rule&other) const;
	friend std::ostream& operator<<(std::ostream& out, const Rule& rule);
	friend struct Grammar;
};
