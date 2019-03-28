#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using centurion::visuals::Color;
using centurion::Centurion;

namespace CenturionTest
{
	TEST_CLASS(ColorTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			Centurion::Init();
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Centurion::Close();
		}

		TEST_METHOD(GetRed)
		{
			int r = 128;
			Color c = Color(r, 0, 0, 0);
			Assert::AreEqual(r, (int) c.GetRed());
		}
		
		TEST_METHOD(GetGreen)
		{
			int g = 27;
			Color c = Color(0, g, 0, 0);
			Assert::AreEqual(g, (int) c.GetGreen());
		}

		TEST_METHOD(GetBlue)
		{
			int b = 27;
			Color c = Color(0, 0, b, 0);
			Assert::AreEqual(b, (int) c.GetBlue());
		}

		TEST_METHOD(GetAlpha)
		{
			int a = 219;
			Color c = Color(0, 0, 0, a);
			Assert::AreEqual(a, (int) c.GetAlpha());
		}

		TEST_METHOD(Constants)
		{
			Assert::AreEqual(255, (int) Color::MAX_VAL);
			Assert::AreEqual(0, (int) Color::MIN_VAL);

			Color red = Color(255, 0, 0, 255);
			compare(red, Color::RED);

			Color green = Color(0, 255, 0, 255);
			compare(green, Color::GREEN);

			Color blue = Color(0, 0, 255, 255);
			compare(blue, Color::BLUE);

			Color white = Color(255, 255, 255, 255);
			compare(white, Color::WHITE);

			Color black = Color(0, 0, 0, 255);
			compare(black, Color::BLACK);
		}

		void compare(const Color& c1, const Color& c2)
		{
			Assert::AreEqual((int) c1.GetRed(), (int) c2.GetRed());
			Assert::AreEqual((int) c1.GetGreen(), (int) c2.GetGreen());
			Assert::AreEqual((int) c1.GetBlue(), (int) c2.GetBlue());
			Assert::AreEqual((int) c1.GetAlpha(), (int) c2.GetAlpha());
		}
	};
}