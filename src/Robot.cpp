#include "WPILib.h"
//#include "math.h"

class Robot: public IterativeRobot
{
	Talon *lDrive;
	Talon *rDrive;
	//RobotDrive *myRobot; // robot drive system
	Joystick *driveStick; // only joydriveStick
	Joystick *manipulatorStick;
	Talon *lifter; //bat
	Talon *lifter2;
	Talon *rake; //bird
	AnalogInput *sonic;
	//Talon rake; //fish
	//Talon motor; //kitty
	//LiveWindow *lw;
	//int autoLoopCounter;

	//bool btnVal = SmartDashboard::GetBoolean("DB/Button 1");

public:
	Robot() {
		Wait(1);
		lDrive = new Talon(2);
		rDrive = new Talon(0);
		//myRobot = new RobotDrive(lDrive,rDrive);	// these must be initialized in the same order
		driveStick = new Joystick(0);// as they are declared above.
		manipulatorStick = new Joystick(1);
		lifter = new Talon(3);
		lifter2 = new Talon(1);
		rake = new Talon(4);
		sonic = new AnalogInput(1);
		//rake(3),
		//motor(1),
		//lw = new LiveWindow(NULL);
		//autoLoopCounter()
		//myRobot->SetExpiration(2);
	}

private:


	double leftX = 0;
	double leftY = 0;
	double rightX = 0;
	double rightY = 0;
	double mLeftY = 0;
	double mRightY = 0;
	double leftTrigger = 0;
	double rightTrigger = 0;
	double threshold = 0.1;
	double cruise = 0;
	double rCruise = 0;
	/*bool pool = false;
	bool fool = false;
	bool tool = false;
	bool cool = false;
	bool spool = false;
	bool drool = false;
	bool cruel = false;
	bool yule = false;
	bool mule = false;*/
	void RobotInit() override
	{
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		//lw = LiveWindow::GetInstance();
		//SmartDashboard::PutString("DB/String 0", "Btn 0 sets container on totes");
	}

	void AutonomousInit()
	{
		//autoLoopCounter = 0;

		/*lDrive->Set(-.475);
		rDrive->Set(-.475);
		Wait(2.1);*
		rake->Set(0.575);
		lDrive->Set(0);
		rDrive->Set(0);
		Wait(1.8);
		rake->Set(-0.1);
		lDrive->Set(-0.225);
		rDrive->Set(0.225);
		//myRobot.Drive(0.25, 0.0);
		Wait(1.6);
		lDrive->Set(0);
		rDrive->Set(0);
		Wait(0.5);
		rake->Set(-0.3);
		Wait(0.5);
		lDrive->Set(-0.15);
		rDrive->Set(0.15);
		//myRobot.Drive(0.0, 0.0);
		Wait(0.5);
		lDrive->Set(0);
		rDrive->Set(0);
		rake->Set(-0.6);
		Wait(3.4);
		rake->Set(-0.3); // FOR CONTAINERS
		//rake->Set(0); // FOR NO CONTAINERS
		Wait(1);
		lDrive->Set(0.35);
		rDrive->Set(-0.35);
		//myRobot.Drive(-1.0, 0.0);
		Wait(3.25); // Testing Field
		//Wait(6); //Full Field
		lDrive->Set(0);
		rDrive->Set(0);
		//Wait(1);
		lDrive->Set(0.15);
		rDrive->Set(0.15);*//*
		rake->Set(-0.2);
		Wait(1);
		rDrive->Set(0);
		lDrive->Set(0);
		//myRobot.Drive(0.0, 0.0);
		//rake->Set(0.25);
		//Wait(1);
		//rake->Set(0);
		 * */
	}

