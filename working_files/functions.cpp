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
	bool startList = true;
	int actualNum = 0;
	
	while(counter < exist.numLength){
		
		if(temp->singleDigit == '0' && !startList){
			listAdd(temp->singleDigit);
			counter = counter + 1;
		}
		else if(temp->singleDigit != '0' && startList){
			
			listAdd(temp->singleDigit);
			startList = false;
			actualNum = actualNum + 1;
		}
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

LLONG::LLONG(int existInt){
	
	longInt = NULL;
	int currentNumber = existInt;
	int mod = 0;
	int digitCount = 0; 
	bool startInt = false;
	
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
		//std::cout << "INITIAL CONSTRUCTOR INT MOD: " << mod << std::endl;
		
		listAdd(mod + '0');

		digitCount = digitCount + 1;
		
	}while(currentNumber != 0);
	//std::cout << "END OF INTGER INTIALISATION: "<< std::endl;
	
	if(digitCount == 1 && mod == 0){
	//	std::cout << "digit count is zero: " << digitCount << std::endl;
		
		
		nptrOne otherTemp = new number;
		otherTemp->singleDigit = '0';
		otherTemp->next = NULL;
		numLength = 0;
		positive = true;
		
		longInt = otherTemp;
		otherTemp = longInt;
		
	//	std::cout << "ZERO: " << longInt->singleDigit << std::endl;
	//	std::cout << "NEXT: " << longInt->next << std::endl;
		
	//	std::cout << "THIS IS THE NUMLENGTH: " << numLength << std::endl;
	}else {
		numLength = digitCount;	
	//	std::cout << "numlength is something else: " << numLength << std::endl;
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
	//std::cout << std::endl;
	//std::cout << std::endl;
	//std::cout << "CALL LIST ADD: " << std::endl;
	//std::cout << "DIGIT OF LIST ADD: " << temp->singleDigit << std::endl;
	
	if(longInt == NULL){
	//	std::cout << "LIST SET TO NULL:" << std::endl;
		
		longInt = temp;
		
	}else {
		nptrOne cur = longInt;
		
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = temp;
		temp = longInt;
		// last number is 3 and it shoud be a 2
	//	std::cout << "LAST ADDRESS OF LLAST NUMBER: " << cur->next <<", " << cur->singleDigit << std::endl;
	}
	//std::cout << std::endl;
	//std::cout << std::endl;
	
	
}

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

int LLONG::compare(const LLONG & exist){

	
	nptrOne native = longInt;
	nptrOne passed = exist.longInt;
	int existLen = exist.numLength;
	
	int receiveVal = 0;
	// return 0 for equal, 1 for >, -1 for <
	//std::cout << "COMPARE FUNCTION" << std::endl;
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
			//std::cout << "increment for otr in not positive and int two end: " << twoGreater << std::endl;
		}
		if(integerTwoEnd && !integerOneEnd){
			
			oneGreater = oneGreater + 1;
			//std::cout << "increment for cur in not positive and int one end: " << oneGreater << std::endl;
		}else{
			if(curInt > oInt){
				
				oneGreater = oneGreater + 1;
				//std::cout << "cur is greater: " << oneGreater << std::endl;
			}else if(curInt < oInt){
				twoGreater = twoGreater + 1;
				//std::cout << "otr is greater: " << oneGreater << std::endl;
			}else if(curInt == oInt){
				oneGreater = oneGreater + 1;
				twoGreater = twoGreater + 1;
				//std::cout << "equal: " << oneGreater << ". " << twoGreater << std::endl;
			}
		}
		//std::cout << "CUR INT: " << curInt << std::endl;
		//std::cout << "oINT: " << oInt << std::endl;
		//std::cout << std::endl;
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
	
	if(compareWithSign){
		if(oneGreater > twoGreater){
			//std::cout << "compare with sign onegreater: " << 1 << std::endl;
			return 1;
		}else if(oneGreater < twoGreater){
			//std::cout << "compare twogreater less: " << -1 << std::endl;
			return -1;
		}else if(oneGreater == twoGreater){
			//std::cout << "compare with equal: " << 0 << std::endl;
			return 0;
		}
	}else{
		if(oneGreater > twoGreater){
			//std::cout << "compare no sign onegreater: " << 1 << std::endl;
			return -1;
		}else if(oneGreater < twoGreater){
			//std::cout << "compare with twogreater: " << 1 << std::endl;
			return 1;
		}else if(oneGreater == twoGreater){
			//std::cout << "equal: " << 1 << std::endl;
			return 0;
		}
	}
	
	return 0;
}


