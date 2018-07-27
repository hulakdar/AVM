#include "OperandFactory.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "IInstruction.hpp"
#include <fstream>
#include <vector>

void Execute(const std::vector<std::unique_ptr<IInstruction>>& Instructions)
{

}

int main(int argc, char *argv[])
{
	std::vector<std::string> Buffer;

	// if filepath provided
	if (argc > 2)
	{
		std::cerr << "Usage:\n";
		std::cerr << "./avm [filepath]";
		return 1;
	}

	if (argc == 2)
	{
		const std::string FilePath(argv[1]);
		std::fstream File(FilePath);
		if (File.fail() || File.bad())
		{
			std::cerr << "File provided is not valid or not a file at all\n";
			return 1;
		}
		for (std::string Line; std::getline(File, Line);)
			Buffer.push_back(Line);
	}
	else
		for (std::string Line; std::getline(std::cin, Line);)
			Buffer.push_back(Line);

	std::vector<std::string> Tokens = Lexer::Tokenize(Buffer);
	std::vector<std::unique_ptr<IInstruction>> Instructions = Parser::Parse(Tokens);

	Execute(Instructions);
}