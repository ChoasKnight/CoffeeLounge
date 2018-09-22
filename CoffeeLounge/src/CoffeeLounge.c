/*
 ============================================================================
 Name        : CoffeeLounge.c
 Author      : Sandun Prabath Silva.
 Description : CoffeeLounge App in C
 ============================================================================
 */

#include <stdio.h>   /* Header files which will include functions i am using for this C project */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 120 /* defining a macro amount */

char input[MAX]; /* variable to store user input in form of string */
char * filter; /* This variable will be used with strtol function */
long totalBill; /*This variable will be used to print the final output to screen. long is used because strtol converts string into long integer*/
long maxOrders = 10; /*This variable to store maximum number of orders allowed for a table*/
long maxToppings = 0;/*This is varialbe is used to store maximum number of toppings according to coffee's bought*/

long tableRecorder(); /* Declartion of a function. This fuction will be used to get the table number from the user. It will return long integer */
int digitCheck(); /* This fuction will be used check if user has input a digit */
char * clearWhiteSpaces(char * clear); /* This function is used to remove spaces in user input */
void welcomeScreen(); /*This function is used to print a welcome message to console*/
void coffeeRecorder(); /*This function is used to process Coffee Orders */
void toppingRecorder(long howMuch); /*This function is used to process toppings*/
void juiceRecorder(); /*This function is used to process juice*/
void sandwichRecorder(); /*This function is used to process sandwich orders*/
void cakeCokkieRecorder(); /*This function is used to process cake and cookie orders*/
void menuScreen(); /*This Function show the main menu screen*/
int letterCheck(char * clear);/* This Function will used check if use has input alphabet letters only. It will return 1 if they haven't which will serve as boolean value for validation in some fucntions.*/
long orderAmount();/* This function is used to return number of orders by a user*/
long toppingAmountGenerator(long maxToppings);/*This function generates maximum number amount of toppings that can be bought*/
char * toUpperCase(char * clear);/*This function is used to convert all string entered by user to uppercase*/
int confirmation();/*This function is used to ask the user wether he wants perform certain action or not.*/

int main() { /*This is main function. Program execution begins here*/

	welcomeScreen();
	long tableNumber = tableRecorder();
	menuScreen();
	printf("Your Bill For Table %li is Rs.%li\n", tableNumber, totalBill);
	return 0;
}

