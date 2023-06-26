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
	unsigned char transparent = 255;

} rect3;

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
	const int fps = 60;
	double time_second = 4.0;
	auto trans_parent = xege::animation::trans(
		static_cast<double>(0),
		static_cast<double>(255),
		fps*5.0,
		xege::animation::builtin_motion::func2
	);
	for (;is_run (); delay_fps (fps), cleardevice ()) {
		xyprintf(1, 1, "fps:%f", getfps());
		eventUpdate ();
		dataUpdate ();
		rect3.transparent = trans_parent();
		drawInterface ();
	}

	closegraph ();
	return 0;
}

void load (void) {
//
	rect3 = { 300, 300, 200, 200 };
	setbkcolor(WHITE);
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

	line(0, 0, 800, 800);

	getimage(unity_img_bg_mix, nullptr, rect3.x, rect3.y, getwidth(unity_img), getheight(unity_img));
	putimage_withalpha(unity_img_bg_mix, unity_img, 0, 0);
	putimage_alphablend(nullptr, unity_img_bg_mix, rect3.x, rect3.y, rect3.transparent);
}
