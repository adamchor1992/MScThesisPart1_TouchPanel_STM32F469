import math

x = list(range(0,360,1))
y = []

print(x)

for i in x:
    y.append(round(math.sin(math.radians(i)),3))

for i in y:
    if (i < 0):
        i = i * (-1)
    print(i)
    print("")
