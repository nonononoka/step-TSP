#!/usr/bin/env python3
import sys
import math

from common import print_tour, read_input,format_tour, read_input


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
