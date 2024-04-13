#include "Arduino.h"
#include "QTRSensors.h"
#include "printer.hpp"

const uint8_t numSensors = 15;
const uint16_t sensorThreshold = 400;
const uint16_t timer = 200;
const int8_t sensorDistance = 4;

const uint8_t sensorPins[numSensors] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, A1, A2, A3, A4};
const int8_t sensorWeights[numSensors] = {7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7};

uint16_t sensorReadings[numSensors];
int8_t sensorValues[numSensors];

int8_t weightedSum;
uint8_t sensorCount;

int8_t output;
int8_t lastOutput;
bool inInitialState = true;

QTRSensors qtr;

printer dataPrinter;

void setup() {
    Serial.begin(9600);

    //Set pinmodes
    for (int i = 0; i < numSensors; i++) {
        pinMode(sensorPins[i], INPUT);
    }

    //Initialiser qtr
    qtr.setTypeRC();
    qtr.setSensorPins(sensorPins, numSensors);
}

void loop() {
    sensorCount = 0;
    weightedSum = 0;

    for (uint8_t i = 0; i < numSensors; i++) {
        sensorValues[i] = 0;
    }

    qtr.read(sensorReadings);



    //Prosseser avlesning
    for (uint8_t i = 0; i < numSensors; i++) {


        if (sensorReadings[i] > sensorThreshold) {
            sensorValues[i] = sensorWeights[i];
            sensorCount++;
        } else {
            sensorValues[i] = 0;
        }
    }

    /*
    //Hvis ingen sensoravlesning
    if (sensorCount == 0) {
        //Kopier forrige output
        Serial.write(output);
        return;
    }
    if (sensorCount >= 6) {
        uint16_t startTime = millis();

        //Holder på i "Timer" millisekund
        while (millis()-startTime < timer) {
            //Reset sensorCount
            sensorCount = 0;

            //Teller gjennom sensorer
            for (uint8_t i = 0; i < numSensors; i++) {
                //Ser etter nye aktive sensorer
                sensorReadings[i] = digitalRead(sensorPins[i]);

                if (sensorReadings[i] > sensorThreshold) {
                    sensorValues[i] = sensorWeights[i];
                }

                //Teller totale aktiverte sensorer
                if (sensorValues[i] != 0) {
                    sensorCount++;
                }
            }

            //Hvis alle har vært aktivert
            if (sensorCount == 14) {
                //Er ikke 90grader
                sensorCount = 0;
                output = 0;

                //Stopp loopen
                Serial.write(output);
                return;
            }
        }

        //Hvis hoyre sensor er inaktiv
        if (sensorValues[14] == 0) {
            //90grader til venstre
            output = 15;
        } else if (sensorValues[0] == 0) {
            //90grader til hoyre
            output = 16;
        }

        //Stopp loopen
        Serial.write(output);
        return;
    }*/
    //Summer sensorvekter
    for (uint8_t i = 0; i < numSensors; i++) {
        weightedSum += sensorValues[i];
    }

    //Deler på antall og runder av
    if (sensorCount == 0) {
        output = 111;
    } else {
        output = weightedSum/sensorCount*sensorDistance;
    }

    if (sensorCount > 5 && abs(sensorValues[0]) != abs(sensorValues[14])) {
        if (sensorValues[0] == 0) {
            output = -40;
        } else {
            output = 40;
        }
    }

    //If changed from initial state, no longer in initial state
    if (output != lastOutput && inInitialState) {
        inInitialState = false;
    }

    //Send if has changed, and if in initialState
    if (output != lastOutput) {
        Serial.write(output);
        delay(10);
    } else if (inInitialState) {
        Serial.write(output);
        delay(100);
    }


    lastOutput = output;
}