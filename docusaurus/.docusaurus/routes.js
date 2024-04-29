import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/ / /',
    component: ComponentCreator('/ / /', '890'),
    routes: [
      {
        path: '/ / /',
        component: ComponentCreator('/ / /', '37e'),
        routes: [
          {
            path: '/ / /tags',
            component: ComponentCreator('/ / /tags', 'e6e'),
            exact: true
          },
          {
            path: '/ / /tags/algorithm',
            component: ComponentCreator('/ / /tags/algorithm', 'e9b'),
            exact: true
          },
          {
            path: '/ / /tags/benchmark',
            component: ComponentCreator('/ / /tags/benchmark', '326'),
            exact: true
          },
          {
            path: '/ / /tags/benchmark-execution',
            component: ComponentCreator('/ / /tags/benchmark-execution', '220'),
            exact: true
          },
          {
            path: '/ / /tags/components',
            component: ComponentCreator('/ / /tags/components', 'c6a'),
            exact: true
          },
          {
            path: '/ / /tags/components-explanation',
            component: ComponentCreator('/ / /tags/components-explanation', '090'),
            exact: true
          },
          {
            path: '/ / /tags/execution',
            component: ComponentCreator('/ / /tags/execution', 'fbf'),
            exact: true
          },
          {
            path: '/ / /tags/export',
            component: ComponentCreator('/ / /tags/export', '9bc'),
            exact: true
          },
          {
            path: '/ / /tags/getting-started',
            component: ComponentCreator('/ / /tags/getting-started', '8f1'),
            exact: true
          },
          {
            path: '/ / /tags/googletest',
            component: ComponentCreator('/ / /tags/googletest', '596'),
            exact: true
          },
          {
            path: '/ / /tags/graphing',
            component: ComponentCreator('/ / /tags/graphing', '6f4'),
            exact: true
          },
          {
            path: '/ / /tags/graphing-components',
            component: ComponentCreator('/ / /tags/graphing-components', '62a'),
            exact: true
          },
          {
            path: '/ / /tags/how-to-use',
            component: ComponentCreator('/ / /tags/how-to-use', '917'),
            exact: true
          },
          {
            path: '/ / /tags/install',
            component: ComponentCreator('/ / /tags/install', '86f'),
            exact: true
          },
          {
            path: '/ / /tags/introduction',
            component: ComponentCreator('/ / /tags/introduction', '293'),
            exact: true
          },
          {
            path: '/ / /tags/packaging',
            component: ComponentCreator('/ / /tags/packaging', 'a46'),
            exact: true
          },
          {
            path: '/ / /tags/partition-algorithm',
            component: ComponentCreator('/ / /tags/partition-algorithm', '35e'),
            exact: true
          },
          {
            path: '/ / /tags/requirements',
            component: ComponentCreator('/ / /tags/requirements', 'c3e'),
            exact: true
          },
          {
            path: '/ / /tags/testing',
            component: ComponentCreator('/ / /tags/testing', 'b95'),
            exact: true
          },
          {
            path: '/ / /tags/uninstall',
            component: ComponentCreator('/ / /tags/uninstall', '36c'),
            exact: true
          },
          {
            path: '/ / /',
            component: ComponentCreator('/ / /', '222'),
            routes: [
              {
                path: '/ / /component-explanation/network-dynamics',
                component: ComponentCreator('/ / /component-explanation/network-dynamics', '37c'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /component-explanation/partition-algorithm',
                component: ComponentCreator('/ / /component-explanation/partition-algorithm', '8cd'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /component-explanation/regular-algorithm',
                component: ComponentCreator('/ / /component-explanation/regular-algorithm', '301'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /getting-started/how-to-use-cxxgraph',
                component: ComponentCreator('/ / /getting-started/how-to-use-cxxgraph', 'a0d'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /getting-started/installation',
                component: ComponentCreator('/ / /getting-started/installation', '5d2'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /getting-started/packaging',
                component: ComponentCreator('/ / /getting-started/packaging', 'e71'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /test-execution/benchmark-execution',
                component: ComponentCreator('/ / /test-execution/benchmark-execution', '5e1'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /test-execution/unit-test-execution',
                component: ComponentCreator('/ / /test-execution/unit-test-execution', 'd16'),
                exact: true,
                sidebar: "docSidebar"
              },
              {
                path: '/ / /',
                component: ComponentCreator('/ / /', 'f09'),
                exact: true
              }
            ]
          }
        ]
      }
    ]
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
