#include <functional>
#include <cmath>

namespace xege {
namespace animation {
long double operator"" pi(long double x) { return x*3.1415926; }
// long double operator"" pi(long long x) { return x*3.1415926; }
double x2(double x) { return x*x; }
double x3(double x) { return x*x*x; }
namespace builtin_motion {

	/**
	 * @brief 贝塞尔运动曲线生成器
	 *
	 * @param x1 P1 x坐标
	 * @param y1 P1 y坐标
	 * @param x2 P2 x坐标
	 * @param y2 P2 y坐标
	 * @return std::function<double(double)>
	 * @retval 返回可接纳的运动曲线函数描述
	 */
	std::function<double(double)> bezier3(double x1, double y1, double x2, double y2) {

		double ax = 3 * x1 - 3 * x2 + 1,
			bx = 3 * x2 - 6 * x1,
			cx = 3 * x1;

		double ay = 3 * y1 - 3 * y2 + 1,
			by = 3 * y2 - 6 * y1,
			cy = 3 * y1;


		auto _bezier3_x = [=](double t) {
			return ((ax * t + bx) * t + cx ) * t;
		};

		auto _bezier3_y = [=](double t) {
			return ((ay * t + by) * t + cy ) * t;
		};

		auto get_t_from_x = [=](double xx) {
			double tolerance = 0.00001,
				t0 = 0.6,
				x = _bezier3_x(t0),
				t;
			while( abs(x - xx) > tolerance ){
				t = t0 - ( _bezier3_x(t0) - xx ) /
					(cx*(1-t0)*(1-t0) + 6*(1-t0)*t0*(x2-x1) + 3*t0*t0*(1-x2));
				t0 = t;
				x = _bezier3_x(t0);
			}
			return t;
		};
		//return 3*(1-t)*(1-t)*t*y1 + 3*(1-t)*t*t*y2 + t*t*t;//这个是返回与x对应的y值
		return [=](double x) -> double {
			return _bezier3_y(get_t_from_x(x));
		};
	}

	/**
	 * @brief 线性运动曲线
	 *
	 */
	auto linear = [](double x) { return x; };
	/**
	 * @brief 线性也可以用贝塞尔曲线表示
	 *
	 */
	auto linear_bezier = bezier3(0.5,0.5,0.5,0.5);
	/**
	 * @brief 平方加速运动（二次方运动曲线）
	 *
	 */
	auto square_speed_up = [](double x) { return x*x; };
	/**
	 * @brief 平方减速运动（二次方运动曲线）
	 *
	 */
	auto square_speed_down = [](double x) { return 1-(x-1)*(x-1); };
	/**
	 * @brief 反向平方加速运动（二次方运动曲线）
	 *
	 */
	auto square_speed_up_reverse = [](double x) { return 1-x*x; };
	/**
	 * @brief 正弦曲线
	 * @param amfier 振幅
	 * @param offsetx x轴偏移
	 * @param offsety y轴偏移
	 * @param angular_frequency 角频率
	 */
	auto sin_wave = [](double x,
		double amfier = 1.0,
		double offsetx = 0.0,
		double offsety = 0.0,
		double angular_frequency = 1.0pi) {
			return offsety+amfier*sin((x-offsetx)*angular_frequency);
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
	double start_time_point = 0.0, bool loop = true, bool reverse = false) {
	double t = start_time_point;           // 函数参数 t
	unsigned int moved_steps = 0;  // 已经移动的步数
	bool reverse_flag = false;
	return [=]() mutable {
		if (t > 1.0) t = 0.0;
		if (t < 0.0) t = 1.0; // start_point 位置矫正
		if (moved_steps >= steps) {
			if (loop) {
				moved_steps = 0;
				if (reverse) reverse_flag = reverse_flag ? false : true;
				t = start_time_point;
			} else {
				t = start_time_point-1.0/steps < 0.0 ? 1.0 : start_time_point-1.0/steps;
			}
			// t = loop ? start_time_point : 1.0;
		} else {
			t += 1.0 / steps;  // 步进
			++moved_steps;
		}

		if (reverse_flag) {
			return start+(end-start) * f(1.0 - t);
		} else {
			return start+(end-start)*f(t);
		}
	};
}

}
}
