#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// allocate one more row & column
bool dp[1001][1001];

bool merge(const string &A, const string &B, const string &C);

int main()
{
    string inputFile, outputFile;
    string A, B, C;

    cout << "Enter the name of input file" << endl;
    cin >> inputFile;
    cout << "Enter the name of output file" << endl;
    cin >> outputFile;

    ifstream inFile;
    ofstream outFile;

    inFile.open(inputFile);
    outFile.open(outputFile);
    while (inFile >> A && inFile >> B && inFile >> C)
    {
        if (merge(A, B, C))
        {
            int j = B.length();
            for (int i = A.length(); i > 0; i--)
            {
                while (true)
                {
                    if (dp[i][j] && (j == 0 || !dp[i][j - 1]))
                    {
                        C.at(i + j - 1) = toupper(C.at(i + j - 1));
                        break;
                    }
                    j--;
                }
            }
            outFile << C << endl;
        }
        else
            outFile << "*** NOT A MERGE ***" << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}

bool merge(const string &A, const string &B, const string &C)
{
    int M = A.length();
    int N = B.length();

    memset(dp, false, sizeof(dp));

    if ((M + N) != C.length())
        return false;

    for (int i = 0; i <= M; ++i)
    {
        for (int j = 0; j <= N; ++j)
        {
            if (i == 0 && j == 0)
                dp[i][j] = true;
            else if (i == 0)
            {
                if (B[j - 1] == C[j - 1])
                    dp[i][j] = dp[i][j - 1];
            }
            else if (j == 0)
            {
                if (A[i - 1] == C[i - 1])
                    dp[i][j] = dp[i - 1][j];
            }
            else if (A[i - 1] == C[i + j - 1] && B[j - 1] != C[i + j - 1])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else if (A[i - 1] != C[i + j - 1] && B[j - 1] == C[i + j - 1])
            {
                dp[i][j] = dp[i][j - 1];
            }
            else if (A[i - 1] == C[i + j - 1] && B[j - 1] == C[i + j - 1])
            {
                dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
            }
        }
    }

    return dp[M][N];
}
