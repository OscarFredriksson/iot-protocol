import {Appearance} from 'react-native';

export default {
  primary: Appearance.getColorScheme() === 'dark' ? '#3385ff' : '#0066ff',
  accent: '#03c0cf',
  background: '#eee',
  inactive: '#bbb',
  blueOpacity: '#0066ff44',
};
