#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#define READY 1
using  namespace std;

int main() {
	ifstream file;
	string da[100];
	string dat[100];
	int data[100];
	int i, mode, c = -1;
	string name;
	int id[5], arrival[5], burst[5], deadline[5], period[5], state[2], ceu[5];
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0;
	int n = 0, g = 0;
	int time = 0;
	int curr_process;
	while (cin >> mode >> name) {
		file.open(name, ios::in); //在讀取模式下開啟txt檔
		if (!file)
		{
			cout << "error\n"; //讀檔錯誤
		}
		while (!file.eof()) {

			while (getline(file, da[n], '\n'))	//各行讀取
			{
				if (n != 0 && n != 2) {	//不讀取1.3行
					stringstream linestream(da[n]);
					while (getline(linestream, dat[n], ' ')) {	//以空白分割讀取
						data[g] = atoi(dat[n].c_str());
						if (g % 5 == 1) {
							id[count1] = data[g];	//各行第1個數字為id
							count1++;
						}
						if (g % 5 == 2) {
							arrival[count2] = data[g];	//各行第2個數字為arrival
							count2++;
						}
						if (g % 5 == 3) {
							burst[count3] = data[g];	//各行第3個數字為burst
							count3++;
						}
						if (g % 5 == 4) {
							deadline[count4] = data[g];		//各行第4個數字為deadline
							count4++;
						}
						if (g != 0 && g % 5 == 0) {
							period[count5] = data[g];		//各行第5個數字為period
							count5++;
						}
						g++;

					}
				}
				n++;
			}
		}
		file.close();	//關閉檔案
		if (mode == 0) {	//模式1=RMS
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//判斷時間是否為process到達時間
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght要求長度，讀檔儲存於date[0]
				curr_process = -1;
				for (i = 0; i < count1; i++) {
					if (state[i] == READY && arrival[i] <= time) {	//process已抵達且可進入
						if (c != i) {	//顯示process開始
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//時間已超過process的deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//抵達時間執行調整，每過一周期再次抵達
						deadline[i] = arrival[i] + period[i];	//截止時間執行調整，抵達時間+週期時間
						state[i] = READY;
						sort(period, period + count1);	//以週期排序
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//結束程式
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//判斷已將burst數量跑完，顯示end結束
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//抵達時間執行調整，每過一周期再次抵達
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//截止時間執行調整，抵達時間+週期時間
						state[curr_process] = READY;
						sort(period, period + count1);	//以週期排序
						ceu[curr_process] = 0;
					}
				}
				time++;
			}
		}
		else if (mode == 1) {	//模式2=EDF
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//判斷時間是否為process到達時間
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght要求長度，讀檔儲存於date[0]
				curr_process = -1;
				int deadl, dead = 0;
				for (int j = 0; j < count1; j++) {
					if (deadline[j] > dead) {
						dead = deadline[j];
					}//判斷出最大的deadline
				}
				for (int k = 0; k < count1; k++) {
					if (deadline[k] < dead) {
						deadl = deadline[k];
					}//再由最大的deadline判斷出最小的deadline
				}
				for (i = 0; i < count1; i++) {	//process已抵達且可進入
					if (state[i] == READY && arrival[i] <= time && deadline[i] <= deadl) {	//process deadline須是最接近的
						if (c != i) {	//顯示process開始
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//時間已超過process的deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//抵達時間執行調整，每過一周期再次抵達
						deadline[i] = arrival[i] + period[i];	//截止時間執行調整，抵達時間+週期時間
						state[i] = READY;
						sort(period, period + count1);	//以period排序
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//結束程式
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//判斷已將burst數量跑完，顯示end結束
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//抵達時間執行調整，每過一周期再次抵達
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//截止時間執行調整，抵達時間+週期時間
						state[curr_process] = READY;
						sort(period, period + count1);	//以period排序
						ceu[curr_process] = 0;
					}
				}
				time++;
			}
		}
		else if (mode == 2) {	//模式3=EDF
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//判斷時間是否為process到達時間
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght要求長度，讀檔儲存於date[0]
				curr_process = -1;
				int deadl, dead = 0;
				for (int j = 0; j < count1; j++) {
					if (deadline[j] > dead) {
						dead = deadline[j];
					}//判斷出最大的deadline
				}
				for (int k = 0; k < count1; k++) {
					if (deadline[k] < dead) {
						deadl = deadline[k];
					}//再由最大的deadline判斷出最小的deadline
				}
				for (i = 0; i < count1; i++) {	//process已抵達且可進入
					if (state[i] == READY && arrival[i] <= time && deadline[i] <= deadl) {	//process deadline須是最接近的
						if (c != i) {	//顯示process開始
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//時間已超過process的deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//抵達時間執行調整，每過一周期再次抵達
						deadline[i] = arrival[i] + period[i];	//截止時間執行調整，抵達時間+週期時間
						state[i] = READY;
						sort(period, period + count1);	//以deadline排序
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//結束程式
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//判斷已將burst數量跑完，顯示end結束
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//抵達時間執行調整，每過一周期再次抵達
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//截止時間執行調整，抵達時間+週期時間
						state[curr_process] = READY;
						sort(period, period + count1);	//以deadline排序
						ceu[curr_process] = 0;
					}
				}
				time++;

			}
		}
	}
	return 0;
}
