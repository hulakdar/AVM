#include "Lexer.hpp"
#include "Parser.hpp"
#include <string>
#include <fstream>
#include <sstream>

namespace Lexer {
	std::vector<std::string> Tokenize(std::vector<std::string>& Lines)
	{
		std::vector<std::string> Tokens;
		
		for (auto& Line : Lines)
		{
			std::string SingleToken;
			auto Comment = Line.find(';');
			if (Comment != Line.npos)
				Line = Line.substr(0, Comment);
			if (Line == "")
				continue;
			std::stringstream Tokenizer(Line);

			int i = 0;
			while (std::getline(Tokenizer, SingleToken, ' '))
			{
				if (Line == "")
					continue;

				if (++i > 2)
					throw Parser::ParseErrorException();

				auto OpeningBracket = SingleToken.find("(", 0);
				if (OpeningBracket != SingleToken.npos)
				{
					Tokens.push_back(SingleToken.substr(0, OpeningBracket));
					auto ClosingBracket = SingleToken.find(")", OpeningBracket);
					if (ClosingBracket == SingleToken.npos)
						throw Parser::ParseErrorException();
					if (OpeningBracket - 1 == ClosingBracket)
						throw Parser::ParseErrorException();
					Tokens.push_back(SingleToken.substr(OpeningBracket + 1, ClosingBracket - OpeningBracket - 1));
				}
				else
					Tokens.push_back(SingleToken);
			}
		}
		return Tokens;
	}
}
