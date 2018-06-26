#include "OperandFactory.hpp"
#include "Lexer.hpp"
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> Buffer;

	if (argc == 2)
	{
		const std::string FilePath(argv[1]);
		std::fstream File(FilePath);
		for (std::string Line; std::getline(File, Line);)
		{
				Buffer.push_back(Line);
		}
	}
	else
		for (std::string Line; std::getline(std::cin, Line);)
			Buffer.push_back(Line);

	std::vector<std::string> Tokens = Lexer::Tokenize(Buffer);
	for (auto& Token : Tokens)
		std::cout << Token << "<--\n";
	std::cout << std::endl;
}