void LLONG::subtract(const LLONG & sValue){
	
	
	nptrOne passedValue = sValue.longInt;
	int passedLength = sValue.numLength;
	bool passedPos = sValue.positive;
	
	if(numLength == 0 && passedValue == 0){
		return;
	}else {
		
		if(positive == false && sValue.positive == false){
			addRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
		}
		
		if(numLength == 0 && passedLength > 0){
			addRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
			positive = false;
			return;
		}else {
			subtractRaw(longInt, passedValue, numLength, passedLength, positive, passedPos);
		}

	}
	
	return;
}

void LLONG::subtractRaw(nptrOne & integerOne, nptrOne & integerTwo, int & lengthOne, int lengthTwo,
bool & positiveOne, bool positiveTwo){
	
	
	//std::cout << std::endl;
	//std::cout << std::endl;
	 int valOne = 0, tempValOne = 0;
	 int valTwo = 0, subtraction = 0, carry = 0, shortLen = 0, largeLen =0;
	 bool subtractVals = false, innerValue = false, longerSecond= false;
	 int counter = 0, returnValue = 0;
	 nptrOne larger, smaller, topInner;
	 nptrOne tempBuildList = NULL;
	
	 int returnType = 0;
	 bool lengthTest = false;

	//std::cout << "TJIS IS THE largerLen BEFORE: " << largeLen << std::endl;
	//std::cout << "TJIS IS THE shortLen before: " << shortLen << std::endl;
	lengthTest = assignAccordingToLength(integerOne, integerTwo, lengthOne, lengthTwo, larger, smaller, largeLen, shortLen, longerSecond);
	
	//std::cout << "AFTER ACCORDINGIN TO LENGTH FUNCITON:" << std::endl;
	//std:: cout << "THIS IS THE LENGTH OF THE HIGHT NUMBER: " << largeLen << std::endl;
	//std::cout << "THIS IS THE LENGTH OF THE LOWER NUMBER: " << shortLen <<std::endl;
	if(!lengthTest){
		//std::cout << "LENGTH TEST: " << std::endl;
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, lengthOne, lengthTwo, false);
		setPointers(integerOne, integerTwo, larger, smaller, topInner, false, returnValue);
		assignLengths(shortLen, largeLen, lengthOne, lengthTwo, returnType, longerSecond);
	}
	

	 while(subtractVals == false){
 
		if(larger->next == NULL){
			//std::cout << "---- END OF LOOP:-------- " << std::endl;
			subtractVals = true;
		}
		//std::cout << std::endl;
		//std::cout << "/////////// TEST STATEMENT: 1 /////////////" << std::endl;
		valOne = int(larger->singleDigit) -48;
		//std::cout << "INITIAL VAL ONE: " << valOne <<std::endl;
		
		//std::cout << "counter: " << counter << ", short length: " << shortLen << std::endl;
		if(counter < shortLen){
			//std::cout << "INSIDE VALUE 2 if first: ";
			valTwo = int(smaller->singleDigit) -48;
			//std::cout << "INITIAL VAL TWO: " << valTwo << std::endl;
		}else {
			valTwo = 0;
			//std::cout << "VAL TWO ZERO: " << valTwo << std::endl;
		}
		
		
		//std::cout << std::endl;
		
		//std::cout << "before the comparison" << std::endl;
		if(valOne < valTwo){
			nptrOne temp = larger->next;
			//std::cout << "ACCESSIONG THE TEMP NEXT: " << std::endl;
		
			if(larger->next != NULL && counter < shortLen){
				//std::cout << "LARGE IS NOT AT THE END" << std::endl;
				do{
					//std::cout << "ADDRESS: " << temp->next << std::endl;
					//if(temp->next != NULL){
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
							//std::cout << "TEMP CARRY: " << temp->singleDigit << std::endl;
						}

						tempValOne = 0;
						temp = temp->next;
					/*}else {
						//std::cout << "we're gonna hit 0" << std::endl;
						// need to do something now
						positive = true;
						test = true;
						return;
					}*/

				}while(innerValue == false);
			}
			tempValOne = 0;
			innerValue = false;
			temp = NULL;
			delete temp;
		}

		subtraction = valOne - valTwo;
		//std::cout << "SUBTRACITON: " << subtraction << std::endl;

		insertToTree(tempBuildList, subtraction + '0');
		
		larger = larger->next;
		innerValue = true;
		
		
		if(counter < shortLen){
			//std::cout << "TEST STATEMENT: 3" << std::endl;
			smaller = smaller->next;
		}

		subtraction = 0;
		counter = counter + 1;
		
		//std::cout << "COUNTER: " << counter << std::endl;
		 //std::cout << std::endl;
		//std::cout << std::endl;
	 }
	 
	 emptyList(integerOne);
	 lengthOne = 0;
	 addToList(integerOne, tempBuildList, true);
	 lengthOne = counter;
	 
	 bool confirmNumbers = false;
	 confirmNumbers = checkZeros(integerOne);
	 if(!confirmNumbers){
	 	reduceTree();
	 }else {
	 	initaliseZero(integerOne, lengthOne);
	 }
	 
	 emptyList(tempBuildList);
	 if(longerSecond){
	 	positiveOne = false;
	 }
	
}

