
class ClockDisplay {
    public:
        virtual void displayTime() = 0;
        virtual void displayDate() = 0;
        virtual void startBlink() = 0;
        virtual void stopBlink() = 0;
};

class ConsoleClockDisplay : public ClockDisplay {
    public:
        ConsoleClockDisplay();
        ~ConsoleClockDisplay();
        void displayTime();
        void displayDate();
        void startBlink();
        void stopBlink();
    private:
        bool needToBlink();
        bool blinking;
        char displayString[9];
};

