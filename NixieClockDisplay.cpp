#include "NixieClockDisplay.h"
#include "Arduino.h"
#include "Time.h"

NixieClockDisplay::NixieClockDisplay(int din, int st, int sh, int oe)
{
    tube = new NixieTube(din, st, sh, oe, 4);
    tube->clear();
    blinking = false;
    on = true;
}

NixieClockDisplay::~NixieClockDisplay()
{
}

bool NixieClockDisplay::needToBlink()
{
    return (blinking && second() % 2 == 1);
}

void NixieClockDisplay::updateDisplay(char* newString)
{
    if (!on)
        return;
    // if string is different, display it no matter what
    if (strcmp(newString, displayString) != 0)
        strcpy(displayString, newString);
    else if (needToBlink())
        strcpy(displayString, "");
    tube->printf(displayString);
    tube->display();
}

void NixieClockDisplay::displayTime()
{
    char displayString[9];
    //sprintf(displayString, "%02d%s%02d%s", hour(), (second() % 2 == 0 ? ":": ""), minute(), (isAM() ? "'": "."));
    sprintf(displayString, "%2d:%02d%s", hourFormat12(), minute(), (isAM() ? "'": "."));
    updateDisplay(displayString);
}

void NixieClockDisplay::displayDate()
{
    char newString[9];
    sprintf(newString, "%02d.%02d", month(), day());
    updateDisplay(newString);
}

void NixieClockDisplay::startBlink()
{
    blinking = true;
}

void NixieClockDisplay::stopBlink()
{
    blinking = false;
}

void NixieClockDisplay::turnOn()
{
    on = true;
}

void NixieClockDisplay::turnOff()
{
    updateDisplay("");
    on = false;  // set this after, or display is not cleared
}
