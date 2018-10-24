#include "Lexer.hpp"
#include <fstream>
#include <sstream>

namespace Lexer {
	std::vector<std::string> Tokenize(const std::vector<std::string>& Lines)
	{
		std::vector<std::string> Tokens;
		
		for (auto& Line : Lines)
		{
			std::stringstream Tokenizer(Line);
			std::string SingleToken;
			while (std::getline(Tokenizer, SingleToken, ' '))
			{
				auto OpeningBracket = SingleToken.find("(", 0);
				if (OpeningBracket != SingleToken.npos)
				{
					Tokens.push_back(SingleToken.substr(0, OpeningBracket));
					//Tokens.push_back("(");
					auto ClosingBracket = SingleToken.find(")", OpeningBracket);
					if (ClosingBracket != SingleToken.npos)
					{
						Tokens.push_back(SingleToken.substr(OpeningBracket + 1, ClosingBracket - OpeningBracket - 1));
						//Tokens.push_back(")");
					}
					else
						Tokens.push_back(SingleToken.substr(OpeningBracket + 1));
				}
				else
					Tokens.push_back(SingleToken);
			}
			//nextline:
			//Tokens.push_back("\n");
		}
		return Tokens;
	}
}
