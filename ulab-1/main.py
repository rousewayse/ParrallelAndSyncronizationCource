import subprocess
import os
import pandas as pd
import sys
from tqdm import tqdm 
from matplotlib import pyplot as plt

def run_executable(*args, timeout=10*60)->str:
    result = subprocess.run(args, capture_output=True, timeout=timeout)
    return result.returncode, result.stdout, result.stderr

def time_command(command):
    returncode, stdout, stderr = run_executable(*['bash', '-c', 'time '+command])
    if returncode != 0:
        return 0.0
    stderr = str(stderr.decode('utf-8')).split('\n')[1]
    time = 0.0
    tmp = ''
    for k in stderr.replace(',', '.').split('\t')[-1]:
        if k.isdigit() or k == '.':
            tmp += k
        else:
            if   k == 'h':
                time += float(tmp)*60*60
            elif k == 'm':
                time += float(tmp)*60
            elif k == 's':
                time += float(tmp)
    return time


def avg_time(command, n: int = 5):
    try:
        t = [time_command(command) for i in range(n)]
    except subprocess.TimeoutExpired:
        return "Timed Out"
    return sum(t)/len(t) if sum(t)/len(t) > 0.1**(6) else 'Unrannable'

if __name__=='__main__':
    execname = sys.argv[1]    

    cores = [i+1 for i in range(6)]
    data_len = [10**(i+1) for i in range(8)]
    data = {
            'data len': data_len,
            }
    plt.figure(figsize=(10, 5))
    plt.xticks([i+1 for i,_ in enumerate(data_len)])
    plt.ylabel('time');
    plt.xlabel('data size');
    for c in cores:
        print(f'Testing with {c} cores')
        data[c] = [ avg_time(f'mpirun --use-hwthread-cpus -N {c} ' + str(execname)+ f' {d}') for d in tqdm(data_len)]
        plt.plot([i for i in range(len(data[c]))], data[c] , label=f'cores {c}', marker='o')
    plt.legend()
    plt.savefig(execname+'.png', bbox_inches='tight')
    #plt.show()
    frame = pd.DataFrame(data)
    print(frame)
    frame.to_markdown(execname+'.md', index=False)
   