long tableRecorder() { /* Implementation of tableRecorder() funtion */

	long tablenumber;

	while (1) {

		printf("Enter The Table Number. Maximum Number Of Tables Are 20\n");
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		if (digitCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Number.Please Try Again!\n");
			memset(input, 0, strlen(input));/* This funtion is used to clear input array. So it wont't overflow in while loop*/
			tableRecorder(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		tablenumber = strtol(input, &filter, 10); /* This function will be used to convert string to an long integer. */
		/* It will return 0 if it fails to convert the string into long integer */

		if (tablenumber > 0 && tablenumber <= 20) {
			return tablenumber;
		}

		if (tablenumber == 0 || tablenumber > 20) { /* This condition return an error message if input is not within range.*/
			printf("Invalid Table Number.Please Try Again!\n");

		}

	}

}

char * clearWhiteSpaces(char * clear) { /* Implementation of clearWhiteSpaces(char * clear) funtion */

	static char removeWhiteSpaces[MAX]; /* static variable is used here to prevent value from being lost after funtion completion*/
	int n = strlen(clear); /* This is used to get length of string array */
	int count = 0;

	for (int i = 0; i < n; i++) {
		if (!isspace(clear[i])) { /*isspace function checks if there are spaces in the array.*/
			removeWhiteSpaces[count] = clear[i];
			count++;
		}
	}

	return removeWhiteSpaces;
}

int digitCheck(char * clear) {/* Implementation of digitCheck(char * clear) funtion */

	int n = strlen(clear);
	for (int i = 0; i < n; i++) {
		if (!isdigit(clear[i])) {/*isdigit function checks if there are digits in the array.*/
			return 1;
		}
	}
	return 0;
}

void welcomeScreen() {/* Implementation of welcomeScreen() funtion */
	printf("*********************************************\n");
	printf("-----------Welcome to Coffee Lounge----------\n");
	printf("*********************************************\n");
	printf("\n");
}

void coffeeRecorder() {/* Implementation of coffeeRecorder() funtion */

	while (1) {

		printf("----------Coffee Menu---------\n");
		printf("C = Cappuccino      - Rs.850/=\n");
		printf("M = Mocha           - Rs.800/=\n");
		printf("L = Latte           - Rs.720/=\n");
		printf("E = Espresso        - Rs.830/=\n");
		printf("A = Americano       - Rs.760/=\n");
		printf("X = Exit\n");
		printf("-------------------------------\n");
		printf("\n");

		printf(
				"Please Enter Letter Of Your Choice.\nMaximum Orders Allowed For A Table Is %li\n",
				maxOrders);
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the end*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			coffeeRecorder(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "C", n) == 0) {/*strncmp function compares two strings and return 0 with they are equal*/
			long amount = orderAmount();/* Asking user amount he wants of the specific product*/
			toppingRecorder(amount);/*After coffe's has been bought ask user if he wants toppings*/
			totalBill = totalBill + ((850 * amount));
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "M", n) == 0) {
			long amount = orderAmount();
			toppingRecorder(amount);
			totalBill = totalBill + ((800 * amount));
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "L", n) == 0) {
			long amount = orderAmount();
			toppingRecorder(amount);
			totalBill = totalBill + ((720 * amount));
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "E", n) == 0) {
			long amount = orderAmount();
			toppingRecorder(amount);
			totalBill = totalBill + ((830 * amount));
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "A", n) == 0) {
			long amount = orderAmount();
			toppingRecorder(amount);
			totalBill = totalBill + ((760 * amount));
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			printf("\n");
			break;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");

		}

	}

}

void toppingRecorder(long howMuch) {/* Implementation of toppingRecorder(long howMuch) funtion */

	long toppingPrize = 0;
	long toppingAmount = 0;
	maxToppings = howMuch;

	while (1) {

		printf("----------Topping Menu---------\n");
		printf("MM = Mini marshmallow - Rs.30/=\n");
		printf("C = Cinnamon          - Rs.30/=\n");
		printf("N = Nutmeg            - Rs.30/=\n");
		printf("W = Wiped Cream       - Rs.30/=\n");
		printf("M = Mint              - Rs.30/=\n");
		printf("X = Exit\n");
		printf("-------------------------------\n");
		printf("\n");

		printf("Please Enter Letter Of Your Choice\n");
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the end*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			toppingRecorder(howMuch); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "MM", n) == 0) {

			toppingAmount = toppingAmountGenerator(maxToppings);
			toppingPrize = toppingPrize + (30 * toppingAmount);
			maxToppings = maxToppings - toppingAmount;
			totalBill = totalBill + toppingPrize;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "C", n) == 0) {
			toppingAmount = toppingAmountGenerator(maxToppings);
			toppingPrize = toppingPrize + (30 * toppingAmount);
			maxToppings = maxToppings - toppingAmount;
			totalBill = totalBill + toppingPrize;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "N", n) == 0) {
			toppingAmount = toppingAmountGenerator(maxToppings);
			toppingPrize = toppingPrize + (30 * toppingAmount);
			maxToppings = maxToppings - toppingAmount;
			totalBill = totalBill + toppingPrize;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "W", n) == 0) {
			toppingAmount = toppingAmountGenerator(maxToppings);
			toppingPrize = toppingPrize + (30 * toppingAmount);
			maxToppings = maxToppings - toppingAmount;
			totalBill = totalBill + toppingPrize;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "M", n) == 0) {
			toppingAmount = toppingAmountGenerator(maxToppings);
			toppingPrize = toppingPrize + (30 * toppingAmount);
			maxToppings = maxToppings - toppingAmount;
			totalBill = totalBill + toppingPrize;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			printf("\n");
			break;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}
	}
}

