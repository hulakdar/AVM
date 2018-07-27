#pragma once
#include "Token.hpp"
#include <vector>

namespace Lexer
{
	std::vector<std::string> Tokenize(const std::vector<std::string>& Stream);
}