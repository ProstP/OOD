#define CATCH_CONFIG_MAIN
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

TEST_CASE("Style tests")
{
	WHEN("Get fill style from same stylies")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		Shapes::Style style;

		style.Enable(true);
		style.SetColor(0x11223344);
		r.SetFillStyle(std::make_shared<Shapes::Style>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		auto groupStyle = group.GetFillStyle();

		THEN("Return style")
		{
			CHECK(groupStyle->IsEnable() == style.IsEnable());
			CHECK(groupStyle->GetColor() == style.GetColor());
		}
	}

	WHEN("Set new style via group style")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		Shapes::Style style;

		style.Enable(true);
		style.SetColor(0x11221122);
		r.SetFillStyle(std::make_shared<Shapes::Style>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		auto groupStyle = group.GetFillStyle();

		THEN("Child of group setting new style")
		{
			CHECK_NOTHROW(groupStyle->SetColor(0x123321));

			CHECK(group.GetShapeAtIndex(0)->GetFillStyle()->GetColor() == 0x123321);
			CHECK(group.GetShapeAtIndex(1)->GetFillStyle()->GetColor() == 0x123321);

			CHECK_NOTHROW(groupStyle->Enable(false));

			CHECK(group.GetShapeAtIndex(0)->GetFillStyle()->IsEnable() == false);
			CHECK(group.GetShapeAtIndex(1)->GetFillStyle()->IsEnable() == false);
		}
	}

	WHEN("Child count = 0")
	{
		Shapes::GroupStyle groupStyle;

		THEN("Exception")
		{
			CHECK_THROWS_WITH(groupStyle.IsEnable(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.Enable(false), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetColor(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.SetColor(0x11111111), "Style withut childs");
		}
	}

	WHEN("Styles not same")
	{
		Shapes::GroupStyle groupStyle;

		Shapes::Style style1;
		style1.Enable(true);
		style1.SetColor(0x123321);
		Shapes::Style style2;
		style2.Enable(true);
		style2.SetColor(0x321123);

		groupStyle.AddStyle(std::make_shared<Shapes::Style>(style1));
		groupStyle.AddStyle(std::make_shared<Shapes::Style>(style2));

		THEN("Return defualt value for this types")
		{
			CHECK(groupStyle.IsEnable() == false);
			CHECK(groupStyle.GetColor() == std::nullopt);
		}
	}
}

TEST_CASE("Style with thickness tests")
{
	WHEN("Get fill style from same stylies")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		Shapes::StyleWithThickness style;

		style.Enable(true);
		style.SetColor(0x11223344);
		style.SetThickness(3);
		r.SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		auto groupStyle = group.GetOutlineStyle();

		THEN("Return style")
		{
			CHECK(groupStyle->IsEnable() == style.IsEnable());
			CHECK(groupStyle->GetColor() == style.GetColor());
			CHECK(groupStyle->GetThickness() == style.GetThickness());
		}
	}

	WHEN("Set new style via group style")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		Shapes::StyleWithThickness style;

		style.Enable(true);
		style.SetColor(0x11221122);
		style.SetThickness(3);
		r.SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		auto groupStyle = group.GetOutlineStyle();

		THEN("Child of group setting new style")
		{
			CHECK_NOTHROW(groupStyle->SetColor(0x123321));

			CHECK(group.GetShapeAtIndex(0)->GetOutlineStyle()->GetColor() == 0x123321);
			CHECK(group.GetShapeAtIndex(1)->GetOutlineStyle()->GetColor() == 0x123321);

			CHECK_NOTHROW(groupStyle->Enable(false));

			CHECK(group.GetShapeAtIndex(0)->GetOutlineStyle()->IsEnable() == false);
			CHECK(group.GetShapeAtIndex(1)->GetOutlineStyle()->IsEnable() == false);

			CHECK_NOTHROW(groupStyle->SetThickness(1));

			CHECK(group.GetShapeAtIndex(0)->GetOutlineStyle()->GetThickness() == 1);
			CHECK(group.GetShapeAtIndex(1)->GetOutlineStyle()->GetThickness() == 1);
		}
	}

	WHEN("Child count = 0")
	{
		Shapes::GroupStyleWithThicness groupStyle;

		THEN("Exception")
		{
			CHECK_THROWS_WITH(groupStyle.IsEnable(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.Enable(false), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetColor(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.SetColor(0x11111111), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetThickness(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.SetThickness(2), "Style withut childs");
		}
	}

	WHEN("Styles not same")
	{
		Shapes::GroupStyleWithThicness groupStyle;

		Shapes::StyleWithThickness style1;
		style1.Enable(true);
		style1.SetColor(0x123321);
		style1.SetThickness(1);
		Shapes::StyleWithThickness style2;
		style2.Enable(true);
		style2.SetColor(0x321123);
		style1.SetThickness(1);

		groupStyle.AddStyle(std::make_shared<Shapes::StyleWithThickness>(style1));
		groupStyle.AddStyle(std::make_shared<Shapes::StyleWithThickness>(style2));

		THEN("Return defualt value for this types")
		{
			CHECK(groupStyle.IsEnable() == false);
			CHECK(groupStyle.GetColor() == std::nullopt);
			CHECK(groupStyle.GetThickness() == 0);
		}
	}
}

TEST_CASE("Resize childs")
{
	WHEN("Child set new frame to group")
	{
		Shapes::Group group(nullptr);

		RectD frame{ 100, 100, 100, 100 };
		group.SetFrame(frame);

		SimpleShapes::Rectangle r(nullptr);
		RectD shapeFrame{ 125, 125, 50, 50 };
		r.SetFrame(shapeFrame);

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Child frame will change")
		{
			CHECK_NOTHROW(group.SetFrame(RectD{ 40, 40, 40, 40 }));
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == 50);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().top == 50);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().width == 20);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().height == 20);
		}
	}
}
