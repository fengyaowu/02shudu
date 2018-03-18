#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include"generator.h"
using namespace std;


int init(int argc, char * argv[]);
void printHelp();
auto oFile = fopen("sudoku.txt", "w");

namespace FastIO {
#define BUF_SIZE 5*1024*1024
#define fStream oFile

class ostream {
	char *buf, *p;
public:
	ostream() { buf = new char[BUF_SIZE]; p = buf; }
	void put(char c) {
		if (p - buf == BUF_SIZE) flush();
		*p++ = c;
	}
	void flush() {
		if (p != buf) {
			fwrite(buf, 1, p - buf, fStream);
			p = buf;
		}
	}
	~ostream() { flush(); }
} os;

inline void putc(char x) { os.put(x); }
inline void endl() { os.put('\n'); }
inline void flush() { os.flush(); }
};


int main(int argc,char * argv[])
{
	int n = init(argc, argv);
	if (n <= 0)printHelp();
	InitGenerator();
	//freopen("sudoku.txt", "w", stdout);
	while (n--) {
		int * sudoku = (int(*))SudokuNext();
		if (sudoku == NULL)return 1;
		REPEAT(i, 9)
			REPEAT(j, 9) {
			int temp = *(sudoku + i * 9 + j);
			FastIO::putc(temp + '0');
			if (j == 8)FastIO::endl();
			else FastIO::putc(' ');
		}
		FastIO::endl();
	}
		
	return 0;
}



int init(int argc,char * argv[])
{
	if (argc != 3 || string("-c") != argv[1]) printHelp();
	int c = 0;
	stringstream ss;
	ss << argv[2];
	ss >> c;
	if (c <= 0) printHelp();
	return c;
}

void printHelp()
{
	printf("Usage:\n");
	printf("        -c <positive number>\n");
	exit(1);
}