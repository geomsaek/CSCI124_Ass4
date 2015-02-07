/******

Name:			Matthew Saliba
Subject:		CSCI124
Description:	Contains the file to call the functions from the LLONG class

				NOTE: DIVISION AND MOD OPERATIONS HAVEN'T BEEN COMPLETELY IMPLEMENTED
				THEY ONLY WORK FOR OPERATIONS INVOLVING 0. BOTH OPERATIONS HAVE BEEN
				IMPLEMENTED IN A SIMLAR WAY TO HOW C++ HANDLES THE USE OF 0 WHEN DEALING
				WITH THESE OPERATIONS

Student #:		3284165
Date Mod:		13th October 2013
Lab:			A - 0830- 1030
FileName:		main.cpp
Make Cmd:		make ass4 - command will create the output file
				to run after the "make command" enter "./ass4"

********/

#include "header.h"
#include<iostream>
#include<fstream>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
	
	LLONG test(12323);
	LLONG another(222);
	
	
	test.multiply(test);
	test.output(cout << "this is: " ) << endl;
	
	return 0;
}
