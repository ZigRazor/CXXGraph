window.BENCHMARK_DATA = {
  "lastUpdate": 1630049084763,
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
      }
    ]
  }
}