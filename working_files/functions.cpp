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
FileName:		functions.cpp
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

// not that for all subtraction and addition functions, the integer one pointer is the one
// that is being operated on and changed

LLONG::LLONG(){

	longInt = NULL;
	positive = true;
	numLength = 0;
}

// assigns the values of another integer from a pre defined class
LLONG::LLONG(const LLONG & exist){
	
	longInt = NULL;
	nptrOne temp = exist.longInt;
	int counter = 0;
	
	while(counter < exist.numLength){

		listAdd(temp->singleDigit);
		temp = temp->next;
		counter = counter + 1;
	}
	
	if(counter == 0){
		nptrOne zeroTemp = new number;
		zeroTemp->singleDigit = '0';
		zeroTemp->next = NULL;
		numLength = 0;
		positive= true;
		longInt = zeroTemp;
		zeroTemp = longInt;
	}
	
	positive = exist.positive;
	numLength = exist.numLength;
}

// creates a list upon passing of an integer value

LLONG::LLONG(int existInt){
	
	longInt = NULL;
	int currentNumber = existInt;
	int mod = 0;
	int digitCount = 0; 
	
	if(existInt < 0){
		positive = false;
	}else {
		positive = true;
	}
	
	do{
		mod = currentNumber % 10;
		currentNumber = currentNumber / 10;
		
		if(!positive){
			mod = mod * -1;
		}
		
		listAdd(mod + '0');

		digitCount = digitCount + 1;
		
	}while(currentNumber != 0);
	
	if(digitCount == 1 && mod == 0){
	
		emptyList(longInt);
	 	initaliseZero(longInt, numLength);
		positive = true;

	}else {
		numLength = digitCount;
	}
}

// destructor function destroys the list after the variable is destroyed
LLONG::~LLONG(){
	
	if(longInt != NULL){
		nptrOne temp = longInt;
		while(longInt->next != NULL){
		
			temp = longInt;
			longInt = longInt->next;
		
			delete temp;
		
		}
		longInt = NULL;
	}
	return;
}

// function inserts the values of the current integer to the ostream object for output
std::ostream & LLONG::output(std::ostream & message){
	
	if(numLength > 0){
	
		char * vals;
		vals = new char[numLength];
		int counter = numLength -1;
		nptrOne lister = longInt;
	  
	  
	  while(lister->next != NULL){
		vals[counter] = lister->singleDigit;
		lister = lister->next;
		counter = counter - 1;
	  }
	  
	vals[0] = lister->singleDigit;
	counter = counter - 1;

		if(!positive){
			message << "-";
		}
		for(int i = 0; i < numLength; i ++){
			message << vals[i];
		}
	}else {
		message << "0" << ", numLength: " << numLength;
	}
	
	return message;
}

// function passes in pointers of the two integers to the actual compare function
int LLONG::compare(const LLONG & exist){

	nptrOne native = longInt;
	nptrOne passed = exist.longInt;
	int existLen = exist.numLength;
	
	int receiveVal = 0;
	
	receiveVal = checkDigit(native, exist.longInt, positive, exist.positive, numLength, exist.numLength, true);
	
	return receiveVal;
}

// constructor calls the subtraction condition function upon call from the main function
void LLONG::subtract(const LLONG & sValue){
	
	nptrOne passedValue = sValue.longInt;
	int passedLength = sValue.numLength;
	bool passedPos = sValue.positive;
	
	subtractCond(longInt, passedValue, numLength, passedLength, positive, passedPos);
	
	return;
}

// function calls the appropriate operation and assigns the appropriate sign based on
// what combination is passed
void LLONG::add(const LLONG & exist) {
	
	nptrOne current = longInt;
	nptrOne passedValue = exist.longInt;
	int passedLength = exist.numLength;
	bool passedPos = exist.positive;
	
	if(positive == false && passedPos == true){
		subtractRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);	
		if(passedLength > numLength){
			positive = false;
		}else {
			positive = true;
		}
	}
	if(positive == true && passedPos == false){
		addRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
		positive = true;
	}
	else{
		addRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
	}
	
	return;
}

// function calls the multiplication condition function upon call from the public section
void LLONG::multiply(const LLONG & multiNum) {
	 
	nptrOne current = longInt;
	nptrOne passedValue = multiNum.longInt;
	int passedLength = multiNum.numLength;
	bool passedPos = multiNum.positive;
	
	multiplyCond(longInt, passedValue, numLength, passedLength, positive, passedPos);

	return;
}

