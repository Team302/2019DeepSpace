/*
 * AutonSelector.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */
//Includes
#include <string>
#include <vector>
#include <dirent.h>

#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>

//Team302 includes
#include <auton/AutonSelector.h>
#include <auton/FMS.h>

//---------------------------------------------------------------------
// Method: 		<<constructor>>
// Description: This creates this object and reads the auto script (CSV)
//  			files and displays a list on the dashboard.
//---------------------------------------------------------------------
AutonSelector::AutonSelector() : m_leftL1XMLFiles(),
								 m_leftL2XMLFiles(),
								 m_centerXMLFiles(),
								 m_rightL1XMLFiles(),
								 m_rightL2XMLFiles(),
								 m_chooserOptions(),
								 m_chooserPosition(),
								 m_chooserLeftHABL1(),
								 m_chooserLeftHABL2(),
								 m_chooserCenter(),
								 m_chooserRightHABL1(),
								 m_chooserRightHABL2(),
								 m_autonPositionModifier( "" ),
								 m_autonOption( "CrossAutonLine.xml")
{
	FindXMLFileNames();
	PutChoicesOnDashboard();
}

//---------------------------------------------------------------------
// Method: 		GetSelectedAutoFile
// Description: This returns the selected auton file to run.  If it
//  			returns "Do Nothing", it is indicating no auton should
//				be run.
// Returns:		std::string			auton file to run
//---------------------------------------------------------------------
std::string AutonSelector::GetSelectedAutoFile()
{
	// initialize output
	std::string autonFile;

	m_autonPositionModifier.clear();

	bool hasError = false;

	// Get Starting Location and strategy
	AutonSelector::AUTON_POSITION  position = GetRobotStartPosition();

	// Handle the strategy
	AutonSelector::AUTON_OPTION strategy = GetDesiredOption();

	switch ( strategy )
	{
		  case AutonSelector::AUTON_OPTION::CROSS_LINE:
			  autonFile = GetCrossLineFile( position );
			  break;

		  case AutonSelector::AUTON_OPTION::CARGO_LEFT_FRONT:
			  autonFile = GetLeftCargoFile( position, AutonSelector::HATCH_POSITION::CFRONT );
			  break;

		  case AutonSelector::AUTON_OPTION::CARGO_RIGHT_FRONT:
			  autonFile = GetRightCargoFile( position, AutonSelector::HATCH_POSITION::CFRONT );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_LEFT_LOW:
			  autonFile = GetLeftRocketFile( position, AutonSelector::HATCH_POSITION::RLOW );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_LEFT_MED:
			  autonFile = GetLeftRocketFile( position, AutonSelector::HATCH_POSITION::RMID );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_LEFT_HIGH:
			  autonFile = GetLeftRocketFile( position, AutonSelector::HATCH_POSITION::RHIGH );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_RIGHT_LOW:
			  autonFile = GetRightRocketFile( position, AutonSelector::HATCH_POSITION::RLOW );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_RIGHT_MED:
			  autonFile = GetRightRocketFile( position, AutonSelector::HATCH_POSITION::RMID );
			  break;

		  case AutonSelector::AUTON_OPTION::ROCKET_RIGHT_HIGH:
			  autonFile = GetRightRocketFile( position, AutonSelector::HATCH_POSITION::RHIGH );
			  break;

		  default:
			  hasError = true;
			  printf( "==>> AutonSelector::GetSelectedAutoFile ... invalid strategy specified \n" );
			  break;
	}

	if ( hasError )
	{
		autonFile = GetCrossLineFile( position );
	}
	autonFile = m_autonDir + autonFile;

	frc::SmartDashboard::PutString("Auton file var", autonFile);

	return autonFile;
}


//---------------------------------------------------------------------
// Method: 		GetCrossLineFile
// Description: This determines which Cross line file to run based on starting
//				position and FMS feedback
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetCrossLineFile
(
	AutonSelector::AUTON_POSITION pos		// <I> - 
)
{
	std::string file;
	switch ( pos )
	{
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L1:
		case AutonSelector::AUTON_POSITION::CENTER_HAB_L1:
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name for Level 1 
			break;
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L2:
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name for Level 2
			break;
		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid position %d \n", pos );
			file = "CrossAutonLine.xml";
			break;
	}
	return file;
}


//---------------------------------------------------------------------
// Method: 		GetLeftCargoFile
// Description: This determines which Left Cargo Ship file to run based on starting
//				position 
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetLeftCargoFile
(
	AutonSelector::AUTON_POSITION pos,	// <I> - starting position
	AutonSelector::HATCH_POSITION loc   // <I> - placing location
)
{
	std::string file;
	switch ( pos )
	{
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::CENTER_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid position %d \n", pos );
			file = "CrossAutonLine.xml";
			break;
	}
	return file;
}

