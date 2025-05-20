#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* I Alexis Fenderson certify that this programming assignment reflects my own work, 
   without the use of any external individuals (other than course/department staff), 
   generative-AI, or any other forbidden resources. I understand/accept the 
   consequences of cheating as outlined in the course syllabus.

*/

float mean(float arr[], int size) { //Add total numbers divide by amount
    float total = 0;
    int index;

    for(index = 0; index < size; index++) {
    total += arr[index];
    }

    float mean = total / size;
    printf("The mean is = %.3f\n", mean); // Be sure to include 3 decimal point precision

    return mean;
} 

float median(float arr[], int size) { // Finding the middle
    float numMiddle;
    float index = size/2;

    if (index / 2 == 0) { // If even compute the "middle two"
    numMiddle = arr[size/2];
}
else {
    numMiddle = (arr[size/2-1] + arr[size/2])/2;
}

printf("The median is = %.3f\n", numMiddle);
return numMiddle;

}

float mode(float arr[], int size) { // What occurs the most
int arrElement;
int check = arr[0];
int occuranceTimes = 0;
int index = 0;

while (index < size) {
    for (arrElement = 0; arrElement < size; arrElement++) {
        if (check == arr[arrElement]) {
            occuranceTimes += 1;
        }
    index++;
    }
}

    if (occuranceTimes == 1) { //If there is no mode
        occuranceTimes = -1; //Return = -1

    } 
    printf("The mode is = %.3f\n", occuranceTimes);

    return occuranceTimes;
}


float std_dev(float arr[], int size) {
    int index = 0;
    double meanValues[size];
    double numTotal = 0.00;

    for (index = 0; index < size; index++) {
        meanValues[index] = pow(fabs(arr[index] - mean(arr,size)), 2);
        numTotal += meanValues[index];
    }

    numTotal = sqrt(numTotal / size);

    printf("The standard deviation is = %.3f\n", numTotal);
    return numTotal;
}

int * rounded_vals(float arr[], int size) {
    int index;
    float ptr = 0.0;
    int fNum;
        for (index = 0; index < size; index++) {
            ptr = arr[index];
            ptr = round(ptr);
            fNum = (int)ptr;
        }

        printf("The Rounded Values is = %.3f\n", fNum);
        return &fNum; //Be sure to return a pointer 
}

char * ascii(int arr[], int size) {
    int ch;
    int index = 0;

    rounded_vals(arr,size);
    for (index = 0; index < size; index++) {
        if (arr[index] > 64 || arr[index] > 123) {
            ch = (char) arr[index];
        }
        else {
            ch = '*';
        }

    }
    printf("The ascii Values is = %c\n", ch);
    return &ch;
}


int main(int argc, char * argv[]) {

int size = argc -1;
float arr[size];
int counter;


for(counter = 1; counter < argc; counter++) {
    int value = (int) atoi(argv[counter]);
    arr[counter - 1] = value;
}


//Sources:

//Reese: Understanding and Using C Pointers, 1st Edition
//Dan, Gookin C Programming for Dummies
//GeeksforGeeks