// public divide handles the ordering of signs before calling the divide function
void LLONG::divide(const LLONG & division){

	nptrOne current = longInt;
	nptrOne passedValue = division.longInt;
	int passedLength = division.numLength;
	bool passedPos = division.positive;
	bool currentPos = positive;
	
	if(numLength < passedLength){
		emptyList(longInt);
		initaliseZero(longInt, numLength);
		positive = true;
		return;
		
	}else if(numLength == 0){
		emptyList(longInt);
		initaliseZero(longInt, numLength);
		positive = true;
		return;
	}else if(passedLength == 0){
	
		emptyList(longInt);
		initaliseZero(longInt, numLength);
		positive = true;
		
		std::cout << std::endl;
		std::cout << "The number is undefined" << std::endl;
		std::cout << std::endl;
		return;
	}else {
		
		if(positive == false || passedPos == false){
			positive = false;
		}
		divideRaw(current, passedValue, numLength, passedLength, currentPos, passedPos);
	}
	
	
	return;
}

// sets the sign of the integer based on the combination of signs between two integers
// calls the appropriate function based on the ordering of signs of the two integers
void LLONG::subtractCond(nptrOne & integerOne, nptrOne & integerTwo, int & lengthOne, int & lengthTwo,
bool & positiveOne, bool & positiveTwo){
	
	if(lengthOne == 0 && lengthTwo == 0){
		return;
	}else {
		if(positiveOne == false && positiveTwo == false){
			addRaw(integerOne, integerTwo, lengthOne, lengthTwo, positiveOne, positiveTwo);
			positive = true;
		}
		else if((positiveOne == false || positiveOne == true ) && positiveTwo == false){
			addRaw(integerOne, integerTwo, lengthOne, lengthTwo, positiveOne, positiveTwo);
		}
		else if(lengthOne == 0 && lengthTwo > 0){
			addRaw(integerOne, integerTwo, lengthOne, lengthTwo, positiveOne, positiveTwo);
			positiveOne = false;
			return;
		}else {
			if(lengthOne < lengthTwo){
				positiveOne = false;
			}else if(lengthOne > lengthTwo){
				positiveOne = true;
			}
			subtractRaw(integerOne, integerTwo, lengthOne, lengthTwo, positiveOne, positiveTwo);
		}
	}
}


// sets the sign of the integer based on the combination of signs between two integers
// then calls the multiplication function
void LLONG::multiplyCond(nptrOne & integerOne, nptrOne & integerTwo, int &lengthOne, int & lengthTwo,
bool & positiveOne, bool & positiveTwo){

	if(lengthOne == 0 || lengthTwo == 0){
	
		emptyList(integerOne);
		initaliseZero(integerOne, lengthOne);
		positiveOne = true;
		
		return;
	}else{
		multiplyRaw(integerOne, integerTwo, lengthOne, lengthTwo, positive, positiveTwo); 
	}

	if(positiveOne == false && positiveTwo == false){
		positiveOne = true;
	}
	else if(positiveOne == false || positiveTwo == false){
		positiveOne = false;
	}else {
		positiveOne = true;
	}
			
}

// performs the most basic form of subtraction on two integers

