#include "animation.hpp"
#define SHOW_CONSOLE
#include <graphics.h>
#include <ctime>
mouse_msg gMouseMsg = { 0 };
key_msg gKeyMsg = { 0 };

using xege::animation::x2;
using xege::animation::operator""pi;
struct {
	int x, y, w, h;
	color_t color;
} rect, rect2;

PIMAGE pic2;

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
		xege::animation::builtin_motion::bezier3(0.68,-0.6,0.32,1.6),
		0.0, true, true
	);
	auto y_pos_trans2 = xege::animation::trans(
		static_cast<double>(rect2.y),
		static_cast<double>(rect2.y+400),
		fps*time_second,
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
		rect2.x = x_pos_trans2();
		// rect2.y = y_pos_trans2();
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
	// setfillcolor(WHITE);

	pic2 = newimage(getwidth(), getheight());
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
	// line(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	setfillcolor(rect.color);
	bar(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	setfillcolor(rect2.color);
	bar(rect2.x, rect2.y, rect2.x + rect2.w, rect2.y + rect2.h);
}
