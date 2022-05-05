import subprocess

benchCount = 100
sum = 0.0
for j in range(benchCount):
    with open("inp", "w") as f:
        p = subprocess.Popen(["./bitap"], stdout=f)
        p.wait()
        f.flush()
    with open("inp", "r") as f:
        temp = float(f.read())
        print(temp)
        sum += temp

print("Average: ", sum / benchCount)
