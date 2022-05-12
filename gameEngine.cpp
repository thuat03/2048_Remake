#include<vector>
#include<ctime>
#include"gameEngine.h"
#include"position.h"

const int SOHANG = 4;
const int SOCOT = 4;

int** createData() {
	int** data = new int* [SOHANG];
	for (int i = 0; i < SOCOT; i++) {
		data[i] = new int[SOCOT];
	}
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			data[i][j] = 0;
		}
	}
	return data;
}

void getEqualArray(int** data_nguon, int** data_cpy) {
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			data_cpy[i][j] = data_nguon[i][j];
		}
	}
}

void updateData(int** data, char key, int& diem) {
	switch (key) {
	case'w': {
		charW(data, diem);
		break;
	}
	case 'a': {
		charA(data, diem);
		break;
	}
	case 's': {
		charS(data, diem);
		break;
	}
	case'd': {
		charD(data, diem);
		break;
	}
	}
}

bool isPossibleMove(int** data1, int** data2) {
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			if (data1[i][j] != data2[i][j])return true;
		}
	}
	return false;
}

void randomUpgrade(int** data) {
	srand(time(nullptr));
	std::vector<Position>vct;
	Position pos;
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			if (data[i][j] == 0) {
				pos.x = i;
				pos.y = j;
				vct.push_back(pos);
			}
		}
	}
	if (vct.size() == 0)return;
	int randomvitri = rand() % vct.size();
	int ramdomgiatri;
	int percent = rand() % 100;
	if (percent < 95)ramdomgiatri = 2;
	else ramdomgiatri = 4;
	data[vct[randomvitri].x][vct[randomvitri].y] = ramdomgiatri;
}

bool check_lose(int** data) {
	int n = 0;
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			if (data[i][j] == 0)return false;
		}
	}
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT - 1; j++) {
			if (data[i][j] != data[i][j + 1])n++;
		}
	}
	for (int i = 0; i < SOCOT; i++) {
		for (int j = 0; j < SOHANG - 1; j++) {
			if (data[j][i] != data[j + 1][i])n++;
		}
	}
	if (n == 24)return true;
	return false;
}

bool check_win(int** data) {
	for (int i = 0; i < SOHANG; i++) {
		for (int j = 0; j < SOCOT; j++) {
			if (data[i][j] == 64)return true;
		}
	}
	return false;
}