void LLONG::subtractRaw(nptrOne & integerOne, nptrOne & integerTwo, int & lengthOne, int lengthTwo,
bool & positiveOne, bool & positiveTwo){
	
	 int valOne = 0, tempValOne = 0, returnType = 0;
	 int valTwo = 0, subtraction = 0, carry = 0, shortLen = 0, largeLen =0;
	 bool subtractVals = false, innerValue = false, longerSecond= false, lengthTest = false;
	 int counter = 0, returnValue = 0;
	 nptrOne larger, smaller, topInner;
	 nptrOne tempBuildList = NULL;

	lengthTest = assignAccordingToLength(integerOne, integerTwo, lengthOne, lengthTwo, larger, smaller, largeLen, shortLen, longerSecond);
	
	if(!lengthTest){
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, lengthOne, lengthTwo, false);
		setPointers(integerOne, integerTwo, larger, smaller, topInner, false, returnType);
		assignLengths(shortLen, largeLen, lengthOne, lengthTwo, returnType, longerSecond);
	}else{
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, lengthOne, lengthTwo, false);
	}
			
			
	 while(subtractVals == false){
 
		if(larger->next == NULL){
			subtractVals = true;
		}
		
		valOne = int(larger->singleDigit) -48;
		
		if(counter < shortLen){
			valTwo = int(smaller->singleDigit) -48;
		}else {
			valTwo = 0;
		}
		
		
		if(valOne < valTwo){
			nptrOne temp = larger->next;
		
			if(larger->next != NULL && counter < shortLen){
			
				do{
						if(temp->next == NULL){
							innerValue = true;
						}
						
						tempValOne = int(temp->singleDigit) -48;
						
						if(tempValOne > 0){
							tempValOne = tempValOne - 1;
							temp->singleDigit = tempValOne + '0';
							innerValue = true;
							valOne = valOne + 10;
						}
						else if(tempValOne == 0 && temp->next != NULL){
						
							temp->singleDigit = (tempValOne + 10) - 1 + '0';
						}

						tempValOne = 0;
						temp = temp->next;

				}while(innerValue == false);
			}
			tempValOne = 0;
			innerValue = false;
			temp = NULL;
			delete temp;
		}

		subtraction = valOne - valTwo;

		insertToTree(tempBuildList, subtraction + '0');
		
		larger = larger->next;
		innerValue = true;
		
		
		if(counter < shortLen){
			smaller = smaller->next;
		}

		subtraction = 0;
		counter = counter + 1;
		
	 }
	 
	 emptyList(integerOne);
	 lengthOne = 0;
	 addToList(integerOne, tempBuildList, true);
	 lengthOne = counter;
	 emptyList(tempBuildList);
	 
}

// integer one is the list that will be operated on
// performs the most basic form of addition without signs
void LLONG::addRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){


	int valOne = 0, valTwo = 0, sum = 0, carry = 0, counter = 0;
	int largeLen = 0, shortLen = 0, tempOne = 0, tempTwo = 0;
	bool carryIndicate = false, addVals = false, longerSecond = false;
	
	// note native pointer refers to the list of digits that are being added to
	
	nptrOne top, bottom;
	nptrOne topInner;
	nptrOne tempBuildList = NULL;
	int tempBuildLen = 0;
	
	int returnType = 0;
	bool lengthTest = false;
	
	lengthTest = assignAccordingToLength(integerOne, integerTwo, iOneLen, iTwoLen, top, bottom, largeLen, shortLen, longerSecond);
	
	if(!lengthTest){
		
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
		setPointers(integerOne, integerTwo, top, bottom, topInner, false, returnType);
		assignLengths(shortLen, largeLen, iOneLen, iTwoLen, returnType, longerSecond);
	}
	
	while(addVals == false){

		if(top->next == NULL){
			addVals = true;
		}

		valOne = int(top->singleDigit) -48;
		
		if(counter < shortLen){
			valTwo = int(bottom->singleDigit) -48;
		}else {
			valTwo = 0;
		}
			
		sum = valOne + valTwo;
		carryAndAdd(carryIndicate, sum, carry);
		
		if(addVals && carryIndicate){
			increaseList(tempBuildList, sum + '0');
			increaseList(tempBuildList, carry + '0');
			tempBuildLen = tempBuildLen + 1;
			carryIndicate = false;
		}else {
			insertToTree(tempBuildList, sum + '0');
		}

		sum = 0;
		top = top->next;
		
		if(counter < shortLen){
			bottom = bottom->next;
		}
		
		counter = counter + 1;
	}
	
	 emptyList(integerOne);
	 iOneLen = 0;
	 addToList(integerOne, tempBuildList, true);
	 iOneLen = tempBuildLen + counter;
	 emptyList(tempBuildList);
	 
	return;

}

