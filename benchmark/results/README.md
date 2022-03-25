# BENCHMARK RESULTS

- To create Json file with results, run:
  
  ```bash
    ./benchmark --benchmark_out=<filename> --benchmark_out_format=json --benchmark_repetitions=20
  ```

- To compare results, run:

    ```bash
        ./compare.py benchmarks /workspaces/CXXGraph/benchmark/results/file1.json /workspaces/CXXGraph/benchmark/results/file2.json
    ```

BFS_X/256_mean                               2376804 ns      2370768 ns           20
BFS_X/16_mean                                  14632 ns        14623 ns           20
BFS_X/1_mean                                    1504 ns         1503 ns           20