#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "../C_Project_EgFWD_HaythamMetawie/Application.h"
#include "../C_Project_EgFWD_HaythamMetawie/shared.h"


ST_cardData_t card = { "\n", "\n", "\n" };
ST_terminalData_t terminal = { 0.0, 0.0, "\n" };
ST_cardData_t* cardPointer = &card;
ST_terminalData_t* terminalPointer = &terminal;

void appStart(void)
{
	EN_cardError_t cardHolderName = CARD_OK;
	EN_cardError_t cardExpiryDate = CARD_OK;
	EN_cardError_t cardPAN = CARD_OK;
	EN_terminalError_t transactionDate = TERMINAL_OK;
	EN_terminalError_t cardExpired = TERMINAL_OK;
	EN_terminalError_t transactionAmount = TERMINAL_OK;
	EN_terminalError_t maxAmount = TERMINAL_OK;
	EN_terminalError_t belowMaxAmount = TERMINAL_OK;


	do cardHolderName = getCardHolderName(cardPointer); while (cardHolderName != CARD_OK);
	do cardExpiryDate = getCardExpiryDate(cardPointer); while (cardExpiryDate != CARD_OK);
	do cardPAN = getCardPAN(cardPointer); while (cardPAN != CARD_OK);
	do transactionAmount = getTransactionAmount(terminalPointer); while (transactionAmount != TERMINAL_OK);
	do maxAmount = setMaxAmount(terminalPointer, 8000.0); while (maxAmount != TERMINAL_OK);
	do transactionDate = getTransactionDate(terminalPointer); while (transactionDate != TERMINAL_OK);
	struct ST_transaction_t transaction = { card, terminal, APPROVED, 0 };
	cardExpired = isCardExpired(cardPointer, terminalPointer);
	if (cardExpired == TERMINAL_OK)
	{
		belowMaxAmount = isBelowMaxAmount(terminalPointer);
		if (belowMaxAmount != TERMINAL_OK)
		{
			printf("Declined Exceeding Max Amount of Transaction! \n");
			return;
		}
		else
		{
			recieveTransactionData(&transaction);
		}
	}
	else if (cardExpired == EXPIRED_CARD)
	{
		printf("Declined Expired Card! \n");
		return;
	}
	else
	{
		printf("Error Occured! \n");
		return;
	}
		

}
