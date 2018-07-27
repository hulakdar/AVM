#pragma once

class IInstruction
{
public:
	virtual void Execute() = 0;
	virtual ~IInstruction() {};
};