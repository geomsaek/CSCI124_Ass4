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

LLONG::LLONG(const LLONG & exist){
	
	longInt = NULL;
	nptrOne temp = exist.longInt;
	int counter = 0;
	
	while(counter < exist.numLength){
		if(temp->singleDigit != '0'){
			listAdd(temp->singleDigit);
			
			counter = counter + 1;
		}
		temp = temp->next;
	}
	
	if(counter == 0){
		longInt = NULL;
		numLength = 0;
	}
	
	positive = exist.positive;
	numLength = exist.numLength;
}

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
		longInt = NULL;
		numLength = 0;
	}else {
		numLength = digitCount;	
	}
}


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
	
}

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
}

std::ostream & LLONG::output(std::ostream & message){

	if(numLength > 0){
		nptrOne temp = longInt;
		char * vals;
		vals = new char[numLength];
		int counter = numLength -1;

		vals[counter] = temp->singleDigit;
		counter = counter - 1;

		while(counter >= 0){
			temp = temp->next;
			vals[counter] = temp->singleDigit;
			counter = counter - 1;
		}

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

int LLONG::compare(const LLONG & exist){

	
	nptrOne native = longInt;
	nptrOne passed = exist.longInt;
	int existLen = exist.numLength;
	
	int receiveVal = 0;
	// return 0 for equal, 1 for >, -1 for <
	receiveVal = checkDigit(native, exist.longInt, positive, exist.positive, numLength, exist.numLength, true);
	
	return receiveVal;
}

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
		}else if(integerTwoEnd && !integerOneEnd){
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
	
	integerOne = NULL;
	delete integerOne;
	integerTwo = NULL;
	delete integerTwo;
	
	if(!compareWithSign){
		if(oneGreater > twoGreater){
			return 1;
		}else if(oneGreater < twoGreater){
			return -1;
		}else if(oneGreater == twoGreater){
			return 0;
		}
	}else{
		if(oneGreater > twoGreater){
			return -1;
		}else if(oneGreater < twoGreater){
			return 1;
		}else if(oneGreater == twoGreater){
			return 0;
		}
	}
	
	return 0;
}


void LLONG::subtract(const LLONG & sValue){
	
	nptrOne current = longInt;
	nptrOne passedValue = sValue.longInt;
	int passedLength = sValue.numLength;
	bool passedPos = sValue.positive;
	
	if(longInt == NULL){
		numLength = 0;
		positive = true;
		return;
	}else {
		if(positive == false && sValue.positive == false){
			addRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
		}
		// call functions according to different signs but then change the signs after ward;
		else {
			subtractRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
		}
		
	}
	
	return;
}

void LLONG::subtractRaw(nptrOne & integerOne, nptrOne & integerTwo, int & lengthOne, int lengthTwo,
bool & positiveOne, bool positiveTwo){
	
	 int valOne = 0, tempValOne = 0;
	 int valTwo = 0, subtraction = 0, carry = 0, shortLen = 0, largeLen =0;
	 bool subtractVals = false, innerValue = false, largerInt = false, longerSecond= false;
	 int counter = 0, returnValue = 0;
	 nptrOne larger, smaller, topInner;
	
	 int returnType = 0;
	
	returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, lengthOne, lengthTwo, false);
	setPointers(integerOne, integerTwo, larger, smaller, topInner, false, returnValue);
	assignLengths(shortLen, largeLen, lengthOne, lengthTwo, returnType, longerSecond);
	bool test = false;
	
	
		while(larger->next != NULL){
			std::cout << "RUN THROUGH: " <<larger->singleDigit << std::endl;
			larger = larger->next;
		}
		std::cout << "OUTER LAST RUN TRHOUGH: " << larger->singleDigit << std::endl;
/*

	
	 while(subtractVals == false){
 
		if(larger->next == NULL){
			std::cout << "END OF LOOP: " << std::endl;
			subtractVals = true;
		}
		valOne = int(larger->singleDigit) -48;
		if(counter < shortLen){
			valTwo = int(smaller->singleDigit) -48;
		}else {
			valTwo = 0;
		}
		std::cout << "INITIAL VAL ONE: " << valOne <<std::endl;
		std::cout << "INITIAL VAL TWO: " << valTwo << std::endl;
		std::cout << std::endl;
		
		if(valOne < valTwo){
			nptrOne temp = larger->next;
			std::cout << "ACCESSIONG THE TEMP NEXT: " << std::endl;
		
			if(larger->next != NULL && counter < shortLen){
				std::cout << "LARGE IS NOT AT THE END" << std::endl;
				do{
					//std::cout << "ADDRESS: " << temp->next << std::endl;
					if(temp->next != NULL){
						if(temp->next == NULL){
							innerValue = true;
						}
					
						tempValOne = int(temp->singleDigit) -48;
						if(tempValOne == 0 && innerValue){
							std::cout << "we are gona hit 0" << std::endl;
						
						}
						else if(tempValOne > 0){
							tempValOne = tempValOne - 1;
							temp->singleDigit = tempValOne + '0';
							innerValue = true;
							valOne = valOne + 10;
						}
						else if(tempValOne == 0 && temp->next != NULL){
						
							temp->singleDigit = (tempValOne + 10) - 1 + '0';
							std::cout << "TEMP CARRY: " << temp->singleDigit << std::endl;
						}

						tempValOne = 0;
						temp = temp->next;
					}else {
						std::cout << "we're gonna hit 0" << std::endl;
						// need to do something now
						positive = true;
						test = true;
						return;
					}

				}while(innerValue == false);
			}
			tempValOne = 0;
			innerValue = false;
			temp = NULL;
			delete temp;
		}

		subtraction = valOne - valTwo;
		std::cout << "SUBTRACITON: " << subtraction << std::endl;

		if(largerInt){	
			smaller->singleDigit = subtraction + '0'; }
		else {
			std::cout << "LONGER native" << std::endl;
			larger->singleDigit = subtraction + '0';
		}
		
		
		larger = larger->next;
		innerValue = true;
		
		if(counter < shortLen){
			smaller = smaller->next;
		}

		subtraction = 0;
		counter = counter + 1;
		std::cout << "COUNTER: " << counter << std::endl;
		 std::cout << std::endl;
		std::cout << std::endl;
	 }
	
	 reduceTree();*/
}

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

