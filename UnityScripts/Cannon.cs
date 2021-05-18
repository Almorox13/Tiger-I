using System.Collections;
using System.Collections.Generic;
using Uduino;
using UnityEngine;
using UnityEngine.InputSystem;

public class Cannon : MonoBehaviour
{
    Gamepad gp = null;
    float cannon;
    void Start()
    {
        gp = InputSystem.GetDevice<Gamepad>();
        UduinoManager.Instance.pinMode(16, PinMode.Output);
        UduinoManager.Instance.pinMode(5, PinMode.Output);
        UduinoManager.Instance.pinMode(13, PinMode.Output);
        UduinoManager.Instance.pinMode(15, PinMode.Output);
    }

    // Update is called once per frame
    void Update()
    {
        cannon = gp.rightStick.ReadValue().y;
        Debug.Log(cannon);

        if (cannon > 0.4)
        {
            UduinoManager.Instance.digitalWrite(16, 0);
            UduinoManager.Instance.digitalWrite(5, 0);
            UduinoManager.Instance.digitalWrite(13, 255);
            UduinoManager.Instance.digitalWrite(15, 0);

            Debug.Log("Cañon arriba");
        }
        else
        {

            if (cannon < -0.4)
            {
                UduinoManager.Instance.digitalWrite(16, 0);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 0);
                UduinoManager.Instance.digitalWrite(15, 255);

                Debug.Log("Cañon abajo");
            }
            else
            {
                UduinoManager.Instance.digitalWrite(16, 0);
                UduinoManager.Instance.digitalWrite(5, 0);
                UduinoManager.Instance.digitalWrite(13, 255);
                UduinoManager.Instance.digitalWrite(15, 255);

                Debug.Log("Cañon stop");
            }
        }
    }
}
