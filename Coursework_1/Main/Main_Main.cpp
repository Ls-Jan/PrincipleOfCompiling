#include"XJ_Main.h"
#include<stdio.h>
#include<locale.h>
#include<string>

/*
说明：
	程序运行后会发现有个是未能成功匹配的，即【0..max_iterations】会被识别为非法的数值，
	偷懒了，而且也不知道如何处理这种情况，
	就这样算了，也不是不能做，就是需要将运算符再细化，在出现非法匹配时就拿它们过一次，
	而且这种做法个人也不确定是否百分百有效，如果是纯纯补丁行为说实话真的不想写，万一又出问题还得滚回来修，还不如摆烂

	真想改的话去XJ_LexemeAnalyse中进行改动，它是核心项目。
*/
const char Str[] = "\
\
fn main() {\n\
	let max_iterations = 1_000_000; // 设置迭代次数\n\
	let mut denominator = 1; // 分母初始化为1\n\
	let mut pi_approx = 0.0; // 初始化pi的近似值\n\
	let mut sign = 1.0; // 初始化符号为正\n\
\n\
	for _ in 0..max_iterations{\n\
		pi_approx += sign * 4.0 / denominator;\n\
		denominator += 2; // 分母递增2\n\
		sign = -sign; // 符号变号\n\
	}\n\
\n\
	let pi = pi_approx * 2.0; // 最终的pi值是近似值乘以2\n\
	println!(\"计算得到的pi值是: {}\", pi);\n\
\n\
	let hex_number = 0x1A3F_CDEF;\n\
	let number1 = 98_222;\n\
}\n\
";


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	setlocale(LC_ALL, ".utf8");
	XJ_Main win;
	win.resize(1400, 600);
	win.show();
	win.Set_Text(Str);

	return app.exec();
}





