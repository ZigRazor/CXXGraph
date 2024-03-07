import {themes as prismThemes} from 'prism-react-renderer';
import type {Config} from '@docusaurus/types';
import type * as Preset from '@docusaurus/preset-classic';

const config: Config = {
  title: 'cxxgraphdocs',
  tagline: 'Header-only C++ library for graph representation and algorithms',
  favicon: 'img/logo.png',
  url: 'https://cxxgraph.github.io',
  baseUrl: '/CXXGraph/',
  organizationName: 'zigrazor',
  projectName: 'cxxgraph.github.io',
  deploymentBranch: 'gh-pages',
  trailingSlash: false,
  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      {
        docs: {
          routeBasePath: '/',
          sidebarPath: './sidebars.ts',
          editUrl:
            'https://github.com/ZigRazor/CXXGraph',
        },
        blog: false,
        theme: {
          customCss: './src/css/custom.css',
        },
      } satisfies Preset.Options,
    ],
  ],

  themeConfig: {
    metadata: [
      {property: 'og:title', content: 'CXXGraph'},
      {name: 'description', content: 'Header-Only C++ Library for Graph Representation and Algorithms'},
      {property: 'og:description', content: 'Header-Only C++ Library for Graph Representation and Algorithms'},
      {name: 'twitter:card', content:'summary'},
      {property: 'twitter:title', content: 'CXXGraph'},
    ],
    headTags: [
      {
        tagName: 'link',
        attributes: {
          rel: 'canonical',
          href: 'https://zigrazor.github.io/CXXGraph/',
        },
      },
      {
        tagName: 'script',
        attributes: {
          type: 'application/ld+json',
        },
        innerHTML: JSON.stringify({
          '@context': 'https://schema.org',
          '@type': 'website',
          'description': 'Header-Only C++ Library for Graph Representation and Algorithms',
          'headline': 'CXXGraph',
          'name': 'CXXGraph',
          'url': 'https://cxxgraphdocs.com'
        }),
      },
    ],
    image: '/img/logo.png',
    navbar: {
      title: 'CXXGraph',
      logo: {
        alt: 'CXXGraph logo',
        src: 'img/logoTransWhite.png',
      },
      items: [
        {
          type: 'docSidebar',
          sidebarId: 'docSidebar',
          position: 'left',
          label: 'Docs',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [
        {
          title: 'Contact',
          items: [
            {
              label: 'Github',
              href: 'https://github.com/ZigRazor/CXXGraph',
            },
            {
              label: 'Email',
              href: 'mailto:zigrazor@gmail.com',
            },
            {
              label: 'Glitter',
              href: 'https://app.gitter.im/#/room/#CXXGraph-Community_community:gitter.im',
            },
          ],
        },
      ],
      copyright: ` `,
    },
    prism: {
      theme: prismThemes.github,
      darkTheme: prismThemes.dracula,
    },
  } satisfies Preset.ThemeConfig,
};

export default config;