void juiceRecorder() {/* Implementation of juiceRecorder() funtion */

	while (1) {

		printf("------------Juice Menu---------\n");
		printf("W = WaterMelon       - Rs.360/=\n");
		printf("L = Limejuice        - Rs.360/=\n");
		printf("S = LimeSoda         - Rs.360/=\n");
		printf("X = Exit\n");
		printf("-------------------------------\n");
		printf("\n");

		printf(
				"Please Enter Letter Of Your Choice.\nMaximum Orders Allowed For A Table Is %li\n",
				maxOrders);
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the end*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			juiceRecorder(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "W", n) == 0) {
			totalBill = totalBill + (360 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "L", n) == 0) {
			totalBill = totalBill + (360 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "S", n) == 0) {
			totalBill = totalBill + (360 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			printf("\n");
			break;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}
	}

}

void sandwichRecorder() {/* Implementation of sandwichRecorder() funtion */

	while (1) {

		printf("---------------SandWich Menu----------------\n");
		printf("C = Cheese and Pickle              -Rs.300/=\n");
		printf("S = Chicken sweet corn and Mayo    -Rs.360/=\n");
		printf("B = Bacon and Mozzarella           -Rs.360/=\n");
		printf("X = Exit\n");
		printf("---------------------------------------------\n");
		printf("\n");

		printf(
				"Please Enter Letter Of Your Choice.\nMaximum Orders Allowed For A Table Is %li\n",
				maxOrders);
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the endto terminate*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			sandwichRecorder(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "C", n) == 0) {
			totalBill = totalBill + (300 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "S", n) == 0) {
			totalBill = totalBill + (360 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "B", n) == 0) {
			totalBill = totalBill + (360 * orderAmount());
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			break;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}
	}
}

void cakeCokkieRecorder() {/* Implementation of cakeCokkieRecorder() funtion */

	while (1) {

		printf("---------Cake Cokkie Menu--------\n");
		printf("C = Chocolate Cookies     -Rs.70/=\n");
		printf("B = Blueberry Cheese Cake -Rs.150/=\n");
		printf("S = Strawberry muffins    -Rs.100/=\n");
		printf("X = Exit\n");
		printf("----------------------------------\n");
		printf("\n");

		printf(
				"Please Enter Letter Of Your Choice.\nMaximum Orders Allowed For A Table Is %li\n",
				maxOrders);
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */
		printf("\n");

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the end*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));
			/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			cakeCokkieRecorder(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "C", n) == 0) {
			totalBill = totalBill + (70 * orderAmount());
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "B", n) == 0) {
			totalBill = totalBill + (150 * orderAmount());
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "S", n) == 0) {
			totalBill = totalBill + (100 * orderAmount());
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			break;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}
	}
}

void menuScreen() {/* Implementation of menuScreen funtion */

	while (1) {

		printf("--------------Main Menu-----------\n");
		printf("C = Coffee\n");
		printf("J = Juice\n");
		printf("S = SandWich\n");
		printf("K = Cake And Cokkie\n");
		printf("B = Receive Bill And Exit\n");/*Exit Program while purchasing Bill*/
		printf("X = Cancel Orders And Start New One\n");
		printf("-----------------------------------\n");
		printf("\n");/*printing a newline*/

		printf(
				"Please Enter Letter Of Your Choice.\nMaximum Orders Allowed For A Table Is %li\n",
				maxOrders);
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		int n = strlen(input) - 1;/* This is used to get length of string array.A C string needs a '\0' at the end*/
		/* So strlen will return one more than the entered input to correct this, I have reduced length by one */

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			printf("\n");
			menuScreen(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "C", n) == 0) {
			coffeeRecorder();
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "J", n) == 0) {
			juiceRecorder();
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "S", n) == 0) {
			sandwichRecorder();
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "K", n) == 0) {
			cakeCokkieRecorder();
			printf("\n");
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "B", n) == 0) {
			if(totalBill == 0){
				printf("You Haven't Ordered Anything!\n");
				if(confirmation()){       /*Asking wether user to wants quit or not*/
					break;
				}else{
					menuScreen();
				}
			}else{
				break;
			}

		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "X", n) == 0) {
			if (confirmation()) {
				totalBill = 0;
				maxOrders = 10;
			}
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}

	}
}