void charW(int** data, int& diem) {
	for (int i = 0; i < SOCOT; i++) {
		if (data[0][i] == data[1][i] && data[0][i] != 0) {
			data[0][i] *= 2;		//2 2 x y
			diem += data[0][i];
			data[1][i] = data[2][i];
			data[2][i] = data[3][i];
			data[3][i] = 0;
			if (data[1][i] == data[2][i]) {
				data[1][i] *= 2;
				diem += data[1][i];
				data[2][i] = 0;
			}
			continue;
		}

		if (data[0][i] == data[2][i] && data[1][i] == 0 && data[0][i] != 0) {
			if (data[3][i] == 0) {
				data[0][i] *= 2;		//2 0 2 x
				diem += data[0][i];
				data[2][i] = 0;
			}
			else {
				data[0][i] *= 2;
				data[2][i] = 0;
				data[1][i] = data[3][i];
				data[3][i] = 0;
			}
			continue;
		}
		if (data[0][i] == data[3][i] && data[1][i] == 0 && data[2][i] == 0 && data[0][i] != 0) {
			data[0][i] *= 2;			//2 0 0 2
			diem += data[0][i];
			data[3][i] = 0;
			continue;
		}
		if (data[1][i] == data[2][i] && data[1][i] != 0) {
			if (data[0][i] == 0) {		//0 2 2 y
				data[0][i] = 2 * data[1][i];
				diem += data[0][i];
				if (data[3][i] == 0) {
					data[1][i] = 0;
					data[2][i] = 0;
				}
				else {
					data[1][i] = data[3][i];
					data[2][i] = 0;
					data[3][i] = 0;
				}

			}
			else {
				data[1][i] *= 2;		//x 2 2 y
				diem += data[1][i];
				if (data[3][i] == 0) {
					data[2][i] = 0;
				}
				else {
					data[2][i] = data[3][i];
					data[3][i] = 0;
				}
			}
			continue;
		}
		if (data[1][i] == data[3][i] && data[2][i] == 0 && data[1][i] != 0) {
			if (data[0][i] == 0) {//0 2 0 2
				data[0][i] = 2 * data[1][i];
				diem += data[0][i];
				data[1][i] = 0;
				data[3][i] = 0;
			}
			else {//x 2 0 2
				data[1][i] *= 2;
				data[3][i] = 0;
			}
			continue;
		}
		if (data[2][i] == data[3][i] && data[2][i] != 0) {//x y 2 2
			if (data[0][i] == 0 && data[1][i] == 0) {
				data[0][i] = 2 * data[2][i];
				diem += data[0][i];
				data[2][i] = 0;
				data[3][i] = 0;
			}
			if (data[0][i] == 0 && data[1][i] != 0 || data[0][i] != 0 && data[1][i] == 0) {
				if (data[0][i] == 0)data[0][i] = data[1][i];
				data[1][i] = 2 * data[2][i];
				diem += data[1][i];
				data[2][i] = 0;
				data[3][i] = 0;
			}
			if (data[0][i] != 0 && data[1][i] != 0) {
				data[2][i] *= 2;
				diem += data[2][i];
				data[3][i] = 0;
			}
			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] == 0) {	//0 x 0 0
			data[0][i] = data[1][i];
			data[1][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] == 0) {	//0 0 x 0
			data[0][i] = data[2][i];
			data[2][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] == 0 && data[2][i] == 0 && data[3][i] != 0) {	//0 0 0 x
			data[0][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] != 0 && data[3][i] == 0) {	//0 x y 0
			data[0][i] = data[1][i];
			data[1][i] = data[2][i];
			data[2][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] != 0) {	//0 x 0 y
			data[0][i] = data[1][i];
			data[1][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] != 0) {	//0 0 x y
			data[0][i] = data[2][i];
			data[1][i] = data[3][i];
			data[2][i] = 0;
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] != 0 && data[3][i] != 0) {	//0 x y z
			data[0][i] = data[1][i];
			data[1][i] = data[2][i];
			data[2][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] == 0) {	//x 0 y 0
			data[1][i] = data[2][i];
			data[2][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] == 0 && data[3][i] != 0) {	//x 0 0 y
			data[1][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] != 0) {	//x 0 y z
			data[1][i] = data[2][i];
			data[2][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] != 0) {	//x y 0 z
			data[2][i] = data[3][i];
			data[3][i] = 0;

			continue;
		}
	}
}