	void AutonomousPeriodic()
	{
		/*if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}*/
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		leftX = driveStick->GetRawAxis(0);
		if(fabs(leftX) < threshold)
			leftX = 0;
		leftY = driveStick->GetRawAxis(1);
		if(fabs(leftY) < threshold)
			leftY = 0;
		mLeftY = manipulatorStick->GetRawAxis(1);
		if(fabs(mLeftY) < threshold)
			mLeftY = 0;
		rightX = driveStick->GetRawAxis(4);
		if(fabs(rightX) < threshold)
			rightX = 0;
		rightY = driveStick->GetRawAxis(5);
		if(fabs(rightY) < threshold)
			rightY = 0;
		mRightY = manipulatorStick->GetRawAxis(5);
		if(fabs(mRightY) < threshold)
			mRightY = 0;
		leftTrigger = (driveStick->GetRawAxis(2));
		if(fabs(leftTrigger) < (threshold))
			leftTrigger = 0;
		rightTrigger = (driveStick->GetRawAxis(3));
		if(fabs(rightTrigger) < (threshold))
			rightTrigger = 0;

		leftX = pow(leftX, 3.0);
		leftY = pow(leftY, 3.0);
		rightX = pow(rightX, 3.0);
		rightY = pow(rightY, 3.0);
		mRightY = pow(mRightY, 3.0);
		mLeftY = pow(mLeftY, 3.0);

		if(driveStick->GetRawButton(6)) {
			rake->Set(rightY/1.5);
			//rake->Set(0);
			if(fabs(mRightY > 0)) {
				lifter->Set((mRightY)/1.5);
				lifter2->Set((mRightY)/1.5);
			} else {
				lifter->Set(0);
				lifter2->Set(0);
			}
		} else if(manipulatorStick->GetRawButton(6)) {
			rake->Set(mRightY/1.5);
			/*if(driveStick->GetRawButton(2)) {
				rake->Set(1);
			} else {
				rake->Set(0);
			}*/
			lifter->Set((rightY)/1.5);
			lifter2->Set((rightY)/1.5);
		} else {
			rake->Set(0);
			if(fabs(mRightY) > 0) {
				lifter->Set((mRightY)/1.5);
				lifter2->Set((mRightY)/1.5);
			} else {
				lifter->Set((rightY)/1.5);
				lifter2->Set((rightY)/1.5);
			}
		} //squirrelly bracket

		//myRobot->ArcadeDrive((-leftY/1.1), ((-leftX/1.1) - (rightTrigger * leftY) + (leftTrigger * leftY))); // drive with arcade style (use correct driveStick)
		lDrive->Set(-((leftY - leftX) * (1-leftTrigger)));
		rDrive->Set((leftY + leftX) * (1-rightTrigger));
		//lDrive->Set(-(leftY - (leftX + leftTrigger*leftY)));
		//rDrive->Set(leftY + (leftX - rightTrigger*leftY));
			//lifter2.Set((rightY + cruise)/1.1);

		/*if(driveStick->GetRawButton(4)) {
			rake->Set(0.4);
		} else if(driveStick->GetRawButton(1)) {
			rake->Set(-0.4);
		} else {
			rake->Set(0);
		}*/

		if(driveStick->GetRawButton(5)) {
			cruise = rightY;
		}
		if(driveStick->GetRawButton(10)) {
			cruise = 0;
		}
		if(driveStick->GetRawButton(9)) {
			rCruise = rightY;
		}

		//SmartDashboard::PutNumber("DB/Slider 0", sonic->GetValue());

		/*if(sonic->GetValue() > 10) {
			SmartDashboard::PutBoolean("DB/LED 0", true);
		} else {
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}*/

		/*if(manipulatorStick->GetRawButton(3)) {
			CameraServer::GetInstance()->StartAutomaticCapture("cam1"); //random numbers and letters.
		}
		if(manipulatorStick->GetRawButton(2)) {
			CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		}*/
	}

	void TestInit()
	{
		lDrive->Set(1);
		Wait(1);
		lDrive->Set(0);
		rake->Set(1);
		Wait(1);
		rake->Set(-1);
		Wait(1);
		rake->Set(0);
	}

	void TestPeriodic()
	{
		//lw->Run();
	}

	void DisabledPeriodic()
	{

	}

};

START_ROBOT_CLASS(Robot);
