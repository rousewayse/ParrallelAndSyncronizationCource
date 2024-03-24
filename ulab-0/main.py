import subprocess
import os
import pandas as pd
from tqdm import tqdm

def build_source(filename: str, builder: str = 'mpicc', outputdir: str = './out')->bool:
    out_basename = os.path.basename(os.path.abspath(filename))
    out_basename = os.path.splitext(out_basename)[0]
    out_filename = f'{os.path.abspath(outputdir)}/{out_basename}'
    lib_type = detect_lib(filename)
    result = None
    if lib_type == 'mpi':
        result =  subprocess.run(['mpicc', '-lm', '-o',  out_filename, str(filename)], capture_output=True)
    if lib_type == 'omp':
        result = subprocess.run(['gcc', '-lm', '-fopenmp', '-o', out_filename, str(filename)], capture_output=True)
    if result.returncode == 0:
        return out_filename, lib_type
    raise(Exception(f'Building failed for file {filename}'))

def run_executable(*args, timeout=3*60)->str:
    result = subprocess.run(args, capture_output=True, timeout=timeout)
    return result.returncode, result.stdout, result.stderr

def time_command(command):
    returncode, stdout, stderr = run_executable(*['bash', '-c', 'time '+command])
    if returncode != 0:
        return 0.0
    stderr = str(stderr.decode('utf-8')).split('\n')[2:-1]
    time = 0.0
    for i in stderr:
        tmp = ''
        for k in i.replace(',', '.').split('\t')[-1]:
            if k.isdigit() or k == '.':
                tmp += k
            else:
                if   k == 'h':
                    time += float(tmp)*60*60
                elif k == 'm':
                    time += float(tmp)*60
                elif k == 's':
                    time += float(tmp)
                tmp=''
    return time


def avg_time(command, n: int = 3):
    try:
        t = [time_command(command) for i in range(n)]
    except subprocess.TimeoutExpired:
        return "Timed Out"
    return sum(t)/len(t) if sum(t)/len(t) > 0.1**(6) else 'Unrannable'


def detect_lib(filename):
    with open(filename, 'rb') as f:
        status = 'Unknown'
        while True:
            try:
                line = f.readline().decode('utf-8')
            except UnicodeDecodeError:
                continue
            if 'include' in line:
                if 'mpi.h' in line:
                    return 'mpi'
                elif 'omp.h' in line:
                    return 'omp'
            if 'omp' in line.lower() or 'openmp' in line.lower():
                return 'omp'
            if len(line) == 0:
                return 'omp'
        return status

if __name__=='__main__':
    files = sorted([ os.path.join('./examples', i) for i in  os.listdir('./examples')])
    cores = [i+1 for i in range(6)]
    data = {
            'filename': files,
            'lib': []
            }
    for c in cores:
        data[str(c)] = []
    for file in files:
        print('Building ' + os.path.abspath(file))
        execname, lib_type = build_source(os.path.abspath(file))
        print('Detected lib: ' + lib_type)
        print(f'Measuring {execname} ...')
        for c in tqdm(cores):
            t = None
            if lib_type == 'mpi':
                t =  avg_time(f'mpirun --use-hwthread-cpus -N {c} '+str(execname))
            if lib_type == 'omp':
                t = avg_time(f'OMP_NUM_THREADS={c} '+str(execname))
            data[str(c)].append(t)
        data['lib'].append(lib_type)
    frame = pd.DataFrame(data)
    print(frame)
    frame.to_excel('result.xlsx', index=False)

