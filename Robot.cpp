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
		RobotDrive *m_robotDrive;

	//Pneumatics
		//Shifter
		Solenoid *m_shifterUp;
		Solenoid *m_shifterDown;

	//Teleop Variables
		//timers
		Timer *lastShift; 	//timer to make sure shifters don't go off repeatedly

	//int and floats
		int shiftValue; 	//value of what gear robot is in
		float leftStickValue;
		float rightStickValue;


	void RobotInit()
	{
		//Define variables
			//Driverstation variables
			m_leftStick = new Joystick(0);
			m_rightStick = new Joystick(1);
			m_gamepad = new Joystick (2);
			lw = LiveWindow::GetInstance();

		//Drivetrain motors
			m_leftFront = new Jaguar(2);
			m_rightFront = new Jaguar(1);
			m_leftBack = new Jaguar(3);
			m_rightBack = new Jaguar(0);
			m_robotDrive = new RobotDrive(m_leftFront,m_leftBack,m_rightFront,m_rightBack);
		//Shifter pneumatics
			m_shifterUp = new Solenoid(2);
			m_shifterDown = new Solenoid(3);
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
		TeleopDrive();
		Shift();
	}

	void TestPeriodic()
	{
		lw->Run();
	}

	//Teleop functions
	void TeleopDrive()
	{

		leftStickValue = m_leftStick->GetY();
		rightStickValue = m_rightStick->GetY();
		m_robotDrive->TankDrive(leftStickValue, rightStickValue);
	}
	void Shift()
	{
		if(m_leftStick->GetTrigger() == 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 0 && lastShift->Get() > 0.3  )
		{
			m_shifterUp->Set(true);
			m_shifterDown->Set(false);
			shiftValue = 1;
			lastShift->Reset();
			printf("Shifter up set to true");
		}
		else if(m_leftStick->GetTrigger() == 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 0 && lastShift->Get() > 0.3)
		{
			m_shifterUp->Set(false);
			m_shifterDown->Set(true);
			shiftValue = 0;
			lastShift->Reset();
			printf("Shifter down set true");
		}
	}
};

START_ROBOT_CLASS(Robot);
