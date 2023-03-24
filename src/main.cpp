#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <cstdio>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <vector>
#include <iostream>

#include <iomanip>
using namespace std;

uint8_t palette[8 * 3] = {
	0, 0, 0,
	255, 255, 255,
	67, 138, 28,
	100, 64, 255,
	191, 0, 0,
	255, 243, 56,
	232, 126, 0,
	194, 164, 244};

int depalette(uint8_t *color)
{
	int p;
	int mindiff = 100000000;
	int bestc = 0;
	for (p = 0; p < sizeof(palette) / 3; p++)
	{
		int diffr = ((int)color[0]) - ((int)palette[p * 3 + 0]);
		int diffg = ((int)color[1]) - ((int)palette[p * 3 + 1]);
		int diffb = ((int)color[2]) - ((int)palette[p * 3 + 2]);
		int diff = (diffr * diffr) + (diffg * diffg) + (diffb * diffb);
		if (diff < mindiff)
		{
			mindiff = diff;
			bestc = p;
		}
	}
	return bestc;
}

int img2carray(int argc, char **argv)
{
	// readfile2();
	ofstream fout;
	if (argc < 2)
	{
		fprintf(stderr, "Usage: converter [image file] [out file]\n");
		printf("Press Enter to exit.");
		getchar();
		return -1;
	}

	fout.open(argv[2]);
	int x, y, n;
	unsigned char *data = stbi_load(argv[1], &x, &y, &n, 0);
	if (!data)
	{
		fprintf(stderr, "Error: Can't open image.\n");
		printf("Press Enter to exit.");
		getchar();
		return -6;
	}
	if ((x != 600) && (x != 640) && (x != 800))
	{
		fprintf(stderr, "Error: Image dimensions must be 600*448/640*400/800*480.\n");
		printf("Press Enter to exit.");
		getchar();
		return -2;
	}
	if (x == 600 && y > 448)
	{
		y = 448;
	}
	if (x == 640 && y > 400)
	{
		y = 400;
	}
	if (x == 800 && y > 480)
	{
		y = 480;
	}

	int i, j;

	int num = 0;
	char buf[256];
	sprintf(buf, "#include \"img_local.h\" \r\n");
	fout << string(buf);
	sprintf(buf, "uint8_t img_local[%d] = {\r\n", x * y / 2);
	fout << string(buf);
	for (j = 0; j < y; j++)
	{
		for (i = 0; i < x / 2; i++)
		{
			int c1 = depalette(data + n * (i * 2 + x * j));
			int c2 = depalette(data + n * (i * 2 + x * j + 1));
			char uc = c2 | (c1 << 4);

			sprintf(buf, "0x%02X,", uc);
			fout << string(buf);
			if (num++ == 15)
			{
				sprintf(buf, "\r\n");
				fout << string(buf);
				num = 0;
			}
		}
	}
	sprintf(buf, "};\r\n");
	fout << string(buf);
	fout.close();
	stbi_image_free(data);
	return 0;
}

void readfile()
{
	const std::string inputFile = "ota.bin";
	std::ifstream infile(inputFile, std::ios_base::binary);

	std::vector<char> buffer;

	// get length of file
	infile.seekg(0, infile.end);
	size_t length = infile.tellg();
	infile.seekg(0, infile.beg);

	// read file
	if (length > 0)
	{
		buffer.resize(length);
		infile.read(&buffer[0], length);

		char buf[16];
		cout << buffer.size()<<endl;
		for (int j = 0; j < buffer.size(); j++)
		{
			sprintf(buf, "0x%02x, ", (unsigned char)buffer.at(j));
			cout << string(buf);
		}
	}
}
void add_file(ofstream out, char const* data, char * buf){
	sprintf(buf, data);
	out << string(buf);
}

void file2carray(int argc, char **argv)
{
	ofstream fout, fout2;
	if (argc < 2)
	{
		fprintf(stderr, "Usage: converter [image file] [out file]\n");
		printf("Press Enter to exit.");
		getchar();
	}
	string filename = argv[1];
	fout.open(filename+".c");
	fout2.open(filename+".go");
	cout << argv[2] << "-" << argv[1] << endl;
	const std::string inputFile = argv[2];
	std::ifstream infile(inputFile, std::ios_base::binary);
	std::vector<char> buffer;
	// get length of file
	infile.seekg(0, infile.end);
	size_t length = infile.tellg();
	infile.seekg(0, infile.beg);
	int rows = 200;
	// read file
	if (length > 0)
	{
		int ota_size = length;
		cout << length << endl;
		buffer.resize(length);
		infile.read(&buffer[0], length);
		char buf[256];
		sprintf(buf, "#include \"fw_local.h\" \r\n");
		fout << string(buf);

		sprintf(buf, "package main \r\n");
		fout2 << string(buf);
		sprintf(buf, "uint8_t fw_local[%d] = {\r\n", (int)ota_size);
		fout << string(buf);

		sprintf(buf, "var fw_local = []byte{\r\n");
		fout2 << string(buf);
		for (int j = 0; j < ota_size - 1; j++)
		{
			sprintf(buf, "0x%02x, ", (unsigned char)buffer.at(j));
			// cout << string(buf);
			fout << string(buf);
			// sprintf(buf, "0x%02x, ", (unsigned char)buffer.at(j));
			// cout << string(buf);
			fout2 << string(buf);
		}
		sprintf(buf, "0x%02x ", (unsigned char)buffer.at(ota_size - 1));
		fout << string(buf);
		fout2 << string(buf);
		sprintf(buf, "};\r\n");
		fout << string(buf);
		sprintf(buf, "}\r\n");
		fout2 << string(buf);
		fout2.close();
		fout.close();
	}
}

int main(int argc, char **argv)
{
	// readfile();
	file2carray(argc, argv);
}
