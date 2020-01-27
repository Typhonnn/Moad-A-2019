#include <string.h>
#include <stdlib.h>
#include "q1.h"

/* This is the data in the file
11 customers
David Adult France
Jon Child France
Helena Baby Germany
Lidia Adult Germany
Judith Soldier France
Zeus Adult Italy
Josef Child Italy
Michel Baby France
Tal Adult Italy
Guy Soldier France
Moshe Child Germany
*/

/*
Correct output is:
In country France the income is: 3100.00
In country Germany the income is: 1500.00
In country Italy the income is: 2500.00
*/

void Q1()
{
	Company theCompany = { NULL, 0 };


	if (!fillCompanySurvey(&theCompany))
	{
		printf("Error filling the survey\n");
		return;
	}

	printTotalIncomePerContry(&theCompany);
	releaseCompany(&theCompany);
}

int		readCustomerFromFile(FILE* fp, Customer* pCust)
{
	int sizeOfStr = 1;
	if (pCust == NULL) {
		return 0;
	}
	//Reading the name.
	fread(&sizeOfStr, sizeof(int), 1, fp);
	pCust->name = calloc(sizeOfStr, sizeof(char));
	if (pCust->name == NULL) {
		return 0;
	}
	fread(pCust->name, sizeof(char), sizeOfStr, fp);
	//Reading the enum.
	fread(&pCust->type, sizeof(int), 1, fp);
	//Reading the country.
	fread(&sizeOfStr, sizeof(int), 1, fp);
	pCust->country = calloc(sizeOfStr, sizeof(char));
	if (pCust->country == NULL) {
		return 0;
	}
	fread(pCust->country, sizeof(char), sizeOfStr, fp);
	return 1;
}

int addCustomerToTrip(Trip* trip, Customer* pCust) {
	if (trip->coustomersCount == 0) {
		trip->country = calloc(strlen(pCust->country) + 1, sizeof(char));
		if (trip->country == NULL) {
			return 0;
		}
		strcpy_s(trip->country, strlen(pCust->country) + 1, pCust->country);
		trip->customersArr = calloc(1, sizeof(Customer*));
		if (trip->customersArr == NULL) {
			return 0;
		}
	}
	Customer** tempArr = trip->customersArr;
	int size = trip->coustomersCount + 1;
	trip->customersArr = realloc(tempArr, size * sizeof(Customer*));
	if (trip->customersArr == NULL) {
		return 0;
	}
	trip->customersArr[trip->coustomersCount] = calloc(1, sizeof(Customer));
	if (trip->customersArr[trip->coustomersCount] == NULL) {
		return 0;
	}
	trip->customersArr[trip->coustomersCount]->name = calloc(strlen(pCust->name) + 1, sizeof(char));
	if (trip->customersArr[trip->coustomersCount]->name == NULL) {
		return 0;
	}
	strcpy_s(trip->customersArr[trip->coustomersCount]->name, strlen(pCust->name) + 1, pCust->name);
	trip->customersArr[trip->coustomersCount]->country = calloc(strlen(pCust->country) + 1, sizeof(char));
	if (trip->customersArr[trip->coustomersCount]->country == NULL) {
		return 0;
	}
	strcpy_s(trip->customersArr[trip->coustomersCount]->country, strlen(pCust->country) + 1, pCust->country);
	trip->customersArr[trip->coustomersCount]->type = pCust->type;
	trip->coustomersCount++;
	return 1;
}

int		addCustomerToCompany(Company* pCompany, Customer* pCust)
{
	int i;
	if (pCompany == NULL) {
		return 0;
	}
	if (pCust == NULL) {
		return 0;
	}
	for (i = 0; i < pCompany->tripsCount; i++) {
		if (strcmp(pCompany->tripsArr[i]->country, pCust->country) == 0) {
			return addCustomerToTrip(pCompany->tripsArr[i], pCust);
		}
	}
	if (pCompany->tripsCount == 0) {
		pCompany->tripsArr = calloc(1, sizeof(Trip*));
		if (pCompany->tripsArr == NULL) {
			return 0;
		}
	}
	Trip** tempArr = pCompany->tripsArr;
	int size = pCompany->tripsCount + 1;
	pCompany->tripsArr = realloc(tempArr, size * sizeof(Trip*));
	if (pCompany->tripsArr == NULL) {
		return 0;
	}
	pCompany->tripsArr[pCompany->tripsCount] = calloc(1, sizeof(Trip));
	if (pCompany->tripsArr[pCompany->tripsCount] == NULL) {
		return 0;
	}
	return addCustomerToTrip(pCompany->tripsArr[pCompany->tripsCount++], pCust);
}

float customerPay(CustomerType type) {
	if (Adult == type) {
		return BASE_PRICE;
	}
	else if (Child == type) {
		return BASE_PRICE * CHILD_PRICE;
	}
	else if (Baby == type) {
		return BASE_PRICE * BABY_PRICE;
	}
	else if (Soldier == type) {
		return BASE_PRICE * SOLDIER_PRICE;
	}
	return -1;
}

float	calculateIncome(Trip* pTrip)
{
	int i;
	float totalIncome = 0;
	if (pTrip == NULL) {
		return -1;
	}
	for (i = 0; i < pTrip->coustomersCount; i++) {
		totalIncome += customerPay(pTrip->customersArr[i]->type);
	}
	return totalIncome;
}



void releaseCompany(Company* pCompany)
{
	int i, j;
	for ( i = 0; i < pCompany->tripsCount; i++)	{
			for (j = 0; j < pCompany->tripsArr[i]->coustomersCount; j++) {
				free(pCompany->tripsArr[i]->customersArr[j]->country);
				free(pCompany->tripsArr[i]->customersArr[j]->name);
				free(pCompany->tripsArr[i]->customersArr[j]);
			}
			free(pCompany->tripsArr[i]->country);
			free(pCompany->tripsArr[i]->customersArr);
			free(pCompany->tripsArr[i]);
	}
	free(pCompany->tripsArr);
}



int fillCompanySurvey(Company* pCompany)
{
	FILE* fp;
	int count,i;
	Customer temp;

	fopen_s(&fp,FILE_NAME, "rb");
	if (!fp)
		return 0;
	if (!fread(&count, sizeof(int), 1, fp))
	{
		fclose(fp);
		return 0;
	}

	for (i = 0; i < count; i++)
	{
		if(!readCustomerFromFile(fp,&temp))
		{
			fclose(fp);
			return 0;
		}
		
		if (!addCustomerToCompany(pCompany, &temp))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}



void printTotalIncomePerContry(Company* pCompany)
{
	int i;
	float income;
	for (i = 0; i < pCompany->tripsCount; i++)
	{
		income = calculateIncome(pCompany->tripsArr[i]);
		printf("In country %s the income is: %.2f\n", pCompany->tripsArr[i]->country, income);
	}
}
