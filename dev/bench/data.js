window.BENCHMARK_DATA = {
  "lastUpdate": 1631179992903,
  "repoUrl": "https://github.com/ZigRazor/CXXGraph",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "96020a672437ba8dd47e3344230fcb9e108b002a",
          "message": "Adjustment for new version of Google Benchmark",
          "timestamp": "2021-08-26T08:23:53Z",
          "tree_id": "3eb14f98916c59ba6927c70e5962b66cb4a449ea",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/96020a672437ba8dd47e3344230fcb9e108b002a"
        },
        "date": 1629966773617,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 18.232418208727314,
            "unit": "ns/iter",
            "extra": "iterations: 37870544\ncpu: 18.221958707537972 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.999999998009599e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 18.803171927589286,
            "unit": "ns/iter",
            "extra": "iterations: 36778204\ncpu: 18.803141855431544 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 7.00000043707405e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.8603168464310387,
            "unit": "ns/iter",
            "extra": "iterations: 175069859\ncpu: 3.8600586352217245 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 6.555222578135989,
            "unit": "ns/iter",
            "extra": "iterations: 102950925\ncpu: 6.554815520113102 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 323.8154141644177,
            "unit": "ns/iter",
            "extra": "iterations: 2231493\ncpu: 323.8082409400342 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 83529.0602534547,
            "unit": "ns/iter",
            "extra": "iterations: 8680\ncpu: 83521.17972350231 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 31043337.63157959,
            "unit": "ns/iter",
            "extra": "iterations: 19\ncpu: 31042421.631578915 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 8917150638.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8916608486 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.99999999298484e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 22.859035859414117,
            "unit": "ns/iter",
            "extra": "iterations: 31814240\ncpu: 22.85867117994964 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 30.98950535503314,
            "unit": "ns/iter",
            "extra": "iterations: 22699291\ncpu: 30.98706030069396 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 550.5255425400443,
            "unit": "ns/iter",
            "extra": "iterations: 1252949\ncpu: 550.5097366293426 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 79797.11049660493,
            "unit": "ns/iter",
            "extra": "iterations: 8679\ncpu: 79789.5974190571 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 34373689.95833386,
            "unit": "ns/iter",
            "extra": "iterations: 24\ncpu: 34372318.87500003 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 10098511976.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10097802421 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 527.418924692035,
            "unit": "ns/iter",
            "extra": "iterations: 1264010\ncpu: 527.3853047048664 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 519.6355981048481,
            "unit": "ns/iter",
            "extra": "iterations: 709608\ncpu: 1032.7711539328754 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 310.9025399036513,
            "unit": "ns/iter",
            "extra": "iterations: 1204652\ncpu: 671.9634616470141 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 83762.42327149837,
            "unit": "ns/iter",
            "extra": "iterations: 8302\ncpu: 83761.00168634123 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 61791.536131472065,
            "unit": "ns/iter",
            "extra": "iterations: 8732\ncpu: 97205.19594594617 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 26168.913595980375,
            "unit": "ns/iter",
            "extra": "iterations: 13732\ncpu: 45998.2703903293 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 33819843.750001155,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 33814363.54999998 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 26837059.916665852,
            "unit": "ns/iter",
            "extra": "iterations: 24\ncpu: 42241510.70833335 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 11953205.325000126,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 20101197.774999954 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 9348586841.999975,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 9347591834.000006 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 5032047341.249992,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 5533734217.499997 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 2259354457.4374995,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2917497764.5000005 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.680093899159234,
            "unit": "ns/iter",
            "extra": "iterations: 261606602\ncpu: 2.6799077494229513 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 5.461005457739021,
            "unit": "ns/iter",
            "extra": "iterations: 129000668\ncpu: 5.460850388774741 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 105.39432103705889,
            "unit": "ns/iter",
            "extra": "iterations: 6741583\ncpu: 105.38728886079123 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 2218.183673018628,
            "unit": "ns/iter",
            "extra": "iterations: 316911\ncpu: 2218.065639879973 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 49514.67215926081,
            "unit": "ns/iter",
            "extra": "iterations: 13412\ncpu: 49511.346480763204 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 816013.1009420619,
            "unit": "ns/iter",
            "extra": "iterations: 743\ncpu: 815942.4414535656 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 23.66553276574403,
            "unit": "ns/iter",
            "extra": "iterations: 29081318\ncpu: 23.66504788400589 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 28.322199205452076,
            "unit": "ns/iter",
            "extra": "iterations: 25786513\ncpu: 28.320019732796027 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 409.4867765524008,
            "unit": "ns/iter",
            "extra": "iterations: 1665791\ncpu: 409.4781308099332 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 6884.421678604014,
            "unit": "ns/iter",
            "extra": "iterations: 106529\ncpu: 6883.999230256513 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 114992.16976556313,
            "unit": "ns/iter",
            "extra": "iterations: 6185\ncpu: 114989.5825383991 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1954365.337110401,
            "unit": "ns/iter",
            "extra": "iterations: 353\ncpu: 1954220.5779036614 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 392.58442425688287,
            "unit": "ns/iter",
            "extra": "iterations: 1837434\ncpu: 392.571690738272 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 518.0499468266956,
            "unit": "ns/iter",
            "extra": "iterations: 1427408\ncpu: 1030.4909402217222 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 256.27437872241205,
            "unit": "ns/iter",
            "extra": "iterations: 1430520\ncpu: 514.4632706987787 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 6708.2604755324555,
            "unit": "ns/iter",
            "extra": "iterations: 104935\ncpu: 6707.653442607498 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 8070.413576374797,
            "unit": "ns/iter",
            "extra": "iterations: 43038\ncpu: 15987.552418792453 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3869.588121919635,
            "unit": "ns/iter",
            "extra": "iterations: 85220\ncpu: 7769.253320816717 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 109927.35685484207,
            "unit": "ns/iter",
            "extra": "iterations: 5952\ncpu: 109919.37684811736 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 175222.3207295633,
            "unit": "ns/iter",
            "extra": "iterations: 2248\ncpu: 330820.4559608583 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 72825.93562835133,
            "unit": "ns/iter",
            "extra": "iterations: 3740\ncpu: 141888.07433155496 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1908650.4748009667,
            "unit": "ns/iter",
            "extra": "iterations: 377\ncpu: 1908429.2307691786 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2902183818.2500234,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 3204544685.5 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 494920610.9375126,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 594620597.2500023 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "8b6e56b6ceb5a177ce7298edcca36d03e440c937",
          "message": "Fix #48 :\nNot removed non compressed files when compression is flagged.",
          "timestamp": "2021-08-27T07:07:44Z",
          "tree_id": "5a4fe87d232fdc5b335f1b73fb3ac8bbeefe1cae",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/8b6e56b6ceb5a177ce7298edcca36d03e440c937"
        },
        "date": 1630048592471,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999923734e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 16.57386721351075,
            "unit": "ns/iter",
            "extra": "iterations: 41381695\ncpu: 16.57217298614762 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 7.010000047102949e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 16.710718207534217,
            "unit": "ns/iter",
            "extra": "iterations: 41637923\ncpu: 16.710175865400398 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 5.999999928008037e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 5.999999928008037e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000001282757e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 5.999999928008037e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000001282757e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.9801527772421887,
            "unit": "ns/iter",
            "extra": "iterations: 177628681\ncpu: 3.980076719704969 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 6.689333713087733,
            "unit": "ns/iter",
            "extra": "iterations: 110302902\ncpu: 6.689020847339081 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 286.7342709104301,
            "unit": "ns/iter",
            "extra": "iterations: 2479085\ncpu: 286.71416187827344 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 77574.78101554932,
            "unit": "ns/iter",
            "extra": "iterations: 9197\ncpu: 77571.7877568772 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 23892199.826087292,
            "unit": "ns/iter",
            "extra": "iterations: 23\ncpu: 23889841.78260871 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 11463560030.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 11458460686 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000022434506e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 23.443131942920203,
            "unit": "ns/iter",
            "extra": "iterations: 29890251\ncpu: 23.44173248996799 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 25.7247170557489,
            "unit": "ns/iter",
            "extra": "iterations: 27076712\ncpu: 25.72381532144679 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 530.0159362977656,
            "unit": "ns/iter",
            "extra": "iterations: 1303816\ncpu: 529.9897516213946 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 84526.23615160327,
            "unit": "ns/iter",
            "extra": "iterations: 7889\ncpu: 84523.34643174066 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 27227105.838709384,
            "unit": "ns/iter",
            "extra": "iterations: 31\ncpu: 27225286.38709676 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 12026838532,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 12026093080.000002 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 506.8598273526976,
            "unit": "ns/iter",
            "extra": "iterations: 1323739\ncpu: 506.8383676842603 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 664.5655855830454,
            "unit": "ns/iter",
            "extra": "iterations: 555122\ncpu: 1323.7488840290894 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 319.9626773911425,
            "unit": "ns/iter",
            "extra": "iterations: 954388\ncpu: 682.7905935531426 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 85704.669762893,
            "unit": "ns/iter",
            "extra": "iterations: 8182\ncpu: 85684.61329748205 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 63068.39504891954,
            "unit": "ns/iter",
            "extra": "iterations: 6746\ncpu: 100942.19759857665 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 34226.3202923753,
            "unit": "ns/iter",
            "extra": "iterations: 15528\ncpu: 64442.68553580627 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 27585649.708332956,
            "unit": "ns/iter",
            "extra": "iterations: 24\ncpu: 27580848.666666508 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 20521042.16666706,
            "unit": "ns/iter",
            "extra": "iterations: 24\ncpu: 34712523.87499994 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 10021507.17500001,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 18082180.92499997 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 11453789772.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 11448061109.000002 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 4287597490.7500024,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 5066030989.000003 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 1976696610.8124998,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2584730358.249999 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.581804058298676,
            "unit": "ns/iter",
            "extra": "iterations: 262417207\ncpu: 2.5817180197333522 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 5.208758850665433,
            "unit": "ns/iter",
            "extra": "iterations: 129843908\ncpu: 5.208222599091829 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 93.43490260246757,
            "unit": "ns/iter",
            "extra": "iterations: 7183344\ncpu: 93.43200325642283 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 2060.3600909698093,
            "unit": "ns/iter",
            "extra": "iterations: 350006\ncpu: 2060.1003268515365 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 35173.79549718606,
            "unit": "ns/iter",
            "extra": "iterations: 20787\ncpu: 35074.80930389205 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 926546.2294429615,
            "unit": "ns/iter",
            "extra": "iterations: 754\ncpu: 926482.1273209709 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 22.059599136511565,
            "unit": "ns/iter",
            "extra": "iterations: 32146355\ncpu: 22.05751659869339 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 24.782386232596856,
            "unit": "ns/iter",
            "extra": "iterations: 29731561\ncpu: 24.78145079567132 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 368.1993123512553,
            "unit": "ns/iter",
            "extra": "iterations: 1919003\ncpu: 368.1806198322783 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5916.589002810752,
            "unit": "ns/iter",
            "extra": "iterations: 122013\ncpu: 5916.504003671767 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 95626.08542647962,
            "unit": "ns/iter",
            "extra": "iterations: 7644\ncpu: 95588.19911041489 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1791000.9625669478,
            "unit": "ns/iter",
            "extra": "iterations: 374\ncpu: 1790961.7540106697 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 381.77382353963014,
            "unit": "ns/iter",
            "extra": "iterations: 1838056\ncpu: 381.75697693650665 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 541.4199781110563,
            "unit": "ns/iter",
            "extra": "iterations: 628628\ncpu: 1081.640270557475 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 274.7051026708863,
            "unit": "ns/iter",
            "extra": "iterations: 1321504\ncpu: 549.4782641596153 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5898.598674999635,
            "unit": "ns/iter",
            "extra": "iterations: 109283\ncpu: 5898.334919429518 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 8946.51639849956,
            "unit": "ns/iter",
            "extra": "iterations: 38906\ncpu: 17868.835835089198 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 4431.859025401246,
            "unit": "ns/iter",
            "extra": "iterations: 75980\ncpu: 8934.252540141795 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 100314.19901756327,
            "unit": "ns/iter",
            "extra": "iterations: 6718\ncpu: 100314.14379279841 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 275092.6809045295,
            "unit": "ns/iter",
            "extra": "iterations: 1194\ncpu: 517204.2445560994 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 82586.28570579684,
            "unit": "ns/iter",
            "extra": "iterations: 4208\ncpu: 158789.88688213256 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1869635.5277045295,
            "unit": "ns/iter",
            "extra": "iterations: 379\ncpu: 1869588.158311323 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 3378731201.49996,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 3579198367.000011 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 984882508.6249917,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 1093401013.4999971 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "69262e68af323de06ddd9c30c55efa3d39a9defa",
          "message": "Documentation update for WriteToFile Function",
          "timestamp": "2021-08-27T07:15:12Z",
          "tree_id": "218becde68bf9e35e7492543b8e9dded8c45a341",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/69262e68af323de06ddd9c30c55efa3d39a9defa"
        },
        "date": 1630049083795,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.99999999995249e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 18.571156635768396,
            "unit": "ns/iter",
            "extra": "iterations: 37842985\ncpu: 18.569150108005484 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 8.000000661922968e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 19.106929071780577,
            "unit": "ns/iter",
            "extra": "iterations: 36626522\ncpu: 19.104969098622032 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 9.000000318337698e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.999999998593466e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 9.000000318337698e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 9.000000003034359e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 4.5001693120733695,
            "unit": "ns/iter",
            "extra": "iterations: 152372477\ncpu: 4.4997766821103795 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 7.087772519285153,
            "unit": "ns/iter",
            "extra": "iterations: 101100368\ncpu: 7.0869818990174185 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 325.0035675776528,
            "unit": "ns/iter",
            "extra": "iterations: 2115441\ncpu: 324.97923364442676 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 89026.47400024859,
            "unit": "ns/iter",
            "extra": "iterations: 7827\ncpu: 89009.11358119338 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 26773998.950000077,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 26773025.200000025 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 10883834087.999958,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10883014545.999998 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 8.000000661922968e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.999999998593466e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 24.71863204596477,
            "unit": "ns/iter",
            "extra": "iterations: 28287237\ncpu: 24.71698653353796 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 27.54806498658502,
            "unit": "ns/iter",
            "extra": "iterations: 25804033\ncpu: 27.545629669594685 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 558.3239430262091,
            "unit": "ns/iter",
            "extra": "iterations: 1262898\ncpu: 558.3259574407432 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 91706.62220197667,
            "unit": "ns/iter",
            "extra": "iterations: 7684\ncpu: 91663.58342009409 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 31725309.888888326,
            "unit": "ns/iter",
            "extra": "iterations: 27\ncpu: 31725387.333333388 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 12353138512.999977,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 12345299719 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 575.798289080897,
            "unit": "ns/iter",
            "extra": "iterations: 1234658\ncpu: 575.7523856808899 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 634.9576834749405,
            "unit": "ns/iter",
            "extra": "iterations: 563456\ncpu: 1263.85265042878 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 334.79959781995575,
            "unit": "ns/iter",
            "extra": "iterations: 1158312\ncpu: 688.2093589637318 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 95266.91768470392,
            "unit": "ns/iter",
            "extra": "iterations: 6876\ncpu: 95261.24781849854 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 65046.35854122331,
            "unit": "ns/iter",
            "extra": "iterations: 5772\ncpu: 102216.54643104618 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 29363.808203518256,
            "unit": "ns/iter",
            "extra": "iterations: 11812\ncpu: 48138.837707416365 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 29616835.181818925,
            "unit": "ns/iter",
            "extra": "iterations: 22\ncpu: 29608782.727272853 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 21491224.659092207,
            "unit": "ns/iter",
            "extra": "iterations: 22\ncpu: 36244449.77272733 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 10633492.317708714,
            "unit": "ns/iter",
            "extra": "iterations: 48\ncpu: 17864195.33333325 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10085193739.999908,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10083698032.999998 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 5210174758.750014,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 6397144517.499999 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 2556484773.8124924,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 3138540951.75 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.95526371721616,
            "unit": "ns/iter",
            "extra": "iterations: 235567404\ncpu: 2.9550320892444244 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 6.058533680668699,
            "unit": "ns/iter",
            "extra": "iterations: 116438825\ncpu: 6.05633801268605 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 102.94827560247883,
            "unit": "ns/iter",
            "extra": "iterations: 7106743\ncpu: 102.94407494403563 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 2276.995789692919,
            "unit": "ns/iter",
            "extra": "iterations: 316604\ncpu: 2276.719387626185 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 38201.038880935084,
            "unit": "ns/iter",
            "extra": "iterations: 18158\ncpu: 38198.51773323058 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 1048663.4373087978,
            "unit": "ns/iter",
            "extra": "iterations: 654\ncpu: 1048569.7538226253 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 25.089542412897867,
            "unit": "ns/iter",
            "extra": "iterations: 28023692\ncpu: 25.088415366540655 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 28.301970480142614,
            "unit": "ns/iter",
            "extra": "iterations: 24649373\ncpu: 28.299432525119247 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 416.3959280611794,
            "unit": "ns/iter",
            "extra": "iterations: 1640005\ncpu: 416.36242938283584 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 6802.801629382337,
            "unit": "ns/iter",
            "extra": "iterations: 98074\ncpu: 6802.369506699066 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 109640.96249808338,
            "unit": "ns/iter",
            "extra": "iterations: 6533\ncpu: 109635.2383284878 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 2030121.5342858215,
            "unit": "ns/iter",
            "extra": "iterations: 350\ncpu: 2030030.7342857393 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 430.35791113139754,
            "unit": "ns/iter",
            "extra": "iterations: 1658448\ncpu: 430.26283850925535 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 503.9522458764075,
            "unit": "ns/iter",
            "extra": "iterations: 713708\ncpu: 1001.90047050053 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 256.5655351305052,
            "unit": "ns/iter",
            "extra": "iterations: 1574644\ncpu: 521.6863564081804 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 6845.622652285721,
            "unit": "ns/iter",
            "extra": "iterations: 106806\ncpu: 6813.427288729164 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 8703.5321916188,
            "unit": "ns/iter",
            "extra": "iterations: 42480\ncpu: 17270.443432203418 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 4126.316256650767,
            "unit": "ns/iter",
            "extra": "iterations: 83452\ncpu: 8236.33772707681 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 110678.03279460192,
            "unit": "ns/iter",
            "extra": "iterations: 6373\ncpu: 110668.23238663047 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 155520.1753694522,
            "unit": "ns/iter",
            "extra": "iterations: 2030\ncpu: 305883.0650246261 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 81974.32793209939,
            "unit": "ns/iter",
            "extra": "iterations: 4212\ncpu: 160759.59283000312 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 2221513.8619633294,
            "unit": "ns/iter",
            "extra": "iterations: 326\ncpu: 2221233.788343628 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2369767832.9999976,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 2615435874.000007 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 831444398.2499995,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 998898695.2499963 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "d5c0a28393ea4c8916a0fb7f8d1b6e63ce0cbe19",
          "message": "Updated Version to 0.1.6",
          "timestamp": "2021-08-30T09:55:07Z",
          "tree_id": "727ad4d20f2ef440ca07e748b9dc8e31a3b7221e",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/d5c0a28393ea4c8916a0fb7f8d1b6e63ce0cbe19"
        },
        "date": 1630317801240,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 5.999999643790943e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000000033756e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 13.67300422839355,
            "unit": "ns/iter",
            "extra": "iterations: 51691962\ncpu: 13.522800875695145 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 7.00000043707405e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000000172533e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 13.657557347964767,
            "unit": "ns/iter",
            "extra": "iterations: 51465210\ncpu: 13.656916138105723 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 7.00000043707405e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.2483376188667306,
            "unit": "ns/iter",
            "extra": "iterations: 215453149\ncpu: 3.248065313726282 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 5.020109480841945,
            "unit": "ns/iter",
            "extra": "iterations: 139411058\ncpu: 5.0198602968783135 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 241.16876263773491,
            "unit": "ns/iter",
            "extra": "iterations: 2899054\ncpu: 241.15612713664544 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 64243.04815992499,
            "unit": "ns/iter",
            "extra": "iterations: 11005\ncpu: 64220.67251249431 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 19294841.428571124,
            "unit": "ns/iter",
            "extra": "iterations: 28\ncpu: 19293906.7857143 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 10089289208.000025,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10088454406 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000010748408e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 17.716372853691105,
            "unit": "ns/iter",
            "extra": "iterations: 39501092\ncpu: 17.715284352138916 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 19.48966913500793,
            "unit": "ns/iter",
            "extra": "iterations: 35916160\ncpu: 19.489084495669992 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 403.0546850038342,
            "unit": "ns/iter",
            "extra": "iterations: 1730767\ncpu: 403.0292766155133 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 66418.93854009101,
            "unit": "ns/iter",
            "extra": "iterations: 10576\ncpu: 66413.33339636917 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 22467575.783782896,
            "unit": "ns/iter",
            "extra": "iterations: 37\ncpu: 22466448.027027022 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 10397527949.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10396741865 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 422.2099692879542,
            "unit": "ns/iter",
            "extra": "iterations: 1689890\ncpu: 422.2076531608561 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 602.7329397984005,
            "unit": "ns/iter",
            "extra": "iterations: 617226\ncpu: 1203.8594728673102 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 293.1733115337377,
            "unit": "ns/iter",
            "extra": "iterations: 1753396\ncpu: 599.7692215563382 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 66440.75486935658,
            "unit": "ns/iter",
            "extra": "iterations: 10525\ncpu: 66436.73045130653 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 56986.25471834901,
            "unit": "ns/iter",
            "extra": "iterations: 6888\ncpu: 91725.2857142858 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 20930.396914131357,
            "unit": "ns/iter",
            "extra": "iterations: 15652\ncpu: 37438.40244058245 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 24498803.44444308,
            "unit": "ns/iter",
            "extra": "iterations: 27\ncpu: 24498821.55555556 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 18165174.875001356,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 30587635.80000016 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 9323383.249999927,
            "unit": "ns/iter",
            "extra": "iterations: 48\ncpu: 15060617.666666688 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10465458979.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10464631008.999994 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 4699676482.000015,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 5335233859 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 2242138756.0624986,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2712143855.249999 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.116427773976334,
            "unit": "ns/iter",
            "extra": "iterations: 330963873\ncpu: 2.116146220587659 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 4.316778676250719,
            "unit": "ns/iter",
            "extra": "iterations: 162187312\ncpu: 4.316511078252543 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 72.81998528048874,
            "unit": "ns/iter",
            "extra": "iterations: 9622602\ncpu: 72.81596277181575 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1606.3086103675246,
            "unit": "ns/iter",
            "extra": "iterations: 438634\ncpu: 1606.2024421271497 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 27684.285637439978,
            "unit": "ns/iter",
            "extra": "iterations: 26026\ncpu: 27682.583301314175 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 801810.8754765516,
            "unit": "ns/iter",
            "extra": "iterations: 787\ncpu: 801786.5705209635 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 17.43112119463985,
            "unit": "ns/iter",
            "extra": "iterations: 40166710\ncpu: 17.430615751202904 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 19.222124855661026,
            "unit": "ns/iter",
            "extra": "iterations: 36468143\ncpu: 19.221878805290643 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 295.3959236715349,
            "unit": "ns/iter",
            "extra": "iterations: 2369338\ncpu: 295.3854570348317 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 4818.044749686201,
            "unit": "ns/iter",
            "extra": "iterations: 145677\ncpu: 4817.825222924628 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 78405.23514934916,
            "unit": "ns/iter",
            "extra": "iterations: 8939\ncpu: 78404.14900995554 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1471878.3480176905,
            "unit": "ns/iter",
            "extra": "iterations: 454\ncpu: 1471817.9911894326 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 305.34363872266636,
            "unit": "ns/iter",
            "extra": "iterations: 2298312\ncpu: 305.29273179620884 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 418.6332775001327,
            "unit": "ns/iter",
            "extra": "iterations: 771942\ncpu: 813.3704099530576 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 209.49797770823318,
            "unit": "ns/iter",
            "extra": "iterations: 1562460\ncpu: 421.0937777607256 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 4951.258408906503,
            "unit": "ns/iter",
            "extra": "iterations: 135630\ncpu: 4949.551493032416 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 7725.530183264149,
            "unit": "ns/iter",
            "extra": "iterations: 45290\ncpu: 15415.049392802266 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3824.5082525397124,
            "unit": "ns/iter",
            "extra": "iterations: 103968\ncpu: 7692.713777316053 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 80513.58143039953,
            "unit": "ns/iter",
            "extra": "iterations: 8627\ncpu: 80501.44835980155 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 185333.01088058326,
            "unit": "ns/iter",
            "extra": "iterations: 1976\ncpu: 354256.7586032386 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 72311.2972972923,
            "unit": "ns/iter",
            "extra": "iterations: 3996\ncpu: 139698.0533033076 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1522492.197777865,
            "unit": "ns/iter",
            "extra": "iterations: 450\ncpu: 1522339.8066666506 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2587865666.249996,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 2775200743.000002 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 776186729.999992,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 904119053.7500008 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "id": "68749f06cbac3f08a67a2bafe6284e75bc2dbcf8",
          "message": "Documentation Update",
          "timestamp": "2021-08-30T09:55:20Z",
          "url": "https://github.com/ZigRazor/CXXGraph/pull/50/commits/68749f06cbac3f08a67a2bafe6284e75bc2dbcf8"
        },
        "date": 1630317837912,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999894978e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 16.18753602141765,
            "unit": "ns/iter",
            "extra": "iterations: 46139216\ncpu: 16.182242606809787 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 5.999999643790943e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000001282757e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 15.08659310677654,
            "unit": "ns/iter",
            "extra": "iterations: 44969434\ncpu: 15.08536058070022 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000001282757e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 4.999999987376214e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 4.999999998478444e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.529947555566528,
            "unit": "ns/iter",
            "extra": "iterations: 201849830\ncpu: 3.5290553080971137 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 5.9482603102159946,
            "unit": "ns/iter",
            "extra": "iterations: 114752930\ncpu: 5.947909826790478 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 284.04094273212127,
            "unit": "ns/iter",
            "extra": "iterations: 2621784\ncpu: 284.0271155060828 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 71199.77044800985,
            "unit": "ns/iter",
            "extra": "iterations: 9732\ncpu: 71193.63193588168 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 30760041.476190466,
            "unit": "ns/iter",
            "extra": "iterations: 21\ncpu: 30758418.857142873 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 8800486290.000038,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8799786953 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.99999999298484e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 22.595188077300833,
            "unit": "ns/iter",
            "extra": "iterations: 29686969\ncpu: 22.594258005928435 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 22.699858736385707,
            "unit": "ns/iter",
            "extra": "iterations: 30807650\ncpu: 22.6973648103637 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 502.2677150000163,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 502.2465690000004 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 74860.50670966545,
            "unit": "ns/iter",
            "extra": "iterations: 9613\ncpu: 74850.08290856142 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 34156048.39130251,
            "unit": "ns/iter",
            "extra": "iterations: 23\ncpu: 34152741.56521751 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 9308383789.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 9307614049.999998 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 516.0039947659943,
            "unit": "ns/iter",
            "extra": "iterations: 1342757\ncpu: 515.950836971992 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 540.7424273826118,
            "unit": "ns/iter",
            "extra": "iterations: 757532\ncpu: 1067.250125407244 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 277.94178398489856,
            "unit": "ns/iter",
            "extra": "iterations: 989616\ncpu: 595.3060954956297 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 76624.40934721287,
            "unit": "ns/iter",
            "extra": "iterations: 9222\ncpu: 76617.92301019306 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 56519.62032473184,
            "unit": "ns/iter",
            "extra": "iterations: 6898\ncpu: 89147.3892432589 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 24322.86052526323,
            "unit": "ns/iter",
            "extra": "iterations: 17496\ncpu: 39770.26200274358 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 32762147.956522435,
            "unit": "ns/iter",
            "extra": "iterations: 23\ncpu: 32756592.652174026 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 25803008.74999845,
            "unit": "ns/iter",
            "extra": "iterations: 18\ncpu: 41335130.83333324 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 11361980.81250015,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 19528236.974999912 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 8725783836.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8724915939.999996 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 4598023986.249998,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 5311047474.5 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 2354480216.8750005,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2899571302.2500005 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.3443972906659853,
            "unit": "ns/iter",
            "extra": "iterations: 309465010\ncpu: 2.3442583056481823 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 4.713649916741694,
            "unit": "ns/iter",
            "extra": "iterations: 141031417\ncpu: 4.713250736181702 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 91.04708490065488,
            "unit": "ns/iter",
            "extra": "iterations: 7088026\ncpu: 91.04101917797735 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 2057.3229386380153,
            "unit": "ns/iter",
            "extra": "iterations: 360793\ncpu: 2057.04496484134 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 54471.38089999726,
            "unit": "ns/iter",
            "extra": "iterations: 10000\ncpu: 54471.44130000012 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 865161.8149100156,
            "unit": "ns/iter",
            "extra": "iterations: 778\ncpu: 865162.0385604105 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 21.208818578766767,
            "unit": "ns/iter",
            "extra": "iterations: 31073193\ncpu: 21.208638101658757 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 25.02575480580268,
            "unit": "ns/iter",
            "extra": "iterations: 28613883\ncpu: 25.02484972067554 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 372.32251064956944,
            "unit": "ns/iter",
            "extra": "iterations: 1977544\ncpu: 372.3048129396809 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5606.1095661358695,
            "unit": "ns/iter",
            "extra": "iterations: 124993\ncpu: 5605.840007040398 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 100674.81183179055,
            "unit": "ns/iter",
            "extra": "iterations: 7015\ncpu: 100669.16963649183 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1865423.1322312052,
            "unit": "ns/iter",
            "extra": "iterations: 363\ncpu: 1865259.432506894 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 362.2297093001289,
            "unit": "ns/iter",
            "extra": "iterations: 1867321\ncpu: 362.1636858365637 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 477.29891732590085,
            "unit": "ns/iter",
            "extra": "iterations: 697994\ncpu: 950.9762562428543 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 234.6220958036978,
            "unit": "ns/iter",
            "extra": "iterations: 1415624\ncpu: 484.92312153508095 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5771.088031841159,
            "unit": "ns/iter",
            "extra": "iterations: 109290\ncpu: 5770.790914081973 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 6826.389538636931,
            "unit": "ns/iter",
            "extra": "iterations: 52670\ncpu: 13583.89453199173 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3988.936217561433,
            "unit": "ns/iter",
            "extra": "iterations: 86164\ncpu: 8332.747841325789 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 108635.42428888143,
            "unit": "ns/iter",
            "extra": "iterations: 5871\ncpu: 108609.45103048524 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 154817.52359389266,
            "unit": "ns/iter",
            "extra": "iterations: 2098\ncpu: 305982.02335558186 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 62492.49829826805,
            "unit": "ns/iter",
            "extra": "iterations: 4848\ncpu: 132863.39480198326 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1738539.5707195483,
            "unit": "ns/iter",
            "extra": "iterations: 403\ncpu: 1738462.3349875833 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2122621532.5000055,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 2345176973.499994 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 435749711.1875048,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 533499046.0000017 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "id": "d769b7cfa1303a00cff0ffa22756f4cc895b1239",
          "message": "Documentation Update",
          "timestamp": "2021-08-30T09:55:20Z",
          "url": "https://github.com/ZigRazor/CXXGraph/pull/50/commits/d769b7cfa1303a00cff0ffa22756f4cc895b1239"
        },
        "date": 1630317848977,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 7.00000043707405e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.99999999995249e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 16.302541368696016,
            "unit": "ns/iter",
            "extra": "iterations: 45247075\ncpu: 16.202331531927754 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 16.921858117469892,
            "unit": "ns/iter",
            "extra": "iterations: 42769804\ncpu: 16.920728909583033 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 0.0000011000000199601345,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.999999998593466e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999997425732e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 4.050291407529627,
            "unit": "ns/iter",
            "extra": "iterations: 181533058\ncpu: 4.050123746607079 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 6.021159831272194,
            "unit": "ns/iter",
            "extra": "iterations: 113586539\ncpu: 6.020872834236105 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 277.6811997377585,
            "unit": "ns/iter",
            "extra": "iterations: 2534954\ncpu: 277.6688926110692 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 76038.88701269568,
            "unit": "ns/iter",
            "extra": "iterations: 8824\ncpu: 76032.59916137799 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 22832673.3478268,
            "unit": "ns/iter",
            "extra": "iterations: 23\ncpu: 22830430.565217398 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 8170364319.000044,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8169694827.000001 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.99999999298484e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 20.080339973591894,
            "unit": "ns/iter",
            "extra": "iterations: 34864002\ncpu: 20.079681385975118 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 22.082732739153855,
            "unit": "ns/iter",
            "extra": "iterations: 31703604\ncpu: 22.082336538142506 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 456.85799307407433,
            "unit": "ns/iter",
            "extra": "iterations: 1532214\ncpu: 456.84327124017824 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 75199.12443729794,
            "unit": "ns/iter",
            "extra": "iterations: 9330\ncpu: 75197.32647374042 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 25355232.060605608,
            "unit": "ns/iter",
            "extra": "iterations: 33\ncpu: 25353106.939394 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 10974180019.999949,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10972804769 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 468.0221246654511,
            "unit": "ns/iter",
            "extra": "iterations: 1496565\ncpu: 467.99653339480784 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 555.2916983171506,
            "unit": "ns/iter",
            "extra": "iterations: 629270\ncpu: 1104.8938277686836 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 290.0434575920198,
            "unit": "ns/iter",
            "extra": "iterations: 1145916\ncpu: 627.2148490814374 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 75322.9913858045,
            "unit": "ns/iter",
            "extra": "iterations: 9287\ncpu: 75318.49187035653 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 56094.39745454424,
            "unit": "ns/iter",
            "extra": "iterations: 8250\ncpu: 90143.26593939378 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 25092.595754660142,
            "unit": "ns/iter",
            "extra": "iterations: 16524\ncpu: 44034.62170176702 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 25904083.8965524,
            "unit": "ns/iter",
            "extra": "iterations: 29\ncpu: 25902808.620689556 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 19559901.02500067,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 32507865.149999678 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 8739522.712500047,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 16932465.824999996 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10377560498.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10374822754.999996 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 3760572945.749999,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 4631919084 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 1944134195.1875017,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2371092640.5 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.3963935990326104,
            "unit": "ns/iter",
            "extra": "iterations: 292160525\ncpu: 2.3962063697688234 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 4.900598319484072,
            "unit": "ns/iter",
            "extra": "iterations: 143208273\ncpu: 4.900481803868969 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 82.64530195549062,
            "unit": "ns/iter",
            "extra": "iterations: 8491682\ncpu: 82.64142910674248 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1821.1261049016975,
            "unit": "ns/iter",
            "extra": "iterations: 384989\ncpu: 1821.0616692944582 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 30237.535462043223,
            "unit": "ns/iter",
            "extra": "iterations: 23645\ncpu: 30235.217593571724 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 861861.7249417523,
            "unit": "ns/iter",
            "extra": "iterations: 858\ncpu: 861828.3962703989 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 19.75509840133625,
            "unit": "ns/iter",
            "extra": "iterations: 35416592\ncpu: 19.753398717753427 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 21.761474230281156,
            "unit": "ns/iter",
            "extra": "iterations: 32168977\ncpu: 21.760650424164854 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 334.90023566301136,
            "unit": "ns/iter",
            "extra": "iterations: 2088151\ncpu: 334.88065183025617 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5432.709620868632,
            "unit": "ns/iter",
            "extra": "iterations: 128346\ncpu: 5432.4477584030055 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 88240.01508675065,
            "unit": "ns/iter",
            "extra": "iterations: 7954\ncpu: 88233.21523761742 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1640972.794457233,
            "unit": "ns/iter",
            "extra": "iterations: 433\ncpu: 1640803.5334873472 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 345.1604723186212,
            "unit": "ns/iter",
            "extra": "iterations: 2023888\ncpu: 345.1380807633618 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 384.7904527668233,
            "unit": "ns/iter",
            "extra": "iterations: 773334\ncpu: 753.6256520468554 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 212.78273615066962,
            "unit": "ns/iter",
            "extra": "iterations: 1585640\ncpu: 437.67221374334895 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5971.26616083326,
            "unit": "ns/iter",
            "extra": "iterations: 110313\ncpu: 5970.7484974572635 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 7311.724778722993,
            "unit": "ns/iter",
            "extra": "iterations: 47678\ncpu: 14593.98498259154 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3676.3360955871726,
            "unit": "ns/iter",
            "extra": "iterations: 96268\ncpu: 7351.9717351559175 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 91211.44143790801,
            "unit": "ns/iter",
            "extra": "iterations: 7650\ncpu: 91141.98666666837 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 176513.51299133856,
            "unit": "ns/iter",
            "extra": "iterations: 3002\ncpu: 335467.15522984543 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 65077.20579953904,
            "unit": "ns/iter",
            "extra": "iterations: 5328\ncpu: 128160.41066066471 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1675759.8815165455,
            "unit": "ns/iter",
            "extra": "iterations: 422\ncpu: 1675760.7867298739 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 1759809196.0000205,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 1923423981.5000117 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 717385370.8749931,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 917381084.4999994 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "46abaa45e5a93e4a035f33fcf1319b73f119eb9e",
          "message": "Documentation Update (#50)\n\n* Updated Doxygen Documentation\r\n\r\n* [CodeFactor] Apply fixes to commit 68749f0\r\n\r\nCo-authored-by: codefactor-io <support@codefactor.io>",
          "timestamp": "2021-08-30T12:09:47+02:00",
          "tree_id": "9ee65018370bc3f8cfa6ed71c785466dbe7d6026",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/46abaa45e5a93e4a035f33fcf1319b73f119eb9e"
        },
        "date": 1630318679008,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999923734e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 15.23242964753148,
            "unit": "ns/iter",
            "extra": "iterations: 41979266\ncpu: 15.231250589279005 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 5.999999928008037e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.000000000172533e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000000756402e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 15.460854185695814,
            "unit": "ns/iter",
            "extra": "iterations: 45415558\ncpu: 15.45985860175934 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 7.999999809271685e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999997425732e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 6.000000212225132e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 5.999999999062311e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.434915660648347,
            "unit": "ns/iter",
            "extra": "iterations: 207808332\ncpu: 3.4346918438284755 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 5.887997096657422,
            "unit": "ns/iter",
            "extra": "iterations: 119175741\ncpu: 5.887639540667927 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 283.6901654410979,
            "unit": "ns/iter",
            "extra": "iterations: 2461178\ncpu: 283.65391694546264 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 70693.75303478575,
            "unit": "ns/iter",
            "extra": "iterations: 9803\ncpu: 70689.6005304498 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 28985900.857143015,
            "unit": "ns/iter",
            "extra": "iterations: 21\ncpu: 28984681.57142859 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 8180347541.000003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8179898661.999999 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.99999999298484e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 20.512268035716126,
            "unit": "ns/iter",
            "extra": "iterations: 32550647\ncpu: 20.511128365589798 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 27.190041925837285,
            "unit": "ns/iter",
            "extra": "iterations: 25374806\ncpu: 27.188618781952457 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 472.88584749688016,
            "unit": "ns/iter",
            "extra": "iterations: 1478855\ncpu: 472.85934253189066 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 75224.17943548116,
            "unit": "ns/iter",
            "extra": "iterations: 8432\ncpu: 75219.16413662225 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 30970102.962963134,
            "unit": "ns/iter",
            "extra": "iterations: 27\ncpu: 30968591.814814825 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 9182747678.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 9182316984 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 504.8883963690068,
            "unit": "ns/iter",
            "extra": "iterations: 1423744\ncpu: 504.85517831857464 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 478.3187771538926,
            "unit": "ns/iter",
            "extra": "iterations: 692810\ncpu: 948.1587159538699 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 304.11081218601987,
            "unit": "ns/iter",
            "extra": "iterations: 1191956\ncpu: 651.3908483199024 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 76962.63603603633,
            "unit": "ns/iter",
            "extra": "iterations: 9435\ncpu: 76935.97890831983 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 58980.50593529625,
            "unit": "ns/iter",
            "extra": "iterations: 7666\ncpu: 93439.02908948621 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 26264.279051859136,
            "unit": "ns/iter",
            "extra": "iterations: 17856\ncpu: 41218.154905914 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 32338917.090909675,
            "unit": "ns/iter",
            "extra": "iterations: 22\ncpu: 32333287.954545524 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 24566223.000000775,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 39300608.999999866 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 10990420.062499594,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 17684513.024999868 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 8427311594.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8420194197.000001 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 4448631723.5,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 5051916467 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 2201138148.3124986,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2593911595.499999 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.4364405684149424,
            "unit": "ns/iter",
            "extra": "iterations: 278293041\ncpu: 2.436105353421311 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 4.726898609649649,
            "unit": "ns/iter",
            "extra": "iterations: 147745707\ncpu: 4.726464830548333 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 96.07824615334549,
            "unit": "ns/iter",
            "extra": "iterations: 7230119\ncpu: 96.0706403310931 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1912.8712513991802,
            "unit": "ns/iter",
            "extra": "iterations: 359134\ncpu: 1912.7465235817158 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 51940.820356203134,
            "unit": "ns/iter",
            "extra": "iterations: 15553\ncpu: 51938.364302707116 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 750938.1854748431,
            "unit": "ns/iter",
            "extra": "iterations: 895\ncpu: 750939.6391061412 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 20.957738039985053,
            "unit": "ns/iter",
            "extra": "iterations: 33708801\ncpu: 20.95718948888139 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 23.799483761397894,
            "unit": "ns/iter",
            "extra": "iterations: 29431352\ncpu: 23.799317170342547 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 366.51354464599564,
            "unit": "ns/iter",
            "extra": "iterations: 1914225\ncpu: 366.50883830270703 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 6078.229339084723,
            "unit": "ns/iter",
            "extra": "iterations: 119622\ncpu: 6078.082886091156 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 107432.08870490556,
            "unit": "ns/iter",
            "extra": "iterations: 6764\ncpu: 107068.00059136616 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1767196.473170776,
            "unit": "ns/iter",
            "extra": "iterations: 410\ncpu: 1767079.392682928 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 362.1386753561145,
            "unit": "ns/iter",
            "extra": "iterations: 1819523\ncpu: 362.1262973867422 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 502.0988467128998,
            "unit": "ns/iter",
            "extra": "iterations: 938448\ncpu: 1000.8352023767014 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 205.8703255756627,
            "unit": "ns/iter",
            "extra": "iterations: 1523824\ncpu: 443.9344891535869 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5843.028295527653,
            "unit": "ns/iter",
            "extra": "iterations: 118676\ncpu: 5841.991009134091 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 7909.425958346746,
            "unit": "ns/iter",
            "extra": "iterations: 43982\ncpu: 15736.934427720174 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3826.5022641871356,
            "unit": "ns/iter",
            "extra": "iterations: 83032\ncpu: 7704.742448694584 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 107251.4241866157,
            "unit": "ns/iter",
            "extra": "iterations: 6516\ncpu: 107238.81230816653 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 134421.72437357364,
            "unit": "ns/iter",
            "extra": "iterations: 2634\ncpu: 264410.04593774024 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 67084.35503246686,
            "unit": "ns/iter",
            "extra": "iterations: 4620\ncpu: 131923.18528138314 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1662513.271428506,
            "unit": "ns/iter",
            "extra": "iterations: 420\ncpu: 1662391.8690476508 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2739549771.750006,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 2988409452.999998 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 610587898.9375029,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 798432141.750005 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "3b2c7c21e38fbd97ce6f3f51ba5e2cc69264c2cb",
          "message": "Merge branch 'master' of https://github.com/ZigRazor/CXXGraph",
          "timestamp": "2021-09-03T07:46:10Z",
          "tree_id": "d4c2c57363f7f030a81dc655cf017aea2392434f",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/3b2c7c21e38fbd97ce6f3f51ba5e2cc69264c2cb"
        },
        "date": 1630655663250,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000000062512e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 15.384223953748558,
            "unit": "ns/iter",
            "extra": "iterations: 45142464\ncpu: 15.382000747677397 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000000756402e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 15.488728706330894,
            "unit": "ns/iter",
            "extra": "iterations: 44952737\ncpu: 15.488034799749792 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 7.00000043707405e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 9.000000000813912e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.6808659921991755,
            "unit": "ns/iter",
            "extra": "iterations: 190173399\ncpu: 3.680741426933219 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 5.688709958320187,
            "unit": "ns/iter",
            "extra": "iterations: 123043133\ncpu: 5.688503632299416 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 265.51745256575657,
            "unit": "ns/iter",
            "extra": "iterations: 2681239\ncpu: 265.5081714088151 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 71892.15295445544,
            "unit": "ns/iter",
            "extra": "iterations: 9748\ncpu: 71891.07468198608 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 21857812.920000013,
            "unit": "ns/iter",
            "extra": "iterations: 25\ncpu: 21857413.71999999 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 10448472885.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10447837925 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999975221272e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 20.077128579553055,
            "unit": "ns/iter",
            "extra": "iterations: 34867231\ncpu: 20.076195812624118 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 22.08434504411286,
            "unit": "ns/iter",
            "extra": "iterations: 31692852\ncpu: 22.083815902715237 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 456.9297990565853,
            "unit": "ns/iter",
            "extra": "iterations: 1531874\ncpu: 456.91428342017815 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 75224.07650214812,
            "unit": "ns/iter",
            "extra": "iterations: 9320\ncpu: 75222.55493562251 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 25459739.303030483,
            "unit": "ns/iter",
            "extra": "iterations: 33\ncpu: 25458479.66666673 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 10998036103.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10997596480.000002 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 469.0964023772502,
            "unit": "ns/iter",
            "extra": "iterations: 1492152\ncpu: 469.06208951902744 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 506.1774028277709,
            "unit": "ns/iter",
            "extra": "iterations: 696804\ncpu: 1011.1170960557065 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 274.51372636920433,
            "unit": "ns/iter",
            "extra": "iterations: 1241388\ncpu: 557.4159287829441 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 75082.65879575246,
            "unit": "ns/iter",
            "extra": "iterations: 9317\ncpu: 75079.81506922797 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 59862.24539877482,
            "unit": "ns/iter",
            "extra": "iterations: 6846\ncpu: 95345.28863570008 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 24161.78122852221,
            "unit": "ns/iter",
            "extra": "iterations: 17460\ncpu: 34105.55252004575 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 26184337.793103136,
            "unit": "ns/iter",
            "extra": "iterations: 29\ncpu: 26154796.620689854 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 15913653.524999917,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 26653411.849999998 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 8946114.255208453,
            "unit": "ns/iter",
            "extra": "iterations: 48\ncpu: 16082590.979166612 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10237359609.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10236406960.000004 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 3602728969.4999924,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 4622164076.000001 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 1734156589.874999,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2370099222.750001 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.3963887951763367,
            "unit": "ns/iter",
            "extra": "iterations: 292262237\ncpu: 2.396174929024457 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 4.909251929284121,
            "unit": "ns/iter",
            "extra": "iterations: 142980373\ncpu: 4.908935613141798 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 82.49660599075199,
            "unit": "ns/iter",
            "extra": "iterations: 8482004\ncpu: 82.49084131533078 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1809.4184134269115,
            "unit": "ns/iter",
            "extra": "iterations: 384426\ncpu: 1809.4075036548136 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 30128.89725158401,
            "unit": "ns/iter",
            "extra": "iterations: 23650\ncpu: 30126.795433403746 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 846522.4232558084,
            "unit": "ns/iter",
            "extra": "iterations: 860\ncpu: 846466.3767441865 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 19.744888858469086,
            "unit": "ns/iter",
            "extra": "iterations: 35445751\ncpu: 19.74366730161818 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 21.751436686476328,
            "unit": "ns/iter",
            "extra": "iterations: 32183953\ncpu: 21.750709584991274 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 337.7775661499949,
            "unit": "ns/iter",
            "extra": "iterations: 2077022\ncpu: 337.7544234004245 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5477.845504811977,
            "unit": "ns/iter",
            "extra": "iterations: 128949\ncpu: 5477.679710583227 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 88417.04076224162,
            "unit": "ns/iter",
            "extra": "iterations: 7924\ncpu: 88414.0395002528 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1629762.169767578,
            "unit": "ns/iter",
            "extra": "iterations: 430\ncpu: 1629666.5651162546 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 345.1176563841221,
            "unit": "ns/iter",
            "extra": "iterations: 2024854\ncpu: 345.08989388865285 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 459.56667770763994,
            "unit": "ns/iter",
            "extra": "iterations: 769860\ncpu: 916.6831164107492 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 214.18178957108495,
            "unit": "ns/iter",
            "extra": "iterations: 1510876\ncpu: 432.5331145640106 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5639.0467893944615,
            "unit": "ns/iter",
            "extra": "iterations: 122656\ncpu: 5637.705729846158 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 7245.701015250595,
            "unit": "ns/iter",
            "extra": "iterations: 48658\ncpu: 14481.120555714882 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3500.006594246693,
            "unit": "ns/iter",
            "extra": "iterations: 92884\ncpu: 7434.617630593112 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 91205.49018843216,
            "unit": "ns/iter",
            "extra": "iterations: 7695\ncpu: 91201.21819363283 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 272620.20714282524,
            "unit": "ns/iter",
            "extra": "iterations: 1050\ncpu: 505712.62761905533 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 64862.88063173171,
            "unit": "ns/iter",
            "extra": "iterations: 4084\ncpu: 133354.94074437002 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1683842.4489309536,
            "unit": "ns/iter",
            "extra": "iterations: 421\ncpu: 1683459.9999999988 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 2330305209.500011,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 2495362595.500005 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 429768458.1875032,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 632442498.5000018 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "32eadf7aaf90ca224aaa5e37f4f25b66bd314c02",
          "message": "Split End, need to rework the creation of the packages",
          "timestamp": "2021-09-07T12:09:31Z",
          "tree_id": "6f33fd24740dffd82b514ff98ba184249075ddd8",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/32eadf7aaf90ca224aaa5e37f4f25b66bd314c02"
        },
        "date": 1631017083641,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000000062512e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 15.489983053795783,
            "unit": "ns/iter",
            "extra": "iterations: 45126328\ncpu: 15.489433751401178 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000000756402e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 15.517399744758759,
            "unit": "ns/iter",
            "extra": "iterations: 45116294\ncpu: 15.516818978970214 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 7.000001005508238e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.000000001866624e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.5981534223331035,
            "unit": "ns/iter",
            "extra": "iterations: 193977327\ncpu: 3.5980476109973414 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 6.0862159830151725,
            "unit": "ns/iter",
            "extra": "iterations: 112860199\ncpu: 6.085903330721577 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 260.8178108593784,
            "unit": "ns/iter",
            "extra": "iterations: 2683464\ncpu: 260.8018620708159 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 72043.89579261106,
            "unit": "ns/iter",
            "extra": "iterations: 9721\ncpu: 72040.53152967793 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 21608865.680000234,
            "unit": "ns/iter",
            "extra": "iterations: 25\ncpu: 21607569.600000005 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 10444734067.000013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10444053259.999998 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 7.999999525054591e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.999999986907369e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 20.079087545607283,
            "unit": "ns/iter",
            "extra": "iterations: 34865085\ncpu: 20.077968948017844 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 21.948268393653212,
            "unit": "ns/iter",
            "extra": "iterations: 31964482\ncpu: 21.946894462422332 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 477.3493074358031,
            "unit": "ns/iter",
            "extra": "iterations: 1497695\ncpu: 477.3323567214955 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 75542.64039354959,
            "unit": "ns/iter",
            "extra": "iterations: 9249\ncpu: 75538.87944642665 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 26037544.27272606,
            "unit": "ns/iter",
            "extra": "iterations: 33\ncpu: 26036502.1212121 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 11587181493.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 11586444303 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 467.14089102337243,
            "unit": "ns/iter",
            "extra": "iterations: 1498165\ncpu: 467.1153270834647 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 642.9258560556435,
            "unit": "ns/iter",
            "extra": "iterations: 525842\ncpu: 1280.816741530732 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 333.63012425178783,
            "unit": "ns/iter",
            "extra": "iterations: 1067912\ncpu: 716.1527747604625 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 75879.5577467835,
            "unit": "ns/iter",
            "extra": "iterations: 9178\ncpu: 75863.58803660871 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 60137.664607443,
            "unit": "ns/iter",
            "extra": "iterations: 6394\ncpu: 96897.4832655615 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 24374.390967979405,
            "unit": "ns/iter",
            "extra": "iterations: 17676\ncpu: 40896.91502602406 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 24342152.185184844,
            "unit": "ns/iter",
            "extra": "iterations: 27\ncpu: 24338421.444444373 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 16524427.692307707,
            "unit": "ns/iter",
            "extra": "iterations: 26\ncpu: 28249968.192307897 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 9252994.161458971,
            "unit": "ns/iter",
            "extra": "iterations: 48\ncpu: 15788103.874999875 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10084754025.000051,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10083112063.000002 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 3667951992.2500105,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 4614667833.5 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 1914123192.1250038,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2314037295.249999 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.4803434991997504,
            "unit": "ns/iter",
            "extra": "iterations: 283205900\ncpu: 2.473928230308774 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 5.025312160497088,
            "unit": "ns/iter",
            "extra": "iterations: 139437406\ncpu: 5.02511566372657 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 85.47899216222007,
            "unit": "ns/iter",
            "extra": "iterations: 8186754\ncpu: 85.47310643510214 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1831.6213632272775,
            "unit": "ns/iter",
            "extra": "iterations: 387947\ncpu: 1831.5477191472185 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 30360.981099206663,
            "unit": "ns/iter",
            "extra": "iterations: 22962\ncpu: 30360.21026043014 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 858391.5030230954,
            "unit": "ns/iter",
            "extra": "iterations: 827\ncpu: 858364.2769044728 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 19.751589214578253,
            "unit": "ns/iter",
            "extra": "iterations: 35454306\ncpu: 19.750526156117694 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 21.752664328860227,
            "unit": "ns/iter",
            "extra": "iterations: 32187468\ncpu: 21.752049555435615 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 334.63279667968015,
            "unit": "ns/iter",
            "extra": "iterations: 2091852\ncpu: 334.6303591267404 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5444.260580750896,
            "unit": "ns/iter",
            "extra": "iterations: 128110\ncpu: 5444.087994692125 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 88483.8092529376,
            "unit": "ns/iter",
            "extra": "iterations: 7911\ncpu: 88480.5252180508 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1614282.782313029,
            "unit": "ns/iter",
            "extra": "iterations: 441\ncpu: 1614270.0839002465 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 345.8957012464565,
            "unit": "ns/iter",
            "extra": "iterations: 2022028\ncpu: 345.84640222587353 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 516.2417907067826,
            "unit": "ns/iter",
            "extra": "iterations: 657852\ncpu: 1029.7542167539552 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 250.29427036868836,
            "unit": "ns/iter",
            "extra": "iterations: 1345104\ncpu: 501.70599596759325 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5627.573684946851,
            "unit": "ns/iter",
            "extra": "iterations: 121497\ncpu: 5627.108266047737 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 8200.209637677326,
            "unit": "ns/iter",
            "extra": "iterations: 42614\ncpu: 16365.16271647853 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 4106.2711528059945,
            "unit": "ns/iter",
            "extra": "iterations: 81384\ncpu: 8209.371817556303 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 91291.58978388982,
            "unit": "ns/iter",
            "extra": "iterations: 7635\ncpu: 91289.60091683085 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 234174.60475352439,
            "unit": "ns/iter",
            "extra": "iterations: 1136\ncpu: 440455.2975352029 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 102191.4041666605,
            "unit": "ns/iter",
            "extra": "iterations: 3000\ncpu: 193730.65466667005 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1701582.3293555786,
            "unit": "ns/iter",
            "extra": "iterations: 419\ncpu: 1701426.3389020995 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 3185649571.7500196,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 3356574350 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 656609378.8750038,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 757661639.4999968 ns\nthreads: 4"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "zigrazor@gmail.com",
            "name": "ZigRazor",
            "username": "ZigRazor"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "76756cc7ea54b76489e01960f412416191a27f8e",
          "message": "Updated Doxyfile for Documentation of splitted Files",
          "timestamp": "2021-09-09T09:24:41Z",
          "tree_id": "2979475c64ddc193d1c083ee1d88a5a4b102b518",
          "url": "https://github.com/ZigRazor/CXXGraph/commit/76756cc7ea54b76489e01960f412416191a27f8e"
        },
        "date": 1631179991888,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "NodeCreation",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999923734e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeCreationDestruction_new_delete",
            "value": 15.52154094791473,
            "unit": "ns/iter",
            "extra": "iterations: 44966893\ncpu: 15.520371821108476 ns\nthreads: 1"
          },
          {
            "name": "NodeGetId",
            "value": 8.000000093488779e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999999646178e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetData",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "BM_EdgeCreation",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "EdgeCreationDestruction_new_delete",
            "value": 21.746599117177546,
            "unit": "ns/iter",
            "extra": "iterations: 32182232\ncpu: 21.746341273035384 ns\nthreads: 1"
          },
          {
            "name": "EdgeGetId",
            "value": 7.999999809271685e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "NodeGetNodePair",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 8.000000000230045e-7 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation",
            "value": 7.000000152856956e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 6.999999997425732e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge",
            "value": 3.518110805188871,
            "unit": "ns/iter",
            "extra": "iterations: 198344881\ncpu: 3.5180328147717606 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/1",
            "value": 6.102050475815723,
            "unit": "ns/iter",
            "extra": "iterations: 115350251\ncpu: 6.102005413061477 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/16",
            "value": 260.77837741987054,
            "unit": "ns/iter",
            "extra": "iterations: 2684379\ncpu: 260.77420476020717 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/256",
            "value": 71871.67420349344,
            "unit": "ns/iter",
            "extra": "iterations: 9730\ncpu: 71869.578622816 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/4096",
            "value": 21658789.59999986,
            "unit": "ns/iter",
            "extra": "iterations: 25\ncpu: 21657206.999999978 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX/65536",
            "value": 10574798186.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10574114945 ns\nthreads: 1"
          },
          {
            "name": "GraphCreation_TS",
            "value": 6.999999868639861e-7,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 7.999999986907369e-7 ns\nthreads: 1"
          },
          {
            "name": "AddEdge_TS",
            "value": 20.075761941387437,
            "unit": "ns/iter",
            "extra": "iterations: 34872958\ncpu: 20.07543211562389 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/1",
            "value": 21.897132918280235,
            "unit": "ns/iter",
            "extra": "iterations: 31973766\ncpu: 21.896716889715062 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/16",
            "value": 457.0357557678361,
            "unit": "ns/iter",
            "extra": "iterations: 1531641\ncpu: 457.0237418559586 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/256",
            "value": 75695.7774656984,
            "unit": "ns/iter",
            "extra": "iterations: 9257\ncpu: 75693.85351625827 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/4096",
            "value": 26017058.242425237,
            "unit": "ns/iter",
            "extra": "iterations: 33\ncpu: 26016973.999999944 ns\nthreads: 1"
          },
          {
            "name": "AddEdgeX_TS/65536",
            "value": 11885417924.999956,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 11882160804.999998 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:1",
            "value": 467.0597652159484,
            "unit": "ns/iter",
            "extra": "iterations: 1498313\ncpu: 467.0442157279515 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:2",
            "value": 590.6260548117378,
            "unit": "ns/iter",
            "extra": "iterations: 572140\ncpu: 1177.4548974027368 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/16/threads:4",
            "value": 315.5058312404551,
            "unit": "ns/iter",
            "extra": "iterations: 1030484\ncpu: 687.2322801712536 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:1",
            "value": 75601.45007032374,
            "unit": "ns/iter",
            "extra": "iterations: 9243\ncpu: 75594.60348371735 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:2",
            "value": 65749.96877648945,
            "unit": "ns/iter",
            "extra": "iterations: 7078\ncpu: 106141.75035320726 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/256/threads:4",
            "value": 22686.547816996477,
            "unit": "ns/iter",
            "extra": "iterations: 20568\ncpu: 39922.18159276549 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:1",
            "value": 26844618.89655189,
            "unit": "ns/iter",
            "extra": "iterations: 29\ncpu: 26841594.27586214 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:2",
            "value": 19646648.750000395,
            "unit": "ns/iter",
            "extra": "iterations: 20\ncpu: 32826725.44999994 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/4096/threads:4",
            "value": 8804518.924999982,
            "unit": "ns/iter",
            "extra": "iterations: 40\ncpu: 15630718.549999934 ns\nthreads: 4"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:1",
            "value": 10218302270.000038,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10217482932.000004 ns\nthreads: 1"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:2",
            "value": 5582106736.249997,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 6039674532.000003 ns\nthreads: 2"
          },
          {
            "name": "BM_AddEdgeX_MT_TS/65536/threads:4",
            "value": 1730248431.8124948,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 2920174852.000001 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdge",
            "value": 2.5092192783211074,
            "unit": "ns/iter",
            "extra": "iterations: 278998465\ncpu: 2.5089050543701195 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/1",
            "value": 5.087681630301185,
            "unit": "ns/iter",
            "extra": "iterations: 138114551\ncpu: 5.087538690981257 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/16",
            "value": 85.46561348904102,
            "unit": "ns/iter",
            "extra": "iterations: 8195452\ncpu: 85.46383591777462 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/256",
            "value": 1756.2658277281057,
            "unit": "ns/iter",
            "extra": "iterations: 389222\ncpu: 1756.2397449270634 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/4096",
            "value": 30459.1619092981,
            "unit": "ns/iter",
            "extra": "iterations: 23087\ncpu: 30455.187941265725 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX/65536",
            "value": 882071.6588380808,
            "unit": "ns/iter",
            "extra": "iterations: 809\ncpu: 882022.3794808519 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdge_TS",
            "value": 19.744202438108942,
            "unit": "ns/iter",
            "extra": "iterations: 35460596\ncpu: 19.743364804133595 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/1",
            "value": 21.74725879183769,
            "unit": "ns/iter",
            "extra": "iterations: 32193013\ncpu: 21.746541182709272 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/16",
            "value": 334.6046238165896,
            "unit": "ns/iter",
            "extra": "iterations: 2092038\ncpu: 334.595732486696 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/256",
            "value": 5435.007743078971,
            "unit": "ns/iter",
            "extra": "iterations: 128631\ncpu: 5434.779625440299 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/4096",
            "value": 88879.99456452546,
            "unit": "ns/iter",
            "extra": "iterations: 7911\ncpu: 88875.27417519923 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_TS/65536",
            "value": 1633570.8127854138,
            "unit": "ns/iter",
            "extra": "iterations: 438\ncpu: 1633544.1164383711 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:1",
            "value": 345.76631060958994,
            "unit": "ns/iter",
            "extra": "iterations: 2024020\ncpu: 345.7154736613255 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:2",
            "value": 495.37416512801434,
            "unit": "ns/iter",
            "extra": "iterations: 701904\ncpu: 988.8879462148757 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/16/threads:4",
            "value": 244.5744137769605,
            "unit": "ns/iter",
            "extra": "iterations: 1444672\ncpu: 494.85433164067575 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:1",
            "value": 5623.924647715431,
            "unit": "ns/iter",
            "extra": "iterations: 122770\ncpu: 5623.772159322241 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:2",
            "value": 7977.643461362774,
            "unit": "ns/iter",
            "extra": "iterations: 43740\ncpu: 15935.78102423404 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/256/threads:4",
            "value": 3695.6274359654444,
            "unit": "ns/iter",
            "extra": "iterations: 82924\ncpu: 8443.18326419352 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:1",
            "value": 91160.79568063245,
            "unit": "ns/iter",
            "extra": "iterations: 7640\ncpu: 91154.90497382193 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:2",
            "value": 955187.528985482,
            "unit": "ns/iter",
            "extra": "iterations: 414\ncpu: 1707830.983091789 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/4096/threads:4",
            "value": 1390304.0848213825,
            "unit": "ns/iter",
            "extra": "iterations: 280\ncpu: 2403925.0142856813 ns\nthreads: 4"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:1",
            "value": 1715132.4595239374,
            "unit": "ns/iter",
            "extra": "iterations: 420\ncpu: 1715054.9023809736 ns\nthreads: 1"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:2",
            "value": 3897778977.999991,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 4070945135.5000057 ns\nthreads: 2"
          },
          {
            "name": "RemoveEdgeX_MT_TS/65536/threads:4",
            "value": 912263257.8749971,
            "unit": "ns/iter",
            "extra": "iterations: 4\ncpu: 1048060818.4999993 ns\nthreads: 4"
          }
        ]
      }
    ]
  }
}