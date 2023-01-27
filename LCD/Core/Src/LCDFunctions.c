/*
 * LCDFunctions.c
 *
 *  Created on: May 13, 2022
 *      Author: T
 */

#include "main.h"
#include "LCDFunctions.h"

void sendCmd(char character) {
	// set R/W to low (0) and set RS to command mode
	sendBit(RWPort, RWPin, 0);
	sendBit(RSPort, RSPin, 0);
	// 40ns
	shitDelay(enableDelay);
	// set E high (1)
	sendBit(EPort, EPin, 1);
	// output byte
	charData(character);
	// 500ns
	shitDelay(disableDelay);
	// set enable low (0)
	sendBit(EPort, EPin, 0);
}

void sendChar(char character) {
	// set R/W to low (0) and set RS to character mode
	sendBit(RWPort, RWPin, 0);
	sendBit(RSPort, RSPin, 1);
	// 40ns
	shitDelay(enableDelay);
	// set E high (1)
	sendBit(EPort, EPin, 1);
	// output byte
	charData(character);
	// 500ns
	shitDelay(disableDelay);
	// set enable low (0)
	sendBit(EPort, EPin, 0);
}

void shitDelay(int t) {
	for (int i; i < t; i++)
	{}
}

void initDisplayModes(){
	// clear artifacts
	sendCmd(0b00000001);
	shitDelay(2000);
	// set 8bit, 2 line display, 5x8 dot font
	sendCmd(0b00111000);
	// enable display and cursor
	sendCmd(0b00001110);
	// move cursor every char
	sendCmd(0b00000110);
}

void sendBit(GPIO_TypeDef *port, uint8_t pin, uint8_t bitState) {
	if (bitState) {
		port->BSRR |= (1 << pin);
	} else {
		port->BRR |= (1 << pin);
	}
}

void charData(char character) {
	sendBit(D0Port, D0Pin, character * 0b00000001);
	sendBit(D1Port, D1Pin, character & 0b00000010);
	sendBit(D2Port, D2Pin, character & 0b00000100);
	sendBit(D3Port, D3Pin, character & 0b00001000);
	sendBit(D4Port, D4Pin, character & 0b00010000);
	sendBit(D5Port, D5Pin, character & 0b00100000);
	sendBit(D6Port, D6Pin, character & 0b01000000);
	sendBit(D7Port, D7Pin, character & 0b10000000);
	shitDelay(100);
}

void setOut(GPIO_TypeDef *port, int pin) {
	if (port == GPIOA)
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	if (port == GPIOB)
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	if (port == GPIOC)
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	if (port == GPIOD)
		RCC->AHBENR |= RCC_AHBENR_GPIODEN;
	if (port == GPIOF)
		RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

	port->MODER &= ~(1 << (pin * 2 + 1));
	port->MODER |= (1 << (pin * 2));
	port->OSPEEDR |= (1 << (pin * 2 + 1)) | (1 << (pin * 2));
	port->OTYPER &= ~(1 << pin);
	port->PUPDR &= ~(1 << pin);
}

void initPins() {
	setOut(D0Port, D0Pin);
	setOut(D1Port, D1Pin);
	setOut(D2Port, D2Pin);
	setOut(D3Port, D3Pin);
	setOut(D4Port, D4Pin);
	setOut(D5Port, D5Pin);
	setOut(D6Port, D6Pin);
	setOut(D7Port, D7Pin);
	setOut(EPort, EPin);
	setOut(RWPort, RWPin);
	setOut(RSPort, RSPin);
}

