/*
 * LCDFunctions.h
 *
 *  Created on: May 13, 2022
 *      Author: T
 */

#ifndef INC_LCDFUNCTIONS_H_
#define INC_LCDFUNCTIONS_H_

#define D0Pin 15
#define D0Port GPIOB
#define D1Pin 6
#define D1Port GPIOC
#define D2Pin 7
#define D2Port GPIOC
#define D3Pin 8
#define D3Port GPIOC
#define D4Pin 9
#define D4Port GPIOC
#define D5Pin 8
#define D5Port GPIOA
#define D6Pin 9
#define D6Port GPIOA
#define D7Pin 10
#define D7Port GPIOA
#define EPin 14
#define EPort GPIOB
#define RWPin 13
#define RWPort GPIOB
#define RSPin 12
#define RSPort GPIOB

#define enableDelay 4
#define disableDelay 8

void sendCmd(char character);
void sendChar(char character);

void shitDelay(int t);

void initDisplayModes(void);
void sendBit(GPIO_TypeDef *port, uint8_t pin, uint8_t bitState);
void charData(char character);
void setOut(GPIO_TypeDef *port, int pin);
void initPins();

#endif /* INC_LCDFUNCTIONS_H_ */
