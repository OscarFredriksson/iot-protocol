import React from 'react';
import {Appearance, StyleSheet, View} from 'react-native';

interface CardProps {
  style?: object;
}

export default function Card(props: React.PropsWithChildren<CardProps>) {
  return <View style={{...styles.card, ...props.style}}>{props.children}</View>;
}

const styles = StyleSheet.create({
  card: {
    shadowColor: 'black',
    shadowOpacity: 0.25,
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowRadius: 8,
    elevation: 5,
    backgroundColor: Appearance.getColorScheme() === 'dark' ? 'black' : 'white',
    borderRadius: 15,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
