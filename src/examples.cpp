/**
 * @file examples.cpp
 * @author Kent Hansen <kenthansen1@gmail.com>
 * @date 8 Jan 2015
 * @brief Example usage of Large-Gap Gray code (LGGC) class.
 *
 * 	1) Shows statistics for LGGC ranging from 3-20 bits
 * 	2) Construction of four different 16-bit codes and their statistics
 *	3) Print of constructed 7-bit code. Note the length of horizontal bit runs
 *
 * For more information, see: http://www.github.com/tckent/largegap-graycode
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "LargeGapGrayCode.h"

void printBinaryCode(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream);
void printBinaryCodeVertical(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream);
void printBinaryCodeCArray(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream);

void printBinaryCodeToFile(const std::vector<std::bitset<20> >& code, int bitWidth, const char* filename, bool vertical = false);
void printBinaryCodeToCFile(const std::vector<std::bitset<20> >& code, int bitWidth, const char* filename);

int main() {
	LargeGapGrayCode lggc;
	std::cout << "####################################################################" << std::endl;
	std::cout << "####### 1)  Printing statistics for all Large-Gap Gray Codes #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	lggc.printAllStatistics();

	std::cout << std::endl << std::endl;
	std::cout << "####################################################################" << std::endl;
	std::cout << "#######  2)  Printing statistics for different 16-bit codes  #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	lggc.printStatisticsHeader();
	lggc.createCodeFromTheorem1(14, 2, 3, 1);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(8, 8, 129, 127);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(9, 7, 65, 63);
	lggc.printStatistics(16);
	lggc.createCodeFromTheorem1(11, 5, 21, 11);
	lggc.printStatistics(16);
	lggc.printStatistics(13);

	std::cout << std::endl << std::endl;
	std::cout << "####################################################################" << std::endl;
	std::cout << "#######       3)  Printing generated 7-bit binary code       #######" << std::endl;
	std::cout << "#######             Note: MinGap = 5 and MaxGap = 11         #######" << std::endl;
	std::cout << "####################################################################" << std::endl << std::endl;
	printBinaryCode(lggc.getBinaryCode(7), 7, std::cout);
    //	printBinaryCodeVertical(lggc.getBinaryCode(7), 7, std::cout);

	printBinaryCodeToFile(lggc.getBinaryCode(16), 16, "16bitcode.txt", true);
	printBinaryCodeToFile(lggc.getBinaryCode(13), 13, "13bitcode.txt", true);
	printBinaryCodeToCFile(lggc.getBinaryCode(13), 13, "large_gap_gray_code_13bit.c");

	return 0;
}


void printBinaryCode(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream)
{
	for(int j = 0; j < bitWidth; ++j)
	{
		for(int i = 0; i < pow(2, bitWidth); i++)
		{
		    stream << code[i][j];
		}
		stream << std::endl;
	}
	stream << std::endl;
}

void printBinaryCodeVertical(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream)
{
    for(int i = 0; i < pow(2, bitWidth); i++)
	{
        for(int j = 0; j < bitWidth; ++j)
        {
		    stream << code[i][j];
		}
		stream << std::endl;
	}
	stream << std::endl;
}

void printBinaryCodeCArray(const std::vector<std::bitset<20> >& code, int bitWidth, std::ostream &stream)
{
    int maxNum = pow(2, bitWidth);
    stream << "unsigned int lggc_" << bitWidth << "[" << maxNum << "] = {" << std::endl;
    int fieldWidth = static_cast<int>(ceil(bitWidth/4.L));
    for(int i = 0; i < maxNum; i++)
	{
        stream << "\t0x" << std::setfill('0') << std::setw(fieldWidth) << std::hex << code[i].to_ulong();
        if (i < maxNum - 1) {
            stream << ",";
        }
        stream << std::endl;
	}
    stream << "};" << std::endl;
}

void printBinaryCodeToFile(const std::vector<std::bitset<20> >& code, int bitWidth, const char* filename, bool vertical)
{
    std::ofstream myfile;
    myfile.open (filename);
    if (myfile.is_open() ) {
        if (vertical) {
            printBinaryCodeVertical(code, bitWidth, myfile);
        } else {
            printBinaryCode(code, bitWidth, myfile);
        }
    }
    myfile.close();
}

void printBinaryCodeToCFile(const std::vector<std::bitset<20> >& code, int bitWidth, const char* filename)
{
    std::ofstream myfile;
    myfile.open (filename);
    if (myfile.is_open() ) {
        printBinaryCodeCArray(code, bitWidth, myfile);
    } else {
        std::cerr << "FAiled to write file: "<< filename << std::endl;
    }
    myfile.close();
}
