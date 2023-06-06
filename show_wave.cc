#include "animation.hpp"
#include <graphics.h>
#include <ctime>

mouse_msg gMouseMsg = { 0 };
key_msg gKeyMsg = { 0 };

using xege::animation::x2;
using xege::animation::operator""pi;
PIMAGE pic2;

// 加载函数，用于初始化资源
void load (void);
// 事件更新函数，主要用来接收事件，比如鼠标键盘事件
void eventUpdate (void);
// 输出更新函数，主要用于处理输入
void dataUpdate (void);
// 画面绘制函数，主要用于显示输出
void drawInterface (void);

std::function<void(void)> draw(PIMAGE pic, int x, int y, int size, std::function<double(double)> func) {
	return [=]() {
		const int fps = 60;
		double time_second = 4.0;
		auto x_pos_trans = xege::animation::trans(
			static_cast<double>(x),
			static_cast<double>(x+size),
			fps*time_second,
			xege::animation::builtin_motion::linear
		);
		auto y_pos_trans = xege::animation::trans(
			static_cast<double>(y+size),
			static_cast<double>(y),
			fps*time_second,
			func
		);
		int lastx = x;
		int lasty = y+size;
		for (size_t i = 0; i < fps*time_second; i++) {
			// putpixel(x_pos_trans(), y_pos_trans(), WHITE, pic);
			int nx = x_pos_trans();
			int ny = y_pos_trans();
			ege_line(lastx, lasty, nx, ny, pic);
			lastx = nx;
			lasty = ny;
		}
	};
}

int main (int argc, char *argv []) {
	// 手动刷新模式
	setinitmode (INIT_RENDERMANUAL);
	// 界面分辨率
	initgraph (800, 800);
	// setbkmode (TRANSPARENT);
	load ();

	const int fps = 60;
	for (;is_run (); delay_fps (fps), cleardevice ()) {
		xyprintf(1, 1, "fps:%f", getfps());
		eventUpdate ();
		dataUpdate ();
		putimage(0, 0, pic2);
		drawInterface ();
	}

	closegraph ();
	return 0;
}

void load (void) {
	pic2 = newimage(getwidth(), getheight());
	ege_enable_aa(true);
	draw(pic2, 100, 100, 100, xege::animation::builtin_motion::func1)();
	draw(pic2, 250, 100, 100, xege::animation::builtin_motion::func2)();
	draw(pic2, 400, 100, 100, xege::animation::builtin_motion::linear)();
	draw(pic2, 550, 100, 100, xege::animation::builtin_motion::sin_wave)();
	draw(pic2, 100, 250, 100, xege::animation::builtin_motion::square_speed_up)();
	draw(pic2, 250, 250, 100, xege::animation::builtin_motion::square_speed_down)();
	// draw(pic2, 400, 250, 100, xege::animation::builtin_motion::square_speed_up_reverse)();
	// draw(pic2, 100, 400, 100, xege::animation::builtin_motion::square_speed_down_reverse)();
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
}
void drawInterface (void) {
}
