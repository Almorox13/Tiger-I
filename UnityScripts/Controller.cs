using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uduino;
using UnityEngine.InputSystem;

public class Controller : MonoBehaviour
{
    Gamepad gp = null;

    float x;
    float y;

    void Start()
    {
        gp = InputSystem.GetDevice<Gamepad>();

        UduinoManager.Instance.pinMode(16, PinMode.Output);
        UduinoManager.Instance.pinMode(5, PinMode.Output);
        UduinoManager.Instance.pinMode(13, PinMode.Output);
        UduinoManager.Instance.pinMode(15, PinMode.Output);
    }

    void FixedUpdate()
    {

        x = gp.leftStick.ReadValue().x;
        y = gp.leftStick.ReadValue().y;


        if ((x < 0.4) && (y < 0.4) && (x > -0.4) && (y > -0.4)) //----------> Movimiento Detenido
        {
            UduinoManager.Instance.digitalWrite(16, 0);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("Stop");
        }

        if ((x > 0.4) && (y < 0.4) && (y > -0.4)) //------------------------> Movimiento Hacia la Derecha
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("3.  x: " + x + " y: " + y);
        }

        if ((x < -0.4) && (y < 0.4) && (y > -0.4)) //-----------------------> Movimiento Hacia la Izquierda
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 255);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("7.  x: " + x + " y: " + y);
        }

        if ((y > 0.4) && (x > -0.4) && (x < 0.4)) //------------------------> Movimiento Hacia Delante
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("1.  x: " + x + " y: " + y);
        }

        if ((y < -0.4) && (x > -0.4) && (x < 0.4)) //-----------------------> Movimiento Hacia Atrás
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 255);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("5.  x: " + x + " y: " + y);
        }

        if ((y > 0.4) && (x > 0.4)) //--------------------------------------> Movimiento Diagonal Superior Derecha
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 255);

            Debug.Log("2.  x: " + x + " y: " + y);
        }

        if ((y < -0.4) && (x > 0.4)) //-------------------------------------> Movimiento Diagonal Inferior Derecha
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 255);

            Debug.Log("4.  x: " + x + " y: " + y);
        }

        if ((y > 0.4) && (x < -0.4)) //-------------------------------------> Movimiento Diagonal Superior Izquierda
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 255);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 255);

            Debug.Log("8.  x: " + x + " y: " + y);
        }

        if ((y < -0.4) && (x < -0.4)) //------------------------------------> Movimiento Diagonal Inferior Izquierda
        {
            UduinoManager.Instance.digitalWrite(16, 255);
            UduinoManager.Instance.digitalWrite(5, 255);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 255);

            Debug.Log("6.  x: " + x + " y: " + y);
        }
    }
}