void charS(int** data, int& diem) {
	for (int i = 0; i < SOCOT; i++) {
		if (data[2][i] == data[3][i] && data[2][i] != 0) {
			data[3][i] *= 2;		//x y 2 2
			diem += data[3][i];
			data[2][i] = data[1][i];
			data[1][i] = data[0][i];
			data[0][i] = 0;
			if (data[2][i] == data[1][i]) {
				data[2][i] *= 2;
				diem += data[2][i];
				data[1][i] = 0;
			}
			continue;
		}

		if (data[3][i] == data[1][i] && data[2][i] == 0 && data[3][i] != 0) {
			if (data[0][i] == 0) {
				data[3][i] *= 2;		//x 2 0 2
				diem += data[3][i];
				data[1][i] = 0;
			}
			else {
				data[3][i] *= 2;
				diem += data[3][i];
				data[1][i] = 0;
				data[2][i] = data[0][i];
				data[0][i] = 0;
			}
			continue;
		}
		if (data[0][i] == data[3][i] && data[1][i] == 0 && data[2][i] == 0 && data[0][i] != 0) {
			data[3][i] *= 2;			//2 0 0 2
			diem += data[3][i];
			data[0][i] = 0;
			continue;
		}
		if (data[1][i] == data[2][i] && data[1][i] != 0) {
			if (data[3][i] == 0) {		//y 2 2 0
				data[3][i] = 2 * data[1][i];
				diem += data[3][i];
				if (data[0][i] == 0) {
					data[1][i] = 0;
					data[2][i] = 0;
				}
				else {
					data[2][i] = data[0][i];
					data[1][i] = 0;
					data[0][i] = 0;
				}

			}
			else {
				data[2][i] *= 2;		//x 2 2 y
				diem += data[2][i];
				if (data[0][i] == 0) {
					data[1][i] = 0;
				}
				else {
					data[1][i] = data[0][i];
					data[0][i] = 0;
				}
			}
			continue;
		}
		if (data[0][i] == data[2][i] && data[1][i] == 0 && data[0][i] != 0) {
			if (data[3][i] == 0) {//2 0 2 0
				data[3][i] = 2 * data[2][i];
				diem += data[3][i];
				data[2][i] = 0;
				data[0][i] = 0;
			}
			else {//2 0 2 x
				data[2][i] *= 2;
				diem += data[2][i];
				data[0][i] = 0;
			}
			continue;
		}
		if (data[0][i] == data[1][i] && data[1][i] != 0) {//2 2 x y
			if (data[2][i] == 0 && data[3][i] == 0) {
				data[3][i] = 2 * data[1][i];
				diem += data[3][i];
				data[1][i] = 0;
				data[0][i] = 0;
			}
			if (data[2][i] == 0 && data[3][i] != 0 || data[2][i] != 0 && data[3][i] == 0) {
				if (data[3][i] == 0)data[3][i] = data[2][i];
				data[2][i] = 2 * data[1][i];
				diem += data[2][i];
				data[1][i] = 0;
				data[0][i] = 0;
			}
			if (data[3][i] != 0 && data[2][i] != 0) {
				data[1][i] *= 2;
				diem += data[1][i];
				data[0][i] = 0;
			}
			continue;
		}
		if (data[0][i] == 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] == 0) {	//0 0 x 0
			data[3][i] = data[2][i];
			data[2][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] == 0) {	//0 x 0 0
			data[3][i] = data[1][i];
			data[1][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] == 0 && data[3][i] == 0) {	//x 0 0 0
			data[3][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] != 0 && data[3][i] == 0) {	//0 x y 0
			data[3][i] = data[2][i];
			data[2][i] = data[1][i];
			data[1][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] == 0) {	//x 0 y 0
			data[3][i] = data[2][i];
			data[2][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] == 0) {	//x y 0 0
			data[3][i] = data[1][i];
			data[2][i] = data[0][i];
			data[1][i] = 0;
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] != 0 && data[2][i] != 0 && data[3][i] == 0) {	//x y z 0
			data[3][i] = data[2][i];
			data[2][i] = data[1][i];
			data[1][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] == 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] != 0) {	//0 x 0 y
			data[2][i] = data[1][i];
			data[1][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] == 0 && data[3][i] != 0) {	//x 0 0 y
			data[2][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] != 0 && data[2][i] == 0 && data[3][i] != 0) {	//x y 0 z
			data[2][i] = data[1][i];
			data[1][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
		if (data[0][i] != 0 && data[1][i] == 0 && data[2][i] != 0 && data[3][i] != 0) {	//x 0 y z
			data[1][i] = data[0][i];
			data[0][i] = 0;

			continue;
		}
	}
}