// performs the most basic form of multiplication of two integers
void LLONG::multiplyRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){
	
	nptrOne top, topInner, bottom;
	nptrOne tempBuildList = NULL;
	int tempBuildLen = 0, returnType = 0, counter = 0, currentDenomLen = 0;
	int longLen =0, shortLen = 0, valOne = 0, valTwo = 0, countZero = 0, multiplyTemp = 0, carry = 0;
	bool tempSign = true, denomSign = true, lengthTest = false;
	bool outerLoop = false, innerLoop = false, longerSecond = false, initialZeroAdd = false, carryIndicate = false;
	

	lengthTest = assignAccordingToLength(integerOne, integerTwo, iOneLen, iTwoLen, top, bottom, longLen, shortLen, longerSecond);
	topInner = top;
	
	if(!lengthTest){
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
		setPointers(integerOne, integerTwo, top, bottom, topInner, true, returnType);
		assignLengths(shortLen, longLen, iOneLen, iTwoLen, returnType, longerSecond);
	}
	
	nptrOne currentDenom = NULL;
	
	while(outerLoop == false){

		while(innerLoop == false){
			
			if(topInner->next == NULL){
				innerLoop = true;
			}
			
			valOne = int(topInner->singleDigit) -48;
			
			if(counter < shortLen){
				valTwo = int(bottom->singleDigit) -48;
				multiplyTemp = valOne * valTwo;
			}else {
				valTwo = 1;
				multiplyTemp = valOne;
			}
			
			carryAndAdd(carryIndicate, multiplyTemp, carry);
			
			nptrOne temp = new number;
			temp->singleDigit = multiplyTemp + '0';
			temp->next= NULL;

			if(countZero > 0 && initialZeroAdd){
				for(int i = 0; i < countZero;i++){
					insertToTree(currentDenom, '0');
				}
				initialZeroAdd = false;
			}
			
			insertToTree(currentDenom, temp->singleDigit);
			
			topInner = topInner->next;
			if(innerLoop && carryIndicate){
				increaseList(currentDenom, carry + '0');
				carry = 0;
				carryIndicate = false;
			}
			
			currentDenomLen = currentDenomLen + 1;
		}
		
	  
	  if(counter == 0){
	  	addToList(tempBuildList, currentDenom, true);
	  }else {
	  		tempBuildLen = listLength(tempBuildList);
			addRaw(tempBuildList, currentDenom, tempBuildLen, currentDenomLen, tempSign, denomSign);
			tempBuildLen = listLength(tempBuildList);
		}

		emptyList(currentDenom);
		currentDenom = 0;
		
		if(bottom->next != NULL){
			topInner = top;
			carry = 0;
			carryIndicate = false;
			bottom = bottom->next;
			innerLoop = false;
			valOne = 0;
			valTwo = 0;
			countZero = countZero + 1;
			initialZeroAdd = true;
			valTwo = int(bottom->singleDigit) -48;
			multiplyTemp = 0;
		}else {
			outerLoop = true;
		}
		
		counter = counter + 1;
	}

	 emptyList(integerOne);
	 iOneLen = 0;
	 bool u = true;
	 addToList(integerOne, tempBuildList, u);
	 iOneLen = listLength(tempBuildList);
	 emptyList(tempBuildList);
	 

	return;
}

// performs the most basic form of division on two integers

void LLONG::divideRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int & iTwoLen,
bool & positiveOne, bool & positiveTwo){
		
	nptrOne tempBuild = NULL;
	int tempLen = iTwoLen;
	bool tempPos = positiveTwo;
	
	bool loopEnd = false;
	int loopCount = 0;
	
	addToList(tempBuild, integerTwo, true);
	
	int compare = -10;
	
	while(loopEnd == false){
		
		subtractCond(integerOne, tempBuild, iOneLen, tempLen, positiveOne, tempPos);
		compare = checkDigit(integerOne, tempBuild, positiveOne, tempPos, iOneLen, tempLen, false);
		
		if(compare == -1 || compare == 0){
			loopEnd = true;
		}
		loopCount = loopCount + 1 ;
	}
	
	std::cout << std::endl;
	std::cout << "unfinished values, but the loop count is: " << loopCount << std::endl;
	std::cout << std::endl;
	
	return;
}

void LLONG::mod(const LLONG & mod){

	nptrOne current = longInt;
	nptrOne passedValue = mod.longInt;
	int passedLength = mod.numLength;
	bool passedPos = mod.positive;
	bool currentPos = positive;
	
	if(numLength < passedLength){
		return;
		
	}else if(numLength == 0){
		emptyList(longInt);
		initaliseZero(longInt, numLength);
		positive = true;
		return;
	}else if(passedLength == 0){
		emptyList(longInt);
		initaliseZero(longInt, numLength);
		positive = true;
		std::cout << std::endl;
		std::cout << "The result is not a number" << std::endl;
		std::cout << std::endl;
	}else {
		std::cout << std::endl;
		std::cout << "This is unfinished: " << std::endl;
		std::cout << std::endl;
	}
	
	
	return;
}

