#include <functional>
#include <cmath>

namespace xege {
namespace animation {
long double operator"" pi(long double x) { return x*3.1415926; }
// long double operator"" pi(long long x) { return x*3.1415926; }
double x2(double x) { return x*x; }
namespace builtin_motion {

	auto linear = [](double x) { return x; };    // 线性运动
	auto square_speed_up = [](double x) { return x*x; };  // 加速运动
	auto square_speed_down = [](double x) { return 1-(x-1)*(x-1); };  // 减速运动
	auto square_speed_up_reverse = [](double x) { return 1-x*x; };  // 反向加速
	/**
	 * @brief
	 *
	 */
	auto sin_wave = [](double x,
		double amfier = 1.0,
		double offsetx = 0.0,
		double offsety = 0.0) {
			return offsety+amfier*sin((x-offsetx)*1.0pi);
	};
	auto func123 = [](double x) { return 1-4*(x-0.5)*(x-0.5); };
	auto func321 = [](double x) { return 4*(x-0.5)*(x-0.5); };
	auto func1 = [](double x) { return x < 0.5 ? x2(x*2) : 1-x2(x*2-1); };
	auto func2 = [](double x) { return x < 0.5 ? 1-x2((x-0.5)*2) : x2((x-1)*2);};
}

// namespace private_test {

// }

template<typename T>
std::function<T(void)>
trans(T start, T end, unsigned int steps,
	std::function<double(double)> f = [](double x) { return x; },
	double start_time_point = 0.0, bool loop = true) {
	double t = start_time_point;           // 函数参数 t
	unsigned int moved_steps = 0;  // 已经移动的步数
	return [=]() mutable {
		if (t > 1.0) t = 0.0;
		if (moved_steps >= steps) {
			if (loop) {
				moved_steps = 0;
				t = start_time_point;
			} else {
				t = 1.0;
			}
			// t = loop ? start_time_point : 1.0;
		} else {
			t += 1.0 / steps;  // 步进
			++moved_steps;
		}
		return start+(end-start)*f(t);
	};
}


}
}
