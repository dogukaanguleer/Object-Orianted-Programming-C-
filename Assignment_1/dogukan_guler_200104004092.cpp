#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string>

using namespace std;
/*Function prototypes*/
bool isUniqe(string str);
int rollDice(int numberOfDigits);
void get_estimates(string secretNumber);
int firstCount(string estimatedNumber, string secretNumber);
void secondCount(string estimatedNumber, string secretNumber);

bool isUniqe(string str) /* checks the given string is uniq or not*/
{
    bool isUniqe = 1; /*uniqe flag*/
    int numberOfDigits = str.length(); /* lenght of string assings to numberOfDigits */

    /* Looks a index and checks with other indices, if there is a same index, assings 0 to isUniqe flag */
    for (int i = 0; i < (numberOfDigits - 1); i++)
        for (int count = i + 1; count < numberOfDigits; count++)
            if (str[i] == str[count])
                isUniqe = 0;

    if (isUniqe == 0 || numberOfDigits > 9) /*if flag is 0 or number of digits bigger than 9 , returns false*/
        return false;
    else
        return true;
}
int rollDice(int numberOfDigits) /* Create a secret number randomly*/
{
    bool isUniqeFlag = 0; /*it holds random number's uniq sitaution*/
    int randomNumber;  /* holds random number */
    string str; /*str string is hold the randomNumber*/
    while (!isUniqeFlag)
    {
        /* it randoms according the given digit number. If 3 is given, then selects a number between 100 and (900 + 100)*/
        randomNumber = (rand() % (9 * (int)pow(10, numberOfDigits - 1))) + (int)pow(10, numberOfDigits - 1);
        str = to_string(randomNumber); /*convert to randomNumber to string*/
        isUniqeFlag = isUniqe(str);    /* calls the function to check is random number is uniqe or not*/
    }
    return randomNumber;
}
void get_estimates(string secretNumber) /*interactive part , this part is used two section in main function. */
{
    string estimatedNumber; /*holds input of user(estimated number) */
    int iteration; /*holds loops iteration number*/
    bool controlFlag = 0; /*To quit from 2 loops*/
    for (iteration = 0; iteration < 100; iteration++) /* Maximum 100 iteration*/
    {
        cin >> estimatedNumber;

        for (int i = 0; i < estimatedNumber.length(); i++) /*Check each chracter of string parameter*/
            if (isdigit(estimatedNumber[i]) == false)      /*if parameter is not digit, it gives a error message */
            {
                cout << "E2" << endl;
                controlFlag = 1;
                break;
            }
        if (controlFlag == 1) /*out to 2 loop*/
            break;

        if (estimatedNumber[0] == '0')
        { /*if the given input's first character is 0. Example: 0123*/
            cout << "E2" << endl;
            break;
        }
        if ((estimatedNumber.length() != secretNumber.length()) || !isUniqe(estimatedNumber)) /*Checks the number of digits is same with secret number and  and given input is uniqe*/
        {
            cout << "E1" << endl;
            break;
        }
        if (firstCount(estimatedNumber, secretNumber) == secretNumber.length()) /* if first count's return value is same with secret number's digit number*/
        {
            cout << "FOUND " << iteration + 1 << endl;
            break;
        }
        secondCount(estimatedNumber, secretNumber); /* calls the secondCount function*/
    }
    if (iteration == 100)
        cout << "FAILED" << endl;
}
int firstCount(string estimatedNumber, string secretNumber) /* finds the match number */
{
    int matchCounter = 0;
    /*checks all digits, if the estimated number's index is same with secret number index, increase match counter */
    for (int i = 0; i < secretNumber.length(); i++)
        if (estimatedNumber[i] == secretNumber[i])
            matchCounter++;

    if (secretNumber.length() != matchCounter) /* If the user find the secret number, doesn't give hint*/
        cout << matchCounter << " ";

    return matchCounter;
}
void secondCount(string estimatedNumber, string secretNumber)
{
    int matchCounter = 0;

    for (int i = 0; i < secretNumber.length(); i++)
        for (int c = 0; c < secretNumber.length(); c++)
            if (secretNumber[i] == estimatedNumber[c] && c != i) /*Don't check if indices are same.*/
                matchCounter++;

    cout << matchCounter << endl;
}

int main(int argc, char **argv)
{
    if (argc <= 2) /*missing parameter check*/
    {
        cout << "E0" << endl;
        return 0;
    }
    string firstArgument = argv[1];   /*it assings argument 1 to a string*/
    string secondParameter = argv[2]; /*it assings argument 2 to a string*/
    int secondArgument = 0;           /* it holds second argument as a integer*/
    int secretNumber;                 /* it holds secret number*/

    if (secondParameter[0] == '0') /*if the second paramter's first character is 0. Example: 0123*/
    {
        cout << "E0" << endl;
        return 0;
    }

    for (int i = 0; i < secondParameter.length(); i++) /*Check each chracter of string parameter*/
        if (isdigit(secondParameter[i]) == false)      /*if parameter is not digit, it gives a error message */
        {
            cout << "E0" << endl;
            return 0;
        }
    secondArgument = stoi(argv[2]);      /*Convert second argument to integer*/
    srand(static_cast<int>(time(NULL))); /*Prevent producing the same random number*/

    if (firstArgument == "-u" && secondArgument > 0) /* Checks first argument is u or r*/
    {
        if (!isUniqe(secondParameter)) /* checks secret number is uniqe or not */
            cout << "E0" << endl;
        else
            get_estimates(argv[2]); /*if secret number is unique, calls the get_estimates function.*/
    }
    else if (firstArgument == "-r" && secondArgument > 0 && secondArgument < 10) /* Checks first argument is u or r*/
    {
        secretNumber = rollDice(secondArgument); /*calls the rollDice function to create a random number*/
        get_estimates(to_string(secretNumber));  /* calls the get_estimates functions*/
    }
    else
    {
        cout << "E0" << endl;
    }
    return 0;
}
