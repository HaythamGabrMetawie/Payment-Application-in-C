#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../C_Project_EgFWD_HaythamMetawie/Card.h"
#include "../C_Project_EgFWD_HaythamMetawie/Terminal.h"
#include "../C_Project_EgFWD_HaythamMetawie/Server.h"

//// Card Module Testing Function
//void cardDataTest(void)
//{
//	struct ST_cardData_t testCard = { "","","" };
//	EN_cardError_t checkCardData;
//	checkCardData = getCardHolderName(&testCard);
//	if (checkCardData == CARD_OK)
//	{
//		checkCardData = getCardPAN(&testCard);
//		if (checkCardData == CARD_OK)
//		{
//			checkCardData = getCardExpiryDate(&testCard);
//			if (checkCardData == CARD_OK)
//			{
//				printf("Card Holder Name: %s", testCard.cardHolderName);
//				printf("Card PAN: %s \n", testCard.primaryAccountNumber);
//				printf("Card Expiration Date: %s \n", testCard.cardExpirationDate);
//			}
//			else { printf("Wrong Expiration Date or Formate! \n"); }
//		}
//		else { printf("Wrong Card PAN!\n"); }
//
//	}
//	else { printf("Wrong Card Holder Name Formate! \n"); }
//}
//
//// Terminal Module Testing Function
//#define MAX_AMOUNT 5000.0
//
//void terminalTest(void)
//{
//	struct ST_cardData_t testCard = { "Haytham Tarek Metawie","8989374615436851","02/23" };
//	struct ST_terminalData_t testTerminal = {0.0, 0.0, ""};
//	setMaxAmount(&testTerminal, MAX_AMOUNT);
//	EN_terminalError_t checkTermineal;
//	checkTermineal = getTransactionDate(&testTerminal);
//	if (checkTermineal == TERMINAL_OK)
//	{
//		checkTermineal = isCardExpired(&testCard, &testTerminal);
//		if (checkTermineal == TERMINAL_OK)
//		{
//			checkTermineal = getTransactionAmount(&testTerminal);
//			if (checkTermineal == TERMINAL_OK)
//			{
//				checkTermineal = isBelowMaxAmount(&testTerminal);
//				if (checkTermineal == TERMINAL_OK)
//				{
//					printf("Transaction Amount: %f\n", testTerminal.transAmount);
//					printf("Max Transaction Amount: %f\n", testTerminal.maxTransAmount);
//					printf("Transaction Date: %s \n", testTerminal.transactionDate);
//				}
//				else { printf("Declined Amount Exceeding Max Transaction Amount! \n"); }
//				
//			}
//			else { printf("Declined Invalide Transaction Amount! \n"); }
//		}
//		else { printf("Declined Expired Card!\n"); }
//
//	}
//	else { printf("Declined Invalide Transaction Date Formate \n"); }
//}
//
//
//// Server Module Testing Function
//void serverTest(void)
//{
//	ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "8989374615436852"}, {100000.0, BLOCKED, "5807007076043875"},
//									{12000.0, RUNNING, "8304968663367294"}, {24500.67, RUNNING, "6056950542528639"},
//									{193050.90, RUNNING, "4590060399500497"}, {81900.0, RUNNING, "6786670162265307"},
//									{1280100.88, RUNNING, "4343960889112705"}, {67904.5, RUNNING, "8989374615436851"},
//									{23760.24, RUNNING, "2288347000790919"}, {1900000.0, BLOCKED, "4083205480734570"} };
//
//	EN_cardError_t cardHolderName = CARD_OK;
//	EN_cardError_t cardExpiryDate = CARD_OK;
//	EN_cardError_t cardPAN = CARD_OK;
//	EN_terminalError_t transactionDate = TERMINAL_OK;
//	EN_terminalError_t cardExpired = TERMINAL_OK;
//	EN_terminalError_t transactionAmount = TERMINAL_OK;
//	EN_terminalError_t maxAmount = TERMINAL_OK;
//	EN_terminalError_t belowMaxAmount = TERMINAL_OK;
//	struct ST_cardData_t cardTest = { "", "", "" };
//	struct ST_terminalData_t terminalTest = { 0.0, 0.0, "" };
//	do cardHolderName = getCardHolderName(&cardTest); while (cardHolderName != CARD_OK);
//	do cardExpiryDate = getCardExpiryDate(&cardTest); while (cardExpiryDate != CARD_OK);
//	do cardPAN = getCardPAN(&cardTest); while (cardPAN != CARD_OK);
//	do transactionAmount = getTransactionAmount(&terminalTest); while (transactionAmount != TERMINAL_OK);
//	do maxAmount = setMaxAmount(&terminalTest, 8000.0); while (maxAmount != TERMINAL_OK);
//	do transactionDate = getTransactionDate(&terminalTest); while (transactionDate != TERMINAL_OK);
//	struct ST_transaction_t transaction = { cardTest, terminalTest, APPROVED, 0 };
//	cardExpired = isCardExpired(&cardTest, &terminalTest);
	/*if (isValidAccount(&cardTest, accountsDB) != ACCOUNT_NOT_FOUND)
	{
		printf("Account is found in Database. \n");
		if (isBlockedAccount(&accountsDB[0]) == BLOCKED_ACCOUNT)
		{
			printf("Account is blocked. \n");
		}
		else
		{
			printf("Account is running. \n");
			if (isAmountAvailable(&terminalTest, &accountsDB[0]) != LOW_BALANCE)
			{
				printf("Amount is availabe. \n");
			}
			else printf("Insuffecient fund. \n");
		}
	}
	else printf("Account is not found in Database. \n");*/

	//if (cardExpired == TERMINAL_OK)
	//{
	//	belowMaxAmount = isBelowMaxAmount(&terminalTest);
	//	if (belowMaxAmount != TERMINAL_OK)
	//	{
	//		printf("Declined Exceeding Max Amount of Transaction! \n");
	//		return;
	//	}
	//	else
	//	{
	//		saveTransaction(&transaction);
	//		//recieveTransactionData(&transaction);
	//	}
	//}
	//EN_transState_t recievetransState = APPROVED;
	
//}



int main(int argc, char* argv[])
{
	printf("Starting Application!\n");
	//cardDataTest();	
	//terminalTest();
	//serverTest();
	for(int i = 0; i < 6; i++)
	{
		appStart();
	}
	//listSavedTransactions();
	return 0;
}
