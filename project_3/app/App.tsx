import React from 'react';

import AppNavigator from './navigators/AppNavigator';
import {NavigationContainer} from '@react-navigation/native';

import {LogBox, StatusBar} from 'react-native';

import 'react-native-gesture-handler';

//https://stackoverflow.com/questions/69538962
LogBox.ignoreLogs(['new NativeEventEmitter']);

export default function App() {
  return (
    <NavigationContainer>
      <StatusBar barStyle="light-content" />
      <AppNavigator />
    </NavigationContainer>
  );
}
