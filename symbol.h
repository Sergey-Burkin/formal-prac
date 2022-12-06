#include <string>

struct Symbol {
private:
	std::string Representation;
	bool terminal;
public:
	Symbol() = default;
	Symbol(const Symbol& other) = default;
	Symbol(char c) : Representation(1, c), terminal(isupper(c)) {}
	Symbol(const std::string& name) : Representation(name), terminal(name.size() > 0 && isupper(name[0])) {}
	Symbol& operator=(const Symbol& other) = default;
	bool operator==(const Symbol& other) const ;
	bool operator!=(const Symbol& other) const;
	bool operator<(const Symbol& other) const;
	std::string getRepresentation() const;
	void setRepresentation(const std::string& name);
	bool isTerminal() const ;
	void setTerminal(bool value);
	void pushBack(char c);
	bool isEmpty() const;
    friend std::ostream& operator<<(std::ostream& out, const Symbol& symbol);
};