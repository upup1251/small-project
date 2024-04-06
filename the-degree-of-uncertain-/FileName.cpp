#include <iostream>
#include <cmath>
using namespace std;

double PIN_JUN_ZHI(const double*,const int);
double Ua(const double*, const int, const double);

int main() {
	while (1) {
		int n;
		cout << "���������ݸ�����" << endl;
		cin >> n;
		double* shuju = new double[n];
		cout << "�������������ֵ��" << endl;
		double ChuShiZhi=0;
		cin >> ChuShiZhi;
		cout << "������" << n << "�����ݵ�ֵ" << endl;
		double JieShouZhi;
		for (int i = 0; i < n; i++) {
			cin >> JieShouZhi;
			shuju[i]=JieShouZhi-ChuShiZhi;
		}
		double PingJunZhi = PIN_JUN_ZHI(shuju, n);
		double UA = Ua(shuju, n, PingJunZhi);
		double YiQiWuCha;
		cout << "�������������" << endl;
		cin >> YiQiWuCha;
		double UB = YiQiWuCha / pow(3, 1.0 / 2);
		double UC = pow((pow(UA, 2) + pow(UB, 2)), 1.0 / 2);
		double U = 2 * UC;
		cout << "ƽ��ֵΪ" << PingJunZhi << endl;
		cout << "UaΪ" << UA << endl;
		cout << "UBΪ" << UB << endl;
		cout << "UΪ" << U << endl;
		cout << "�������ݵĽ��Ϊ��" << endl;
		cout << PingJunZhi << "��" << U << endl<<endl;
		cout << "����y��������������˳�����" << endl;
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