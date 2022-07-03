from matplotlib import pyplot


x=[]

with open ("ijk_time.txt") as f:
    ijk_time=f.readlines()
N=len(ijk_time)

for i in range(1,N+1):
    x.append(i)

with open ("ikj_time.txt") as f:
    ikj_time=f.readlines()

with open ("jik_time.txt") as f:
    jik_time=f.readlines()
    

with open ("jki_time.txt") as f:
    jki_time=f.readlines()
    

with open ("kij_time.txt") as f:
    kij_time=f.readlines()

with open ("kji_time.txt") as f:
    kji_time=f.readlines()


pyplot.plot(x, ijk_time,color="coral",label="ijk")
pyplot.plot(x, ikj_time,color="red",label="ikj")
pyplot.plot(x, jik_time,color="black",label="jik")
pyplot.plot(x, jki_time,color="gray",label="iki")
pyplot.plot(x, kij_time,color="yellow",label="kij")
pyplot.plot(x, kji_time,color="pink",label="kji")
pyplot.legend()
pyplot.yscale("log")


pyplot.xlabel("size")
pyplot.ylabel("time/seconds")
pyplot.show()