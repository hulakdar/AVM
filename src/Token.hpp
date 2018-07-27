#pragma once
#include "IOperand.hpp"
#include <map>

typedef enum {
	Instruction,
	Symbol,
	Type,
	Separator,
	OpeningBracket,
	ClosingBracket,
	None
} ETokenType;

class Token {
	static const std::map<std::string, ETokenType> s_Tokens;
	ETokenType m_Type;
	const std::string *m_Value;
public:
	Token();
	Token(const Token& Other);
	Token(const std::string& Value);
	Token& operator=(const Token& Other);
	~Token();

	ETokenType GetType(void) const ;
	const std::string& GetValue(void) const ;
};
