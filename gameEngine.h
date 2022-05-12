#pragma once

int** createData();

void getEqualArray(int** data_nguon, int** data_cpy);

void updateData(int** data, char key, int& diem);

bool isPossibleMove(int** data1, int** data2);

void randomUpgrade(int** data);

bool check_lose(int** data);

bool check_win(int** data);

void charW(int** data, int& diem);

void charS(int** data, int& diem);

void charA(int** data, int& diem);

void charD(int** data, int& diem);

void deleteData(int** data);
