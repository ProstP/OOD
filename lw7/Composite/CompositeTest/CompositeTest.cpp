﻿#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/SimpleShapes/SimpleShapes.h"
#include <iostream>

TEST_CASE("Insert new shape")
{
	WHEN("Empty, to start, to end, index > size")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		RectD rect1{ 1, 1, 1, 1 };
		RectD rect2{ 2, 2, 2, 2 };
		RectD rect3{ 3, 3, 3, 3 };
		RectD rect4{ 4, 4, 4, 4 };

		THEN("Success inserting, last - error")
		{
			CHECK(group.GetShapeCount() == 0);
			CHECK_NOTHROW(r.SetFrame(rect1));
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetShapeCount() == 1);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect1.left);

			CHECK_NOTHROW(r.SetFrame(rect2));
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetShapeCount() == 2);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect1.left);

			CHECK_NOTHROW(r.SetFrame(rect3));
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 2));
			CHECK(group.GetShapeCount() == 3);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect1.left);
			CHECK(group.GetShapeAtIndex(2)->GetFrame().left == rect3.left);

			CHECK_NOTHROW(r.SetFrame(rect4));
			CHECK_THROWS_WITH(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 10), "Out of range in inserting shape");
			CHECK(group.GetShapeCount() == 3);
		}
	}
}

TEST_CASE("Change group frame in insert")
{
	Shapes::Group group(nullptr);

	RectD frame{ 100, 100, 100, 100 };
	group.SetFrame(frame);

	WHEN("Shape frame into group frame")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 110, 110, 20, 20 };
		r.SetFrame(shapeFrame);

		THEN("Group frame not change")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
		}
	}

	WHEN("Shape left smaller")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 90, 110, 20, 20 };
		r.SetFrame(shapeFrame);

		THEN("Group left will change")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == shapeFrame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width + group.GetFrame().left == frame.left + frame.width);
			CHECK(group.GetFrame().height + group.GetFrame().top == frame.top + frame.height);
		}
	}

	WHEN("Shape top smaller")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 110, 50, 20, 20 };
		r.SetFrame(shapeFrame);

		THEN("Group top will change")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == shapeFrame.top);
			CHECK(group.GetFrame().width + group.GetFrame().left == frame.left + frame.width);
			CHECK(group.GetFrame().height + group.GetFrame().top == frame.top + frame.height);
		}
	}

	WHEN("Shape endX > group endX")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 190, 110, 20, 20 };
		r.SetFrame(shapeFrame);

		THEN("Width will bigger")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width + group.GetFrame().left >= shapeFrame.left + shapeFrame.width);
			CHECK(group.GetFrame().height == frame.height);
		}
	}

	WHEN("Shape endY > group endY")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 110, 190, 20, 20 };
		r.SetFrame(shapeFrame);

		THEN("Height")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height + group.GetFrame().top >= shapeFrame.top + shapeFrame.height);
		}
	}

	WHEN("Shape frame bigger group frame")
	{
		SimpleShapes::Rectangle r(nullptr);

		RectD shapeFrame{ 50, 50, 200, 200 };
		r.SetFrame(shapeFrame);

		THEN("Height")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(group.GetFrame().left == shapeFrame.left);
			CHECK(group.GetFrame().top == shapeFrame.top);
			CHECK(group.GetFrame().width + group.GetFrame().left >= shapeFrame.left + shapeFrame.width);
			CHECK(group.GetFrame().height + group.GetFrame().top >= shapeFrame.top + shapeFrame.height);
		}
	}
}

TEST_CASE("Getting shape")
{
	WHEN("Index > group count")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Exception")
		{
			CHECK(group.GetShapeCount() == 6);
			CHECK_THROWS_WITH(group.GetShapeAtIndex(7), "Out of range in getting shape");
		}
	}
}

TEST_CASE("Removing shape")
{
	WHEN("Index > group count")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Exception")
		{
			CHECK(group.GetShapeCount() == 6);
			CHECK_THROWS_WITH(group.RemoveShapeAtIndex(7), "Out of range in removing shape");
		}
	}

	WHEN("Index is right")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		RectD rect1{ 1, 1, 1, 1 };
		RectD rect2{ 2, 2, 2, 2 };
		RectD rect3{ 3, 3, 3, 3 };
		RectD rect4{ 4, 4, 4, 4 };
		
		r.SetFrame(rect4);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		r.SetFrame(rect3);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		r.SetFrame(rect2);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		r.SetFrame(rect1);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Removing right shape")
		{
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect1.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(2)->GetFrame().left == rect3.left);
			CHECK(group.GetShapeAtIndex(3)->GetFrame().left == rect4.left);

			CHECK_NOTHROW(group.RemoveShapeAtIndex(2));

			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect1.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(2)->GetFrame().left == rect4.left);

			CHECK_NOTHROW(group.RemoveShapeAtIndex(0));

			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect4.left);

			CHECK_NOTHROW(group.RemoveShapeAtIndex(1));

			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect2.left);
		}
	}
}