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

		THEN("Success inserting")
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
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r),10));
			CHECK(group.GetShapeCount() == 4);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == rect2.left);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == rect1.left);
			CHECK(group.GetShapeAtIndex(2)->GetFrame().left == rect3.left);
			CHECK(group.GetShapeAtIndex(3)->GetFrame().left == rect4.left);
		}
	}
}

TEST_CASE("Getting frame")
{
	WHEN("Shape is one")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		RectD frame{ 10, 10, 10, 10 };
		r.SetFrame(frame);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Group frame == shape frame")
		{
			CHECK(group.GetFrame().left == frame.left);
			CHECK(group.GetFrame().top == frame.top);
			CHECK(group.GetFrame().width == frame.width);
			CHECK(group.GetFrame().height == frame.height);
		}
	}

	WHEN("Many shapes")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);

		RectD frame1{ 10, 10, 10, 10 };
		r.SetFrame(frame1);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		RectD frame2{ 15, 55, 100, 10 };
		r.SetFrame(frame2);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		RectD frame3{ 50, 100, 20, 30 };
		r.SetFrame(frame3);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Shape frames into group frame")
		{
			CHECK(group.GetFrame().left >= frame1.left);
			CHECK(group.GetFrame().top >= frame1.top);
			CHECK(group.GetFrame().left + group.GetFrame().width >= frame2.left + frame2.width);
			CHECK(group.GetFrame().top + group.GetFrame().height >= frame3.top + frame3.height);
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
		auto getFn = []() {
			return std::vector<std::shared_ptr<Shapes::IStyle>>();
		};
		auto editFn = [](std::optional<bool>, std::optional<RGBAColor>) {};

		Shapes::GroupStyle groupStyle(getFn, editFn);

		THEN("Exception")
		{
			CHECK_THROWS_WITH(groupStyle.IsEnable(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetColor(), "Style withut childs");
		}
	}

	WHEN("Styles not same")
	{
		auto getFn = []() {
			Shapes::Style style1;
			style1.Enable(false);
			style1.SetColor(0x123321);
			Shapes::Style style2;
			style2.Enable(true);
			style2.SetColor(0x321123);

			std::vector<std::shared_ptr<Shapes::IStyle>> styles;

			styles.push_back(std::make_shared<Shapes::Style>(style1));
			styles.push_back(std::make_shared<Shapes::Style>(style2));

			return styles;
		};
		auto editFn = [](std::optional<bool>, std::optional<RGBAColor>) {};

		Shapes::GroupStyle groupStyle(getFn, editFn);

		THEN("Return defualt value for this types")
		{
			CHECK(groupStyle.IsEnable() == false);
			CHECK(groupStyle.GetColor() == std::nullopt);
		}
	}

	WHEN("Add new shapes after getting style from gruo")
	{
		Shapes::Group group(nullptr);

		auto groupStyle = group.GetFillStyle();

		SimpleShapes::Rectangle r(nullptr);

		Shapes::Style style;

		style.Enable(true);
		style.SetColor(0x11221122);
		r.SetFillStyle(std::make_shared<Shapes::Style>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

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
	WHEN("Get fill style before inserting shapes")
	{
		Shapes::Group group(nullptr);

		auto groupStyle = group.GetFillStyle();

		SimpleShapes::Rectangle r(nullptr);

		Shapes::Style style1;
		style1.Enable(true);
		style1.SetColor(0x123321);
		Shapes::Style style2;
		style2.Enable(true);
		style2.SetColor(0x321123);
		r.SetFillStyle(std::make_shared<Shapes::Style>(style1));
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		THEN("Return style")
		{
			CHECK(groupStyle->IsEnable() == style1.IsEnable());
			CHECK(groupStyle->GetColor() == style1.GetColor());
			CHECK_NOTHROW(r.SetFillStyle(std::make_shared<Shapes::Style>(style2)));
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(groupStyle->IsEnable() == true);
			CHECK(groupStyle->GetColor() == std::nullopt);
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
		auto getFn = []() {
			return std::vector<std::shared_ptr<Shapes::IStyleWithThickness>>();
		};
		auto editFn = [](std::optional<bool>, std::optional<RGBAColor>, std::optional<int>) {};
		Shapes::GroupStyleWithThicness groupStyle(getFn, editFn);

		THEN("Exception")
		{
			CHECK_THROWS_WITH(groupStyle.IsEnable(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetColor(), "Style withut childs");
			CHECK_THROWS_WITH(groupStyle.GetThickness(), "Style withut childs");
		}
	}

	WHEN("Styles not same")
	{
		auto getFn = []() {
			Shapes::StyleWithThickness style1;
			style1.Enable(false);
			style1.SetColor(0x123321);
			style1.SetThickness(2);
			Shapes::StyleWithThickness style2;
			style2.Enable(true);
			style2.SetColor(0x321123);
			style1.SetThickness(1);

			std::vector<std::shared_ptr<Shapes::IStyleWithThickness>> styles;

			styles.push_back(std::make_shared<Shapes::StyleWithThickness>(style1));
			styles.push_back(std::make_shared<Shapes::StyleWithThickness>(style2));

			return styles;
		};
		auto editFn = [](std::optional<bool>, std::optional<RGBAColor>, std::optional<int>) {};
		Shapes::GroupStyleWithThicness groupStyle(getFn, editFn);

		THEN("Return defualt value for this types")
		{
			CHECK(groupStyle.IsEnable() == false);
			CHECK(groupStyle.GetColor() == std::nullopt);
			CHECK(groupStyle.GetThickness() == 0);
		}
	}
	WHEN("Add new shapes after getting style from gruop")
	{
		Shapes::Group group(nullptr);

		auto groupStyle = group.GetOutlineStyle();

		SimpleShapes::Rectangle r(nullptr);

		Shapes::StyleWithThickness style;

		style.Enable(true);
		style.SetColor(0x11221122);
		style.SetThickness(3);
		r.SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style));

		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

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
	WHEN("Get fill style before inserting shapes")
	{
		Shapes::Group group(nullptr);

		auto groupStyle = group.GetOutlineStyle();

		SimpleShapes::Rectangle r(nullptr);

		Shapes::StyleWithThickness style1;
		style1.Enable(true);
		style1.SetColor(0x123321);
		style1.SetThickness(3);
		Shapes::StyleWithThickness style2;
		style2.Enable(true);
		style2.SetColor(0x321123);
		style2.SetThickness(5);
		r.SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style1));
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);
		THEN("Return style")
		{
			CHECK(groupStyle->IsEnable() == style1.IsEnable());
			CHECK(groupStyle->GetColor() == style1.GetColor());
			CHECK_NOTHROW(r.SetOutlineStyle(std::make_shared<Shapes::StyleWithThickness>(style2)));
			CHECK_NOTHROW(group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0));
			CHECK(groupStyle->IsEnable() == true);
			CHECK(groupStyle->GetColor() == std::nullopt);
		}
	}
}