void charA(int** data, int& diem) {
	for (int i = 0; i < SOCOT; i++) {
		if (data[i][0] == data[i][1] && data[i][0] != 0) {
			data[i][0] *= 2;		//2 2 x y
			diem += data[i][0];
			data[i][1] = data[i][2];
			data[i][2] = data[i][3];
			data[i][3] = 0;
			if (data[i][1] == data[i][2]) {
				data[i][1] *= 2;
				diem += data[i][1];
				data[i][2] = 0;
			}
			continue;
		}

		if (data[i][0] == data[i][2] && data[i][1] == 0 && data[i][0] != 0) {
			if (data[i][3] == 0) {
				data[i][0] *= 2;		//2 0 2 x
				diem += data[i][0];
				data[i][2] = 0;
			}
			else {
				data[i][0] *= 2;
				data[i][2] = 0;
				data[i][1] = data[3][i];
				data[i][3] = 0;
			}
			continue;
		}
		if (data[i][0] == data[i][3] && data[i][1] == 0 && data[i][2] == 0 && data[i][0] != 0) {
			data[i][0] *= 2;			//2 0 0 2
			diem += data[i][0];
			data[i][3] = 0;
			continue;
		}
		if (data[i][1] == data[i][2] && data[i][1] != 0) {
			if (data[i][0] == 0) {		//0 2 2 y
				data[i][0] = 2 * data[i][1];
				diem += data[i][0];
				if (data[i][3] == 0) {
					data[i][1] = 0;
					data[i][2] = 0;
				}
				else {
					data[i][1] = data[3][i];
					data[i][2] = 0;
					data[i][3] = 0;
				}

			}
			else {
				data[i][1] *= 2;		//x 2 2 y
				diem += data[i][1];
				if (data[i][3] == 0) {
					data[i][2] = 0;
				}
				else {
					data[i][2] = data[i][3];
					data[i][3] = 0;
				}
			}
			continue;
		}
		if (data[i][1] == data[i][3] && data[i][2] == 0 && data[i][1] != 0) {
			if (data[i][0] == 0) {//0 2 0 2
				data[i][0] = 2 * data[i][1];
				diem += data[i][0];
				data[i][1] = 0;
				data[i][3] = 0;
			}
			else {//x 2 0 2
				data[i][1] *= 2;
				diem += data[i][1];
				data[i][3] = 0;
			}
			continue;
		}
		if (data[i][2] == data[i][3] && data[i][2] != 0) {//x y 2 2
			if (data[i][0] == 0 && data[i][1] == 0) {
				data[i][0] = 2 * data[i][2];
				diem += data[i][0];
				data[i][2] = 0;
				data[i][3] = 0;
			}
			if (data[i][0] == 0 && data[i][1] != 0 || data[i][0] != 0 && data[i][1] == 0) {
				if (data[i][0] == 0)data[i][0] = data[i][1];
				data[i][1] = 2 * data[i][2];
				diem += data[i][1];
				data[i][2] = 0;
				data[i][3] = 0;
			}
			if (data[i][0] != 0 && data[i][1] != 0) {
				data[i][2] *= 2;
				diem += data[i][2];
				data[i][3] = 0;
			}
			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] == 0) {	//0 x 0 0
			data[i][0] = data[i][1];
			data[i][1] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] == 0) {	//0 0 x 0
			data[i][0] = data[i][2];
			data[i][2] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] == 0 && data[i][2] == 0 && data[i][3] != 0) {	//0 0 0 x
			data[i][0] = data[i][3];
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] != 0 && data[i][3] == 0) {	//0 x y 0
			data[i][0] = data[i][1];
			data[i][1] = data[i][2];
			data[i][2] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] != 0) {	//0 x 0 y
			data[i][0] = data[i][1];
			data[i][1] = data[i][3];
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] != 0) {	//0 0 x y
			data[i][0] = data[i][2];
			data[i][1] = data[i][3];
			data[i][2] = 0;
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] != 0 && data[i][3] != 0) {	//0 x y z
			data[i][0] = data[i][1];
			data[i][1] = data[i][2];
			data[i][2] = data[i][3];
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] == 0) {	//x 0 y 0
			data[i][1] = data[i][2];
			data[i][2] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] == 0 && data[i][3] != 0) {	//x 0 0 y
			data[i][1] = data[i][3];
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] != 0) {	//x 0 y z
			data[i][1] = data[i][2];
			data[i][2] = data[i][3];
			data[i][3] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] != 0) {	//x y 0 z
			data[i][2] = data[i][3];
			data[i][3] = 0;

			continue;
		}
	}
}

