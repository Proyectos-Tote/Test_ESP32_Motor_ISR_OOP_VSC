# Test_ESP32_Motor_ISR_OOP_VSC
Programa de demostración del control de velocidad de motores PaP por medio de interrupciones y temporizadores del ESP32.

Crear una carpeta local, descargar todos los archivos en ella y abrir la carpeta con Visual Studio Code. 
El código fuente del programa principal está en la carpeta 'src'. 

Te harán falta dos librerías adicionales: 

  ToteESP32MotorTimer, que está aquí: https://github.com/MisLibrerias/ToteESP32MotorTimer
  ToteESP32TimerIsr, que está aquí: https://github.com/MisLibrerias/ToteESP32TimerIsr
  
  ToteESP32MotorTimer es una clase especializada de ToteESP32TimerIsr, por lo que tendrás que editar el archivo 'ToteESP32MotorTimer.cpp' para ajustar la ruta en donde te hayas descargado la librería 'ToteESPTimerIsr' (Que es su clase base).
  
  De la misma forma, deberás editar el programa principal 'Test_ESP32_Motor_ISR_OOP_VSC', que está en la carpeta 'src' y ajustar el include de la clase 'ToteESP32MotorTimer' a la ruta donde la hayas descargado.
  
