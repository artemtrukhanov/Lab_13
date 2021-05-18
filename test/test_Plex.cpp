#include <../gtest/gtest.h>
#include <TPlex.h>

TEST(TPlex, can_create_plex)
{
	ASSERT_NO_THROW(TPlex());
}

TEST(TPlex, can_create_some_plex)
{
	TPoint a(12, 23);
	TPoint b(34, 45);
	ASSERT_NO_THROW(TPlex c(&a, &b));
}

TEST(TPlex, can_add_line_in_plex)
{
	TPoint a(12, 23);
	TPoint b(34, 45);
	TPoint c(56, 67);

	TPlex d(&a, &b);

	ASSERT_NO_THROW(d.AddLine(&b, &c));
}

TEST(TLine, can_create_line)
{
	TPoint a(12, 23);
	TPoint b(34, 45);

	ASSERT_NO_THROW(TLine AB(a, b));
}

TEST(TSquare, can_create_square)
{
	TPoint a(12, 23);
	TPoint b(34, 45);
	TPoint c(56, 67);
	TPoint d(89, 110);

	TLine AB(a, b);
	TLine BC(b, c);
	TLine CD(c, d);
	TLine DA(d, a);

	ASSERT_NO_THROW(TSquare ABCD(AB, BC, CD, DA));
}

TEST(TCanvas, can_get_empty_canvas)
{
	ASSERT_NO_THROW(TCanvas canvas);
}

TEST(TCanvas, can_get_canvas_from_plex)
{
	TPoint a(12, 23);
	TPoint b(34, 45);
	TPlex c(&a, &b);

	TCanvas canvas;
	ASSERT_NO_THROW(canvas.AddObj(&c));
}

TEST(TCanvas, can_get_canvas_from_line)
{
	TPoint a(12, 23);
	TPoint b(34, 45);

	TLine AB(a, b);

	TCanvas canvas;
	ASSERT_NO_THROW(canvas.AddObj(&AB));
}

TEST(TCanvas, can_get_canvas_from_point)
{
	TPoint a(12, 23);

	TCanvas canvas;
	ASSERT_NO_THROW(canvas.AddObj(&a));
}

TEST(TCanvas, can_get_canvas_from_square)
{
	TPoint a(12, 23);
	TPoint b(34, 45);
	TPoint c(56, 67);
	TPoint d(89, 110);

	TLine AB(a, b);
	TLine BC(b, c);
	TLine CD(c, d);
	TLine DA(d, a);

	TSquare ABCD(AB, BC, CD, DA);

	TCanvas canvas;
	ASSERT_NO_THROW(canvas.AddObj(&ABCD));
}

TEST(Print, can_print_point)
{
	TPoint a(12, 23);
	ASSERT_NO_THROW(a.Print());
}

TEST(Print, can_print_plex)
{
	TPoint a(12, 23);
	TPoint b(34, 45);

	TPlex plex(&a, &b);
	ASSERT_NO_THROW(plex.Print());
}

TEST(Print, can_print_line)
{
	TPoint a(12, 23);
	TPoint b(34, 45);

	TLine line(a, b);
	ASSERT_NO_THROW(line.Print());
}

TEST(Print, can_use_print_all)
{
	TPoint a(12, 23);
	TPoint b(34, 45);

	TPlex plex(&a, &b);
	ASSERT_NO_THROW(plex.PrintAll());
}