import React from 'react';
import {Modal, StyleSheet, View} from 'react-native';
import {SafeAreaView} from 'react-native-safe-area-context';
import Card from '../ui/Card';

import IonIcon from 'react-native-vector-icons/Ionicons';
import {TouchableOpacity} from 'react-native-gesture-handler';
import Colors from '../../constants/Colors';

interface StatsModalProps {
  visible: boolean;
  close: () => void;
}

export default function StatsModal(props: StatsModalProps) {
  return (
    <Modal
      animationType="fade"
      transparent={true}
      visible={props.visible}
      onRequestClose={() => props.close()}>
      <SafeAreaView style={styles.container}>
        <Card style={styles.card}>
          <View style={styles.row}>
            <TouchableOpacity onPress={() => props.close()}>
              <View style={styles.closeButton}>
                <IonIcon name="close" size={20} color="#333" />
              </View>
            </TouchableOpacity>
          </View>
        </Card>
      </SafeAreaView>
    </Modal>
  );
}

const styles = StyleSheet.create({
  container: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#222222aa',
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'flex-end',
    width: '100%',
  },
  card: {
    width: '90%',
    height: 300,
    justifyContent: 'flex-start',
    alignItems: 'center',
  },
  closeButton: {
    backgroundColor: Colors.blueOpacity,
    width: 30,
    height: 30,
    borderRadius: 15,
    justifyContent: 'center',
    alignItems: 'center',
    marginTop: 10,
    marginRight: 10,
  },
  button: {
    borderRadius: 20,
    padding: 10,
    elevation: 2,
  },
  buttonOpen: {
    backgroundColor: '#F194FF',
  },
  buttonClose: {
    backgroundColor: '#2196F3',
  },
  textStyle: {
    color: 'white',
    fontWeight: 'bold',
    textAlign: 'center',
  },
  modalText: {
    marginBottom: 15,
    textAlign: 'center',
  },
});