void LLONG::initaliseZero(nptrOne & list, int &length){
	
	nptrOne temp = list;
	nptrOne keep;
	bool tester = false;
	
	while(tester == false){
		if(temp->next == NULL){
			tester = true;
		}else{
		
		keep = temp;
		delete keep;
		}
		temp = temp->next;
	}
	
	length = 0;
	list->singleDigit = '0';
	list->next = NULL;
	
	return;
}

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

bool LLONG::checkZeros(nptrOne & list){
	
	int counter = 0;
	int zeroCount = 0;
	
	nptrOne cur = list;
	while(counter < numLength){
		
		if(cur->singleDigit == '0'){
			zeroCount = zeroCount + 1;
		}
		cur = cur->next;
		counter = counter + 1;
	}
	
	cur = NULL;
	delete cur;
	
	if(zeroCount == counter){
		return true;
	}else{
		return false;
	}
	
}

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

// integer one is the list that will be operated on

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
	
	//std::cout << "THIS IS THE LARGE LEN: " << largeLen << std::endl;
	//std::cout << "THIS IS THE SMALL LEN: " << shortLen << std::endl;
	
	if(!lengthTest){
		
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
		setPointers(integerOne, integerTwo, top, bottom, topInner, false, returnType);
		assignLengths(shortLen, largeLen, iOneLen, iTwoLen, returnType, longerSecond);
	}
	
	//std::cout << "integer one: " << largeLen << std::endl;
	//std::cout << "integer two: " << shortLen << std::endl;
	//std::cout << std::endl;
	
	while(addVals == false){

		if(top->next == NULL){
			//std::cout << "APPRAOCHING THE END: " << std::endl;
			addVals = true;
		}

		//std::cout << "STATEMENT BEFORE THE FRIST VALUE" << std::endl;
		valOne = int(top->singleDigit) -48;
		//std::cout << "THIS IS THE VALONE VALUE: " << valOne << std::endl;
		if(counter < shortLen){
		//	std::cout << "THIS IS IN THE SHORT LEN: " << std::endl;
			valTwo = int(bottom->singleDigit) -48;
		//	std::cout << "THIS IS THE TOP ASSIGNED VALUE OF VALTWO: " << valTwo <<std::endl;
		}else {
		//	std::cout << "THIS IS IN THE SHORT LEN ELSE STATEMENT: " << std::endl;
			valTwo = 0;
		}
			
		sum = valOne + valTwo;
		carryAndAdd(carryIndicate, sum, carry);
		//std::cout << "AFTER THE CARRRY ADD FUNCTION: " << carryIndicate << ", " << sum << ", " << carry << std::endl;
		
		if(addVals && carryIndicate){
			//std::cout << "carry" << sum << ", carry: " << carry << std::endl;
			
			
			increaseList(tempBuildList, sum + '0');
			increaseList(tempBuildList, carry + '0');
			tempBuildLen = tempBuildLen + 1;
			//addNewDigit(carry + '0');
			carryIndicate = false;
		}else {
		//	std::cout << "ADDING TO BUILD: " << std::endl;
			insertToTree(tempBuildList, sum + '0');
		}

		sum = 0;
		//std::cout << "AFTER TOP NEXT" << std::endl;
		top = top->next;
		
	//	std::cout << "STATEMETN FOR NEXT BOTTOM VALU: "<< std::endl;
		if(counter < shortLen){
		//	std::cout << "IN THE BOTTOM LENGTH INCREMENT: " << std::endl;
			bottom = bottom->next;
		}
	//	std::cout << "COUNTER: " << counter << ", " << std::endl;
		counter = counter + 1;
	//	std::cout << std::endl;
	//	std::cout << std::endl;
	//	if(addVals){
	//		std::cout << "END OF ADD VALUES: " << std::endl;
	//	}
	}
	
	 emptyList(integerOne);
	 iOneLen = 0;
	 addToList(integerOne, tempBuildList, true);
	 iOneLen = tempBuildLen + counter;
	 emptyList(tempBuildList);
	 
	return;

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
	
		if(numLength == 0 || passedLength == 0){
			return;
		}else{
			multiplyRaw(current, passedValue, numLength, passedLength, positive, passedPos); 
		}
	
		if(positive == false && multiNum.positive == false){
			positive = true;
		}
		else if(positive == false || multiNum.positive == false){
			positive = false;
		}else {
			positive = true;
		}
		
		
	 longInt = current;

	
		
	return;
}

