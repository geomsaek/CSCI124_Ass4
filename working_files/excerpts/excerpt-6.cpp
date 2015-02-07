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