void LLONG::checkZeros(){
	
	int counter = 0;
	int zeroCount = 0;
	
	nptrOne cur = longInt;
	while(counter < numLength){
		
		if(cur->singleDigit == '0'){
			zeroCount = zeroCount + 1;
		}
		cur = cur->next;
		counter = counter + 1;
	}
	
	if(zeroCount == counter){
		std::cout << "ALL ZEROS" << std::endl;
		nptrOne temp = new number;
		temp->singleDigit = '0';
		temp->next = NULL;
		emptyList(longInt);
		longInt = temp;
	}else{
		std::cout << "NOT  ALL: " << std::endl;
	}
	cur = NULL;
	delete cur;
	
}

void LLONG::add(const LLONG & exist) {
	
	nptrOne current = longInt;
	nptrOne passedValue = exist.longInt;
	int passedLength = exist.numLength;
	bool passedPos = exist.positive;
	
	addRaw(current, passedValue, numLength, passedLength, positive, passedPos);
	
	return;
}

// integer one is the list that will be operated on

void LLONG::addRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){

	int valOne = 0, valTwo = 0, sum = 0, carry = 0, counter = 0;
	int largeLen = 0, shortLen = 0, tempOne = 0, tempTwo = 0;
	bool carryIndicate = false, addVals = false, largerInt = false, longerSecond = false;
	
	// note native pointer refers to the list of digits that are being added to
	
	nptrOne top, bottom, native = integerOne;
	nptrOne topInner;
	
	int returnType = 0;
	
	returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
	setPointers(integerOne, integerTwo, top, bottom, topInner, false, returnType);
	assignLengths(shortLen, largeLen, iOneLen, iTwoLen, returnType, longerSecond);

	while(addVals == false){

		if(top->next == NULL){
			addVals = true;
		}

		if(counter < shortLen){
			valOne = int(top->singleDigit) -48;
			valTwo = int(bottom->singleDigit) -48;
			tempOne = valOne;
			tempTwo = valTwo;
			sum = valOne + valTwo;
		}else {
			valOne = int(top->singleDigit) -48;
			valTwo = 0;
			sum = valOne + valTwo;
		}

		carryAndAdd(carryIndicate, sum, carry);

		if(addVals && carryIndicate){
			addNewDigit(carry + '0');
			carryIndicate = false;
		}

		native->singleDigit = sum + '0';
		sum = 0;
		native = native->next;
		top = top->next;
	
		nptrOne cur = longInt;
		if(bottom->next != NULL){
			bottom = bottom->next;
		}
		counter = counter + 1;
	}

	bottom = NULL;
	delete bottom;
	top = NULL;
	delete top;
	native = NULL;
	delete native;
}

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

