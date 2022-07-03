#include <bits/stdc++.h>
#include <time.h>
using namespace std;
int i_j_k_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "i-j-k"
         << " " << time << endl;
    return 0;
}

int i_k_j_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int j = 0; j < N; j++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "i-k-j"
         << " " << time << endl;
    return 0;
}

int j_i_k_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < N; k++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "j-i-k"
         << " " << time << endl;
    return 0;
}

int j_k_i_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int i = 0; i < N; i++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "j-k-i"
         << " " << time << endl;
    return 0;
}

int k_i_j_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "k-i-j"
         << " " << time << endl;
    return 0;
}

int k_j_i_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
{
    vector<vector<int>> ans(N, vector<int>(N, 0));
    clock_t start = clock();
    for (int k = 0; k < N; k++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                ans.at(i).at(j) = matrix1.at(i).at(k) * matrix2.at(k).at(j);
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "k-j-i"
         << " " << time << endl;
    return 0;
}

int main()
{
    // // N*Nの行列の計算
    cout << "what size?";
    int N;
    cin >> N;
    vector<vector<int>> matrix1(N, vector<int>(N, 0));
    vector<vector<int>> matrix2(N, vector<int>(N, 0));

    i_j_k_matrix(matrix1, matrix2, N);
    i_k_j_matrix(matrix1, matrix2, N);
    j_i_k_matrix(matrix1, matrix2, N);
    j_k_i_matrix(matrix1, matrix2, N);
    k_i_j_matrix(matrix1, matrix2, N);
    k_j_i_matrix(matrix1, matrix2, N);
}
