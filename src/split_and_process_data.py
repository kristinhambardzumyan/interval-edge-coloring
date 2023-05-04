import os
import time
import subprocess
import ray

ray.init()

@ray.remote
def run_cpp_program(input_file_name, output_file_name1, output_file_name2, output_file_name3, time_limit):
    subprocess.call(['./bin/coloring', input_file_name, output_file_name1, output_file_name2, output_file_name3, time_limit])

def split_input_file(input_file, K):
    with open(input_file, 'r') as f:
        num_lines = sum(1 for line in f)
    
    print(f'Number of input graphs: {num_lines}')

    lines_per_chunk = num_lines // K
    remainder = num_lines % K

    with open(input_file, 'r') as input_file_handle:
        for i in range(K):
            output_file_name = f'input-chunk-{i}.txt'
            with open(output_file_name, 'w') as output_file_handle:
                chunk_size = lines_per_chunk
                if i < remainder:
                    chunk_size += 1
                for j in range(chunk_size):
                    line = input_file_handle.readline()
                    output_file_handle.write(line)
 
def merge_output_files(input_prefix, output_file_name, K):
    with open(output_file_name, 'a') as output_file_handle:
        if 'time-limited' in output_file_name:
            output_file_handle.seek(0)
            output_file_handle.truncate(0)
        for i in range(K):
            input_file_name = f'{input_prefix}-{i}.txt'
            try:
                with open(input_file_name, 'r') as input_file_handle:
                    for line in input_file_handle:
                        output_file_handle.write(line)
            except FileNotFoundError:
                continue

def main(time_limit):
    input_file = 'results/time-limited-5-12-d2.txt'
    K = 60 # number of cores, multiprocessing.cpu_count()
    split_input_file(input_file, K)
    futures = []
    for i in range(K):
        input_file_name = f'input-chunk-{i}.txt'
        output_file_name1 = f'colorables-{i}.txt'
        output_file_name2 = f'non-colorables-{i}.txt'
        output_file_name3 = f'time-limited-{i}.txt'
        future = run_cpp_program.remote(input_file_name, output_file_name1, output_file_name2, output_file_name3, str(time_limit))
        futures.append(future)

    ray.get(futures)

    # Merge the output files into a single output file for each condition(colorable/non/time limited)
    merge_output_files('colorables', 'results/colorables-5-12-d2.txt', K)
    merge_output_files('non-colorables', 'results/non-colorables-5-12-d2.txt', K)
    merge_output_files('time-limited', 'results/time-limited-5-12-d2.txt', K)

    for i in range(K):
        input_file_name = f'input-chunk-{i}.txt'
        output_file_name1 = f'colorables-{i}.txt'
        output_file_name2 = f'non-colorables-{i}.txt'
        output_file_name3 = f'time-limited-{i}.txt'
        try:
            os.remove(input_file_name)
        except FileNotFoundError:
            pass
        try:
           os.remove(output_file_name1)
        except FileNotFoundError:
            pass
        try:
            os.remove(output_file_name2)
        except FileNotFoundError:
            pass
        try:
            os.remove(output_file_name3)
        except FileNotFoundError:
            pass

if __name__ == '__main__':
    total_start_time = time.time()
    time_limit = 100 # in ms
    iteration = 0
    while iteration < 2:
        print(f'Iteration {iteration}')
        start_time = time.time()
        main(time_limit)
        end_time = time.time()
        total_time = end_time - start_time
        print(f'Total time: {total_time} seconds ({total_time/60:.2f} minutes)')
        print()
        iteration += 1
    
    total_end_time = time.time()
    total_time = total_end_time - total_start_time
    print(f'Total time taken: {total_time} seconds ({total_time/60:.2f} minutes)')
