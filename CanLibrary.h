#ifndef CANLIBRARY_H_
#define CANLIBRARY_H_

#include <stdio.h>

class DriverStation;

/**
 * Handle input from Logitech Dual Action CanLibrary connected to the Driver
 * Station.
 */
class CanLibrary
{
public:
    typedef enum
    {
        kLeftXAxis, kLeftYAxis, kRightXAxis, kRightYAxis
    } AxisType;

    typedef enum
    {
        kCenter, kUp, kUpLeft, kLeft, kDownLeft, kDown, kDownRight, kRight,
        kUpRight
    } DPadDirection;

    CanLibrary(UINT32 port);
    ~CanLibrary();

    float GetLeftX();
    float GetLeftY();
    float GetRightX();
    float GetRightY();
    float GetAxis(AxisType axis);
    float GetRawAxis(UINT32 axis);

    bool GetNumberedButton(unsigned buttonNumber);
    bool GetLeftPush();
    bool GetRightPush();

    DPadDirection GetDPad();

protected:
    static const UINT32 kLeftXAxisNum = 1;
    static const UINT32 kLeftYAxisNum = 2;
    static const UINT32 kRightXAxisNum = 3;
    static const UINT32 kRightYAxisNum = 4;
    static const UINT32 kDPadXAxisNum = 5;
    static const UINT32 kDPadYAxisNum = 6;

    static const unsigned kLeftAnalogStickButton = 11;
    static const unsigned kRightAnalogStickButton = 12;

    DriverStation *ap_ds;
    UINT32 a_port;
};

#endif 

