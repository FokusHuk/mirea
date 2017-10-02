#include<stdio.h>
#include<stdlib.h>

#define FC(f) (((f) - 32) / 1.8)
#define CF(c) ((c) * 1.8 + 32)
#define CK(c) ((c) + 273.75)
#define KC(k) ((k) - 273.15)
#define F "%.2f F\n%.2f C\n%.2f K\n"
#define C "%.2f C\n%.2f F\n%.2f K\n"
#define K "%.2f K\n%.2f C\n%.2f F\n"
#define FCK "%.2f F\n%.2f C\n%.2f K\n\n%.2f C\n%.2f F\n%.2f K\n\n%.2f K\n%.2f C\n%.2f F\n"

int main(int argc, char *argv[])
{
    if(argc == 3)
	    switch(argv[2][0]) {
			case 'F': case 'f': printf(F, atof(argv[1]), FC(atof(argv[1])), CK(FC(atof(argv[1])))); break;
			case 'C': case 'c': printf(C, atof(argv[1]), CF(atof(argv[1])), CK(atof(argv[1]))); break;
			case 'K': case 'k': printf(K, atof(argv[1]), KC(atof(argv[1])), CF(KC(atof(argv[1])))); break; }
	else if(argc == 2) printf(FCK, atof(argv[1]), FC(atof(argv[1])), CK(FC(atof(argv[1]))), atof(argv[1]), CF(atof(argv[1])), CK(atof(argv[1])), atof(argv[1]), KC(atof(argv[1])), CF(KC(atof(argv[1]))));
	else printf("Incorrect arguments.\n");
	return 0;
}
