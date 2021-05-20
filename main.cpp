#include <iostream>
#include <vector>

using namespace std;

void clacNeed(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<vector<int>> &max, int n, int m);
void calculateSafeSequence(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<int> &available, int n, int m, int processIndex, int isRequest);
void request(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<int> &available,vector<int> &requestList, int processIndex, int n, int m);

int main()
{    
    int n, m;
    int requestNumbers;
    int processIndex;

    cout << "Entre the number of processes:\n";
    cin >> n;
    cout << "Enter the number of resources:\n";
    cin >> m;

    vector<vector<int>> need(n);
    vector<vector<int>> max(n);
    vector<vector<int>> allocation(n);
    vector<int> available(m);
    vector<int> requestList(m);


    for(int i = 0; i < n; i++)
    {
        need[i] = vector<int>(m);
        max[i] = vector<int>(m);
        allocation[i] = vector<int>(m);
    }

    cout << "Fill the allocation array:\n";
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            cin >> allocation[i][j];
        }   
    }

    cout << "Fill the MAX array:\n";
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < max[i].size(); j++)
            cin >> max[i][j];
           
    }

    cout << "Fill the available array:\n";

    for(int i = 0; i < m; i++)
        cin >> available[i];

    clacNeed(need, allocation, max, n, m);

    char input;
    cout << "Choose one of the following algorithms:\n";
    cout << "a - The safety algorithm\n";
    cout << "b - The request algorithm\n";

    cin >> input;


    if(input == 'a')
    {
        calculateSafeSequence(need, allocation, available, n, m, 0, 0);
    }
    else if(input == 'b')
    {
        cout << "Enter value of x in Px:\n";
        cin >> processIndex;
        cout << "Enter request vector:\n";
        for (int i = 0; i < m; i++)
        {
            cin >> requestList[i];
        }
        request(need, allocation, available, requestList, processIndex, n, m);
    }

    cout << "The Need matrix :\n";
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

void clacNeed(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<vector<int>> &max, int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void calculateSafeSequence(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<int> &available, int n, int m, int processIndex, int isRequest)
{  
    vector<int> finish(n, 0);
    vector<int> safe(n, 0);
    int count = 0;

    while (count < n)
    {
        int flag = 0;
            for (int i = 0; i < n; i++) 
            {

                if (finish[i] == 0) 
                {
    
                    int j;
                    for (j = 0; j < m; j++) 
                    {
                        if (need[i][j] > available[j])
                        {
                            break;
                        }
                    }
                    if (j == m)
                    {
                        safe[count++] = i;
                        finish[i] = true;
                        flag = true;
                        for (j = 0; j < m; j++)
                        {
                            available[j] = available[j] + allocation[i][j];
                        }
                    }
                }
            }

            if (flag == false)
            {
                break;
            }
        }
        
        if (count < n)
        {
            std::cout << "The System is UnSafe!\n";
        }
        else
        {
            std::cout << "Yes, Safe state <";
            if(isRequest)
            {
                std::cout << "P" << char(processIndex + '0') << "req,";
                
            }
            for (int i = 0; i < n; i++)
            {
                std::cout << "P" << safe[i];
                if (i != n - 1)
                    std::cout << ",";
            }
            std::cout << ">\n";
        }
}

void request(vector<vector<int>> &need, vector<vector<int>> &allocation, vector<int> &available,vector<int> &requestList, int processIndex, int n, int m)
{
    int j = 0;
    int isRequest = 1;
    for(j = 0; j < m; j++)
    {
        if(requestList[j] > need[processIndex][j] || requestList[j] > available[j])
        {
            std::cout << "Request can't be granted for process " << processIndex << endl;
            return ;
        }
    }
    if(j == m)
    {
        for(int k = 0; k < m; k++)
        { 
            available[k] -= requestList[k];
            allocation[processIndex][k] += requestList[k];
            need[processIndex][k] -= requestList[k];
        }  

        std:: cout << "Yes request can be granted. ";

        calculateSafeSequence(need, allocation, available, n, m, processIndex, isRequest);
    }
}
