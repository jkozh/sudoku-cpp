#include <iostream>
#include <fstream>

using std::cout;

typedef unsigned int ui;
const ui N = 9;


void separator(char a, char b, char c, char d, char e) {
	cout << a;
	for (ui k = 0; k < N/3; k++) {
		for (ui l = 0; l < N; l++) {
			cout << b;
			if (l == 2 || l == 5)
				cout << c;
		}
		if (k != 2) cout << d;
	}
	cout << e;
}


void show(ui a[][N]) {
	separator('\xc9', '\xcd', '\xd1', '\xcb', '\xbb');
	cout << '\n';
	for (ui i = 0; i < N; i++) {
		cout << '\xba';
		for (ui j = 0; j < N; j++) {
			cout << ' ';
			a[i][j] ? cout << a[i][j] : cout << ' ';
			cout << ' ';
			if (j == 2 || j == 5 || j == 8) cout << '\xba'; else cout << '\xb3';
		}
		cout << '\n';
		if (i == 2 || i == 5) separator('\xcc', '\xcd', '\xd8', '\xce', '\xb9');
		else if (i == N-1) separator('\xc8', '\xcd', '\xcf', '\xca', '\xbc');
		else separator('\xc7', '\xc4', '\xc5', '\xd7', '\xb6');
		cout << '\n';
	}
}


bool checkLocation(ui a[][N], ui &row, ui &col);

bool isSafe(ui a[][N], ui row, ui col, ui num);


bool solve(ui a[][N]) {
	ui row, col;
	if (!checkLocation(a, row, col)) return 1;
	for (ui num = 1; num <= N; num++)
		if (isSafe(a, row, col, num)) {
			a[row][col] = num;
			if (solve(a)) return 1;
			a[row][col] = 0;
		}
	return 0;
}


bool checkLocation(ui a[][N], ui &row, ui &col) {
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (a[row][col] == 0) return 1;
	return 0;
}


bool isPossibleRow(ui a[][N], ui row, ui num) {
	for (ui i = 0; i < N; i++)
		if (a[row][i] == num) return 1;
	return 0;
}


bool isPossibleColumn(ui a[][N], ui col, ui num) {
	for (ui i = 0; i < N; i++)
		if (a[i][col] == num) return 1;
	return 0;
}


bool isPossibleBlock(ui a[][N], ui row, ui col, ui num) {
	for (ui i = 0; i < N/3; i++)
		for (ui j = 0; j < N/3; j++)
			if (a[i + row][j +col] == num) return 1;
	return 0;
}


bool isSafe(ui a[][N], ui row, ui col, ui num) {
	return !isPossibleRow(a, row, num) && !isPossibleColumn(a, col, num) && !isPossibleBlock(a, row - row % 3, col - col % 3, num);
}


int main() {
	ui a[N][N] = {};
	std::ifstream f("sudoku.txt");
	if (f.is_open()) {
		for (ui i = 0; i < N; i++)
			for (ui j = 0; j < N; j++) {
				f >> a[i][j];
			}
		f.close();
	}
	else std::cerr << "File not found";
	
	show(a);
	cout << "\n";
	if (solve(a)) show(a);
	else cout << "No solution exists";
	
	std::ofstream myfile("solved.txt");
	if (myfile.is_open()) {
		for (ui i = 0; i < N; i++) {
			for (ui j = 0; j < N; j++)
				myfile << a[i][j] << ' ';
			myfile << "\n";
		}
		myfile.close();
	}
	else std::cerr << "Unable to open file";
	cout << "\n\n";
	return 0;
}