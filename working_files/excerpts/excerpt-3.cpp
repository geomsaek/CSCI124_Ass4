			if(valOne < valTwo && valOne > 0){
				nptrOne temp = larger->next;
				std::cout << "ACCESSIONG THE TEMP NEXT: " << std::endl;
			
				if(larger->next != NULL && counter < shortLen){
					std::cout << "LARGE IS NOT AT THE END" << std::endl;
					do{
						if(temp->next == NULL){
							innerValue = true;
						}
						
						tempValOne = int(temp->singleDigit) -48;
						std::cout << "THIS TEMP VALUE VBEOFREE: " << tempValOne << std::endl;
						if(tempValOne > 0){
							tempValOne = tempValOne - 1;
							std::cout << "TEMP VALONE: " << tempValOne << std::endl;
							temp->singleDigit = tempValOne + '0';
							innerValue = true;
							valOne = valOne + 10;

						}else if(tempValOne == 0 && temp->next != NULL){
							
							temp->singleDigit = (tempValOne + 10) - 1 + '0';
							std::cout << "getting the next denomination value " << temp->singleDigit << std::endl;
						}
	
						tempValOne = 0;
						temp = temp->next;
	
					}while(innerValue == false);
				}
				tempValOne = 0;
				innerValue = false;
				temp = NULL;
				delete temp;
			}else {
				
				subtraction = valOne - valTwo;
				std::cout << "LESS THAN 0: " << subtraction << std::endl;
			}
			
			
			
			
			
			void LLONG::determineLonger(const LLONG & exist, nptrOne & top, nptrOne & bottom,
bool & longerSecond, bool topInnerPres, nptrOne & topInner, int& shortLen, int & longLen){

	/*
	if(passedValue.numLength > numLength){
		top = passedValue.longInt;
		if(topInnerPres){
			topInner = passedValue.longInt;
		}
		bottom = longInt;
		longLen = passedValue.numLength;
		shortLen = numLength;
		longerSecond = true;
	}else {
		top = longInt;
		if(topInnerPres){
			topInner = longInt;
		}
		bottom = passedValue.longInt;
		longLen = numLength;
		shortLen = passedValue.numLength;
		longerSecond = false;
	}*/
	
	return;
}