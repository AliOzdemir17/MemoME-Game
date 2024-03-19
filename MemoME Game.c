#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int boardSize();
int initializeBoard(char** boardseem,char** boardhidden,int n);
int getCoordinates(int* row1,int* row2,int *column1,int* column2,char **boardseem,char **boardhidden,int n);
int checkCharacters(int row1,int row2,int column1,int column2,char **boardseem,char **boardhidden,int n);
void displayBoard(int sump1,int sump2);

int main()
{
	char again;
	int getcor;
	printf("Welcome to MemoME!\n");
	
	do//if user want to play again this loop work again
	{
	int n=boardSize();// the board size(n) is taken from user
	int i,j,sump1=0,sump2=0,player=1;
	int row1,row2,column1,column2,countmatched=0;
	
	char **boardseem = (char **)malloc(n * sizeof(char *));//arrays are stored dynamically
    for (i = 0; i < n; i++) 
	{
    boardseem[i] = (char *)malloc(n * sizeof(char));
    }
    
    char **boardhidden = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++) 
	{
    boardhidden[i] = (char *)malloc(n * sizeof(char));
    }
	
	initializeBoard(boardseem,boardhidden,n); //the board is populated randomly
	
	do
	{
		if(player%2==1)
		{
			printf("--Player 1 Turn:--\n");
		}
		else
		{
			printf("--Player 2 Turn:--\n");
		}
		
	printf("    ");
	
	for(i=0;i<n;i++)
	{
		printf("%2d ",i+1);
	}
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%2d ",i+1);
		for(j=0;j<n;j++)
		{
			printf("%3c",boardhidden[i][j]);
		}
		printf("\n");
	}	
	getcor=getCoordinates(&row1,&row2,&column1,&column2,boardseem,boardhidden,n);//Get coordinates from the user
	while(getcor == 0)
	    {
            getcor=getCoordinates(&row1,&row2,&column1,&column2,boardseem,boardhidden,n);
        }
        while (getcor==1) 
		{
            break;
        }
	
	if(checkCharacters(row1,row2,column1,column2,boardseem,boardhidden,n)==1)
	{
		//If characters match
		boardhidden[row1-1][column1-1]=boardseem[row1-1][column1-1];
		boardhidden[row2-1][column2-1]=boardseem[row2-1][column2-1];
		printf("    ");
	
	    for(i=0;i<n;i++)
	    {
		printf("%2d ",i+1);
	    }
	    
	    printf("\n");
	    
	    for(i=0;i<n;i++)
	    {
		printf("%2d ",i+1);
		for(j=0;j<n;j++)
		{
			printf("%3c",boardhidden[i][j]);
		}
		printf("\n");
	    }
	    
	    if(player%2==1)
		{
			countmatched++;
		    sump1+=2;
			printf("Lucky you! Your score: 2, total score: %d\n\n",sump1);
		}
		else
		{
			countmatched++;
			sump2+=2;
			printf("Lucky you! Your score: 2, total score: %d\n\n",sump2);
		}
	}//big if end
	
	
	else
	{
		//If characters do not match
		boardhidden[row1-1][column1-1]=boardseem[row1-1][column1-1];
		boardhidden[row2-1][column2-1]=boardseem[row2-1][column2-1];
		printf("    ");
	
	    for(i=0;i<n;i++)
	    {
		printf("%2d ",i+1);
	    }
	    
	    printf("\n");
	    
	    for(i=0;i<n;i++)
	    {
		printf("%2d ",i+1);
		for(j=0;j<n;j++)
		{
			printf("%3c",boardhidden[i][j]);
		}
		printf("\n");
	    }
	    
	    if(player%2==1)
		{
		    sump1-=1;
			printf("Unlucky! Your score= -1, total score: %d\n\n",sump1);	
		}
		else
		{
			sump2-=1;
			printf("Unlucky! Your score= -1, total score: %d\n\n",sump2);
		}
		//Unmatched characters revert back to old 
		boardhidden[row1-1][column1-1]='@';
		boardhidden[row2-1][column2-1]='@';

	}
	player++;
	
	if(countmatched==(n*n)/2)
	{
		printf("Would you like to play again (Y/N)? ");
		scanf(" %c",&again);
		if(again=='N')
		{
			printf("Byee");
		}
	}
	
	
}while(countmatched!=(n*n)/2 );//do while end
	

	printf("\n");
	//Display the final scores
	displayBoard(sump1,sump2);
	
	//Free allocated memory
	for (i = 0; i < n; i++)
    {
        free(boardseem[i]);
    }
    free(boardseem);
    
    for (i = 0; i < n; i++)
    {
        free(boardhidden[i]);
    }
    free(boardhidden);
    
}while(again=='Y');	
	
	
	return 0;
}

