//Kshitij Bantupalli

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

long numbers[100000];

void writeFile()		//Function to write to file.
{
	FILE *fp;
	int i= 0;
	fp = fopen("data.txt", "w");
	for(i=0; i<10000; i++)
	{
		fprintf(fp, "%d ", rand());
	}
	fclose(fp);
}

int readFile()			//Function to read file.
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
       			//printf("%d\n", readNumber);
			numbers[i] = readNumber;
			i++;					//do whatever you want with the readNumber here...
       
       	        	digitCount = 0;  //reset buffer to read new number
		}
        } while(iochar != EOF);
}

int main(int argc, char * argv[])
{
	struct timeval t1, t2;
	double elapsedTime;

	gettimeofday(&t1, NULL);			//Start time.
	long max, min, sum, k=0;
	long count[1000] = {};
	int  j=0;	
	char *p;
	printf("The number of intervals are : %s\n", argv[1]);
	long conv = strtol(argv[1], &p, 10);
	long temp[100];
	writeFile();		//Writing to file.
	int i = readFile();
	max = numbers[0];
	min = numbers[0];
	for (j=1; j<10000; j++)
	{
		if(numbers[j] < min)
			min = numbers[j];
		else if(numbers[j] > max)
			max = numbers[j];
	}
	long intSize = (max - min)/conv;
	printf("\nThe max is: %d", max);
	printf("\nThe min is: %d\n", min); 
	printf("\nThe interval size is :%ld\n", intSize);
	j=1;
	temp[0] = min;
	sum = min + intSize;
	while(sum<max)
	{
		temp[j] = sum;
		sum += intSize;
		j++;
	}
	temp[conv]= max;
	j = 0, k= 0;
	for(j = 0; j< 10000; j++)
	{
		while(k<conv)
		{
			if((numbers[j]>=temp[k])&&(numbers[j]<=temp[k+1]))
			{
				count[k] += 1;
				//printf("\n%ld\n", count[k]);
			}
			k++;
		}
	k=0;
	}
	printf("\n");
	for(k=0; k<conv; k++)
	{
		printf("The interval %ld to %ld has %ld elements.\n", temp[k], temp[k+1],count[k]);
	}
	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;		//End time.
	printf("\nTime elapsed : %f\n", elapsedTime);
	return 0;
}
