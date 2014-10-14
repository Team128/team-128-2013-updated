#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
//initialize variables
	//Driverstation variables
		Joystick *m_leftStick;
		Joystick *m_rightStick;
		Joystick *m_gamepad;
		LiveWindow *lw;

	//Drivetrain motors
		Jaguar *m_leftFront;
		Jaguar *m_rightFront;
		Jaguar *m_leftBack;
		Jaguar *m_rightBack;

	//Pneumatics
		//Shifter
		Solenoid shiftUp;
		Solenoid shiftDown;

	RobotDrive *m_robotDrive;
	//Teleop Variables
		//timers
		Timer *lastShift; 	//timer to make sure shifters don't go off repeatedly

	//int and floats
		int shiftValue; 	//value of what gear robot is in


	void RobotInit()
	{
		//Define variables
			//Driverstation variables
			m_leftStick = new Joystick(0);
			m_rightStick = new Joystick(1);
			m_gamepad = new Joystick (2);
			lw = LiveWindow::GetInstance();

		//Drivetrain motors
			m_leftFront = new Jaguar(3);
			m_rightFront = new Jaguar(2);
			m_leftBack = new Jaguar(4);
			m_rightBack = new Jaguar(1);
			m_robotDrive = new RobotDrive(m_leftFront,m_rightFront,m_leftBack,m_rightBack);

		//teleop
			//timers
			lastShift = new Timer();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{
		lastShift->Start();
		shiftValue = 0; //Changes based on what gear robot is in. 0 = low gear, 1 = high gear
	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}

	//Teleop functions
	void TeleopDrive()
	{
		m_robotDrive->TankDrive(m_leftStick,m_rightStick);
	}
	void Shift()
	{
		if(m_leftStick->GetTrigger() == 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 0 && lastShift->Get() > 0.3  )
		{

		}
	}
};

START_ROBOT_CLASS(Robot);