int boardSize()// Function to get the board size from the user
{
	int n;
	
	do
	{
	  printf("Please specify the board size(2-32): ");
	  scanf("%d",&n);
	  
	  if(n<2 || n>32)
	  {
	  printf("Board size can only be between 2-32!\n");
	  }
	  if(n>2 && n<32)
	  {
	  	if(n%2!=0)
	   {
	  printf("Board size can only be a multiple of two!\n");
	   }
	  }
	}while(n>32 || n<2 || n%2!=0 );
	
	printf("A Board is created for you with the size of %dx%d!\n",n,n);
		
	return n;
}

int initializeBoard(char **boardseem,char **boardhidden,int n)//the board is populated randomly
{
	int i,j,x,y;
	int isCoordinatUsed[n][n];//this function checks that x and y are used
	srand(time(NULL));
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			isCoordinatUsed[i][j]=0;//the elements of this function are initially set equal to 0
		}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			do
			{
			x=rand()%(n);//A random number is assigned to the x value
	        y=rand()%(n);//A random number is assigned to the y value		
			}while(isCoordinatUsed[x][y]!=0);//if x and y are not used , their value equal 0
			
	        isCoordinatUsed[x][y]=1;// x and y which are used set equal 1
	        boardseem[x][y]=33+i;//the elements of array are assigned to ASCII codes
		}
	}	
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			boardhidden[i][j]='@';   
		}
	}
		
}

int getCoordinates(int* row1,int* row2,int *column1,int* column2,char **boardseem,char **boardhidden,int n)//Coordinates are taken from user and checked
{
	int i,j;
	
	printf("Enter the coordinates of doors to open: ");
	scanf("%d,%d  %d,%d",&*row1,&*column1,&*row2,&*column2);
	
	if(*row1>n || *row2>n || *column1>n || *column2>n || *row1<1 || *row2<1 || *column1<1 || *column2<1)
	{
		printf("Sorry, wrong coordinates!\n");
		return 0;
	}
	if(*row1==*row2 && *column1==*column2)
	{
		printf("Sorry, two door coordinates are same!\n");
		return 0;
	}
	if( boardhidden[*row1-1][*column1-1]!='@')
	{
		printf("%d,%d already opened!\n",*row1,*column1);
		return 0;
	}
	if( boardhidden[*row2-1][*column2-1]!='@')
	{
		printf("%d,%d already opened!\n",*row2,*column2);
		return 0;
	}
	
	return 1;  
}

int checkCharacters(int row1,int row2,int column1,int column2,char **boardseem,char **boardhidden,int n)//Coordinates which are taken from the user checked that these coordinates are equal
{
	if(boardseem[row1-1][column1-1]==boardseem[row2-1][column2-1])//if coordinates are equal returned 1 else return 0
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

void displayBoard(int sump1,int sump2)//The scores are taken from the players are compared with each other and the winner is determined.
{
	if(sump1>sump2)
	{
		printf("***Winner is Player 1!***\n");
	}
	if(sump2>sump1)
	{
		printf("***Winner is Player 2!***\n");
	}
	if(sump1==sump2)
	{
		printf("***There is no winner Draw!***\n");
	}
}




