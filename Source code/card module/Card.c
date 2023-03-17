#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "../C_Project_EgFWD_HaythamMetawie/Card.h"

/*
Validation function for Card Holder Name
Inputs: char array
Outputs: enum either OK or WRONG_NAME
*/
EN_cardError_t validateCardHolderName(char* CardHolderName) 
{
	if (strlen(CardHolderName)  <= 24 && strlen(CardHolderName) >= 20)
	{
		for (int i = 0; i < strlen(CardHolderName); i++)
		{
			if (!isalpha(CardHolderName[i]) && !isspace(CardHolderName[i])) return WRONG_NAME;
		}
		return CARD_OK;
	}
	else return WRONG_NAME;

		
}



/*
Validation function for Card Expiration Date
Inputs: char array
Outputs: enum either CARD_OK or WRONG_EXP_DATE
*/
EN_cardError_t validateCardExpiryDate(char* cardExpirationDate)
{

if (strlen(cardExpirationDate) == 5) 
{
	char cardMonth[3] = "\n", cardYear[3] = "\n";
	cardMonth[0] = cardExpirationDate[0];
	cardMonth[1] = cardExpirationDate[1];
	cardYear[0] = cardExpirationDate[3];
	cardYear[1] = cardExpirationDate[4];
	if (atoi(cardMonth) > 0 && atoi(cardMonth) <= 12 && cardExpirationDate[2] == '/' &&
		atoi(cardYear) >= 22 && atoi(cardYear) <= 99) return CARD_OK; // I need to free buffer
	else return WRONG_EXP_DATE;
}
else return WRONG_EXP_DATE;
}


/*
Validation function for Card PAN
Inputs: char array
Outputs: enum either CARD_OK or WRONG_PAN
*/
EN_cardError_t validateCardPAN(char* primaryAccountNumber)
{
	if (strlen(primaryAccountNumber) >= 16 && strlen(primaryAccountNumber) <= 19)
	{
		for (int i = 0; i < strlen(primaryAccountNumber); i++)
		{
			if(!isdigit(primaryAccountNumber[i])) return WRONG_PAN;
		}
		return CARD_OK;
	}
	else return WRONG_PAN;
}

/*
Function to get Card Holder Name
Inputs: a pointer to a user-defined struct ST_cardData_t
Outputs: enum either CARD_OK or WRONG_NAME
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please enter the card holder name! \n");
	fgets(cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);
	return validateCardHolderName(&cardData->cardHolderName);
}

/*
Function to get Card Expiration Date
Inputs: a pointer to a user-defined struct ST_cardData_t
Outputs: enum either CARD_OK or WRONG_EXP_DATE
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter the card expiration date in form of (MM/YY)! \n");
	scanf("%s", cardData->cardExpirationDate);
	return validateCardExpiryDate(&cardData->cardExpirationDate);
}

/*
Function to get Card PAN
Inputs: a pointer to a user-defined struct ST_cardData_t
Outputs: enum either CARD_OK or WRONG_PAN
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter the card primary account number! \n");
	scanf("%s", cardData->primaryAccountNumber);
	return validateCardPAN(&cardData->primaryAccountNumber);
}
