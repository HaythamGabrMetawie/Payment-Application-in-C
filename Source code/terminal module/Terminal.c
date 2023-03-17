#include <stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../C_Project_EgFWD_HaythamMetawie/Terminal.h"

/*
Validation function for Transaction Date
Inputs: char array
Outputs: enum either TERMINAL_OK or WRONG_DATE
*/
EN_terminalError_t validateTransactionDate(char* transactionDate)
{
	char transDay[3] = "\n", transMonth[3] = "\n", transYear[5] = "\n";
	
	if (strlen(transactionDate) == 10)
	{
		transDay[0] = transactionDate[0];
		transDay[1] = transactionDate[1];
		transMonth[0] = transactionDate[3];
		transMonth[1] = transactionDate[4];
		transYear[0] = transactionDate[6];
		transYear[1] = transactionDate[7];
		transYear[2] = transactionDate[8];
		transYear[3] = transactionDate[9];
		if (atoi(transDay) > 0 && atoi(transDay) <= 31 && transactionDate[2] == '/' &&
			atoi(transMonth) > 0 && atoi(transMonth) <= 12 && transactionDate[5] == '/' &&
			atoi(transYear) >= 2022 && atoi(transYear) <= 2999)
			return TERMINAL_OK; // I need to free buffers
		else return WRONG_DATE;
	}
	else return WRONG_DATE;
}
/*
Function to get Transaction Date
Inputs: a pointer to a user-defined struct ST_terminalData_t
Outputs: enum either TERMINAL_OK or WRONG_DATE
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Please enter the transaction date in form of (DD/MM/YYYY)! \n");
	scanf("%s", termData->transactionDate);
	return validateTransactionDate(termData->transactionDate);
}

/*
Function to check expiration of the card
Inputs: pointers to a user-defined structs ST_cardData_t and ST_terminalData_t
Outputs: enum either TERMINAL_OK or EXPIRED_CARD
*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	char transMonth[3] = "\n", transYear[3] = "\n", cardMonth[3] = "\n", cardYear[3]="\n";
	transMonth[0] = termData->transactionDate[3];
	transMonth[1] = termData->transactionDate[4];
	transYear[0] = termData->transactionDate[8];
	transYear[1] = termData->transactionDate[9];
	cardMonth[0] = cardData->cardExpirationDate[0];
	cardMonth[1] = cardData->cardExpirationDate[1];
	cardYear[0] = cardData->cardExpirationDate[3];
	cardYear[1] = cardData->cardExpirationDate[4];

	if (atoi(transYear) > atoi(cardYear)) return EXPIRED_CARD;
	else if (atoi(transYear) == atoi(cardYear) && atoi(transMonth) > atoi(cardMonth)) return EXPIRED_CARD;
	else return TERMINAL_OK;	
}

/*
Function to get the transaction amount
Inputs: a pointer to a user-defined struct ST_terminalData_t
Outputs: enum either TERMINAL_OK or INVALID_AMOUNT
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the transaction amount! \n");
	scanf("%f", &(termData->transAmount));
	if (termData->transAmount <= 0) return INVALID_AMOUNT;
	else return TERMINAL_OK;

}


/*
Function to compare the transaction amount with the terminal max allowed amount.
Inputs: a pointer to a user-defined struct ST_terminalData_t
Outputs: enum either TERMINAL_OK or EXCEED_MAX_AMOUNT
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount) return EXCEED_MAX_AMOUNT;
	else return TERMINAL_OK;
}

/*
Function to set the transaction max amount
Inputs: a pointer to a user-defined struct ST_terminalData_t
Outputs: enum either TERMINAL_OK or INVALID_MAX_AMOUNT
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0) return INVALID_MAX_AMOUNT;
	else
	{
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}

}