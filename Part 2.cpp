# include <iostream>
# include <pthread.h>

using namespace std;

pthread_t tid[2];

bool Solution_Exists = true;
bool rowclear = false, columnclear = false;
pthread_mutex_t mtlock1 = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mtlock2 = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mtlock3 = PTHREAD_MUTEX_INITIALIZER; 
int invalidentries = 0, threadscreated = 0, noofmoves = 0;
int allthreadids[30];

int matrix[9][9] = {
    
	{6, 2, 4, 5, 3, 9, 1, 8, 7},
	{6, 1, 9, 7, 2, 8, 6, 3, 4},
	{8, 3, 7, 6, 1, 4, 2, 9, 5},
	{1, 4, 3, 8, 6, 5, 7, 2, 9},
	{9, 5, 8, 2, 4, 7, 3, 6, 1},
	{7, 3, 2, 2, 9, 1, 4, 5, 8},
	{3, 7, 1, 9, 5, 7, 8, 4, 2},
	{4, 9, 6, 1, 8, 9, 5, 7, 3},
	{2, 8, 5, 4, 7, 3, 9, 1, 6}

    
};

bool verifier(int digit)
{
    int counter = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (digit == matrix[i][j])
                counter += 1;
        }
    }

    if (counter == 9)
        return true;
    else
        return false;
}

void display()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0 ; j < 9; j++)
        {
            cout << "  " << matrix[i][j] << " ";
        }
        cout << endl;
    }    
}

bool roweligible(int row, int old)
{
    for(int x = 0; x < 9; x++)
    {
        if(matrix[row][x] == old)
            return false;
    }
    return true;
}

bool columneligible(int column, int new_value)
{
    for(int y = 0; y < 9; y++)
    {
        if(matrix[y][column] == new_value)
            return false;
    }
    return true;
}

bool grideligible(int row, int column, int new_value)
{
    for (int x = 0; x < 3; x++)
    { 
        for (int y = 0; y < 3; y++)
        { 
            if (matrix[x + row][y + column] == new_value)
                return false;
	    }
    } 
    return true;     
}

bool eligible(int row, int column, int new_value)
{
    bool decision = roweligible(row, new_value) and columneligible(column, new_value); //and grideligible(row, column, new_value);
    return decision;
}

bool update(int i, int j)
{
    int old = matrix[i][j];
    for(int x = 1; x <  9; x++)
    {
        int new_value = x;
        if( eligible(i, j, new_value) )
        {
            matrix[i][j] = new_value;
            cout << "\n  Value Swapping => Old Value = " << old  << " new value : " <<  new_value << endl;
            cout << "  Position => ( " << i  << " , " <<  j << " ) " << endl;
            noofmoves += 1;
            return true;
        }
    }
    return false;
}

void* rowcheck(void* arg)
{
    bool valid[9];
    for(int i = 0; i < 9; i++)
    {
        for(int k = 0; k < 9; k++) // for one row
            valid[k] = false; 
            
        for(int j = 0; j < 9; j++)
        {
            if(Solution_Exists)
            {
                if (matrix[i][j] > 9 or matrix[i][j] < 1)
                {
                    pthread_mutex_lock(&mtlock1);
                    Solution_Exists = false;
                    cout << "Solution does not exists, Error at Row : " << i << " Column : " << j << " Value : " << matrix[i][j] << endl;
                    pthread_mutex_unlock(&mtlock1);
                    pthread_exit(NULL);
                }
                if (valid[matrix[i][j] - 1] == false)
                {
                    valid[matrix[i][j] - 1] = true;
                }
                else
                {
                    pthread_mutex_lock(&mtlock2);
                    bool decision = update(i,j);
                    pthread_mutex_unlock(&mtlock2);
                    pthread_exit(NULL);
                }
            }
            else
                pthread_exit(NULL);
        }
    }
    
    pthread_mutex_lock(&mtlock3);
    rowclear = true;
    pthread_mutex_unlock(&mtlock3); 
    
    pthread_exit(NULL);
    return 0;
}

void* columncheck(void* arg)
{
    bool valid[9];
    for(int i = 0; i < 9; i++)
    {
        for(int k = 0; k < 9; k++) // for one row
            valid[k] = false; 
            
        for(int j = 0; j < 9; j++)
        {
            if(Solution_Exists)
            {
                if (matrix[j][i] > 9 or matrix[j][i] < 1)
                {
                    pthread_mutex_lock(&mtlock1);
                    Solution_Exists = false;
                    cout << "Solution does not exists, Error at Row : " << i << " Column : " << j << " Value : " << matrix[i][j] << endl;
                    pthread_mutex_unlock(&mtlock1);
                    pthread_exit(NULL);
                }
                if (valid[matrix[j][i] - 1] == false)
                {
                    valid[matrix[j][i] - 1] = true;
                }
                else
                {
                    pthread_mutex_lock(&mtlock2);
                    bool decision = update(j,i);
                    invalidentries += 1;
                    cout << "  Threads Created For This Invalid Entry: " << 2 << endl;
                    cout << "  No. of Moves: " << 2 << endl;
                    pthread_mutex_unlock(&mtlock2);

                    pthread_exit(NULL);
                }
            }
            else
                pthread_exit(NULL);
        }
    }
    
    pthread_mutex_lock(&mtlock3);
    columnclear = true;
    pthread_mutex_unlock(&mtlock3); 
    
    pthread_exit(NULL);
    return 0;
}

int main()
{
    cout << "\n ..................." << endl;
    cout << " | 1) Initial Grid |" << endl;
    cout << " ...................\n" << endl;
     
    display();
    
    cout << "\n\n\n ..................." << endl;
    cout << " | 2) Calculations |" << endl;
    cout << " ...................\n" << endl;
    
    cout << "\n (A) Swappings " << endl;
    while((!rowclear or !columnclear) and Solution_Exists)
    {
        pthread_create(&tid[0], NULL, rowcheck, NULL);
        pthread_create(&tid[1], NULL, columncheck, NULL);
        
        allthreadids[threadscreated] = tid[0];
        threadscreated += 1;
        allthreadids[threadscreated] = tid[1];
        threadscreated += 1;
        
        pthread_join(tid[0] , NULL);
        pthread_join(tid[1] , NULL);
    }

    cout << "\n\n (B) IDs Of All Threads & Indexes \n" << endl;
    for(int i = 0; i < threadscreated; i++)
    {
        cout << "  Thread : " << i + 1 << " Thread ID : " << allthreadids[i] << endl;
    }
    
    cout << "\n\n\n ................." << endl;
    cout << " | 3) Final Grid |" << endl;
    cout << " .................\n" << endl;
    
    display();

    cout << "\n ..........." << endl;
    cout << " | Results |" << endl;
    cout << " ..........." << endl;
    
    cout << "\n 4) Total Invalid Entries : " << invalidentries << endl;
    cout << "\n 5) Total Threads Created : " << threadscreated << endl;
    
	pthread_exit(NULL);
    return 0;
}