import React from 'react';
import {StyleSheet, TouchableOpacity} from 'react-native';

import IonIcon from 'react-native-vector-icons/Ionicons';
import Colors from '../../constants/Colors';
import Card from '../ui/Card';

interface OnOffButtonProps {
  onPress: () => void;
  isOn?: boolean;
  style?: object;
}

export default function OnOffButton(props: OnOffButtonProps) {
  return (
    <Card style={{...props.style, ...styles.card}}>
      <TouchableOpacity onPress={props.onPress}>
        <IonIcon
          name="power"
          size={50}
          color={
            props.isOn || props.isOn === undefined
              ? Colors.primary
              : Colors.inactive
          }
        />
      </TouchableOpacity>
    </Card>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 100,
    width: 100,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
