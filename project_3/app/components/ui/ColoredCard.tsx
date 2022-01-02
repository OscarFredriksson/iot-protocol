import React from 'react';
import {StyleSheet, View} from 'react-native';
import Colors from '../../constants/Colors';

interface ColoredCardProps {
  style?: object;
}

export default function ColoredCard(
  props: React.PropsWithChildren<ColoredCardProps>,
) {
  return <View style={[props.style, styles.card]}>{props.children}</View>;
}

const styles = StyleSheet.create({
  card: {
    backgroundColor: Colors.primaryOpacity,
    borderRadius: 15,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
