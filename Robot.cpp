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



	void RobotInit()
	{
		//Define variables
		m_leftStick = new Joystick(0);
		m_rightStick = new Joystick(1);
		m_gamepad = new Joystick (2);
		lw = LiveWindow::GetInstance();

		m_leftFront = new Jaguar(3);
		m_rightFront = new Jaguar(2);
		m_leftBack = new Jaguar(4);
		m_rightBack = new Jaguar(1);
		m_robotDrive = new RobotDrive(m_leftFront,m_rightFront,m_leftBack,m_rightBack);
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
