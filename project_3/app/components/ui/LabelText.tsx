import React from 'react';
import {StyleSheet, Text} from 'react-native';

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
    fontSize: 14,
    width: '100%',
    textAlign: 'left',
    color: '#000',
    fontWeight: 'bold',
    marginTop: 0,
  },
});
