#include "ClockDisplay.h"
#include "Arduino.h"
#include "Time.h"

ConsoleClockDisplay::ConsoleClockDisplay()
{
    Serial.begin(115200);
    blinking = false;
}

ConsoleClockDisplay::~ConsoleClockDisplay()
{
}

bool ConsoleClockDisplay::needToBlink()
{
    return (blinking && second() % 2 == 1);
}

void ConsoleClockDisplay::displayTime()
{
    char displayString[9];
    if (needToBlink())
        sprintf(displayString, "OFF");
    else
        sprintf(displayString, "%02d:%02d:%02d", hour(), minute(), second());
    Serial.println(displayString);
}

void ConsoleClockDisplay::displayDate()
{
    char newString[9];
    sprintf(newString, "%02d.%02d", month(), day());
    // if string is different, display it no matter what
    if (strcmp(newString, displayString) != 0)
        strcpy(displayString, newString);
    else if (needToBlink())
        strcpy(displayString, "OFF");
    Serial.println(displayString);
}

void ConsoleClockDisplay::startBlink()
{
    blinking = true;
}

void ConsoleClockDisplay::stopBlink()
{
    blinking = false;
}
