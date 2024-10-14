#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../lib/Canvas/ICanvas.h"
#include "../lib/Client/Client.h"
#include "../lib/Designer/IDesigner.h"
#include "../lib/Factory/IShapeFactory.h"
#include "../lib/Painter/IPainter.h"
#include "../lib/Shapes/PictureDraft.h"
#include <iostream>

class TestCanvas final : public Canvas::ICanvas
{
public:
	void DrawLine(const Shapes::Point& start, const Shapes::Point& end) override
	{
		m_shapes.clear();
		m_shapes.push_back("line " + std::to_string(start.x) + " " + std::to_string(start.y) + " " + std::to_string(end.x) + " " + std::to_string(end.y));
	}
	void DrawEllipse(const Shapes::Point& center, double hr, double vr) override
	{
		m_shapes.clear();
		m_shapes.push_back("ellipse " + std::to_string(center.x) + " " + std::to_string(center.y) + " " + std::to_string(hr) + " " + std::to_string(vr));
	}
	void SetColor(Shapes::Color color)
	{
		m_color = color;
	}

	~TestCanvas() override = default;

	Shapes::Color m_color;
	std::vector<std::string> m_shapes;
};

class TestDesigner final : public Designer::IDesigner
{
public:
	TestDesigner(std::unique_ptr<ShapeFactory::IShapeFactory>&& factory)
		: m_factory(std::move(factory))
	{
	}

	Shapes::PictureDraft CreateDraft(std::istream& in) override
	{
		Shapes::PictureDraft draft;
		std::string line;

		while (std::getline(in, line))
		{
			draft.AddShape(std::move(m_factory->CreateShape(line)));
		}

		return draft;
	}

	~TestDesigner() override = default;

private:
	std::unique_ptr<ShapeFactory::IShapeFactory> m_factory;
};

class TestLine final : public Shapes::Shape
{
public:
	TestLine(const std::string& color, double p1x, double p1y, double p2x, double p2y)
	{
		SetColor(color);
		m_p1 = Shapes::Point{ p1x, p1y };
		m_p2 = Shapes::Point{ p2x, p2y };
	}
	void Draw(Canvas::ICanvas& canvas)
	{
		canvas.SetColor(GetColor());

		canvas.DrawLine(m_p1, m_p2);
	}

private:
	Shapes::Point m_p1;
	Shapes::Point m_p2;
};

class TestEllipse final : public Shapes::Shape
{
public:
	TestEllipse(const std::string& color, double cx, double cy, double rh, double rv)
	{
		SetColor(color);
		m_c = Shapes::Point{ cx, cy };
		m_rh = rh;
		m_rv = rv;
	}
	void Draw(Canvas::ICanvas& canvas)
	{
		canvas.SetColor(GetColor());

		canvas.DrawEllipse(m_c, m_rh, m_rv);
	}

private:
	Shapes::Point m_c;
	double m_rh;
	double m_rv;
};

class TestFactoryLine final : public ShapeFactory::IShapeFactory
{
public:
	std::unique_ptr<Shapes::Shape> CreateShape(const std::string& shape) override
	{
		const std::regex pattern("^(\\w+)\\s+(\\w+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s*$");
		std::smatch m;
		std::regex_match(shape, m, pattern);

		std::string type = m[1].str();
		std::string color = m[2].str();
		double p1 = std::stod(m[3].str());
		double p2 = std::stod(m[4].str());
		double p3 = std::stod(m[5].str());
		double p4 = std::stod(m[6].str());

		if (type == "line")
		{
			return std::make_unique<TestLine>(color, p1, p2, p3, p4);
		}
		else
		{
			throw std::invalid_argument("Unknown type " + type);
		}
	}

	~TestFactoryLine() override = default;
};

class TestFactoryEllipse final : public ShapeFactory::IShapeFactory
{
public:
	std::unique_ptr<Shapes::Shape> CreateShape(const std::string& shape) override
	{
		const std::regex pattern("^(\\w+)\\s+(\\w+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s+(\-?[\\d\.]+)\\s*$");
		std::smatch m;
		std::regex_match(shape, m, pattern);

		std::string type = m[1].str();
		std::string color = m[2].str();
		double p1 = std::stod(m[3].str());
		double p2 = std::stod(m[4].str());
		double p3 = std::stod(m[5].str());
		double p4 = std::stod(m[6].str());

		if (type == "ellipse")
		{
			return std::make_unique<TestEllipse>(color, p1, p2, p3, p4);
		}
		else
		{
			throw std::invalid_argument("Unknown type " + type);
		}
	}

	~TestFactoryEllipse() override = default;
};

class TestPainter final : public Painter::IPainter
{
public:
	void DrawPicture(Shapes::PictureDraft& draft, Canvas::ICanvas& canvas) override
	{
		for (auto shape = draft.begin(); shape != draft.end(); shape++)
		{
			shape->get()->Draw(canvas);
		}
	}

	~TestPainter() override = default;
};

TEST_CASE("Change factory in designer")
{
	TestPainter painter;
	TestCanvas canvas;
	std::stringstream lineCommand;
	lineCommand << "line red 12.01 22 13.5 14";
	std::stringstream ellipseCommand;
	ellipseCommand << "ellipse blue 22 20 100 50";

	WHEN("Line factory")
	{
		TestDesigner designer(std::make_unique<TestFactoryLine>());

		THEN("Line created successful, ellipse with exception")
		{
			auto draft = designer.CreateDraft(lineCommand);
			painter.DrawPicture(draft, canvas);

			CHECK(canvas.m_color == Shapes::Color::Red);
			CHECK(canvas.m_shapes[0] == "line 12.010000 22.000000 13.500000 14.000000");
			CHECK_THROWS_WITH(designer.CreateDraft(ellipseCommand), "Unknown type ellipse");
		}
	}

	WHEN("Ellipse factory")
	{
		TestDesigner designer(std::make_unique<TestFactoryEllipse>());

		THEN("Line created successful, ellipse with exception")
		{
			auto draft = designer.CreateDraft(ellipseCommand);
			painter.DrawPicture(draft, canvas);

			CHECK(canvas.m_color == Shapes::Color::Blue);
			CHECK(canvas.m_shapes[0] == "ellipse 22.000000 20.000000 100.000000 50.000000");
			CHECK_THROWS_WITH(designer.CreateDraft(lineCommand), "Unknown type line");
		}
	}
}
