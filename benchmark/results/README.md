# BENCHMARK RESULTS

- To create Json file with results, run:
  
  ```bash
    ./benchmark --benchmark_out=<filename> --benchmark_out_format=json --benchmark_repetitions=20
  ```

- To compare results, run:

    ```bash
        ./compare.py benchmarks /workspaces/CXXGraph/benchmark/results/file1.json /workspaces/CXXGraph/benchmark/results/file2.json
    ```
