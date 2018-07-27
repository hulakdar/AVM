#pragma once
#include <vector>
#include <memory>
#include "IInstruction.hpp"

namespace Parser
{
	std::vector<std::unique_ptr<IInstruction>> Parse(const std::vector<std::string>& Tokens);
}