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
		file.open(name, ios::in); //�bŪ���Ҧ��U�}��txt��
		if (!file)
		{
			cout << "error\n"; //Ū�ɿ��~
		}
		while (!file.eof()) {

			while (getline(file, da[n], '\n'))	//�U��Ū��
			{
				if (n != 0 && n != 2) {	//��Ū��1.3��
					stringstream linestream(da[n]);
					while (getline(linestream, dat[n], ' ')) {	//�H�ťդ���Ū��
						data[g] = atoi(dat[n].c_str());
						if (g % 5 == 1) {
							id[count1] = data[g];	//�U���1�ӼƦr��id
							count1++;
						}
						if (g % 5 == 2) {
							arrival[count2] = data[g];	//�U���2�ӼƦr��arrival
							count2++;
						}
						if (g % 5 == 3) {
							burst[count3] = data[g];	//�U���3�ӼƦr��burst
							count3++;
						}
						if (g % 5 == 4) {
							deadline[count4] = data[g];		//�U���4�ӼƦr��deadline
							count4++;
						}
						if (g != 0 && g % 5 == 0) {
							period[count5] = data[g];		//�U���5�ӼƦr��period
							count5++;
						}
						g++;

					}
				}
				n++;
			}
		}
		file.close();	//�����ɮ�
		if (mode == 0) {	//�Ҧ�1=RMS
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//�P�_�ɶ��O�_��process��F�ɶ�
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght�n�D���סAŪ���x�s��date[0]
				curr_process = -1;
				for (i = 0; i < count1; i++) {
					if (state[i] == READY && arrival[i] <= time) {	//process�w��F�B�i�i�J
						if (c != i) {	//���process�}�l
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//�ɶ��w�W�Lprocess��deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[i] = arrival[i] + period[i];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[i] = READY;
						sort(period, period + count1);	//�H�g���Ƨ�
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//�����{��
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//�P�_�w�Nburst�ƶq�]���A���end����
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[curr_process] = READY;
						sort(period, period + count1);	//�H�g���Ƨ�
						ceu[curr_process] = 0;
					}
				}
				time++;
			}
		}
		else if (mode == 1) {	//�Ҧ�2=EDF
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//�P�_�ɶ��O�_��process��F�ɶ�
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght�n�D���סAŪ���x�s��date[0]
				curr_process = -1;
				int deadl, dead = 0;
				for (int j = 0; j < count1; j++) {
					if (deadline[j] > dead) {
						dead = deadline[j];
					}//�P�_�X�̤j��deadline
				}
				for (int k = 0; k < count1; k++) {
					if (deadline[k] < dead) {
						deadl = deadline[k];
					}//�A�ѳ̤j��deadline�P�_�X�̤p��deadline
				}
				for (i = 0; i < count1; i++) {	//process�w��F�B�i�i�J
					if (state[i] == READY && arrival[i] <= time && deadline[i] <= deadl) {	//process deadline���O�̱���
						if (c != i) {	//���process�}�l
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//�ɶ��w�W�Lprocess��deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[i] = arrival[i] + period[i];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[i] = READY;
						sort(period, period + count1);	//�Hperiod�Ƨ�
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//�����{��
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//�P�_�w�Nburst�ƶq�]���A���end����
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[curr_process] = READY;
						sort(period, period + count1);	//�Hperiod�Ƨ�
						ceu[curr_process] = 0;
					}
				}
				time++;
			}
		}
		else if (mode == 2) {	//�Ҧ�3=EDF
			for (i = 0; i < count1; i++) {
				state[i] = READY;
				ceu[i] = 0;
				if (time == arrival[i]) {	//�P�_�ɶ��O�_��process��F�ɶ�
					cout << time << " t" << i + 1 << ": arrive" << endl;
				}
			}
			while (time <= data[0]) {	//time lenght�n�D���סAŪ���x�s��date[0]
				curr_process = -1;
				int deadl, dead = 0;
				for (int j = 0; j < count1; j++) {
					if (deadline[j] > dead) {
						dead = deadline[j];
					}//�P�_�X�̤j��deadline
				}
				for (int k = 0; k < count1; k++) {
					if (deadline[k] < dead) {
						deadl = deadline[k];
					}//�A�ѳ̤j��deadline�P�_�X�̤p��deadline
				}
				for (i = 0; i < count1; i++) {	//process�w��F�B�i�i�J
					if (state[i] == READY && arrival[i] <= time && deadline[i] <= deadl) {	//process deadline���O�̱���
						if (c != i) {	//���process�}�l
							cout << time << " t" << i + 1 << ": start" << endl;
							c = i;
						}
						curr_process = i;
						break;
					}
				}
				for (i = 0; i < count1; i++) {
					if (deadline[i] <= time) {	//�ɶ��w�W�Lprocess��deadline
						cout << time << " t" << i + 1 << ": deadline miss" << endl;
						arrival[i] += period[i];	//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[i] = arrival[i] + period[i];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[i] = READY;
						sort(period, period + count1);	//�Hdeadline�Ƨ�
						ceu[i] = 0;
						cout << "Simulation terminated" << endl;
						exit(1);	//�����{��
					}
				}

				if (curr_process > -1) {
					//cout << time << " ";
					ceu[curr_process]++;
					if (ceu[curr_process] == burst[curr_process]) {		//�P�_�w�Nburst�ƶq�]���A���end����
						cout << time + 1 << " t" << curr_process + 1 << ": end" << endl;
						arrival[curr_process] += period[curr_process];		//��F�ɶ�����վ�A�C�L�@�P���A����F
						deadline[curr_process] = arrival[curr_process] + period[curr_process];	//�I��ɶ�����վ�A��F�ɶ�+�g���ɶ�
						state[curr_process] = READY;
						sort(period, period + count1);	//�Hdeadline�Ƨ�
						ceu[curr_process] = 0;
					}
				}
				time++;

			}
		}
	}
	return 0;
}
