#include <stdio.h>
#include <math.h>

// CORRESPONDING FUNCTION:
//-----------------------------------------------//
double function(double x) {
    double res = x - cos(x);

    return res;
}

double function_derivative(double x) {
    double res = 1 + sin(x);

    return res;
}
//-----------------------------------------------//

// FUNCTIONS' DECLARATIONS:
//-----------------------------------------------//
double limit_decimal(int max, double num);
//-----------------------------------------------//

// ROOT FINDING METHODS' DECLARATIONS:
//-----------------------------------------------//
double BISECTION(double lower_bound, double upper_bound);
double NEWTON_RAPHSON(double random_point);
double REGULA_FALSI(double lower_bound, double upper_bound);
double SECANT(double lower_bound, double upper_bound);
//-----------------------------------------------//

// MAIN FUNCTION:
//-----------------------------------------------//
int main() {
    // BISECTION(lower_bound, upper_bound); 
    BISECTION(0, 100);

    // NEWTON-RAPHSON(random_point); 
    NEWTON_RAPHSON(2);

    // REGULA-FALSI(lower_bound, upper_bound); 
    REGULA_FALSI(0, 100);
    
    // SECANT(lower_bound, upper_bound); 
    SECANT(0, 100);

    return 0;
}
//-----------------------------------------------//

// ROOT FINDING METHODS' DEFINATIONS:
//-----------------------------------------------//
double BISECTION(double lower_bound, double upper_bound) {
    printf("\n------------------------------------\n");
    printf("Running Bisection Method (lower --> upper --> x --> f(x)):\n");
    printf("Lower Bound: %f\n", lower_bound);
    printf("Upper Bound: %f\n\n", upper_bound);

    double x = 0, prev_x = -1;
    int iteration = 0;

    while(prev_x != x) {
        iteration++;
        prev_x = x;
        x = (upper_bound + lower_bound) / 2;

        if (function(x) > 0) {
            upper_bound = x;
        } else {
            lower_bound = x;
        }

        x =limit_decimal(9, x);
        prev_x = limit_decimal(9, prev_x);

        printf("%d)\t%0.9f --> %.9f --> %.9f --> %.9f\n", iteration, lower_bound, upper_bound, x, function(x));
    }

    printf("\nCorresponding Root (Bisection Method): %.9f", x);
    printf("\n------------------------------------\n");

    return x;
}

double NEWTON_RAPHSON(double random_point) {
    printf("\n------------------------------------\n");
    printf("Running Newton-Raphson Method (previous x --> x):\n");
    printf("Random Starting Point: %.0f\n\n", random_point);

    double x = random_point, prev_x = -1;
    int iteration = 0;

    while(prev_x != x) {
        iteration++;
        printf("%d)\t%0.9f --> %.9f \n", iteration, prev_x, x);

        prev_x = x;
        x = prev_x - (function(x)/function_derivative(x));

        x = limit_decimal(9, x);
        prev_x = limit_decimal(9, prev_x);
    }
    printf("%d)\t%0.9f --> %.9f \n", iteration+1, prev_x, x);

    printf("\nCorresponding Root (Newton-Raphson): %.9f", x);
    printf("\n------------------------------------\n");

    return x;
};

double REGULA_FALSI(double lower_bound, double upper_bound) {
    printf("\n------------------------------------\n");
    printf("Running Regula-Falsi Method (previous x --> x --> f(lower) --> f(upper) --> f(x)):\n");
    printf("Lower Bound: %.0f\n", lower_bound);
    printf("Upper Bound: %.0f\n\n", upper_bound);

    double x = 0, prev_x = -1;
    int iteration = 0;

    while(prev_x != x) {
        iteration++;
        prev_x = x;
        x = (lower_bound * function(upper_bound) - upper_bound * function(lower_bound)) / (function(upper_bound) - function(lower_bound));

        if (function(x) > 0) {
            if (function(lower_bound) > 0) {
                lower_bound = x;
            } else {
                upper_bound = x;
            }
        } else {
            if (function(lower_bound) > 0) {
                upper_bound = x;
            } else {
                lower_bound = x;
            }
        }

        x = limit_decimal(9, x);
        prev_x = limit_decimal(9, prev_x);

        printf("%d)\t%0.9f --> %.9f --> %.9f --> %.9f --> %.9f \n", iteration, prev_x, x, function(lower_bound), function(upper_bound), function(x));
    }

    printf("\nCorresponding Root (Regula-Falsi): %.9f", x);
    printf("\n------------------------------------\n");

    return x;
}

double SECANT(double lower_bound, double upper_bound) {
    printf("\n------------------------------------\n");
    printf("Running Secant Method (previous x --> x --> f(lower) --> f(upper) --> f(x)):\n");
    printf("Lower Bound: %.0f\n", lower_bound);
    printf("Upper Bound: %.0f\n\n", upper_bound);

    double x = 0, prev_x = -1;
    int iteration = 0;

    while(prev_x != x) {
        iteration++;
        prev_x = x;
        x = (lower_bound * function(upper_bound) - upper_bound * function(lower_bound)) / (function(upper_bound) - function(lower_bound));

        lower_bound = upper_bound;
        upper_bound = x;

        x = limit_decimal(9, x);
        prev_x = limit_decimal(9, prev_x);

        printf("%d)\t%0.9f --> %.9f --> %.9f --> %.9f --> %.9f \n", iteration, prev_x, x, function(lower_bound), function(upper_bound), function(x));
    }

    printf("\nCorresponding Root (Secant Method): %.9f", x);
    printf("\n------------------------------------\n");

    return x;
}
//-----------------------------------------------//

// FUNCTIONS' DEFINATIONS:
//-----------------------------------------------//
double limit_decimal(int max, double num) {
    if (num > 2) {
        return num;
    }
    double processed_num = (int) (num * pow(10, max));

    return (double) (processed_num / pow(10, max));
}
//-----------------------------------------------//