void LLONG::convertValues(bool largerInt, bool otherPos, bool nativePos, int & valOne, int & valTwo){

	if(largerInt){
		if(otherPos == false){
			valOne = valOne * -1;
		}
	}else if(otherPos == false){
		valTwo = valTwo * -1;
	}
	
	if(!largerInt){
		if(!positive){
			valOne = valOne * -1;
		}
	}else {
		if(!positive){
			valTwo = valTwo * -1;
		}	
	}
					
	return;
}

void LLONG::multiply(const LLONG & multiNum) {
	
	nptrOne current = longInt;
	nptrOne passedValue = multiNum.longInt;
	int passedLength = multiNum.numLength;
	bool passedPos = multiNum.positive;
	
	
		multiplyRaw(current, passedValue, numLength, passedLength, positive, passedPos);
	
		if(positive == false && multiNum.positive == false){
			positive = true;
		}
		else if(positive == false || multiNum.positive == false){
			positive = false;
		}else {
			positive = true;
		}
	
	
	return;
}

void LLONG::multiplyRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){

	nptrOne top, topInner, bottom;
	bool outerLoop = false, innerLoop = false, longerSecond = false, initalZeroAdd = false, carryIndicate = false;
	int longLen =0, shortLen = 0, valOne = 0, valTwo = 0, countZero = 0, multiplyTemp = 0, carry = 0;
	
	int returnType = 0;
	
	returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
	setPointers(integerOne, integerTwo, top, bottom, topInner, true, returnType);
	assignLengths(shortLen, longLen, iOneLen, iTwoLen, returnType, longerSecond);
	
	nptrOne list = NULL;
	nptrOne currentDenom = NULL;
	
	valTwo = int(bottom->singleDigit) -48;
	
	while(outerLoop == false){
	
		while(innerLoop == false){
			if(topInner->next == NULL){
				innerLoop = true;
			}
			valOne = int(topInner->singleDigit) -48;
			multiplyTemp = valOne * valTwo;
			
			
			carryAndAdd(carryIndicate, multiplyTemp, carry);
			
			nptrOne temp = new number;
			temp->singleDigit = multiplyTemp + '0';
			temp->next= NULL;

			if(countZero > 0 && initalZeroAdd){
				for(int i = 0; i < countZero;i++){
					insertToTree(currentDenom, '0');
				}
				initalZeroAdd = false;
			}
			insertToTree(currentDenom, temp->singleDigit);
			
			
			topInner = topInner->next;
			if(innerLoop && carryIndicate){
				increaseList(currentDenom, carry + '0');
				carry = 0;
				carryIndicate = false;
			}
		}
		
		if(countZero == 0){
			addToList(list, currentDenom, true);
		}
		else {
			addToList(list, currentDenom, false);
		}
		emptyList(currentDenom);
		if(bottom->next != NULL){
			topInner = top;
			carry = 0;
			carryIndicate = false;
			bottom = bottom->next;
			innerLoop = false;
			valOne = 0;
			valTwo = 0;
			countZero = countZero + 1;
			initalZeroAdd = true;
			valTwo = int(bottom->singleDigit) -48;
			multiplyTemp = 0;
		}else {
			outerLoop = true;
		}
	}

	emptyList(longInt);
	numLength = 0;
	addToList(longInt, list, true);
	numLength = listLength(list);
}

void LLONG::divide(const LLONG & division){
	
	bool divideLoop = false;
	int counter = 0, compVal = 0;
	
	nptrOne temp = new number;
	temp->singleDigit = '0';
	temp->next = NULL;
	
	nptrOne currentStatus = NULL;
	
	if(numLength < division.numLength){
		emptyList(longInt);
		longInt = temp;
		numLength = 0;
	}else {
		for(int i = 0; i < 12; i++){
			subtract(division);
		}
		
		
		/*
		//addToList(currentStatus, division.longInt, true);
		
		/*
		while(divideLoop == false){

			compVal = compare(division);
			std::cout << "COMP VALUE: " << compVal << std::endl;
			switch(compVal){
				case -1:
					subtract(division);
					emptyList(longInt);
					addToList(longInt, currentStatus, true);
					divideLoop = true;
				break;
				
				case 0:
					std::cout << "TST" << std::endl;
					emptyList(longInt);
					longInt = temp;
					numLength = 1;
					divideLoop = true;
				break;
				
				case 1:
					subtract(division);
				break;
			}
			
		
			counter= counter + 1;
		}*/
	}
	
	std::cout << "counter: " << counter << std::endl;
	
	return;
}

