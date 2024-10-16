#pragma once

namespace Command
{

class ICommand
{
public:
	virtual void Execute() = 0;

	virtual ~ICommand() = default;
};

} // namespace Command
