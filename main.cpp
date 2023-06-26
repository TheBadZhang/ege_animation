#include "animation.hpp"
#define SHOW_CONSOLE
#include <graphics.h>
#include <ctime>
#include <vector>
#include <cstdio>
mouse_msg gMouseMsg = { 0 };
key_msg gKeyMsg = { 0 };

using xege::animation::x2;
using xege::animation::operator""pi;
struct {
	int x, y, w, h;
	color_t color;
} rect, rect2, rect3;

PIMAGE pic2;
PIMAGE unity_img;
PIMAGE unity_img_bg_mix;

// 加载函数，用于初始化资源
void load (void);
// 事件更新函数，主要用来接收事件，比如鼠标键盘事件
void eventUpdate (void);
// 输出更新函数，主要用于处理输入
void dataUpdate (void);
// 画面绘制函数，主要用于显示输出
void drawInterface (void);

int main (int argc, char *argv []) {
	// 手动刷新模式
	setinitmode (INIT_RENDERMANUAL);
	// 界面分辨率
	initgraph (800, 800);
	// setbkmode (TRANSPARENT);
	load ();
	std::vector<double> x_motion;
	const int fps = 60;
	double time_second = 4.0;
	rect.x = 100;
	auto x_pos_trans = xege::animation::trans(
		static_cast<double>(rect.x),
		static_cast<double>(rect.x+400),
		fps*time_second,
		xege::animation::builtin_motion::func1
	);
	auto y_pos_trans = xege::animation::trans(
		static_cast<double>(rect.y),
		static_cast<double>(rect.y+400),
		fps*time_second,
		xege::animation::builtin_motion::func2,
		0.5
	);
	auto x_pos_trans2 = xege::animation::trans(
		static_cast<double>(rect2.x),
		static_cast<double>(rect2.x+400),
		fps*3.0,
		xege::animation::builtin_motion::easeInOutElastic,
		// xege::animation::builtin_motion::bezier3(0.68,-0.6,0.32,1.6),
		0.0, true, true
	);
	for (int i = 0; i < fps*3.0; i++) {
		x_motion.push_back(x_pos_trans2());
	}
	auto another_x = xege::animation::trans(x_motion);
	auto y_pos_trans2 = xege::animation::trans(
		static_cast<double>(0),
		static_cast<double>(255),
		fps*5.0,
		xege::animation::builtin_motion::func2
	);
	auto color_trans = xege::animation::trans(
		0, 255, fps*time_second,
		[](double x) { return sin(x*1.0pi); }
	);
	auto color_trans2 = xege::animation::trans(
		255, 0, fps*time_second,
		[](double x) { return sin(x*1.0pi); }
	);
	for (;is_run (); delay_fps (fps), cleardevice ()) {
		xyprintf(1, 1, "fps:%f", getfps());
		eventUpdate ();
		dataUpdate ();
		rect.x = x_pos_trans();
		rect.y = y_pos_trans();
		rect2.y = another_x();
		rect3.w = y_pos_trans2();
		putpixel(rect.x, rect.y, WHITE, pic2);
		putpixel(rect2.x, rect2.y, WHITE, pic2);
		putimage(0, 0, pic2);
		rect.color = EGERGB(255, color_trans(), 255);
		rect2.color = EGERGB(255, color_trans2(), 255);
		drawInterface ();
	}

	closegraph ();
	return 0;
}

void load (void) {
//
	rect = { 100, 100, 200, 200 };
	rect2 = { 100, 100, 200, 200 };
	rect3 = { 300, 300, 200, 200 };
	// setfillcolor(WHITE);
	pic2 = newimage(getwidth(), getheight());
	unity_img = newimage();
	getimage_pngfile(unity_img, "./res/unity2.png");
	unity_img_bg_mix = newimage(getheight(unity_img), getwidth(unity_img));

}
void eventUpdate (void) {
//
	while (mousemsg ()) {
		gMouseMsg = getmouse ();
	}
	while (kbmsg ()) {
		gKeyMsg = getkey ();
	}
}
void dataUpdate (void) {
//

}
void drawInterface (void) {
//
	setbkcolor(WHITE, pic2);
	cleardevice(pic2);
	// line(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	setfillcolor(rect.color);
	bar(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	setfillcolor(rect2.color);
	bar(rect2.x, rect2.y, rect2.x + rect2.w, rect2.y + rect2.h);
	getimage(unity_img_bg_mix, nullptr, rect3.x, rect3.y, getwidth(unity_img), getheight(unity_img));
	putimage_withalpha(unity_img_bg_mix, unity_img, 0, 0);
	putimage_alphablend(nullptr, unity_img_bg_mix, rect3.x, rect3.y, rect3.w);
	// printf("%d\n", err);
}
