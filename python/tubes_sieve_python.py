N = 2_000_000
prima = [True] * (N + 1)

prima[0] = False
prima[1] = False

import math
limit = int(math.sqrt(N))

import time

start_time = time.perf_counter() 
end_time = time.perf_counter()    

duration = (end_time - start_time) * 1_000_000

i = 2
while i <= limit:
    if prima[i] == True:
        j = i * i
        while j <= N:
            prima[j] = False
            j = j + i  
    i = i + 1

count = prima[2:].count(True)

print(f"Batas N: {N}")
print(f"Jumlah bilangan prima: {count}")
print(f"Waktu eksekusi: {duration:.2f} mikrodetik")