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

	//Motors
		//Drivetrain
		Jaguar *m_leftFront;
		Jaguar *m_rightFront;
		Jaguar *m_leftBack;
		Jaguar *m_rightBack;
		RobotDrive *m_robotDrive;
		//Shooter
		Talon *m_shooter;

	//Pneumatics
		//compressor
		Compressor *m_compressor;
		//Shifter
		Solenoid *m_shifterUp;
		Solenoid *m_shifterDown;
		//Pusher
		Solenoid *m_pusher;
		Solenoid *m_pusher2;
		//TheBar
		Solenoid *m_TheBarUp;
		Solenoid *m_TheBarDown;

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

		//Motors
			//Drivetrain
			m_leftFront = new Jaguar(2);
			m_rightFront = new Jaguar(1);
			m_leftBack = new Jaguar(3);
			m_rightBack = new Jaguar(0);
			m_robotDrive = new RobotDrive(m_leftFront,m_leftBack,m_rightFront,m_rightBack);
			//Shooter
			m_shooter = new Talon(4);

		//Pneumatics
			//compressor
			m_compressor = new Compressor(0);
			//shifter
			m_shifterUp = new Solenoid(2);
			m_shifterDown = new Solenoid(3);
			//Pusher
			m_pusher = new Solenoid(0);
			m_pusher2 = new Solenoid(1);
			//TheBar
			m_TheBarUp = new Solenoid(4);
			m_TheBarDown = new Solenoid()
		//teleop
			//timers
			lastShift = new Timer();
		m_compressor->SetClosedLoopControl(true);
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
		Pusher();
		Shooter();
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
			printf("Shifter up set to true \n");

		}
		else if(m_leftStick->GetTrigger() == 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 1 && lastShift->Get() > 0.3)
		{
			m_shifterUp->Set(false);
			m_shifterDown->Set(true);
			shiftValue = 0;
			lastShift->Reset();
			printf("Shifter down set true");
		}
	}
	void Pusher()
	{
		if(m_gamepad->GetRawButton(1))
		{
			m_pusher->Set(true);
			m_pusher2->Set(false);
		}
		else if(m_gamepad->GetRawButton(2))
		{
			m_pusher->Set(false);
			m_pusher2->Set(true);
		}
	}
	void Shooter()
	{
		if(m_gamepad->GetRawButton(7))
		{
			m_shooter->Set(0.70);
		}
		else if(m_gamepad->GetRawButton(8))
		{
			m_shooter->Set(1.0);
		}
	}
	void TheBar()
	{
		if(m_gamepad->GetRawButton(10))
		{
			m_TheBarUp->Set(true);
			m_TheBarDown->Set(false);
		}
		else if(m_gamepad->GetRawButton(9))
		{
			m_TheBarUp->Set(false);
			m_TheBarDown->Set(true);
		}
	}
};

START_ROBOT_CLASS(Robot);
