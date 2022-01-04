import React from 'react';

import Colors from '../constants/Colors';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import ConnectingScreen from '../screens/ConnectingScreen';

import DashboardScreen from '../screens/DashboardScreen';
import {createStackNavigator} from '@react-navigation/stack';
import {Platform} from 'react-native';

const Stack =
  Platform.OS === 'ios' ? createNativeStackNavigator() : createStackNavigator();

const defaultNavOptions: any = {
  headerShadowVisible: false,
  headerStyle: {
    backgroundColor: Colors.primary,
    height: Platform.OS === 'android' ? 100 : undefined,
  },
  // headerBlurEffect: 'light',
  headerTitleStyle: {
    fontSize: Platform.OS === 'android' ? 32 : 18,
  },
  headerTintColor: 'white',
  presentation: 'fullScreenModal',
};

export default function AppNavigator() {
  return (
    <Stack.Navigator screenOptions={defaultNavOptions}>
      {/* <Stack.Screen
        name="Connecting"
        component={ConnectingScreen}
        options={{title: ''}}
      /> */}
      <Stack.Screen
        name="Dashboard"
        component={DashboardScreen}
        options={{
          title: 'Dashboard',
          headerLargeTitle: true,
          headerBackVisible: false,
          headerLeft: () => null,
        }}
      />
    </Stack.Navigator>
  );
}
