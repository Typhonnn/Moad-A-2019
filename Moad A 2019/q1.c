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


int StringToEnum(char* type) {
	if ("Adult" == type) {
		return 0;
	}
	else if ("Child" == type) {
		return 1;
	}
	else if ("Baby" == type) {
		return 2;
	}
	else if ("Soldier" == type) {
		return 3;
	}
	return -1;
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
		trip->country = calloc(strlen(pCust->country), sizeof(char));
		if (trip->country == NULL) {
			return 0;
		}
		trip->country = pCust->country;
		trip->customersArr = calloc(1, sizeof(Customer*));
		if (trip->customersArr == NULL) {
			return 0;
		}
	}
	Customer** temp = trip->customersArr;
	trip->customersArr = realloc(temp, (trip->coustomersCount + 1) * sizeof(Customer*));
	if (trip->customersArr == NULL) {
		return 0;
	}
	trip->customersArr[trip->coustomersCount++] = pCust;
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
		pCompany->tripsArr[0] = calloc(1, sizeof(Trip));
		if (pCompany->tripsArr[0] == NULL) {
			return 0;
		}
	}
	Trip** tempArr = pCompany->tripsArr;
	pCompany->tripsArr = realloc(tempArr, (pCompany->tripsCount + 1) * sizeof(Trip*));
	if (pCompany->tripsArr == NULL) {
		return 0;
	}
	Trip* temp = pCompany->tripsArr[pCompany->tripsCount];
	pCompany->tripsArr[pCompany->tripsCount] = realloc(temp, sizeof(Trip));
	if (pCompany->tripsArr[pCompany->tripsCount] == NULL) {
		return 0;
	}
	return addCustomerToTrip(pCompany->tripsArr[pCompany->tripsCount++], pCust);
}

float	calculateIncome(Trip* pTrip)
{


	return 0;
}



void releaseCompany(Company* pCompany)
{



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
