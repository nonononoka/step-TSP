#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <cmath>
#include "input.h"
#include "output.h"

using namespace std;
double distance(std::pair<double, double> city1, std::pair<double, double> city2)
{
    return std::sqrt((city1.first - city2.first) * (city1.first - city2.first) + (city1.second - city2.second) * (city1.second - city2.second));
}

vector<vector<double>> dist_list_cal(std::vector<std::pair<double, double>> cities)
{
    int N = cities.size();
    vector<vector<double>> dist_list(N, vector<double>(N, 0.0));
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            dist_list[i][j] = distance(cities[i], cities[j]);
            dist_list[j][i] = distance(cities[i], cities[j]);
        }
    }

    return dist_list;
}

vector<int> change_connection_two(vector<int> tour, int i, int j)
{
    vector<int> tmp_dis; // tmp_disはtourのi+1~jmのsub_vectour
    for (int m = i + 1; m < j + 1; m++)
    {
        tmp_dis.push_back(tour[m]);
    }
    reverse(tmp_dis.begin(), tmp_dis.end()); // tmp_disを反転
    for (int m = i + 1; m < j + 1; m++)
    {
        tour[m] = tmp_dis[m - (i + 1)];
    }

    return tour;
}

vector<int> subvector(int i, int j, vector<int> tour) // indexがi~jまでのsubvectorを作る。
{
    vector<int> tmp_dis;
    for (int m = i; m < j + 1; m++)
    {
        tmp_dis.push_back(tour[m]);
    }

    return tmp_dis;
}

pair<vector<int>, double> nearest_insert(int N, vector<vector<double>> dist_list)
{

    int start = 0;
    double short_dist = -1.0;
    map<int, int> short_path;
    for (int i = 0; i < 20; i++) //始点変える。
    {
        map<int, int> path;
        path[i] = i;
        double tmp_dist = 0;
        for (int k = i; k < i + N; k++)
        {
            int cur_vertex = k % N;
            int before_cur_vertex = i;
            int l = i;
            double min_path = dist_list[i][cur_vertex] + dist_list[cur_vertex][path[i]];
            while (true)
            {

                if (dist_list[l][cur_vertex] + dist_list[cur_vertex][path[l]] - dist_list[l][path[l]] < min_path)
                {
                    min_path = dist_list[l][cur_vertex] + dist_list[cur_vertex][path[l]] - dist_list[l][path[l]];
                    before_cur_vertex = l;
                }

                l = path[l];
                if (l == i)
                {
                    break;
                }
            }
            // pathの入れ替え
            path[cur_vertex] = path[before_cur_vertex];
            path[before_cur_vertex] = cur_vertex; // cur_vertexを入れる前の点がbefore_cur_vertex
            tmp_dist += min_path;
        }
        if (tmp_dist < short_dist or short_dist < 0)
        {
            start = i;
            short_dist = tmp_dist;
            short_path = path;
        }
    }
    int now = start;
    vector<int> tour;
    tour.push_back(start);
    while (short_path[now] != start)
    {
        tour.push_back(short_path[now]);
        now = short_path[now];
    }
    pair<vector<int>, double> p(tour, short_dist);
    cout << "nearest_insertで" << p.second << "mの経路が出たよ" << endl;
    return p;
}

