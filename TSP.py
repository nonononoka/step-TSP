#!/usr/bin/env python3
import sys
import math

from common import print_tour, read_input,format_tour, read_input

def two_three_opt(tour, dist_list,distance):
    N = len(tour)

    while True:
        count = 0
        for i in range(N - 2):
            # print(i)
            for j in range(i + 2, N - 2):
                for k in range(j + 2, N):
                    
                    
                    A, B, C, D, E, F = tour[i], tour[i + 1], tour[j], tour[j + 1], tour[k], tour[(k + 1) % N]
                    d=[0]*8
                    d[0] = dist_list[A][B] + dist_list[C][D] + dist_list[E][F]
                    # d[0]が現在の繋ぎ方の場合の距離
                    
                    #two_opt
                    d[1] = dist_list[A][C] + dist_list[B][D] + dist_list[E][F] 
                    d[2] = dist_list[A][B] + dist_list[C][E] + dist_list[D][F] 
                    d[3] = dist_list[F][B] + dist_list[C][D] + dist_list[E][A] 
                    
                    #three_opt　
                    d[4] = dist_list[A][E] + dist_list[D][B] + dist_list[C][F]
                    d[5] = dist_list[A][D] + dist_list[E][C] + dist_list[B][F]
                    d[6] = dist_list[A][D] + dist_list[E][B] + dist_list[C][F] 
                    d[7] = dist_list[A][C] + dist_list[E][B] + dist_list[F][D]
                    min=0
                    for l in range(8):
                        if d[l]<d[min]:
                            min=l
                    # print(i,j,k,min)
                    if min==0:
                        continue
                    
                    #2_optの場合の繋ぎかえ
                    if min==1: #新しい繋ぎ方の方が短い場合、tour[i + 1]からtour[j]までを逆順にする
                        tour[i + 1 : j + 1] = reversed(tour[i + 1 : j + 1])
                        distance -= d[0]-d[1]
                        count += 1
                    elif min==2:
                        tour[j + 1 : k + 1] = reversed(tour[j + 1 : k + 1])
                        distance -= d[0]-d[2]
                        count += 1
                    elif min==3:    
                        tour[i + 1 : k + 1] = reversed(tour[i + 1 : k + 1])
                        distance -= d[0]-d[3]
                        count += 1
                    
                    #3_optの場合の繋ぎかえ
                    elif min==4:
                        tmp = list(reversed(tour[ j + 1 : k + 1])) + tour[i + 1 : j + 1]
                        tour[i + 1 : k + 1] = tmp
                        distance -= d[0]-d[4]
                        count += 1
                        
                    
                    elif min==5:
                        tmp = tour[j + 1 : k + 1] + list(reversed(tour[i + 1 : j + 1]))
                        tour[i + 1 : k + 1] = tmp
                        distance -= d[0]-d[5]
                        count += 1
                    
                    elif min==6:
                        tmp = tour[j + 1 : k + 1] + tour[i + 1 : j + 1]
                        tour[i + 1 : k + 1] = tmp
                        distance -= d[0]-d[6]
                        count += 1
                        
                    elif min==7:
                        tmp = list(reversed(tour[j + 1 : k + 1])) + list(reversed(tour[i + 1 : j + 1]))
                        tour[i + 1 : k + 1] = tmp
                        distance -= d[0]-d[6]
                        count += 1

        if count == 0:
            #これ以上距離が短くならなかったら
            break

    return tour


def distance(city1, city2):
    return math.sqrt((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2)


def solve(cities):
    N = len(cities)

    dist = [[0] * N for i in range(N)]
    for i in range(N):
        for j in range(i, N):
            dist[i][j] = dist[j][i] = distance(cities[i], cities[j]) #どこも経由しない場合(直接i→jに行く)場合の経路長
    

    path_list=[] #iからstartした時の経路を保存
    ans=[0.0]*N #iからstartした時の経路長を保存
    for i in range(N): 
        #iからstartする場合
        path={}
        path[i]=i #次に進む点を保存しておく辞書。path[1]=2だったら、1→2の順番で進む。
        for k in range(i,i+N): #iからiに戻るまでに経由する点をi,i+1,i+2・・の順に増やしていく。 
            k=k%N
            point=i #kを入れる前の点がpoint
            l=i
            min_path=dist[i][k]+dist[k][path[i]]
            while not path[l]==i: #再びiに辿り着くまで、kを次に入れて最小の経路になるようなpointを探す。
                if dist[l][k]+dist[k][path[l]]-dist[l][path[l]]<min_path:
                    min_path=dist[l][k]+dist[k][path[l]]-dist[l][path[l]]
                    point=l
                l=path[l] 
            
            #iの前の点について調べる。
            if dist[l][k]+dist[k][path[l]]-dist[l][path[l]]<min_path:
                min_path=dist[l][k]+dist[k][path[l]]-dist[l][path[l]]
                point=l
            #k→point→path[k]の順番になるように、pathのvalueを入れ替える。
            path[k]=path[point] 
            path[point]=k 
            
            ans[i]=ans[i]+min_path
        path_list.append(path)
    
    
    start=ans.index(min(ans)) #ansの最小値探す。
    tmp_path=path_list[start] #長さが最小となるような経路の辞書
    
    now=start
    ans_list=[start]
    while not tmp_path[now]==start: #ans_listに経路を追加していく。
        ans_list.append(tmp_path[now])
        now=tmp_path[now]
    
    ans_list=two_three_opt(ans_list,dist,min(ans))
    #ここから最適化していく。
    
    return ans_list
    


if __name__ == '__main__':
    assert len(sys.argv) > 1
    tour = solve(read_input(sys.argv[1]))
    print_tour(tour)
    
    

#各変数の型
# dist:二次元配列 どこも経由しない場合(直接i→jに行く)場合の経路長を保存
# path_list:リスト iからstartした時の経路を保存する。リストの中身は辞書
# ans:リスト iからstartした時の経路長を保存
# path:辞書 1:2,2:3,3:4・・・のようにvalueがkeyの次の点になっている。
# min_path:float i→k→jの経路長-i→jの経路長
# point:float kを次に入れる点