TEST_CASE("Resize childs")
{
	WHEN("Child set new frame to group")
	{
		Shapes::Group group(nullptr);

		SimpleShapes::Rectangle r(nullptr);
		RectD shapeFrame1{ 100, 100, 20, 20 };
		r.SetFrame(shapeFrame1);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		RectD shapeFrame2{ 140, 160, 60, 40 };
		r.SetFrame(shapeFrame2);
		group.InsertShape(std::make_shared<SimpleShapes::Rectangle>(r), 0);

		THEN("Child frame will change")
		{
			CHECK(group.GetFrame().left == 100);
			CHECK(group.GetFrame().top == 100);
			CHECK(group.GetFrame().width == 100);
			CHECK(group.GetFrame().height == 100);
			CHECK_NOTHROW(group.SetFrame(RectD{ 50, 50, 50, 50 }));
			CHECK(group.GetFrame().left == 50);
			CHECK(group.GetFrame().top == 50);
			CHECK(group.GetFrame().width == 50);
			CHECK(group.GetFrame().height == 50);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().left == 50);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().top == 50);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().width == 10);
			CHECK(group.GetShapeAtIndex(1)->GetFrame().height == 10);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().left == 70);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().top == 80);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().width == 30);
			CHECK(group.GetShapeAtIndex(0)->GetFrame().height == 20);
		}
	}
}
