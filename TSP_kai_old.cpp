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

    vector<map<int, int>> path_list(10);
    vector<double> ans(10, 0.0);
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
        map<int, int> path;
        path[i] = i;
        for (int k = i; k < i + N; k++)
        {
            // cout << i << " " << k << " " << endl;
            int tmp_k = k % N;
            int point = i;
            int l = i;
            double min_path = dist_list[i][tmp_k] + dist_list[tmp_k][path[i]];
            // cout << min_path << endl;
            while (path[l] != i)
            {
                if (dist_list[l][tmp_k] + dist_list[tmp_k][path[l]] - dist_list[l][path[l]] < min_path)
                {
                    min_path = dist_list[l][tmp_k] + dist_list[tmp_k][path[l]] - dist_list[l][path[l]];
                    point = l;
                }

                l = path[l];
            }
            if (dist_list[l][tmp_k] + dist_list[tmp_k][path[l]] - dist_list[l][path[l]] < min_path)
            {
                min_path = dist_list[l][tmp_k] + dist_list[tmp_k][path[l]] - dist_list[l][path[l]];
                point = l;
            }
            path[tmp_k] = path[point];
            path[point] = tmp_k; // kを入れる前の点がpoint
            ans[i] = ans[i] + min_path;
        }
        path_list[i] = path;
    }
    auto shortest_dist = min_element(ans.begin(), ans.end());
    // cout << shortest_dist << endl;
    int start = std::distance(ans.begin(), shortest_dist);
    map<int, int> tmp_path = path_list[start];
    int now = start;
    vector<int> tour;
    tour.push_back(start);
    while (tmp_path[now] != start)
    {
        tour.push_back(tmp_path[now]);
        now = tmp_path[now];
    }
    pair<vector<int>, double> p(tour, ans[start]);
    cout << p.second << endl;
    return p;
}

pair<vector<int>, double> two_three_opt(vector<int> tour, vector<vector<double>> dist_list, double distance)
{
    int N = tour.size();
    vector<double> tmp_distance_list(6);
    vector<vector<int>> tmp_tour_list(6, vector<int>(N, 0));
    tmp_distance_list[0] = distance;
    tmp_tour_list[0] = tour;
    for (int t = 0; t < 5; t++) // 5回最適化を行う。
    {
        int count = 0;
        for (int i = 0; i < N - 2; i++)
        {
            cout << i << endl;
            for (int j = i + 2; j < N - 2; j++)
            {
                for (int k = j + 2; k < N; k++)
                {
                    // cout << i << endl;
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
                    // cout << i << " " << count << endl;
                }
            }
        }
        tmp_distance_list[t + 1] = distance;
        tmp_tour_list[t + 1] = tour;
        // if (count == 0 || distance < first_dist)
        // {
        //     break;
        // }
    }
    auto shortest_dist = min_element(tmp_distance_list.begin(), tmp_distance_list.end());
    // cout << shortest_dist << endl;
    int start = std::distance(tmp_distance_list.begin(), shortest_dist);
    pair<vector<int>, double> p(tmp_tour_list[start], tmp_distance_list[start]);
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

    return 0;
}