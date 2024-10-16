#pragma once
#include "ICommand.h"

namespace Command
{

class IUnexecutableCommand : public Command::ICommand
{
public:
	virtual void Unexecute() = 0;
};

} // namespace Command
