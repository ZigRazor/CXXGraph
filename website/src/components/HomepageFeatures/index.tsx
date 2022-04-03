import React from 'react';
import clsx from 'clsx';
import styles from './styles.module.css';

type FeatureItem = {
  title: string;
  Svg: React.ComponentType<React.ComponentProps<'svg'>>;
  description: JSX.Element;
};

const FeatureList: FeatureItem[] = [
  {
    title: 'Enhance Productivity',
    Svg: require('@site/static/img/undraw_dev_productivity_re_fylf.svg')
      .default,
    description: (
      <>
        CXXGraph helps enhances your productivity by providing helper algorithms
        right when you need them.
      </>
    ),
  },
  {
    title: 'Focuses only on graphs',
    Svg: require('@site/static/img/undraw_key_points_re_u903.svg').default,
    description: (
      <>
        CXXGraph only focuses on graphs and does it well; saving you time and
        effort.
      </>
    ),
  },
  {
    title: 'All about graphs',
    Svg: require('@site/static/img/undraw_stars_re_6je7.svg').default,
    description: (
      <>
        The community strives to ensure that common graph algorithms are
        covered.{' '}
      </>
    ),
  },
];

function Feature({ title, Svg, description }: FeatureItem) {
  return (
    <div className={clsx('col col--4')}>
      <div className='text--center'>
        <Svg className={styles.featureSvg} role='img' />
      </div>
      <div className='text--center padding-horiz--md'>
        <h3>{title}</h3>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures(): JSX.Element {
  return (
    <section className={styles.features}>
      <div className='container'>
        <div className='row'>
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
