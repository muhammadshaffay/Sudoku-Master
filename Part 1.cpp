# include <iostream>
# include <pthread.h>
# include <ctime>
# include <stdlib.h>

using namespace std;

pthread_t pid[11];

int** arr = new int*[9];
pthread_mutex_t mtlock;     

struct suduko // for keeping check of grids' row/columns
{	
	int row =0;
	int column =0;
};

void* row(void* arg) // row checker
{ 
    suduko *obj1 = (suduko*) arg;
    int count=0;
    cout << "\n\n------Row Wise Checking---------\n\n\n";

    int temp[9] ;
    for(int i=0; i<9;i++)
    {
        for (int k = 0; k<9;k++)
            temp[k] = false;
        
        for (int j=0; j<9; j++)
        {
            if ( (arr[i][j] > 9) || (arr[i][j] < 1) )
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j] << endl;
                bool boolean = false;
                return (void*) boolean;
            }
            
            if (temp[arr[i][j]-1] == true)
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j]<< endl;
                count++;
            }
            else
                temp[arr[i][j]-1] = true;  
        }
    }
    
    cout << "Row-Vise matrix has repeated values: " << count << endl;
    if (count>0)
        cout << "Validity: 0" << endl; 
    else
        cout << "Validity: 1" << endl;
    
    pthread_exit(NULL);
    return 0;
}

void* column(void* arg) // column checker
{
    suduko *obj1 = (suduko*) arg;
    int count=0;
    cout << "\n\n------Column Wise Checking---------\n\n\n";

    int temp[9] ;
    for(int i=0; i<9;i++)
    {
        for (int k = 0; k<9;k++)
            temp[k] = false;
        
        for (int j=0; j<9; j++)
        {
            if ( (arr[j][i] > 9) || (arr[j][i] < 1) )
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j]<< endl;
                bool boolean = false;
                return (void*) boolean;
            }
            
            if (temp[arr[j][i]-1] == true)
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j]<< endl;
                count++;
            }
            else
                temp[arr[j][i]-1] = true;
        }
    }
    
    cout << "Column-Vise matrix has repeated values: " << count << endl;
    if (count>0)
        cout << "Validity: 0" << endl; 
    else
        cout << "Validity: 1" << endl;
    pthread_exit(NULL);
    
    return 0;
}

void* grid(void* arg) // grid checker
{
    suduko* obj1 = (suduko*) arg;
    int count=0;
    
    pthread_mutex_lock(&mtlock);  
    
    cout << "\n\n------Grid Wise Checking---------\n\n";
    
    cout << endl;
    int rows = obj1->row;
    int columns = obj1->column;
    
    if (obj1->column>6)
    {
        obj1->row+=3;
        obj1->column=0;
    }
    
    rows = obj1->row;
    columns = obj1->column;
    
    cout << rows << " " << columns << endl;
    obj1->column+=3;

    pthread_mutex_unlock(&mtlock);  
   
    int temp[9] ;
    
    for (int k = 0; k<9;k++)
        temp[k] = false;

    for(int i=rows; i<rows+3;i++)
    {
        for (int j=columns; j<columns+3; j++)
        {
            if ( (arr[i][j] > 9) || (arr[i][j] < 1) )
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j] << endl;
                bool boolean = false;
                return (void*) boolean;
            }
            
            if (temp[arr[i][j]-1] == true)
            {
                cout << "row: " << i+1 << " colummn: " << j+1 << " value: " << arr[i][j] << endl;
                count++; 
            }
            else
                temp[arr[i][j]-1] = true;
        }
    }
    
    cout << "Matrix-Vise matrix has repeated values: " << count << endl;
    if (count>0)
        cout << "Validity: 0" << endl; 
    else
        cout << "Validity: 1" << endl;
    pthread_exit(NULL);
}

int main()
{
    for(int i = 0; i < 9; ++i)
        arr[i] = new int[9];

    int arr_temp[9][9] = {
        
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,7,4,5,6,3,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        {1,2,3,4,5,6,7,8,9} ,
        
    } ;
    
    suduko obj2 ;
    
    for (int i=0; i<9; i++)
    {
        for (int j =0 ; j<9; j++)
        {
            arr[i][j] = arr_temp[i][j];
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // row & column threads
    pthread_create(&pid[0] , NULL , row , (void*) &obj2);
	pthread_create(&pid[1] , NULL , column , (void*) &obj2);
    
    obj2.column=0;
    obj2.row=0;
    
    // Grid threads
    for(int i=2 ; i<=10 ; i++)
	    pthread_create(&pid[i] , NULL , grid , (void*) &obj2 );

	pthread_exit(NULL);	
	return 0;
}