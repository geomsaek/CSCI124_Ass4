#include<iostream>
#include<fstream>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include <stdio.h>
#include <stdlib.h>

struct number;
typedef number * nptrOne;

struct number {
	char singleDigit;
	nptrOne next;
};

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
           //void mod(const LLONG &);
           std::ostream & output(std::ostream &);
           int compare(const LLONG &);
           void outputValues();
           // return 0 for equal, 1 for >, -1 for <
     private:
     		nptrOne longInt;
     		
     		void subtractRaw(nptrOne &, nptrOne &, int&, int, bool&, bool);
     		void addRaw(nptrOne &, nptrOne &, int&, int, bool &, bool);
     		void multiplyRaw(nptrOne &, nptrOne &, int&, int, bool &, bool);
     		int checkDigit(nptrOne, nptrOne, bool, bool, int, int, bool);
     		void divideRaw(nptrOne &, nptrOne &, int &, int, bool &, bool);
     		
     		bool assignAccordingToLength(nptrOne &, nptrOne&, int, int , nptrOne &, nptrOne &, int&, int&, bool&);
     		
     		void increaseList(nptrOne & list, char value);
     		
     		void setPointers(nptrOne &, nptrOne &, nptrOne &, nptrOne &, nptrOne &, bool, int);
     		void assignLengths(int &, int &, int, int, int, bool&);
     		void listAdd(char digit);
     		void addToList(nptrOne &, nptrOne &, bool);
     		
     		void reduceTree();
     		void emptyList(nptrOne &);
     		void insertToTree(nptrOne &, char);
     		
     		
     		int listLength(nptrOne & list);
     		void convertValues(bool, bool, bool, int &, int &);
     		void carryAndAdd(bool &, int &, int &);
     		bool checkZeros(nptrOne&);
     		void initaliseZero(nptrOne & list, int&);
     		int numLength;
     		bool positive;
     		
};
