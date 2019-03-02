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
			LEFT_CORNER,
			CENTER,
			RIGHT_CORNER
		};

		enum AUTON_OPTION
		{
			CROSS_LINE,
			SWITCH,
			SCALE,
			SWITCH_SCALE,
			SCALE_ONE_CUBE_BACKUP,
			SMART
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

		enum FIELD_STATE
		{
            LEFTSWITCH_LEFTSCALE_LEFT = 0,
            RIGHTSWITCH_LEFTSCALE_LEFT = 1,
            LEFTSWITCH_RIGHTSCALE_LEFT = 10,
            RIGHTSWITCH_RIGHTSCALE_LEFT = 11,
            LEFTSWITCH_LEFTSCALE_CENTER = 100,
            RIGHTSWITCH_LEFTSCALE_CENTER = 101,
            LEFTSWITCH_RIGHTSCALE_CENTER = 110,
            RIGHTSWITCH_RIGHTSCALE_CENTER = 111,
            LEFTSWITCH_LEFTSCALE_RIGHT = 200,
            RIGHTSWITCH_LEFTSCALE_RIGHT = 201,
            LEFTSWITCH_RIGHTSCALE_RIGHT = 210,
            RIGHTSWITCH_RIGHTSCALE_RIGHT =211,
		};

		//---------------------------------------------------------------------
		// Method: 		GetCrossLineFile
		// Description: This determines which Cross line file to run based on starting
		//				position and FMS feedback
		// Returns:		std::string		filename to run
		//---------------------------------------------------------------------
        std::string GetCrossLineFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetSwitchFile
        // Description: This determines which Switch file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetSwitchFile
        (
            int state		// <I> - FIELD_STATE enum value
        );

        //---------------------------------------------------------------------
        // Method: 		GetScaleFile
        // Description: This determines which Scale file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetScaleFile
        (
            int state		// <I> - FIELD_STATE enum value
        );


        //---------------------------------------------------------------------
        // Method: 		GetSwitchScaleFile
        // Description: This determines which Switch/Scale file to run based on starting
        //				position and FMS feedback
        // Returns:		std::string		filename to run
        //---------------------------------------------------------------------
        std::string GetSwitchScaleFile
        (
            int state		// <I> - FIELD_STATE enum value
        );


        //does what the other ones do :)
        std::string GetScaleBackUpFile
		(
			int state		// <I> - FIELD_STATE enum value
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


		bool ProcessSmartOptions
		(
			AUTON_POSITION		startPosition,				// <I> - robot starting position
			FMS::POS			fmsSwitch,					// <I> - FMS setting for our switch
			FMS::POS			fmsScale					// <I> - FMS setting for the scale
		);

		// Attributes
		std::vector<std::string> m_leftXMLFiles;
		std::vector<std::string> m_centerXMLFiles;
		std::vector<std::string> m_rightXMLFiles;


		// 16 character limits to avoid some smartdashboard issues
		const std::string CROSS_AUTON_LINE_STR = "Auto Line";
		const std::string PLACE_IN_SWITCH_STR = "Switch";
		const std::string PLACE_ON_SCALE_STR = "Scale";
		const std::string PLACE_ON_SWITCH_SCALE_STR = "ScaleNoCross";
//        const std::string PLACE_ON_SCALE_BACK_UP_STR = "Scale One Cube Back Up";
        const std::string PLACE_ON_SCALE_BACK_UP_STR = "Scale+Back Up";
		const std::string SMART_AUTON_STR = "Smart Auto";
		frc::SendableChooser<std::string> m_chooserOptions;


		const std::string LEFT_CORNER_STR = "LeftCorner";
		const std::string LEFT_INSIDE_STR = "LeftInside";
		const std::string CENTER_STR = "Center";
		const std::string RIGHT_INSIDE_STR = "RightInside";
		const std::string RIGHT_CORNER_STR = "RightCorner";
		frc::SendableChooser<std::string> m_chooserPosition;

		const std::string PARTNER_IN_MIDDLE_STR = "Partner in Middle can get switch";
		const std::string PARTNER_GET_THEIR_SIDE_SWITCH_STR = "Partner can get switch on their side";
		const std::string PARTNER_GET_THEIR_SIDE_SCALE_STR = "Partner can get scale on their side";
		const std::string PARTNERS_ONLY_MOVE = "Partners only cross auton line";
		const std::string PARTNERS_DO_NOT_MOVE = "Partners do not move";
		frc::SendableChooser<std::string> m_chooserPartners;

		frc::SendableChooser<std::string> m_chooser;
		frc::SendableChooser<std::string> m_chooserLeft;
		frc::SendableChooser<std::string> m_chooserCenter;
		frc::SendableChooser<std::string> m_chooserRight;

		const std::string m_autonDir = "/home/lvuser/auton/";
		const std::string m_defaultFile = "CrossAutonLine.xml";
		std::string 	  m_autonPositionModifier;
		std::string 	  m_autonOption;


        const std::string XML = ".xml";
        const std::string DTD = ".dtd";

		const std::string CROSS_AUTON_LINE = "Cross Auton Line";
};

#endif /* SRC_AUTON_AUTONSELECTOR_H_ */
