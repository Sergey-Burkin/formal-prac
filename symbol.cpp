#include "symbol.h"

std::ostream& operator<<(std::ostream& out, const Symbol& symbol) {
	out << symbol.Representation;
	return out;
}

std::string Symbol::getRepresentation() const {return Representation;}

void Symbol::setRepresentation(const std::string& name) {Representation = name;};

bool Symbol::isTerminal() const {return terminal;};

void Symbol::setTerminal(bool value) {terminal = value;};

void Symbol::pushBack(char c) {Representation.push_back(c);}

bool Symbol::isEmpty() const {return Representation.empty();}

bool Symbol::operator==(const Symbol& other) {
	return Representation == other.Representation && terminal == other.terminal;
}
bool Symbol::operator!=(const Symbol& other) {
	return !(*this == other);
}