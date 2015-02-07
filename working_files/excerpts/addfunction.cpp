


///// THIS WASA A FUNCTION THAT WAS USED TO ADD BUT YOU DONT REALLY NEED IT NOW
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