package com.example.tiger_i;

import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.io.OutputStream;

public class Bluetooth{

    private OutputStream os = null;

    public Bluetooth(BluetoothSocket socket){
        try {
            os = socket.getOutputStream();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void write(String input){

        try {
            Log.d("String",""+input);
            os.write(input.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