void charD(int** data, int& diem) {
	for (int i = 0; i < SOCOT; i++) {
		if (data[i][2] == data[i][3] && data[i][2] != 0) {
			data[i][3] *= 2;		//x y 2 2
			diem += data[i][3];
			data[i][2] = data[i][1];
			data[i][1] = data[i][0];
			data[i][0] = 0;
			if (data[i][2] == data[i][1]) {
				data[i][2] *= 2;
				diem += data[i][2];
				data[i][1] = 0;
			}
			continue;
		}

		if (data[i][3] == data[i][1] && data[i][2] == 0 && data[i][3] != 0) {
			if (data[i][0] == 0) {
				data[i][3] *= 2;		//x 2 0 2
				diem += data[i][3];
				data[i][1] = 0;
			}
			else {
				data[i][3] *= 2;
				diem += data[i][3];
				data[i][1] = 0;
				data[i][2] = data[i][0];
				data[i][0] = 0;
			}
			continue;
		}
		if (data[i][0] == data[i][3] && data[i][1] == 0 && data[i][2] == 0 && data[i][0] != 0) {
			data[i][3] *= 2;			//2 0 0 2
			diem += data[i][3];
			data[i][0] = 0;
			continue;
		}
		if (data[i][1] == data[i][2] && data[i][1] != 0) {
			if (data[i][3] == 0) {		//y 2 2 0
				data[i][3] = 2 * data[i][1];
				diem += data[i][3];
				if (data[i][0] == 0) {
					data[i][1] = 0;
					data[i][2] = 0;
				}
				else {
					data[i][2] = data[i][0];
					data[i][1] = 0;
					data[i][0] = 0;
				}

			}
			else {
				data[i][2] *= 2;		//x 2 2 y
				diem += data[i][2];
				if (data[i][0] == 0) {
					data[i][1] = 0;
				}
				else {
					data[i][1] = data[i][0];
					data[i][0] = 0;
				}
			}
			continue;
		}
		if (data[i][0] == data[i][2] && data[i][1] == 0 && data[i][0] != 0) {
			if (data[i][3] == 0) {//2 0 2 0
				data[i][3] = 2 * data[2][2];
				diem += data[i][3];
				data[i][2] = 0;
				data[i][0] = 0;
			}
			else {//2 0 2 x
				data[i][2] *= 2;
				diem += data[i][2];
				data[i][0] = 0;
			}
			continue;
		}
		if (data[i][0] == data[i][1] && data[i][1] != 0) {//2 2 x y
			if (data[i][2] == 0 && data[i][3] == 0) {
				data[i][3] = 2 * data[i][1];
				diem += data[i][3];
				data[i][1] = 0;
				data[i][0] = 0;
			}
			if (data[i][2] == 0 && data[i][3] != 0 || data[i][2] != 0 && data[i][3] == 0) {
				if (data[i][3] == 0)data[i][3] = data[i][2];
				data[i][2] = 2 * data[i][1];
				diem += data[i][2];
				data[i][1] = 0;
				data[i][0] = 0;
			}
			if (data[i][3] != 0 && data[i][2] != 0) {
				data[i][1] *= 2;
				diem += data[i][1];
				data[i][0] = 0;
			}
			continue;
		}
		if (data[i][0] == 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] == 0) {	//0 0 x 0
			data[i][3] = data[i][2];
			data[i][2] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] == 0) {	//0 x 0 0
			data[i][3] = data[i][1];
			data[i][1] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] == 0 && data[i][3] == 0) {	//x 0 0 0
			data[i][3] = data[i][0];
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] != 0 && data[i][3] == 0) {	//0 x y 0
			data[i][3] = data[i][2];
			data[i][2] = data[i][1];
			data[i][1] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] == 0) {	//x 0 y 0
			data[i][3] = data[i][2];
			data[i][2] = data[i][0];
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] == 0) {	//x y 0 0
			data[i][3] = data[i][1];
			data[i][2] = data[i][0];
			data[i][1] = 0;
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] != 0 && data[i][2] != 0 && data[i][3] == 0) {	//x y z 0
			data[i][3] = data[i][2];
			data[i][2] = data[i][1];
			data[i][1] = data[i][0];
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] == 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] != 0) {	//0 x 0 y
			data[i][2] = data[i][1];
			data[i][1] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] == 0 && data[i][3] != 0) {	//x 0 0 y
			data[i][2] = data[i][0];
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] != 0 && data[i][2] == 0 && data[i][3] != 0) {	//x y 0 z
			data[i][2] = data[i][1];
			data[i][1] = data[i][0];
			data[i][0] = 0;

			continue;
		}
		if (data[i][0] != 0 && data[i][1] == 0 && data[i][2] != 0 && data[i][3] != 0) {	//x 0 y z
			data[i][1] = data[i][0];
			data[i][0] = 0;

			continue;
		}
	}
}

void deleteData(int** data) {
	for (int i = 0; i < SOHANG; i++) {
		delete[]data[i];
	}
	delete[]data;
}