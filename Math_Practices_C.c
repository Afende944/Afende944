#include <stdio.h> <stdlib.h> <math.h>
#define PI;

/*I Alexis Fenderson here certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus
 */

/* Computes and returns the values (as a dynamicaly allocated array)
    of the following function given input values
*/


double * linear_func(int a, int b, const double * values, int size) {

double *ptr = (double *)malloc(size * sizeof(double));

for (int i = 0; i < size; i++) { //Loop through
    ptr[i] = (a * values[i]) + b; //point array to the proper arithmetic (then repeat)

}

return ptr;

}

/* Computes and returns the values (as a dynamically allocated array) 
of the following function (given input values):
*/

double * quadratic_func(int a, int b, const double * values, int size) {


    double *ptr = (double *)malloc(size * sizeof(double));

        for (int i = 0; i < size; i++) {
         ptr[i] = (pow(values[i], 2) + (a * values[i]) + b); //pow

    }

return ptr;

}

/* Computes and returns the values
 (as a dynamically allocated array) of the following function (given input values):
*/
double * exp_func(int a, int b, const double * values, int size) {


double *ptr = (double *) malloc(size * sizeof(double));

    for (int i = 0; i < size; i++) {
        ptr[i] = exp(values[i] * a); //exp

    }

return ptr;

}

/* Computes and returns the values (as a dynamically allocated array) 
of the following function (given input values)
*/
double * sin_func(int a, int b, const double * values, int size) {

double *ptr = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++) {
        ptr[i] = a * sin(b * values[i]); //use sin

    }

    return ptr;

}

/* Using a switch statement based on the value of order, compute the following derivative
approximations, using the value of order. 

/* Param */

//You must declare function pointers to compute all of these values. 

/* For other values of order, please return the value 3.14159 in the default
switch case. The function computed is taken in by string (const char *), and the following
string values (you may assume only these values) are used */



double * func_derivative(const char * func, double * val_plus, double * val, double *
    val_minus, int a, int b, int order, double h, int size) {


    double *Final_arr = (double *)malloc(size * sizeof(double)); //Dynamically store array

        if (order >= 3) { //Before our cases, if order is greater than 3 just return PI
            return PI;
        
        }

        if (func == "lin") { //For each possible func, theres 0-2 cases in which there are 3 things you can do to it

            switch (order) {
                case 0: // First do the math for a linear function
                *Final_arr = *linear_func(a, b, val, size); 
                break;

                case 1: //Next case, calculate the linear function and then take first derivative
                *Final_arr = (*linear_func(a, b, val_plus, size) - *linear_func(a,b,val_minus,size) / h);
                break;

                case 2: // Final case, calculate linear function then take the second derivative
                *Final_arr = (*linear_func(a, b, val_plus, size) - (2 * *linear_func(a,b,val,size)) + *linear_func(a,b,val_minus,size)) / pow(h, 2);
                break;

    }
}

    //Basically repeat that for each arithemetic type
    
     else if (func == "exp") { //Same thing here

        switch (order) {
            case 0:
            *Final_arr = *exp_func(a, b, val, size); //Now we just take the arithmetic of the exp function and calculate it as f(x)
            break;

            case 1:
            *Final_arr = (*exp_func(a, b, val_plus, size) - *exp_func(a,b,val_minus,size) / h); //First derivative formula
            break;

            case 2:
            *Final_arr = (*exp_func(a, b, val_plus, size) - (*exp_func(a, b, val, size) * 2) + *exp_func(a,b,val_minus,size) / pow(h,2)); //Second Deriv formula
            break;

    }
}

    else if (func == "quad") { //Quadratic formula

    switch (order) {
        case 0:
        *Final_arr = *quadratic_func(a, b, val, size); //Same concept
        break;

        case 1:
        *Final_arr = (*quadratic_func(a, b, val_plus, size) - *quadratic_func(a, b, val_minus, size) / h);
        break;

        case 2:
        *Final_arr = (*quadratic_func(a, b, val_plus, size) - (*quadratic_func(a, b, val, size) * 2) + *quadratic_func(a, b, val_minus, size))/ pow(h, 2);
        break;

    }
 }

    else if (func == "sin") { //compares func to see if it equates to sin

    switch (order) { //determines which order
        case 0:
        *Final_arr = *sin_func(a, b, val, size); //Final one
        break;

        case 1:
        *Final_arr = (*sin_func(a, b, val, size) / h);
        break;

        case 2:
        *Final_arr = (*sin_func(a, b, val_plus, size) - (2 * *sin_func(a, b, val, size)) + *sin_func(a, b, val_minus, size) / pow(h, 2));
        break;
    
    }
}
    
    return Final_arr;

    free(Final_arr); //frees dynamically located array

}

int main(int argc, char *argv[]) {

    int size =  argc - 2; 
    double *val = (double *) malloc(size *sizeof(double));
    double *val_plus = (double *) malloc(size *sizeof(double)); 
    double *val_minus = (double *) malloc(size *sizeof(double)); 
    
    for (int i = 0; i < size - 1; i++) { //val array
        val[i] = atof(argv[i + 1]);
    }

    double h = atof(argv[size]);
    
    for (int i = 0; i < size - 1; i++) {
        val_plus[i] = val[i] + h; //Values x+h
        val_minus[i] = val[i] - h; //Value x-h
    }
    
    free(val);
    free(val_plus);
    free(val_minus);
    

    return 0;

}


/* Sources */

// GeeksforGeeks
// C Programming for Dummies
