#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Card.h"
#include "../C_Project_EgFWD_HaythamMetawie/Server.h"
#include "../C_Project_EgFWD_HaythamMetawie/shared.h"

//server-side accounts' database
ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "8989374615436852"}, {100000.0, BLOCKED, "5807007076043875"},
									{12000.0, RUNNING, "8304968663367294"}, {24500.67, RUNNING, "6056950542528639"},
									{193050.90, RUNNING, "4590060399500497"}, {81900.0, RUNNING, "6786670162265307"},
									{1280100.88, RUNNING, "4343960889112705"}, {67904.5, RUNNING, "8989374615436851"},
									{23760.24, RUNNING, "2288347000790919"}, {1900000.0, BLOCKED, "4083205480734570"}};

//server-side transactions' database
ST_transaction_t transactionsDB[255]; // check initialization

uint8_t DBSize = 10;
uint8_t transactionsSize = 0;
ST_accountsDB_t* validAccountPointer = NULL;
EN_transState_t transactionState = APPROVED;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t recievetransState = APPROVED;
	EN_serverError_t validAccountState = SERVER_OK;
	EN_serverError_t  accountState = RUNNING;
	EN_serverError_t availableAmountState = SERVER_OK;
	EN_serverError_t saveTransactionState = SERVER_OK;
	ST_transaction_t* saveTransactionPointer = transData;

	validAccountState = isValidAccount(cardPointer, accountsDB);
	accountState = isBlockedAccount(validAccountPointer);
	availableAmountState = isAmountAvailable(terminalPointer, validAccountPointer);

	if (validAccountState == ACCOUNT_NOT_FOUND)
	{
		transactionState = FRAUD_CARD;
		recievetransState = FRAUD_CARD;
	}
	else if (validAccountState == SERVER_OK)
	{
		if (accountState == BLOCKED_ACCOUNT)
		{
			transactionState = DECLINED_STOLEN_CARD;
			recievetransState = DECLINED_STOLEN_CARD;
		}
		else if (accountState == SERVER_OK)
		{
			if (availableAmountState == LOW_BALANCE)
			{
				transactionState = DECLINED_INSUFFECIENT_FUND;
				recievetransState = DECLINED_INSUFFECIENT_FUND;
			}
			else
			{
				validAccountPointer->balance = validAccountPointer->balance - terminalPointer->transAmount;
				transactionState = APPROVED;
				recievetransState = APPROVED;
			}
		}
		else recievetransState = INTERNAL_SERVER_ERROR;

	}
	else recievetransState = INTERNAL_SERVER_ERROR;

	saveTransactionState = saveTransaction(saveTransactionPointer);
	if (saveTransactionState != SERVER_OK)
	{
		transactionState = INTERNAL_SERVER_ERROR;
		recievetransState = INTERNAL_SERVER_ERROR;
	}
	return recievetransState;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference)
{
	for (int i = 0; i < DBSize; i++)
	{
		if(!strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber, 20))
		{
			validAccountPointer = accountReference;
			return SERVER_OK;
		}
		accountReference ++;
	}
	
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference)
{
	if (accountReference != NULL)
	{
		if (accountReference->state == BLOCKED) return BLOCKED_ACCOUNT;
		else if (accountReference->state == RUNNING) return SERVER_OK;
		else return BLOCKED_ACCOUNT;
	}
	else return ACCOUNT_NOT_FOUND;
		
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference)
{	
	if (accountReference != NULL)
	{
		if (accountReference->balance < termData->transAmount) return LOW_BALANCE;
		else return SERVER_OK;
	}
	else return ACCOUNT_NOT_FOUND;
		
	
}
/* Helper Function to list the last saved Transaction */
void listSavedTransaction(void)
{
	printf("#################################################### \n");
	printf("Transaction Sequence Number: %d \n", transactionsDB[transactionsSize - 1].transactionSequenceNumber);
	printf("Transaction Date: %s \n", transactionsDB[transactionsSize - 1].terminalData.transactionDate);
	printf("Transaction Amount: %f \n", transactionsDB[transactionsSize - 1].terminalData.transAmount);
	switch (transactionsDB[transactionsSize - 1].transState)
	{
	case APPROVED: printf("Transaction State: APPROVED\n"); break;
	case DECLINED_INSUFFECIENT_FUND: printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n"); break;
	case DECLINED_STOLEN_CARD: printf("Transaction State: DECLINED_STOLEN_CARD\n"); break;
	case FRAUD_CARD: printf("Transaction State: FRAUD_CARD\n"); break;
	case INTERNAL_SERVER_ERROR: printf("Transaction State: INTERNAL_SERVER_ERROR\n"); break;
	default: break;
	}
	printf("Terminal Max Amount: %f \n", transactionsDB[transactionsSize - 1].terminalData.maxTransAmount);
	printf("Cardholder Name: %s \n", transactionsDB[transactionsSize - 1].cardHolderData.cardHolderName);
	printf("PAN: %s \n", transactionsDB[transactionsSize - 1].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s \n", transactionsDB[transactionsSize - 1].cardHolderData.cardExpirationDate);
	printf("#################################################### \n");

}

EN_serverError_t saveTransaction(ST_transaction_t* transData) 
{
	if (transactionsSize == 0)
	{
		/*strcpy(transData->cardHolderData.cardHolderName, cardPointer->cardHolderName);
		strcpy(transData->cardHolderData.primaryAccountNumber, cardPointer->primaryAccountNumber);
		strcpy(transData->cardHolderData.cardExpirationDate, cardPointer->cardExpirationDate);
		transData->terminalData.transAmount = terminalPointer->transAmount;
		transData->terminalData.maxTransAmount = terminalPointer->maxTransAmount;
		strcpy(transData->terminalData.transactionDate, terminalPointer->transactionDate);*/
		transData->transState = transactionState;
		transData->transactionSequenceNumber = rand() % 4294967296;
		transactionsDB[transactionsSize] = *transData;
		transactionsSize++;
		listSavedTransaction();
		return SERVER_OK;
	}

	else if (transactionsSize < 255)
	{
		/*strcpy(transData->cardHolderData.cardHolderName, cardPointer->cardHolderName);
		strcpy(transData->cardHolderData.primaryAccountNumber, cardPointer->primaryAccountNumber);
		strcpy(transData->cardHolderData.cardExpirationDate, cardPointer->cardExpirationDate);
		transData->terminalData.transAmount = terminalPointer->transAmount;
		transData->terminalData.maxTransAmount = terminalPointer->maxTransAmount;
		strcpy(transData->terminalData.transactionDate, terminalPointer->transactionDate);*/
		transData->transState = transactionState;
		transData->transactionSequenceNumber = (transactionsDB[transactionsSize - 1].transactionSequenceNumber + 1);
		transactionsDB[transactionsSize] = *transData;
		transactionsSize++;
		listSavedTransaction();
		return SERVER_OK;
	}

	else return SAVING_FAILED;
}

void listSavedTransactions(void)
{
	for (int i = 0; i < transactionsSize; i++)
	{
		printf("#################################################### \n");
		printf("Transaction Sequence Number: %d \n", transactionsDB[i].transactionSequenceNumber);
		printf("Transaction Date: %s \n", transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount: %f \n", transactionsDB[i].terminalData.transAmount);
		switch (transactionsDB[i].transState)
		{
		case APPROVED: printf("Transaction State: APPROVED\n"); break;
		case DECLINED_INSUFFECIENT_FUND: printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n"); break;
		case DECLINED_STOLEN_CARD: printf("Transaction State: DECLINED_STOLEN_CARD\n"); break;
		case FRAUD_CARD: printf("Transaction State: FRAUD_CARD\n"); break;
		case INTERNAL_SERVER_ERROR: printf("Transaction State: INTERNAL_SERVER_ERROR\n"); break;
		default: break;
		}
		printf("Terminal Max Amount: %f \n", transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s \n", transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %s \n", transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s \n", transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#################################################### \n");
	}
}