void LLONG::addToList(nptrOne & list, nptrOne & temporaryList, bool copyOrAdd){
	
	bool loop = false;
	
	if(copyOrAdd){
		nptrOne cur = temporaryList;
		while(loop == false){
			if(cur->next == NULL){
				loop = true;
			}
			insertToTree(list, cur->singleDigit);
			cur= cur->next;
		}	
	}else {
		addValues(list, temporaryList);
	}
	
	return;
}

void LLONG::addValues(nptrOne & list, nptrOne & listToCopy){
	
	int listLen = 0, copyLen = 0, valOne = 0, valTwo = 0, sum = 0, carry = 0, counter= 0;
	bool inCopy = false, carryIndicate =false, listEnd = false, copyEnd = false;
	
	nptrOne curList = list;
	nptrOne copy = listToCopy;
	
	listLen = listLength(list);
	copyLen = listLength(listToCopy);
	
	while(copyEnd == false){
		
		if(copy->next == NULL){
			copyEnd = true;
		}

		valOne = int(copy->singleDigit) -48;
		if(counter < listLen){
			valTwo = int(curList->singleDigit) -48; }
		else {
			valTwo = 0;
		}
		
		sum = valOne + valTwo;
		
		if(carryIndicate){
			sum = sum + carry;
			carry= 0;
			carryIndicate = false;
		}
		
		if(sum > 9){
			carry = sum / 10;
			sum = sum % 10;
			carryIndicate = true;
		}
		
		if(counter < listLen){
			curList->singleDigit = sum + '0';
			sum = 0;
			copy = copy->next;
		}else{
			increaseList(list, sum + '0');
		}
		
		if(curList->next != NULL){
			curList = curList->next;
			listEnd =true;
		}
		
		if(listEnd && carryIndicate && counter >= copyLen){
			increaseList(list, carry + '0');
		}

		counter = counter + 1;
	}
	listEnd = false;
	carryIndicate = false;
	carry = 0;
	
	return;
}

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

void LLONG::increaseList(nptrOne & list, char value){
	
	nptrOne temp = new number;
	temp->singleDigit = value;
	temp->next = NULL;
	
	nptrOne cur = list;
	
	while(cur->next != NULL){
		cur = cur->next;
	}
	cur->next = temp;
	temp = longInt;
	
}

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
		temp = cur;
	}
	
	return;
}

void LLONG::emptyList(nptrOne & list){

	bool removeComplete = false;
	
	nptrOne curDelete = list;
	while(removeComplete == false){
		if(list->next == NULL){
			removeComplete = true;
		}
		curDelete = list->next;
		delete list;
		list = NULL;
		list = curDelete;
	}
	
}

void LLONG::addNewDigit(char newNum){
	
	nptrOne temp = new number;
	temp->singleDigit = newNum;
	temp->next = NULL;
	
	nptrOne cur = longInt;
	
	while(cur->next != NULL){
		cur = cur->next;
	}
	cur->next = temp;
	temp = longInt;
	
	numLength = numLength + 1;
	
	return;
}

void LLONG::reduceTree(){
	
	bool nodeEnd = false, leadDigit = false;
	nptrOne cur = longInt;
	
	char *ptr;
	ptr = new char[numLength];
	int beginNumber = 0, tempVal = 0, counter = numLength -1;
	
	ptr[counter] = cur->singleDigit;
	counter = counter - 1;
	
	while(counter >= 0){
		cur = cur->next;
		ptr [counter] = cur->singleDigit;
		counter = counter - 1;
	}
	
	for(int i = 0; i < numLength; i++){
		tempVal = int(ptr[i]) -48;
		if(leadDigit == false){
			if(tempVal == 0){
				beginNumber = beginNumber + 1;
			}else {
				leadDigit = true;
			}
		}
	}
	
	beginNumber = numLength - beginNumber;
	
	nptrOne swap = longInt;
	nptrOne temp;
	int treeCount = 0;
	
	while(swap->next != NULL){
		
		if(treeCount >= beginNumber){
			temp = swap->next;
			delete swap;
			swap = temp;
			numLength = numLength -1;
		}else {
			swap = swap->next;
		}
		treeCount = treeCount + 1;
		
	}
	
	
	if(beginNumber == 0){
	
		longInt = NULL;
		
		numLength = 0;
	}
	
	return;
}


//*this
