#pragma once
#include "../Behaviors/IDanceBehavior.h"
#include "../Behaviors/IFlyBehavior.h"
#include "../Behaviors/IQuackBehavior.h"
#include <cassert>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(std::unique_ptr<IDanceBehavior>&& d)
	{
	}

	Duck(std::unique_ptr<IDanceBehavior>&& danceBehavior,
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior)
	{
		assert(danceBehavior);
		assert(flyBehavior);
		assert(quackBehavior);
		m_danceBehavior = std::move(danceBehavior);
		m_flyBehavior = std::move(flyBehavior);
		m_quackBehavior = std::move(quackBehavior);
	};

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Fly() const
	{
		m_flyBehavior->Fly();
	}
	void Dance() const
	{
		m_danceBehavior->Dance();
	}

	virtual ~Duck() = default;

private:
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
};