//---------------------------------------------------------------------
// Method: 		GetRightCargoFile
// Description: This determines which Right Cargo Ship file to run based on starting
//				position 
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetRightCargoFile
(
	AutonSelector::AUTON_POSITION pos,	// <I> - starting position
	AutonSelector::HATCH_POSITION loc   // <I> - placing location
)
{
	std::string file;
	switch ( pos )
	{
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::CENTER_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid position %d \n", pos );
			file = "CrossAutonLine.xml";
			break;
	}
	return file;
}

//---------------------------------------------------------------------
// Method: 		GetLeftRocketFile
// Description: This determines which Left Rocket file to run based on starting
//				position
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetLeftRocketFile
(
	AutonSelector::AUTON_POSITION pos,	// <I> - starting position
	AutonSelector::HATCH_POSITION loc   // <I> - placing location
)
{
	std::string file;
	switch ( pos )
	{
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::CENTER_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid position %d \n", pos );
			file = "CrossAutonLine.xml";
			break;
	}
	return file;
}

//---------------------------------------------------------------------
// Method: 		GetRightRocketFile
// Description: This determines which Right Rocket file to run based on starting
//				position
// Returns:		std::string		filename to run
//---------------------------------------------------------------------
std::string AutonSelector::GetRightRocketFile
(
	AutonSelector::AUTON_POSITION pos,	// <I> - starting position
	AutonSelector::HATCH_POSITION loc   // <I> - placing location
)
{
	std::string file;
	switch ( pos )
	{
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::LEFT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::CENTER_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L1:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		case AutonSelector::AUTON_POSITION::RIGHT_HAB_L2:
			file = "CrossAutonLine.xml";		// TODO:: need file name
			break;
		default:
			printf( "==>> AutonSelector::GetCrossLineFile ... invalid position %d \n", pos );
			file = "CrossAutonLine.xml";
			break;
	}	
	return file;
}


//---------------------------------------------------------------------
// Method: 		GetRobotStartPosition
// Description: Read the starting position from the smart dashboard
// Returns:		AutonSelector::AUTON_POSITION		starting position
//---------------------------------------------------------------------
AutonSelector::AUTON_POSITION AutonSelector::GetRobotStartPosition()
{
	AutonSelector::AUTON_POSITION position = AutonSelector::AUTON_POSITION::LEFT_HAB_L1;

	auto selection = m_chooserPosition.GetSelected();
	if ( selection.compare( LEFT_HAB_L1_STR ) == 0 )
	{
		position = AutonSelector::AUTON_POSITION::LEFT_HAB_L1;
	}
	else if ( selection.compare( LEFT_HAB_L2_STR ) == 0  )
	{
		position = AutonSelector::AUTON_POSITION::LEFT_HAB_L2;
	}
	else if ( selection.compare( RIGHT_HAB_L1_STR ) == 0  )
	{
		position = AutonSelector::AUTON_POSITION::RIGHT_HAB_L1;
	}
	else if ( selection.compare( RIGHT_HAB_L2_STR ) == 0  )
	{
		position = AutonSelector::AUTON_POSITION::RIGHT_HAB_L2;
	}
	else
	{
		position = AutonSelector::AUTON_POSITION::CENTER_HAB_L1;
	}
	return position;
}