void LLONG::multiplyRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){
	
	nptrOne top, topInner, bottom;
	nptrOne tempBuildList = NULL;
	int tempBuildLen = 0;
	bool tempSign = true;
	int currentDenomLen = 0;
	bool denomSign = true;
	
	bool outerLoop = false, innerLoop = false, longerSecond = false, initialZeroAdd = false, carryIndicate = false;
	int longLen =0, shortLen = 0, valOne = 0, valTwo = 0, countZero = 0, multiplyTemp = 0, carry = 0;
	
	int returnType = 0;
	bool lengthTest = false;
	int counter = 0;

	//std::cout << "TJIS IS THE largerLen BEFORE: " << largeLen << std::endl;
	//std::cout << "TJIS IS THE shortLen before: " << shortLen << std::endl;
	lengthTest = assignAccordingToLength(integerOne, integerTwo, iOneLen, iTwoLen, top, bottom, longLen, shortLen, longerSecond);
	topInner = top;
	//std::cout << "AFTER ACCORDINGIN TO LENGTH FUNCITON:" << std::endl;
	//std:: cout << "THIS IS THE LENGTH OF THE HIGHT NUMBER: " << longLen << std::endl;
	//std::cout << "THIS IS THE LENGTH OF THE LOWER NUMBER: " << shortLen <<std::endl;
	
	if(!lengthTest){
		//std::cout << "LENGTH TEST: " << std::endl;
		returnType = checkDigit(integerOne, integerTwo, positiveOne, positiveTwo, iOneLen, iTwoLen, false);
		setPointers(integerOne, integerTwo, top, bottom, topInner, true, returnType);
		assignLengths(shortLen, longLen, iOneLen, iTwoLen, returnType, longerSecond);
	}
	
	
	//std::cout << "AFTER ACCORDINGIN TO LENGTH FUNCITON:" << std::endl;
	//std:: cout << "THIS IS THE LENGTH OF THE HIGHT NUMBER: " << longLen << std::endl;
	//std::cout << "THIS IS THE LENGTH OF THE LOWER NUMBER: " << shortLen <<std::endl;
	
	//std::cout << std::endl;
	
	nptrOne currentDenom = NULL;
	
	while(outerLoop == false){
	
		//std::cout << "inside multiply" << std::endl;
		while(innerLoop == false){
			
			//std::cout << "beginInnerLoop" << std::endl;
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
			
			//std::cout << "after the assigning of values: " << std::endl;
			//std::cout << "THIS IS VALUE ONE: " << valOne << std::endl;
			//std::cout << "THIS IS VALUE TWO: " << valTwo << std::endl;
			//std::cout << "THIS IS THE MULTIPLICATION: " << multiplyTemp << std::endl;
			carryAndAdd(carryIndicate, multiplyTemp, carry);
			
			//std::cout << "values have been added and carried: " << std::endl;
			nptrOne temp = new number;
			temp->singleDigit = multiplyTemp + '0';
			temp->next= NULL;
			
			//std::cout << "BEFORE THE ADDING OF ZEROS. Count Zero: " << countZero << ", initialZeroAdd: " << initialZeroAdd << std::endl;
			if(countZero > 0 && initialZeroAdd){
				//std::cout << "ADDING THE ZEROS: " << countZero << std::endl;
				for(int i = 0; i < countZero;i++){
					insertToTree(currentDenom, '0');
				}
				initialZeroAdd = false;
			}
			//std::cout << "BEFORE THE INSERINT OF INSERT TO TREE FUNCITON: " << std::endl;
			insertToTree(currentDenom, temp->singleDigit);
			//std::cout << "AFTER VALUES HAVE BEEN INSERTED TO TREE: " << std::endl;
			
			topInner = topInner->next;
			if(innerLoop && carryIndicate){
				increaseList(currentDenom, carry + '0');
				carry = 0;
				carryIndicate = false;
			}
			
			currentDenomLen = currentDenomLen + 1;
			//std::cout << "END OF INNER LOOP" << std::endl;
			//std::cout << std::endl;
			//std::cout << std::endl;
		}
		
	  
	  if(counter == 0){
	  	addToList(tempBuildList, currentDenom, true);
	  }else {
	  		tempBuildLen = listLength(tempBuildList);
			addRaw(tempBuildList, currentDenom, tempBuildLen, currentDenomLen, tempSign, denomSign);
			tempBuildLen = listLength(tempBuildList);
			//std::cout << "ASDASDA: " << tempBuildLen << std::endl;
		}

		//std::cout << "FINISHED WITH ADDING:" << std::endl;
		emptyList(currentDenom);
		currentDenom = 0;
		//std::cout << "NOW WE ARE HAVE FINISHED EMPYTING THE CURRENT DENOM FUNCTION: " << std::endl;
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

void LLONG::divide(const LLONG & division){
	
	
	
	return;
}

void LLONG::divideRaw(nptrOne & integerOne, nptrOne & integerTwo, int & iOneLen, int iTwoLen,
bool & positiveOne, bool positiveTwo){
/*
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
		*/
		
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
	//}
	
	return;
}


void LLONG::addToList(nptrOne & list, nptrOne & temporaryList, bool copyOrAdd){
	
	bool loop = false;
	
	//std::cout << "THIS IS IN THE ADD TO LIST FUNCTIOON: " << std::endl;
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
	}/*else {
		addValues(list, temporaryList);
	}*/
	
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
	temp = list;
	
	cur = NULL;
	delete cur;
	
}

void LLONG::insertToTree(nptrOne & list, char value){
	
	nptrOne temp = new number;
	temp->singleDigit = value;
	temp->next = NULL;
	
	//std::cout << "IN THE INSET FUNCTION: " << std::endl;
	if(list == NULL){
		
		list = temp;
	//	std::cout << "THIS the first value here: " << list->singleDigit << std::endl;
	}else {
		nptrOne cur = list;
		while(cur->next != NULL){
			cur = cur->next; 
		}
		
		cur->next = temp;
	//THIS	std::cout << "THIS the end value: " << cur->next->singleDigit << std::endl;
		temp = list;
	}
	
	return;
}

void LLONG::emptyList(nptrOne & list){

	bool removeComplete = false;
	//std::cout << "at the start of the empy function: " << std::endl;
	
	nptrOne curDelete = list;
	
	while(removeComplete == false){
		
		//std::cout << "ABOVE THE IF" << std::endl;
		
		if(list->next == NULL){
		//	std::cout << "comparision sees next is null" << std::endl;
			removeComplete = true;
		}else {
			curDelete = list->next;
		//	std::cout << "swapping" << std::endl;
			delete list;
		//	std::cout << "deleting" << std::endl;
		
			list = NULL;
		//	std::cout << "List is null" << std::endl;
			list = curDelete;
		//	std::cout << "LIST is now temp: " << list->singleDigit << ", " << list << std::endl;
		}
	}
	
	delete list;
	list = NULL;
	
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
