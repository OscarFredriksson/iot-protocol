import React from 'react';

import AppNavigator from './navigators/AppNavigator';
import {NavigationContainer} from '@react-navigation/native';

import {LogBox} from 'react-native';

//https://stackoverflow.com/questions/69538962
LogBox.ignoreLogs(['new NativeEventEmitter']);

export default function App() {
  return (
    <NavigationContainer>
      <AppNavigator />
    </NavigationContainer>
  );
}
