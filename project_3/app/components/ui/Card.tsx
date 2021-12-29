import React from 'react';
import {StyleSheet, View} from 'react-native';

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
    backgroundColor: 'white',
    borderRadius: 15,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
