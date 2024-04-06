#include <iostream>
#include <cmath>
using namespace std;

double PIN_JUN_ZHI(const double*,const int);
double Ua(const double*, const int, const double);

int main() {
	while (1) {
		int n;
		cout << "请输入数据个数：" << endl;
		cin >> n;
		double* shuju = new double[n];
		cout << "请输入初读数的值：" << endl;
		double ChuShiZhi=0;
		cin >> ChuShiZhi;
		cout << "请输入" << n << "个数据的值" << endl;
		double JieShouZhi;
		for (int i = 0; i < n; i++) {
			cin >> JieShouZhi;
			shuju[i]=JieShouZhi-ChuShiZhi;
		}
		double PingJunZhi = PIN_JUN_ZHI(shuju, n);
		double UA = Ua(shuju, n, PingJunZhi);
		double YiQiWuCha;
		cout << "请输入仪器误差" << endl;
		cin >> YiQiWuCha;
		double UB = YiQiWuCha / pow(3, 1.0 / 2);
		double UC = pow((pow(UA, 2) + pow(UB, 2)), 1.0 / 2);
		double U = 2 * UC;
		cout << "平均值为" << PingJunZhi << endl;
		cout << "Ua为" << UA << endl;
		cout << "UB为" << UB << endl;
		cout << "U为" << U << endl;
		cout << "该组数据的结果为：" << endl;
		cout << PingJunZhi << "±" << U << endl<<endl;
		cout << "输入y继续，其余键将退出程序" << endl;
		char c;
		cin >> c;
		if (c != 'y')break;
	}

	return 0;
}
double PIN_JUN_ZHI(const double* pt,const int n) {
	double sum = 0; 
	int i = 0;
	while (i < n) {
		sum += pt[i];
		i++;
	}
	return sum / n;
}
double Ua(const double* pt, const int n,const double ave) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += pow((pt[i] - ave), 2);
	}
	return pow((sum / (n * (n - 1))), 1.0 / 2);
}