int letterCheck(char * clear) { /* Implementation of letterCheck(char * clear) funtion */
	int n = strlen(clear);
	for (int i = 0; i < n; i++) {
		if (!isalpha(clear[i])) {/*isalpha function checks if there are letters in the array.*/
			return 1;
		}
	}
	return 0;
}

long orderAmount() { /* Implementation of orderAmount() funtion */

	long numberOfOrders;

	while (1) {

		printf(
				"Please Enter The Amount You Want.Maximum Number Of Orders For Table is %li\n",
				maxOrders);/*li means long integer*/
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin);/* This function is used to get a string input from the keyboard */

		if (digitCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Number.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));
			orderAmount(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		numberOfOrders = strtol(input, &filter, 10); /* This function will be used to convert string to an long integer. */
		/* It will return 0 if it fails to convert the string into long integer */

		if (numberOfOrders >= 0 && numberOfOrders <= maxOrders) {
			maxOrders = maxOrders - numberOfOrders;
			return numberOfOrders;
		}

		if (numberOfOrders > maxOrders) { /* This condition return an error message if input is not within range.*/
			printf(
					"Maximum Allowed Orders.Please Enter The No Of Orders Within Range!\n");

		}

	}
}

long toppingAmountGenerator(long maxToppings) {/* Implementation of toppingAmountGenerator(long maxToppings) funtion */

	long numberOfOrders;
	long maxToppingOrders = maxToppings;

	while (1) {

		printf("For How Many Of Your %li Coffee's Do You U Need Toppings?\n",
				maxToppingOrders);/*li means long integer*/
		fflush(stdout); /* This is used to prevent output from being buffered. */
		fgets(input, MAX, stdin); /* This function is used to get a string input from the keyboard */

		if (digitCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Number.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			toppingAmountGenerator(maxToppings); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		numberOfOrders = strtol(input, &filter, 10); /* This function will be used to convert string to an long integer. */
		/* It will return 0 if it fails to convert the string into long integer */

		if (numberOfOrders >= 0 && numberOfOrders <= maxToppingOrders) {
			maxToppings = maxToppings - numberOfOrders;
			return numberOfOrders;
		}

		if (numberOfOrders > maxToppingOrders) { /* This condition return an error message if input is not within range.*/
			printf(
					"Maximum Allowed Orders For This Table is %li.Please Enter The No Of Orders Within Range!\n",
					maxToppings);
		}

	}
}

char * toUpperCase(char * clear) {/*Implementation of toUpperCase(char * clear) function*/
	int n = strlen(clear);/*Gets string length*/
	static char toUpperCase[MAX];
	for (int i = 0; i < n; i++) {/*Running a for loop to convert all char to uppercase*/
		toUpperCase[i] = toupper(clear[i]);
	}
	return toUpperCase;/*Return string of uppercase*/
}

int confirmation() {/*Implementation of confirmation() function.It return 1 if user enter Y or 0 If N*/
					/*works as a boolean function for other if conditions in this program*/
	while (1) {
		printf("Are U Sure Y = Yes | N = No\n");
		fflush(stdout);
		fgets(input, MAX, stdin);
		int n = strlen(input) - 1;

		if (letterCheck(clearWhiteSpaces(input))) {
			printf("This Is Not A Letter.Please Try Again!\n");
			memset(clearWhiteSpaces(input), 0, strlen(clearWhiteSpaces(input)));/*This funtion is used to clear array returned in clearwhitespaces() funtion. So it wont't overflow in while loop*/
			printf("\n");
			confirmation(); /* This is a recursive funtion to prevent code from executing the bottom code*/
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "Y", n) == 0) {
			return 1;
		}

		else if (strncmp(clearWhiteSpaces(toUpperCase(input)), "N", n) == 0) {
			return 0;
		}

		else {
			printf("Invalid Letter.Please Try Again!\n");
			printf("\n");
		}
	}
}
