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
FileName:		header.h
Make Cmd:		make ass4 - command will create the output file
				to run after the "make command" enter "./ass4"

********/

#include<iostream>
#include<fstream>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include <stdio.h>
#include <stdlib.h>

// structure pointer and declaration that will hold the integer list
struct number;
typedef number * nptrOne;

struct number {
	char singleDigit;
	nptrOne next;
};

// class declaration

class LLONG {

	public:
           LLONG();
           LLONG(int);
           LLONG(const LLONG &);
           ~LLONG();
           void add(const LLONG &);
           void subtract(const LLONG &);
           void multiply(const LLONG &);
           void divide(const LLONG &);
           void mod(const LLONG &);
           std::ostream & output(std::ostream &);
           int compare(const LLONG &);
           // return 0 for equal, 1 for >, -1 for <
           void outputValues();
     private:
     		// native values to the class, the integer list pointer, the length and the sign of the integer
     		nptrOne longInt;
     		int numLength;
     		bool positive;
     		
     		// function is called to compare the signs of two integers and call the appropriate function
     		// according to the size and sign of the integer
     		
			void subtractCond(nptrOne &, nptrOne &, int &, int &, bool &, bool &);
     		void multiplyCond(nptrOne &, nptrOne &, int &, int &, bool &, bool &);
     		
     		// functions perform the basic operations of the values in a linked list
     		void subtractRaw(nptrOne &, nptrOne &, int&, int, bool&, bool&);
     		void addRaw(nptrOne &, nptrOne &, int&, int, bool &, bool);
     		void multiplyRaw(nptrOne &, nptrOne &, int&, int, bool &, bool);
     		void divideRaw(nptrOne &, nptrOne &, int &, int &, bool &, bool&);
     		
     		// compares two digits. can also be used to compare signs
     		int checkDigit(nptrOne, nptrOne, bool, bool, int, int, bool);
     		
     		// performs a quick check on the lengths of two integers and assigns a passed pointer
     		// and length value tot he larger and smaller of the two numbers
     		bool assignAccordingToLength(nptrOne &, nptrOne&, int, int , nptrOne &, nptrOne &, int&, int&, bool&);
     		
     		// used in conjunction with the previous function
     		void setPointers(nptrOne &, nptrOne &, nptrOne &, nptrOne &, nptrOne &, bool, int);
     		
     		// assigns the length of the longer integer based on the use of the previous two functions
     		void assignLengths(int &, int &, int, int, int, bool&);
     		
     		// adds a value to an list
     		void increaseList(nptrOne & list, char value);
     		
     		//adds a single value the inherit class list
     		void listAdd(char digit);
     		
     		//performs a copy of a list
     		void addToList(nptrOne &, nptrOne &, bool);
     		
     		// empties the contents of a passed list
     		void emptyList(nptrOne &);
     		
     		// inserts a value to an existing list passed via a reference pointer
     		void insertToTree(nptrOne &, char);
     		
     		// retrieves the list of an existing passed list
     		int listLength(nptrOne & list);
     		
     		// functions performs the carrying an adding of two numbers
     		void carryAndAdd(bool &, int &, int &);
     		
     		// function initialises a list back to 0 and resets the number count
     		void initaliseZero(nptrOne & list, int&);
     		
};