//---------------------------------------------------------------------
// Method: 		GetDesiredOption
// Description: Read the desired behavior from the smart dashboard
// Returns:		AutonSelector::AUTON_OPTION		desired behavior
//---------------------------------------------------------------------
AutonSelector::AUTON_OPTION AutonSelector::GetDesiredOption()
{
	AutonSelector::AUTON_OPTION option = AutonSelector::AUTON_OPTION::CROSS_LINE;

	std::string selection = m_chooserOptions.GetSelected();
	frc::SmartDashboard::PutString("selected auton: ", selection);
	if ( selection.compare( CROSS_AUTON_LINE_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::CROSS_LINE;
	}
	else if ( selection.compare( HATCH_CARGO_FRONT_LEFT_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::CARGO_LEFT_FRONT;
	}
	else if ( selection.compare( HATCH_CARGO_FRONT_RIGHT_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::CARGO_RIGHT_FRONT;
	}	
	else if ( selection.compare( ROCKET_LEFT_LOW_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_LEFT_LOW;
	}	
	else if ( selection.compare( ROCKET_LEFT_MID_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_LEFT_MED;
	}	
	else if ( selection.compare( ROCKET_LEFT_HIGH_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_LEFT_HIGH;
	}
	else if ( selection.compare( ROCKET_RIGHT_LOW_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_RIGHT_LOW;
	}	
	else if ( selection.compare( ROCKET_RIGHT_MID_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_RIGHT_MED;
	}	
	else if ( selection.compare( ROCKET_RIGHT_HIGH_STR ) == 0 )
	{
		option = AutonSelector::AUTON_OPTION::ROCKET_RIGHT_HIGH;
	}
	else
	{
		option = AutonSelector::AUTON_OPTION::CROSS_LINE;
	}

	return option;
}



//---------------------------------------------------------------------
// Method: 		FindXMLFileNames
// Description: This builds up a list of XML files in the directory and
//				stores them in the attributes.
// Returns:		void
//---------------------------------------------------------------------
void AutonSelector::FindXMLFileNames()
{
	DIR* directory;
	struct dirent* files;

	directory = opendir("/home/lvuser/auton/");
	if (directory != nullptr)
	{
		bool moreFiles = true;
		while (moreFiles)
		{
			files = readdir(directory);
			if (files == nullptr)
			{
				moreFiles = false;
				break;
			}

			std::string fileName = std::string( files->d_name );

			// skip the current directory and parent directory filenames
			if ( fileName.compare( "." ) )
			{
				continue;
			}
			if ( fileName.compare( ".." ) )
			{
				continue;
			}

			auto foundPos = fileName.find( XML );
			if ( foundPos != std::string::npos )		// has xml extension
			{
				foundPos = fileName.find( LEFT_HAB_L1_STR );
				if ( foundPos != std::string::npos )
				{
					m_leftL1XMLFiles.emplace_back( fileName );
				}
				else
				{
					foundPos = fileName.find( LEFT_HAB_L2_STR );
					if ( foundPos != std::string::npos )
					{
						m_leftL2XMLFiles.emplace_back( fileName );
					}
					else
					{
						foundPos = fileName.find( RIGHT_HAB_L1_STR );
						if ( foundPos != std::string::npos )
						{
							m_rightL1XMLFiles.emplace_back( fileName );
						}
						else
						{
							foundPos = fileName.find( RIGHT_HAB_L2_STR );
							if ( foundPos != std::string::npos )
							{
								m_rightL2XMLFiles.emplace_back( fileName );
							}
							else
							{
								foundPos = fileName.find( CENTER_HAB_L1_STR );
								if ( foundPos != std::string::npos )
								{
									m_centerXMLFiles.emplace_back( fileName );
								}
							}
						}
					}
				}
			}
			else
			{
				// skip dtd files
				foundPos = fileName.find( DTD );
				if ( foundPos != std::string::npos )
				{
					continue;
				}

				// else invalid file name
				printf( "==>> invalid auton file %s \n", fileName.c_str() );
			}
		}
	}
	else
	{
		printf( "==>> auton directory not found \n" );
	}
}

//---------------------------------------------------------------------
// Method: 		PutChoicesOnDashboard
// Description: This puts the list of files in the m_csvFiles attribute
//				up on the dashboard for selection.
// Returns:		void
//---------------------------------------------------------------------
void AutonSelector::PutChoicesOnDashboard()
{
	// Where is the robot located
	m_chooserPosition.SetDefaultOption( LEFT_HAB_L1_STR, LEFT_HAB_L1_STR );
	m_chooserPosition.AddOption( LEFT_HAB_L2_STR, LEFT_HAB_L2_STR );
	m_chooserPosition.AddOption( CENTER_HAB_L1_STR, CENTER_HAB_L1_STR );
	m_chooserPosition.AddOption( RIGHT_HAB_L1_STR, RIGHT_HAB_L1_STR );
	m_chooserPosition.AddOption( RIGHT_HAB_L2_STR, RIGHT_HAB_L2_STR );
	frc::SmartDashboard::PutData( "Auton: Robot Start Position", &m_chooserPosition );

	// What is our desired action
	m_chooserOptions.SetDefaultOption( CROSS_AUTON_LINE_STR, CROSS_AUTON_LINE_STR );
	m_chooserOptions.AddOption( HATCH_CARGO_FRONT_LEFT_STR, HATCH_CARGO_FRONT_LEFT_STR );
	m_chooserOptions.AddOption( HATCH_CARGO_FRONT_RIGHT_STR, HATCH_CARGO_FRONT_RIGHT_STR );
	m_chooserOptions.AddOption( ROCKET_LEFT_LOW_STR, ROCKET_LEFT_LOW_STR );
	m_chooserOptions.AddOption( ROCKET_LEFT_MID_STR, ROCKET_LEFT_MID_STR );
	m_chooserOptions.AddOption( ROCKET_LEFT_HIGH_STR, ROCKET_LEFT_HIGH_STR );
	m_chooserOptions.AddOption( ROCKET_RIGHT_LOW_STR, ROCKET_RIGHT_LOW_STR );
	m_chooserOptions.AddOption( ROCKET_RIGHT_MID_STR, ROCKET_RIGHT_MID_STR );
	m_chooserOptions.AddOption( ROCKET_RIGHT_HIGH_STR, ROCKET_RIGHT_HIGH_STR );
	frc::SmartDashboard::PutData( "Auton: Strategy Option", &m_chooserOptions );
}
