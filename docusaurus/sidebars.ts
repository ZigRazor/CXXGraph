import type {SidebarsConfig} from '@docusaurus/plugin-content-docs';

const sidebars: SidebarsConfig = {
  docSidebar: [
    {
      type: 'category',
      label: 'Getting Started',
      collapsed: false,
      items: [
        'getting-started/how-to-use-cxxgraph',
        'getting-started/installation',
        'how-to-make-a-graph',
        'getting-started/packaging',
      ],
    },
    {
      type: 'category',
      label: 'Components',
      collapsed: true,
      items: [
        'component-explanation/network-dynamics',
        'component-explanation/partition-algorithm',
        'component-explanation/regular-algorithm',
      ],
    },
    {
      type: 'category',
      label: 'Testing Executions',
      collapsed: true,
      items: [
        'test-execution/unit-test-execution',
        'test-execution/benchmark-execution',
      ],
    },
   ],
  };

export default sidebars;