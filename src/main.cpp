#include "OperandFactory.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Instruction.hpp"
#include <fstream>
#include <vector>

void Execute(const std::vector<std::unique_ptr<Instruction>>& Instructions)
{
	for (auto& Instruction : Instructions)
		if (!Instruction->Execute())
			break;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> Buffer;

	// if filepath provided
	if (argc > 2)
	{
		std::cerr << "Usage:\n";
		std::cerr << "./avm [filepath]\n";
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
			if (Line == ";;")
				break;
			else
				Buffer.push_back(Line);

	const std::vector<std::string> Tokens = Lexer::Tokenize(Buffer);
	std::vector<std::unique_ptr<Instruction>> Instructions = Parser::Parse(Tokens);

	Execute(Instructions);
	getchar();
}