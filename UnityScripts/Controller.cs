using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uduino;
using UnityEngine.InputSystem;

public class Controller : MonoBehaviour
{
    private Gamepad gp = null;
    private float moveX;
    private float moveY;
    private float cañon;

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
        moveX = gp.leftStick.ReadValue().x;
        moveY = gp.leftStick.ReadValue().y;
        cañon = gp.rightStick.ReadValue().y;
        
        if ((moveX < 0.4) && (moveX > -0.4) && (moveY < 0.4) && (moveY > -0.4) && (cañon < 0.4) && (cañon > -0.4))
            {

            UduinoManager.Instance.digitalWrite(16, 0);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 0);
              
            Debug.Log("Parar Orugas"); // --------------------------------------------------> Parar Todo
        }
        else
        {
            if ((moveX > 0.4) && (moveY < 0.4) && (moveY > -0.4)) //------------------------> Movimiento Hacia la Derecha
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 255);
                UduinoManager.Instance.digitalWrite(15, 0);
            }

            if ((moveX < -0.4) && (moveY < 0.4) && (moveY > -0.4)) //-----------------------> Movimiento Hacia la Izquierda
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 255);
                UduinoManager.Instance.digitalWrite(13, 255);
                UduinoManager.Instance.digitalWrite(15, 0);
            }

            if ((moveY > 0.4) && (moveX > -0.4) && (moveX < 0.4)) //------------------------> Movimiento Hacia Delante
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 0);
                UduinoManager.Instance.digitalWrite(15, 0);
            }

            if ((moveY < -0.4) && (moveX > -0.4) && (moveX < 0.4)) //-----------------------> Movimiento Hacia Atrás
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 255);
                UduinoManager.Instance.digitalWrite(13, 0);
                UduinoManager.Instance.digitalWrite(15, 0);
            }

            if ((moveY > 0.4) && (moveX > 0.4)) //--------------------------------------> Movimiento Diagonal Superior Derecha
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 0);
                UduinoManager.Instance.digitalWrite(15, 255);
            }

            if ((moveY < -0.4) && (moveX > 0.4)) //-------------------------------------> Movimiento Diagonal Inferior Derecha
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 255);
                UduinoManager.Instance.digitalWrite(15, 255);
            }

            if ((moveY > 0.4) && (moveX < -0.4)) //-------------------------------------> Movimiento Diagonal Superior Izquierda
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 255);
                UduinoManager.Instance.digitalWrite(13, 255);
                UduinoManager.Instance.digitalWrite(15, 255);
            }

            if ((moveY < -0.4) && (moveX < -0.4)) //------------------------------------> Movimiento Diagonal Inferior Izquierda
            {
                UduinoManager.Instance.digitalWrite(16, 255);
                UduinoManager.Instance.digitalWrite(5, 255);
                UduinoManager.Instance.digitalWrite(13, 0);
                UduinoManager.Instance.digitalWrite(15, 255);
            }
        }
        if (cañon > 0.4) 
        {
            UduinoManager.Instance.digitalWrite(16, 0);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 0);
        }
        if (cañon < -0.4)
        {
            UduinoManager.Instance.digitalWrite(16, 0);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 0);
            UduinoManager.Instance.digitalWrite(15, 255);
        }
    }
}