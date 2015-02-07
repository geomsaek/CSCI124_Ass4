nptrOne exist = longInt;
 		nptrOne passed = sValue.longInt;
 		bool values = false;
 		bool longStop = false;
 		bool passedStop = false;
 		int existHigh = 0;
 		int passedHigh = 0;
 		int compOne = 0;
 		int compTwo = 0;
 		
 		while(values == false){
 			if(exist->next == NULL){
 				longStop = true;
 				compOne = 0;
 			}
 			if(passed->next == NULL){
 				passedStop = true;
 				compTwo = 0;
 			}
 			
 			if(!longStop){
 				compOne = int(exist->singleDigit) -48;
 				std::cout << compOne <<std::endl;
 			}
 			if(!passedStop){
				compTwo = int(passed->singleDigit) -48;
			}
			
 			if(compOne < compTwo){
 				passedHigh = passedHigh + 1;
 			}
 			else if(compOne > compTwo){
 				existHigh = existHigh + 1;	
 			}
 			if(!longStop){
 				exist = exist->next;
 			}
 			if(!passedStop){
 				passed = passed->next;
 			}
 			if(longStop && passedStop){
 				values = true;
 			}
 			values = true;
 		}
 		
 		if(existHigh == passedHigh){
 			returnValue = 0;
 		} 
 		else if(existHigh > passedHigh){
 			returnValue = -1;
 		}else if(passedHigh > existHigh){
 			returnValue = 1;
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
 				positive = false;
 				largeLen = sValue.numLength;
 				shortLen = sValue.numLength;
 			break;
 		}