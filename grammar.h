#include "rule.h"
#include <set>
#include <map>
struct Grammar {
private:
	std::set<Rule> rules;
	bool isInChomskyForm = false;
	Symbol start = 'S';
	void dfsUnit(const Symbol current, const std::map<Symbol, std::vector<Symbol>>& graph,
		std::map<Symbol, bool>& visited);
public:
	void addRule(const Rule& rule);
	void addRule(const char* rule);
	void eraseRule(const Rule& rule);
	void print() const;
	void print(const std::string& sep) const;
	void removeMixedRules();
	void removeLongRules();
	void removeEpsilonRules();
	void removeUnitRules();
	void makeChomskyForm();
	bool runCYK(const std::string& word);
};