import React from 'react';
import {Appearance, StyleSheet, Text} from 'react-native';

interface LabelTextProps {
  style?: object;
}

export default function LabelText(
  props: React.PropsWithChildren<LabelTextProps>,
) {
  return (
    <Text style={{...props.style, ...styles.label}}>{props.children}</Text>
  );
}

const styles = StyleSheet.create({
  label: {
    width: '100%',
    textAlign: 'left',
    color: Appearance.getColorScheme() === 'dark' ? '#eee' : '#444',
    fontWeight: '500',
  },
});