// returns an integer value based on two integer pointers and their lengths that are passed to it
// function also accepts a boolean to compare with signs or just plain values

int LLONG::checkDigit(nptrOne integerOne, nptrOne integerTwo, bool positiveOne, bool positiveTwo,
int lengthOne, int lengthTwo, bool compareWithSign){
	
	bool findValue = false, integerOneEnd = false, integerTwoEnd = false;
	int counter = 0, curInt = 0, oInt = 0, oneGreater = 0, twoGreater = 0, max = 0;
	
	if(lengthOne > lengthTwo){
		max = lengthOne;
	}else if(lengthOne < lengthTwo){
		max = lengthTwo;
	}else {
		max = lengthOne;
	}
	
	while(counter < max){
		if(!integerOneEnd){
			curInt =  int(integerOne->singleDigit) -48;
		}else{
			curInt = 0;
		}
		
		if(!integerTwoEnd){
			oInt = int(integerTwo->singleDigit) -48;
		}else{
			oInt = 0;
		}
		
		if(compareWithSign){
			if(!positiveOne && !integerOneEnd){
				curInt = curInt * -1;
			}
			if(!positiveTwo && !integerTwoEnd){
				oInt = oInt * -1;
			}
		}
		if(integerOneEnd && !integerTwoEnd){
			twoGreater = twoGreater + 1;
		}
		if(integerTwoEnd && !integerOneEnd){
			oneGreater = oneGreater + 1;
		}else{
			if(curInt > oInt){
				oneGreater = oneGreater + 1;
			}else if(curInt < oInt){
				twoGreater = twoGreater + 1;
			}else if(curInt == oInt){
				oneGreater = oneGreater + 1;
				twoGreater = twoGreater + 1;
			}
		}
		
		curInt = 0;
		oInt = 0;
		counter = counter + 1;
		
		if(integerOne->next != NULL){
			integerOne = integerOne->next;
		}else {
			if(!integerOneEnd){
				integerOneEnd = true;
			}
		}
		
		if(integerTwo->next != NULL){
			integerTwo = integerTwo->next;
		}else {
			if(!integerTwoEnd){
				integerTwoEnd = true;
			}
		}
	}
	
	int startOne = integerOne->singleDigit;
	int startTwo =  integerTwo->singleDigit;
	
	
	// compare includes the use of signed numbers
	if(compareWithSign){
		if(oneGreater > twoGreater){
			// compare with sign returns a number of one if the number is greater
			return 1;
		}else if(oneGreater < twoGreater){
			//std::cout << "compare twogreater less: " << -1 << std::endl;
			return -1;
		}else if(oneGreater == twoGreater){
			//std::cout << "compare with equal: " << 0 << std::endl;
			return 0;
		}
	}else{
		if(startOne != startTwo){
			if(startOne > startTwo){
				return 1;
			}else{
				return -1;
			}
		}else {
			if(oneGreater > twoGreater){
				return -1;
			}else if(oneGreater < twoGreater){
				return 1;
			}else if(oneGreater == twoGreater){
				return 0;
			}
		}
	}
	
	return 0;
}


// assigns a pointer to a number list based on the length of the list and returns a boolean if a
// difference in lengths is detected, otherwise it returns a false boolean

bool LLONG::assignAccordingToLength(nptrOne & integerOne, nptrOne & integerTwo, int intOneLen,
int intTwoLen , nptrOne & higher, nptrOne & lower, int & higherLen, int& lowerLen, bool & longerSecond){

	if(intOneLen > intTwoLen){
		higher = integerOne;
		lower = integerTwo;
		
		higherLen = intOneLen;
		lowerLen = intTwoLen;
		longerSecond = false;
		return true;
	}
	else if(intOneLen < intTwoLen){
		
		higher = integerTwo;
		lower = integerOne;
		
		higherLen = intTwoLen;
		lowerLen = intOneLen;
		longerSecond = true;
		return true;
		
	}else {
		return false;
	}
	
}

// assigns a pointer to a pointer to an integer list based on a passed case number provided
// by an integer value

