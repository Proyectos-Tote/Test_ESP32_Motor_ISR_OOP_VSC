
#include <Arduino.h>

#include "C:\Users\Antonio\OneDrive\MIS COSAS\Proyectos Electronica\Arduino\Mis_Librerias\ToteESP32MotorTimer\ToteESP32MotorTimer_V1_0.cpp"
 
#define AR_PIN 2
#define DEC_PIN 18

void IRAM_ATTR myMotorAR_ISR(void);
void IRAM_ATTR myMotorDEC_ISR(void);

// stepPeriod = 1s, pulsePeriod = 4 us, timer = 0, Prescaler = 80.
ToteESP32MotorTimer myMotorARTimer = ToteESP32MotorTimer(1000000, 20, 0, &myMotorAR_ISR, 80);

// stepPeriod = 1s, pulsePeriod = 4 us, timer = 1, Prescaler = 80.
ToteESP32MotorTimer myMotorDECTimer = ToteESP32MotorTimer(1000000, 20, 1, &myMotorDEC_ISR, 80);


void IRAM_ATTR myMotorAR_ISR(void) {
	// Primero se comprueba si ya se está procesando la interrupción.
  	if (myMotorARTimer.isHandlingISR() == true) {
		return;
	}
    	
	// Indico que se está atendiendo la interrupción.
  	myMotorARTimer.setHandlingISR(true);

	
	// Compruebo si es el flanco de subida.
	if (myMotorARTimer.getEdge() == ToteESP32MotorTimer::RISING_EDGE) {
		digitalWrite(AR_PIN, HIGH); // Flanco de subida del pulso de activación de pasos.

		// Cambio el semáforo de flanco.
		myMotorARTimer.setEdge(ToteESP32MotorTimer::FAILING_EDGE); // El flanco de bajada se producirá en...

		// Cambio la cuenta al valor del 'pulsePeriod'
		myMotorARTimer.setCount(myMotorARTimer.getPulsePeriod());
	} else { // Si no es el de subida, estamos procesando el de bajada.
		digitalWrite(AR_PIN, LOW); // Flanco de bajada del pulso de activación de pasos.

		// Cambio el semáforo de flanco.
		myMotorARTimer.setEdge(ToteESP32MotorTimer::RISING_EDGE); // El flanco de subida se producirá en...

		// Cambio la cuenta al valor del 'stepPeriod' -'pulsePeriod' (Lo queda) 
		myMotorARTimer.setCount(myMotorARTimer.getStepPeriod() - myMotorARTimer.getPulsePeriod());
	}


  	// Nos preparamos para otra interrupción.
  	myMotorARTimer.setHandlingISR(false);
}



void IRAM_ATTR myMotorDEC_ISR(void) {
	// Primero se comprueba si ya se está procesando la interrupción.
  	if (myMotorDECTimer.isHandlingISR() == true) {
		return;
	}
    	
	// Indico que se está atendiendo la interrupción.
  	myMotorDECTimer.setHandlingISR(true);

	
	// Compruebo si es el flanco de subida.
	if (myMotorDECTimer.getEdge() == ToteESP32MotorTimer::RISING_EDGE) {
		digitalWrite(DEC_PIN, HIGH); // Flanco de subida del pulso de activación de pasos.

		// Cambio el semáforo de flanco.
		myMotorDECTimer.setEdge(ToteESP32MotorTimer::FAILING_EDGE); // El flanco de bajada se producirá en...

		// Cambio la cuenta al valor del 'pulsePeriod'
		myMotorDECTimer.setCount(myMotorDECTimer.getPulsePeriod());
	} else { // Si no es el de subida, estamos procesando el de bajada.
		digitalWrite(DEC_PIN, LOW); // Flanco de bajada del pulso de activación de pasos.

		// Cambio el semáforo de flanco.
		myMotorDECTimer.setEdge(ToteESP32MotorTimer::RISING_EDGE); // El flanco de subida se producirá en...

		// Cambio la cuenta al valor del 'stepPeriod' -'pulsePeriod' (Lo queda) 
		myMotorDECTimer.setCount(myMotorDECTimer.getStepPeriod() - myMotorDECTimer.getPulsePeriod());
	}


  	// Nos preparamos para otra interrupción.
  	myMotorDECTimer.setHandlingISR(false);
}




void setup() {
	Serial.begin(115200);
  	
	pinMode(AR_PIN, OUTPUT);  // Built-in Led.
	pinMode(DEC_PIN, OUTPUT);
	

	// Inicialmente apagado
	digitalWrite(AR_PIN, LOW);
	digitalWrite(DEC_PIN, LOW);

	Serial.println();
  	Serial.println();
  	Serial.println();

	Serial.println("Escribe por Serial el valor de 'stepPeriod' en microsegundos");

  	myMotorARTimer.init();
	myMotorDECTimer.init();

	myMotorARTimer.enable();
	myMotorDECTimer.enable();
}
 
void loop() {
	static uint64_t theStepPeriod;	//El intervalo entre pulsos.

	if (Serial.available()) {
        String data = Serial.readStringUntil('\n');
        
        // Convierto la pulsación de teclas en un comando para el telescopio.
        theStepPeriod = data.toInt();

		Serial.print("Estableciendo AR stepPeriod a ");
		Serial.println((long) theStepPeriod);

		Serial.print("Estableciendo DEC stepPeriod a ");
		Serial.println((long) theStepPeriod * 2);
		
		
		myMotorARTimer.setStepPeriod(theStepPeriod);
		myMotorDECTimer.setStepPeriod(theStepPeriod * 2);
	}

	//Flipa
	delay(3000);
}