pair<vector<int>, double> two_three_opt(vector<int> tour, vector<vector<double>> dist_list, double distance)
{
    double short_dist = -1.0;
    vector<int> short_tour;
    int N = tour.size();
    for (int t = 0; t < 10; t++)
    {
        int count = 0;
        for (int i = 0; i < N - 2; i++)
        {
            for (int j = i + 2; j < N - 2; j++)
            {
                for (int k = j + 2; k < N; k++)
                {
                    int A, B, C, D, E, F;
                    A = tour[i];
                    B = tour[i + 1];
                    C = tour[j];
                    D = tour[j + 1];
                    E = tour[k];
                    F = tour[(k + 1) % N];
                    vector<double> tmp_tour(8);
                    tmp_tour[0] = dist_list[A][B] + dist_list[C][D] + dist_list[E][F]; //現在の繋ぎ方
                    // cout << tmp_tour[0] << endl;
                    // two_opt
                    tmp_tour[1] = dist_list[A][C] + dist_list[B][D] + dist_list[E][F];
                    tmp_tour[2] = dist_list[A][B] + dist_list[C][E] + dist_list[D][F];
                    tmp_tour[3] = dist_list[F][B] + dist_list[C][D] + dist_list[E][A];

                    // three_opt　
                    tmp_tour[4] = dist_list[A][E] + dist_list[D][B] + dist_list[C][F];
                    tmp_tour[5] = dist_list[A][D] + dist_list[E][C] + dist_list[B][F];
                    tmp_tour[6] = dist_list[A][D] + dist_list[E][B] + dist_list[C][F];
                    tmp_tour[7] = dist_list[A][C] + dist_list[E][B] + dist_list[F][D];
                    int min = 0;
                    for (int l = 0; l < 8; l++)
                    {
                        if (tmp_tour[l] < tmp_tour[min])
                        {
                            min = l;
                        }
                    }
                    if (min == 0)
                    {
                        continue;
                    }

                    // 2_optの繋ぎかえ
                    if (min == 1)
                    {
                        tour = change_connection_two(tour, i, j);
                        distance -= (tmp_tour[0] - tmp_tour[1]);
                        count += 1;
                    }
                    else if (min == 2)
                    {
                        tour = change_connection_two(tour, j, k);
                        distance -= (tmp_tour[0] - tmp_tour[2]);
                        count += 1;
                    }
                    else if (min == 3)
                    {
                        tour = change_connection_two(tour, i, k);
                        distance -= (tmp_tour[0] - tmp_tour[3]);
                        count += 1;
                    }

                    // 3_optの繋ぎかえ
                    else if (min == 4)
                    {
                        vector<int> tmp_dis_1, tmp_dis_2;
                        tmp_dis_1 = subvector(j + 1, k, tour);
                        reverse(tmp_dis_1.begin(), tmp_dis_1.end());
                        tmp_dis_2 = subvector(i + 1, j, tour);
                        tmp_dis_1.insert(tmp_dis_1.end(), tmp_dis_2.begin(), tmp_dis_2.end());
                        for (int m = i + 1; m < k + 1; m++)
                        {
                            tour[m] = tmp_dis_1[m - (i + 1)];
                        }
                        distance -= (tmp_tour[0] - tmp_tour[4]);
                        count += 1;
                    }

                    else if (min == 5)
                    {
                        vector<int> tmp_dis_1, tmp_dis_2;
                        tmp_dis_1 = subvector(j + 1, k, tour);
                        tmp_dis_2 = subvector(i + 1, j, tour);
                        reverse(tmp_dis_2.begin(), tmp_dis_2.end());
                        tmp_dis_1.insert(tmp_dis_1.end(), tmp_dis_2.begin(), tmp_dis_2.end());
                        for (int m = i + 1; m < k + 1; m++)
                        {
                            tour[m] = tmp_dis_1[m - (i + 1)];
                        }
                        distance -= (tmp_tour[0] - tmp_tour[5]);
                        count += 1;
                    }
                    else if (min == 6)
                    {
                        vector<int> tmp_dis_1, tmp_dis_2;
                        tmp_dis_1 = subvector(j + 1, k, tour);
                        tmp_dis_2 = subvector(i + 1, j, tour);
                        tmp_dis_1.insert(tmp_dis_1.end(), tmp_dis_2.begin(), tmp_dis_2.end());
                        for (int m = i + 1; m < k + 1; m++)
                        {
                            tour[m] = tmp_dis_1[m - (i + 1)];
                        }
                        distance -= (tmp_tour[0] - tmp_tour[6]);
                        count += 1;
                    }
                    else if (min == 7)
                    {
                        vector<int> tmp_dis_1, tmp_dis_2;
                        tmp_dis_1 = subvector(j + 1, k, tour);
                        reverse(tmp_dis_1.begin(), tmp_dis_1.end());
                        tmp_dis_2 = subvector(i + 1, j, tour);
                        reverse(tmp_dis_2.begin(), tmp_dis_2.end());
                        tmp_dis_1.insert(tmp_dis_1.end(), tmp_dis_2.begin(), tmp_dis_2.end());
                        for (int m = i + 1; m < k + 1; m++)
                        {
                            tour[m] = tmp_dis_1[m - (i + 1)];
                        }
                        distance -= (tmp_tour[0] - tmp_tour[7]);
                        count += 1;
                    }
                }
            }
        }

        if (distance < short_dist || short_dist < 0)
        {
            short_dist = distance;
            short_tour = tour;
        }
    }
    pair<vector<int>, double> p(short_tour, short_dist);
    return p;
}

int main()
{
    int id;
    std::cout << "Please input challenge number:";
    std::cin >> id;

    std::vector<std::pair<double, double>> cities;
    input::read_csv(cities, id);
    std::vector<int> tour;
    int N;
    N = cities.size();
    vector<vector<double>> dist_list(N, vector<double>(N, 0.0));
    // tourに出力
    dist_list = dist_list_cal(cities);
    pair<vector<int>, double> p = nearest_insert(N, dist_list);
    tour = p.first;
    double distance = p.second;
    p = two_three_opt(tour, dist_list, distance);
    tour = p.first;
    cout << p.second << endl;
    output::print_tour(tour, id);
}