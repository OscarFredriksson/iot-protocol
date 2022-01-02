import React from 'react';
import {StyleSheet, View} from 'react-native';
import Colors from '../../constants/Colors';

interface HeaderProps {
  style?: object;
}

export default function Header(props: HeaderProps) {
  return <View style={[props.style, styles.container]} />;
}

const styles = StyleSheet.create({
  container: {
    width: '100%',
    height: 75,
    backgroundColor: Colors.primary,
    // borderBottomLeftRadius: 20,
    // borderBottomRightRadius: 20,
    shadowColor: 'black',
    shadowOpacity: 0.2,
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowRadius: 2,
    elevation: 2,
  },
});
