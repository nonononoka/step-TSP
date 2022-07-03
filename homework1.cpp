#include <bits/stdc++.h>
#include <time.h>
using namespace std;
//似たようなコードが多い。まとまられたかも。
double i_j_k_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

double i_k_j_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

double j_i_k_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

double j_k_i_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

double k_i_j_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

double k_j_i_matrix(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int N)
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
    return time;
}

int main()
{
    // // N*Nの行列の計算
    string output_ijk_file_path = "ijk_time.txt";
    string output_ikj_file_path = "ikj_time.txt";
    string output_jik_file_path = "jik_time.txt";
    string output_jki_file_path = "jki_time.txt";
    string output_kij_file_path = "kij_time.txt";
    string output_kji_file_path = "kji_time.txt";
    cout << "what size?";
    int N;
    cin >> N;
    vector<double> i_j_k_time(N);
    vector<double> i_k_j_time(N);
    vector<double> j_i_k_time(N);
    vector<double> j_k_i_time(N);
    vector<double> k_i_j_time(N);
    vector<double> k_j_i_time(N);
    // 1*1~N*Nの正方行列同士の行列積を計算
    for (int i = 1; i < N + 1; i++)
    {
        vector<vector<int>> matrix1(i, vector<int>(i, 0));
        vector<vector<int>> matrix2(i, vector<int>(i, 0));
        i_j_k_time[i - 1] = i_j_k_matrix(matrix1, matrix2, i);
        i_k_j_time[i - 1] = i_k_j_matrix(matrix1, matrix2, i);
        j_i_k_time[i - 1] = j_i_k_matrix(matrix1, matrix2, i);
        j_k_i_time[i - 1] = j_k_i_matrix(matrix1, matrix2, i);
        k_i_j_time[i - 1] = k_i_j_matrix(matrix1, matrix2, i);
        k_j_i_time[i - 1] = k_j_i_matrix(matrix1, matrix2, i);
    }
    std::ofstream output_ijk_data;
    output_ijk_data.open(output_ijk_file_path);
    for (int i = 0; i < N; i++)
    {
        output_ijk_data << i_j_k_time[i] << endl;
    }
    std::ofstream output_ikj_data;
    output_ikj_data.open(output_ikj_file_path);
    for (int i = 0; i < N; i++)
    {
        output_ikj_data << i_k_j_time[i] << endl;
    }
    std::ofstream output_jik_data;
    output_jik_data.open(output_jik_file_path);
    for (int i = 0; i < N; i++)
    {
        output_jik_data << i_k_j_time[i] << endl;
    }
    std::ofstream output_jki_data;
    output_jki_data.open(output_jki_file_path);
    for (int i = 0; i < N; i++)
    {
        output_jki_data << j_k_i_time[i] << endl;
    }
    std::ofstream output_kij_data;
    output_kij_data.open(output_kij_file_path);
    for (int i = 0; i < N; i++)
    {
        output_kij_data << j_k_i_time[i] << endl;
    }
    std::ofstream output_kji_data;
    output_kji_data.open(output_kji_file_path);
    for (int i = 0; i < N; i++)
    {
        output_kji_data << k_j_i_time[i] << endl;
    }
}

//各indexについて、[0,1,3.5,・・・]みたいに実行時間が並んでいるイメージ