#pragma once
#include <vector>
#include <memory>
#include "Instruction.hpp"

namespace Parser
{
	std::vector<std::unique_ptr<Instruction>> Parse(const std::vector<std::string>& Tokens);
}