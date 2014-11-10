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

		BuiltInAccelerometer *accl;
		SmartDashboard *smart;
	//Teleop Variables
		//timers
		Timer *lastShift; 	//timer to make sure shifters don't go off repeatedly
		Timer *autonTimer;

	//int and floats
		int shiftValue; 	//value of what gear robot is in
		int AutonSwitch;
		int autoCounter;
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
			m_TheBarDown = new Solenoid(5);
		//teleop
			//timers
			lastShift = new Timer();
			autonTimer = new Timer();
			smart = new SmartDashboard();
			accl = new BuiltInAccelerometer();
		m_compressor->SetClosedLoopControl(true);
	}

	void AutonomousInit()
	{
		AutonSwitch = 0;
		autoCounter = 0;
		autonTimer->Start();

	}

	void AutonomousPeriodic()
	{
		AutonQuickShootAndDrive();
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
		TheBar();
		SmartDashboard();
	}

	void TestPeriodic()
	{
		lw->Run();
		Pusher();

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
			m_shooter->Set(0.0);
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
	//Auto functions
	void AutonQuickShootAndDrive()
	{
		switch(AutonSwitch)
		{
		case 0:
			printf("ON step zero \n");
			m_shooter->Set(1.0);
			if(autonTimer->Get() >= 0.75)
			{
				autonTimer->Reset();
				AutonSwitch = 1;
			}
			break;
		case 1:
			printf("ON step one \n");
			m_shooter->Set(0.75);
			if(autonTimer->Get() >= 1.0)
			{
				autonTimer->Reset();
				AutonSwitch = 2;
			}
			break;
		case 2:
			printf("ON step two \n");
			if(autoCounter <= 2)
			{
				m_pusher->Set(false);
				m_pusher2->Set(true);
				autonTimer->Reset();
				autoCounter++;
				AutonSwitch = 3;
			}

			{
				AutonSwitch = 6;
			}
			break;
		case 3:
			printf("ON step three \n");
			if(autonTimer->Get() >= 0.2)
			{
				m_pusher->Set(true);
				m_pusher2->Set(false);
				m_shooter->Set(1.0);
				autonTimer->Reset();
				AutonSwitch = 4;
			}
			break;
		case 4:
			printf("ON step four \n");
			if(autonTimer->Get() >= 0.28)
			{
				m_shooter->Set(0.70);
				autonTimer->Reset();
				AutonSwitch = 5;
			}
			break;
		case 5:
			printf("ON step five \n");
			if(autonTimer->Get() >= 0.28)
			{
				AutonSwitch = 2;
			}
			break;
		case 6:
			printf("ON step six \n");
			m_shooter->Set(0.0);
			m_robotDrive->Drive(-0.8,0.0);
			autonTimer->Reset();
			AutonSwitch = 7;
			break;
		case 7:
			printf("ON step seven \n");
			if(autonTimer->Get() >= 1.5)
			{
				m_robotDrive->Drive(0.0,0.0);
			}
			break;
		}
	}
void SmartDashboard()
{
	smart->PutNumber("Accel X-Axis", accl->GetX());
	smart->PutNumber("Accel Y-Axis", accl->GetY());
	smart->PutNumber("Accel Z-Axis", accl->GetZ());
}


};

START_ROBOT_CLASS(Robot);
