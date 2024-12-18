#pragma once
#include "../Model/ShapeStore.h"

class Controller
{
public:
	Controller(Model::ShapeStore& store)
		: m_store(store)
	{
	}

private:
	Model::ShapeStore& m_store;
};
