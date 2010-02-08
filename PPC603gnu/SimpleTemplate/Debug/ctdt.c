/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */


void _GLOBAL__I__Z20FRC_userClassFactoryv();

void _GLOBAL__I__ZN12ControlBoardC2Ev();

void _GLOBAL__I__ZN14AutoControllerC2EP10RobotDriveP4GyroP9CANJaguar();

void _GLOBAL__I__ZN3LogC2EPc();

void _GLOBAL__I__ZN6KickerC2Ev();

void _GLOBAL__I__ZN9ErrorBase16globalErrorMutexE();

void _GLOBAL__I__ZN9RobotBase10m_instanceE();

void _GLOBAL__I__ZN10Ultrasonic6m_taskE();

void _GLOBAL__I_AxisCamera_debugFlag();

extern void (*_ctors[])();
void (*_ctors[])() =
    {
    _GLOBAL__I__Z20FRC_userClassFactoryv,
    _GLOBAL__I__ZN12ControlBoardC2Ev,
    _GLOBAL__I__ZN14AutoControllerC2EP10RobotDriveP4GyroP9CANJaguar,
    _GLOBAL__I__ZN3LogC2EPc,
    _GLOBAL__I__ZN6KickerC2Ev,
    _GLOBAL__I__ZN9ErrorBase16globalErrorMutexE,
    _GLOBAL__I__ZN9RobotBase10m_instanceE,
    _GLOBAL__I__ZN10Ultrasonic6m_taskE,
    _GLOBAL__I_AxisCamera_debugFlag,
    0
    };

void _GLOBAL__D__Z20FRC_userClassFactoryv();

void _GLOBAL__D__ZN12ControlBoardC2Ev();

void _GLOBAL__D__ZN14AutoControllerC2EP10RobotDriveP4GyroP9CANJaguar();

void _GLOBAL__D__ZN6KickerC2Ev();

void _GLOBAL__D__ZN9ErrorBase16globalErrorMutexE();

void _GLOBAL__D__ZN9RobotBase10m_instanceE();

void _GLOBAL__D__ZN10Ultrasonic6m_taskE();

void _GLOBAL__D_AxisCamera_debugFlag();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _GLOBAL__D__Z20FRC_userClassFactoryv,
    _GLOBAL__D__ZN12ControlBoardC2Ev,
    _GLOBAL__D__ZN14AutoControllerC2EP10RobotDriveP4GyroP9CANJaguar,
    _GLOBAL__D__ZN6KickerC2Ev,
    _GLOBAL__D__ZN9ErrorBase16globalErrorMutexE,
    _GLOBAL__D__ZN9RobotBase10m_instanceE,
    _GLOBAL__D__ZN10Ultrasonic6m_taskE,
    _GLOBAL__D_AxisCamera_debugFlag,
    0
    };
