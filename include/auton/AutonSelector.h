/*
 * AutonSelector.h
 *
 *  Created on: Jan 20, 2018
 *      Author: The Realest of Authors and Magic Mike Wazowski, creator of bad code, and destroyer of minds.
 *      Copy-and-Paster-and-Converter-To-2018-Guy: jonah
 */

#ifndef SRC_AUTON_AUTONSELECTOR_H_
#define SRC_AUTON_AUTONSELECTOR_H_

#include <string>
#include <vector>
#include <frc/SmartDashboard/SendableChooser.h>
#include <auton/FMS.h>

class AutonSelector
{
	public:


		enum AUTON_POSITION
		{
			LEFT_HAB_L1,
			LEFT_HAB_L2,
			CENTER_HAB_L1,
			RIGHT_HAB_L1,
			RIGHT_HAB_L2
		};

		enum AUTON_OPTION
		{
			CROSS_LINE,
			CARGO_LEFT_FRONT,
			CARGO_RIGHT_FRONT,
			ROCKET_LEFT_LOW,
			ROCKET_LEFT_MED,
			ROCKET_LEFT_HIGH,
			ROCKET_RIGHT_LOW,
			ROCKET_RIGHT_MED,
			ROCKET_RIGHT_HIGH
		};
		//---------------------------------------------------------------------
		// Method: 		<<constructor>>
		// Description: This creates this object and reads the auto script (CSV)
		//  			files and displays a list on the dashboard.
		//---------------------------------------------------------------------
		AutonSelector();

		//---------------------------------------------------------------------
		// Method: 		<<destructor>>
		// Description: default cleanup
		//---------------------------------------------------------------------
		virtual ~AutonSelector() = default;

		//---------------------------------------------------------------------
		// Method: 		GetSelectedAutoFile
		// Description: This returns the selected auton file to run.  If it
		//  			returns "Do Nothing", it is indicating no auton should
		//				be run.
		// Returns:		std::string			auton file to run
		//---------------------------------------------------------------------
		std::string GetSelectedAutoFile();

	private:

		enum HATCH_POSITION
		{
			RLOW,
			RMID,
			RHIGH,
			CFRONT,
			CFIRST,
			CSECOND,
			CTHIRD
		};


		//---------------------------------------------------------------------
		// Method: 		GetCrossLineFile
		// Description: This determines which Cross line file to run based on starting
		//				position and FMS feedback
		// Returns:		std::string		filename to run
		//---------------------------------------------------------------------
        std::string GetCrossLineFile
        (
			AutonSelector::AUTON_POSITION pos		// <I> - 
        );

        //---------------------------------------------------------------------
        // Method: 		GetLeftCargoFile
        // Description: This determines which Left Cargo Ship file to run based on starting
        //				position 
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetLeftCargoFile
        (
            AutonSelector::AUTON_POSITION pos,	// <I> - starting position
			AutonSelector::HATCH_POSITION loc   // <I> - placing location
        );

        //---------------------------------------------------------------------
        // Method: 		GetRightCargoFile
        // Description: This determines which Right Cargo Ship file to run based on starting
        //				position 
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetRightCargoFile
        (
            AutonSelector::AUTON_POSITION pos,	// <I> - starting position
			AutonSelector::HATCH_POSITION loc   // <I> - placing location
        );

        //---------------------------------------------------------------------
        // Method: 		GetLeftRocketFile
        // Description: This determines which Left Rocket file to run based on starting
        //				position
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetLeftRocketFile
        (
            AutonSelector::AUTON_POSITION pos,	// <I> - starting position
			AutonSelector::HATCH_POSITION loc   // <I> - placing location
        );
		
        //---------------------------------------------------------------------
        // Method: 		GetRightRocketFile
        // Description: This determines which Right Rocket file to run based on starting
        //				position
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetRightRocketFile
        (
            AutonSelector::AUTON_POSITION pos,	// <I> - starting position
			AutonSelector::HATCH_POSITION loc   // <I> - placing location
        );

		//---------------------------------------------------------------------
		// Method: 		FindXMLFileNames
		// Description: This builds up a list of XML files in the directory and
		//				stores them in the attributes.
		// Returns:		void
			//---------------------------------------------------------------------
		void FindXMLFileNames();

		//---------------------------------------------------------------------
		// Method: 		PutChoicesOnDashboard
		// Description: This puts the list of files in the m_csvFiles attribute
		//				up on the dashboard for selection.
		// Returns:		void
		//---------------------------------------------------------------------
		void PutChoicesOnDashboard();

		//---------------------------------------------------------------------
		// Method: 		GetRobotStartPosition
		// Description: Read the starting position from the smart dashboard
		// Returns:		AutonSelector::AUTON_POSITION		starting position
		//---------------------------------------------------------------------
		AUTON_POSITION GetRobotStartPosition();

		//---------------------------------------------------------------------
		// Method: 		GetDesiredOption
		// Description: Read the desired behavior from the smart dashboard
		// Returns:		AutonSelector::AUTON_OPTION		desired behavior
		//---------------------------------------------------------------------
		AUTON_OPTION GetDesiredOption();


		// Attributes
		std::vector<std::string> m_leftL1XMLFiles;
		std::vector<std::string> m_leftL2XMLFiles;
		std::vector<std::string> m_centerXMLFiles;
		std::vector<std::string> m_rightL1XMLFiles;
		std::vector<std::string> m_rightL2XMLFiles;


		// 16 character limits to avoid some smartdashboard issues
		const std::string CROSS_AUTON_LINE_STR = "Auto Line";
		const std::string HATCH_CARGO_FRONT_LEFT_STR = "Cargo Left";
		const std::string HATCH_CARGO_FRONT_RIGHT_STR = "Cargo Right";
		const std::string ROCKET_LEFT_LOW_STR = "LeftRocket Low";
		const std::string ROCKET_LEFT_MID_STR = "LeftRocket Mid";
		const std::string ROCKET_LEFT_HIGH_STR = "LeftRocket Top";
		const std::string ROCKET_RIGHT_LOW_STR = "RightRocket Low";
		const std::string ROCKET_RIGHT_MID_STR = "RightRocket Mid";
		const std::string ROCKET_RIGHT_HIGH_STR = "RightRocket Top";
		frc::SendableChooser<std::string> m_chooserOptions;


		const std::string LEFT_HAB_L1_STR = "LeftHAB_L1";
		const std::string LEFT_HAB_L2_STR = "LeftHAB_L2";
		const std::string CENTER_HAB_L1_STR = "Center_L1";
		const std::string RIGHT_HAB_L1_STR = "RightHAB_L1";
		const std::string RIGHT_HAB_L2_STR = "RightHAB_L2";
		frc::SendableChooser<std::string> m_chooserPosition;

		frc::SendableChooser<std::string> m_chooser;
		frc::SendableChooser<std::string> m_chooserLeftHABL1;
		frc::SendableChooser<std::string> m_chooserLeftHABL2;
		frc::SendableChooser<std::string> m_chooserCenter;
		frc::SendableChooser<std::string> m_chooserRightHABL1;
		frc::SendableChooser<std::string> m_chooserRightHABL2;

		const std::string m_autonDir = "/home/lvuser/auton/";
		const std::string m_defaultFile = "CrossAutonLine.xml";
		std::string 	  m_autonPositionModifier;
		std::string 	  m_autonOption;


        const std::string XML = ".xml";
        const std::string DTD = ".dtd";

		const std::string CROSS_AUTON_LINE = "Cross Auton Line";
};

#endif /* SRC_AUTON_AUTONSELECTOR_H_ */
