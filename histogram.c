#include<stdio.h>
#include<stdlib.h>

int numbers[100];

void writeFile()		//Function to write to file.
{
	FILE *fp;
	int i= 0;
	fp = fopen("data.txt", "w");
	for(i=0; i<10; i++)
	{
		fprintf(fp, "%d ", rand());
	}
	fclose(fp);
}

int readFile()
{
	FILE *fp;
	fp = fopen("data.txt", "r");
	int i=0;
	char simpleBuffer[12];    //max 10 int digits + 1 negative sign + 1 null char string....if you read more, then you probably don't    have an int there....
	int  digitCount = 0;
	int iochar;

	int readNumber; //the number read from the file on each iteration
	do {

    		iochar=getc(fp);

    		if(iochar!=' ' && iochar != EOF)
		{
        		if(digitCount >= 11)
            		return 0;   //handle this exception in some way

        		simpleBuffer[digitCount++] = (char) iochar;
    		}
    		else if(digitCount > 0)
		{
        		simpleBuffer[digitCount] = 0; 		//append null char to end string format

        		readNumber = atoi(simpleBuffer);    	//convert from string to int
       			printf("%d\n", readNumber);
			numbers[i] = readNumber;
			i++;					//do whatever you want with the readNumber here...
       
       	        	digitCount = 0;  //reset buffer to read new number
		}
        } while(iochar != EOF);
}

int main(int argc, char * argv[])
{
	int max = numbers[0], min= numbers[0], j=0;
	char *p;
	printf("The number of intervals are : %d\n", argv[1]);
	long conv = strtol(argv[1], &p, 10);
	int interval = conv;
	writeFile();		//Writing to file.
	int i = readFile();
	for (j=1; j<10; j++)
	{
		if(numbers[j] < min)
			min = numbers[j];
		else if(numbers[j] > max)
			max = numbers[j];
	}
	int intSize = (max + min)/interval;
	printf("\n%d\n", intSize); 
	return 0;
}
