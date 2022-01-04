import React from 'react';
import {
  ActivityIndicator,
  StyleSheet,
  TouchableOpacity,
  View,
} from 'react-native';

import IonIcon from 'react-native-vector-icons/Ionicons';
import Colors from '../../constants/Colors';
import ColoredCard from '../ui/ColoredCard';

interface OnOffButtonProps {
  isLoading?: boolean;
  onPress: () => void;
  isOn: boolean;
  style?: object;
}

export default function OnOffButton(props: OnOffButtonProps) {
  return (
    <ColoredCard style={{...props.style, ...styles.card}}>
      {props.isLoading ? (
        <View style={styles.centered}>
          <ActivityIndicator size="large" color={Colors.primary} />
        </View>
      ) : (
        <TouchableOpacity onPress={props.onPress}>
          <IonIcon
            name="power"
            size={50}
            color={props.isOn ? Colors.primary : 'white'}
          />
        </TouchableOpacity>
      )}
    </ColoredCard>
  );
}

const styles = StyleSheet.create({
  card: {
    height: 100,
    width: 100,
    alignItems: 'center',
    justifyContent: 'center',
  },
  centered: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
  },
});