void LLONG::setPointers(nptrOne & integerOne, nptrOne & integerTwo, nptrOne & larger,
nptrOne & smaller, nptrOne & topInner, bool topAssign, int returnValue){
	
	switch(returnValue){
		case -1:
			larger = integerTwo;
			smaller = integerOne;
			if(topAssign){
				topInner = integerTwo;
			}
		break;
		
		case 0:
			larger = integerOne;
			smaller = integerTwo;
			if(topAssign){
				topInner = integerOne;
			}
		break;
		
		case 1:
			larger = integerOne;
			smaller = integerTwo;
			if(topAssign){	
				topInner = integerOne;
			}
		break;
	}
	
	return;
}

// assigns a pointer to two different list based on the length of the integer
// sets a boolean if the second integer is greater than the first

void LLONG::assignLengths(int & shortLength, int & largeLength, int lengthOne,
int lengthTwo, int returnType, bool & longerSecond){
	
	switch(returnType){
		case -1:
			largeLength = lengthTwo;
			shortLength = lengthOne;
			longerSecond = true;
		break;
		
		case 0:
			largeLength = lengthOne;
			shortLength = lengthTwo;
			longerSecond = false;
		break;
		
		case 1:
			largeLength = lengthOne;
			shortLength = lengthTwo;
			longerSecond = false;
		break;
	}
	return;
}

// inserts an integer to a list
void LLONG::increaseList(nptrOne & list, char value){
	
	nptrOne temp = new number;
	temp->singleDigit = value;
	temp->next = NULL;
	
	nptrOne cur = list;
	
	while(cur->next != NULL){
		
		
		cur = cur->next;
	}
	
	cur->next = temp;
	temp = list;
	
	cur = NULL;
	delete cur;
	
}

//adds a single value the inherit class list
void LLONG::listAdd(char digit){
	
	nptrOne temp = new number;
	temp->singleDigit = digit;
	temp->next = NULL;
	
	if(longInt == NULL){	
		longInt = temp;
		
	}else {
		nptrOne cur = longInt;
		
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = temp;
		temp = longInt;
	}
	
	return;
}

// copies the values from one list to another
void LLONG::addToList(nptrOne & list, nptrOne & temporaryList, bool copyOrAdd){
	
	bool loop = false;
	
	if(copyOrAdd){
	//	std::cout << "THIS IS IN THE MAIN FIUNCTON for adding: " << std::endl;
		nptrOne cur = temporaryList;
		while(loop == false){
			if(cur->next == NULL){
				loop = true;		
			}
			insertToTree(list, cur->singleDigit);
			cur= cur->next;
		}	
	}
	
	return;
}


// empties a current list of integers
void LLONG::emptyList(nptrOne & list){

	bool removeComplete = false;
	
	nptrOne curDelete = list;
	
	while(removeComplete == false){
		
		
		if(list->next == NULL){
			removeComplete = true;
		}else {
			curDelete = list->next;
			delete list;
		
			list = NULL;
			list = curDelete;
		}
	}
	
	delete list;
	list = NULL;
	
}

// inserts a new node to the current passed list
void LLONG::insertToTree(nptrOne & list, char value){
	
	nptrOne temp = new number;
	temp->singleDigit = value;
	temp->next = NULL;
	
	
	if(list == NULL){
		list = temp;
	}else {
		nptrOne cur = list;
		while(cur->next != NULL){
			cur = cur->next; 
		}
		cur->next = temp;
		temp = list;
	}
	
	return;
}

// retrieves the length of a passed list pointer
int LLONG::listLength(nptrOne & list){

	int length = 0;
	bool end = false;
	
	nptrOne current = list;
	while(end == false){
		if(current->next == NULL){
			end = true;
		}
		current = current->next;
		length = length + 1;
	}
	
	current = NULL;
	delete current;
	
	return length;
}

// function adds the sum of two integers that are passed to it and sets a true boolean if they
// exceed the value of 10
void LLONG::carryAndAdd(bool & carryIndicate, int & sum, int & carry){
	
	if(carryIndicate){
		sum = sum + carry;
		carryIndicate = false;
		carry = 0;
	}
	if(sum > 9){
		carry = sum / 10;
		sum = sum % 10;
		carryIndicate = true;
	}
	
	return;
}

// function resets the list pointer and length to a zero value
void LLONG::initaliseZero(nptrOne & list, int &length){
	
	nptrOne otherTemp = new number;
	otherTemp->singleDigit = '0';
	otherTemp->next = NULL;
	positive = true;
		
	list = otherTemp;
	otherTemp = list;
	
	length = 0;

	return;
}
