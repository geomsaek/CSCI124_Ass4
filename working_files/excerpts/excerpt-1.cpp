if(countZero > 0 && initalZeroAdd){
					zeroExist = true;
					
					push(temp, list, zeroExist, countZero);
					
				}else {
					push(temp, list, false, 0);
				}
				
				
				
 		
 		switch(returnValue){
 			case -1:
 				larger = longInt;
 				smaller = sValue.longInt;
 				shortLen = sValue.numLength;
 				largeLen = numLength;
 			break;
 			
 			case 0:
 				larger = longInt;
 				smaller = sValue.longInt;
 				largeLen = numLength;
 				shortLen = sValue.numLength;
 			break;
 			
 			case 1:
 				larger = sValue.longInt;
 				smaller = longInt;
 				largerInt = true;
 				largeLen = sValue.numLength;
 				shortLen = sValue.numLength;
 			break;
 		}
 		
						
		nptrOne test = list;
		while(test->next != NULL){
			std::cout << "RUN THROUGH: " << test->singleDigit << std::endl;
			test = test->next;
		}
		std::cout << "OUTER LAST RUN TRHOUGH: " << test->singleDigit << std::endl;
		
		
		if(carryIndicate){
				multiplyTemp = multiplyTemp + carry;
				carryIndicate = false;
				carry = 0;
			}
			
			if(multiplyTemp > 9){
				carry = multiplyTemp / 10;
				multiplyTemp = multiplyTemp % 10;
				carryIndicate = true;
			}
		
		nptrOne tCur = currentDenom;
			while(tCur->next != NULL){
				
				tCur = tCur->next;
			}
			tCur->next = temp;
			temp = tCur;



		if(exist.numLength > numLength){
			top = exist.longInt;
			largeLen = exist.numLength;
			shortLen = numLength;
			bottom = longInt;
			largerInt = true;
		}else {
			largerInt = false;
			top = longInt;
			bottom = exist.longInt;
			largeLen = numLength;
			shortLen = exist.numLength;
		}
		
		
			 if(sValue.numLength > numLength){
		larger = sValue.longInt;
		largeLen = sValue.numLength;
		shortLen = numLength;
		smaller = longInt;
		largerInt = true;
		positive = false;
	 }else {
		larger = longInt;
		largerInt = false;
		largeLen = numLength;
		shortLen =sValue.numLength;
		smaller = sValue.longInt;
		positive = true;
	 }
	 

	if(multiNum.numLength > numLength){
		top = multiNum.longInt;
		topInner = multiNum.longInt;
		bottom = longInt;
		longLen = multiNum.numLength;
		shortLen = numLength;
		longerSecond = true;
	}else {
		top = longInt;
		topInner = longInt;
		bottom = multiNum.longInt;
		longLen = numLength;
		shortLen = multiNum.numLength;
		longerSecond = false;
	}