/*
 *DragonTalonTach.h
 */

#ifndef SRC_MAIN_INCLUDE_HW_DRAGONTALONTACH_H_
#define SRC_MAIN_INCLUDE_HW_DRAGONTALONTACH_H_

#include <vector>

#include <iostream>

#include <ctre/phoenix/CANifier.h> 



class DragonTalonTach
{
    public:
        enum TALON_TACH_USAGE
	    {
	        UNKNOWN_TALON_TACH_USAGE = -1,
            MIN_WRIST_ANGLE,
            MAX_WRIST_ANGLE,
            TOP_HATCH_PRESENT,
            BOTTOM_HATCH_PRESENT,
            ARM_BOTTOM,
            ARM_TOP,
            MAX_TALON_TACH_USAGE
	    };

        //------------------------------------------------------------------------------
        // Method:		<<constructor>>
        // Description:
        //------------------------------------------------------------------------------
	    DragonTalonTach	
            (
                TALON_TACH_USAGE                        usage,	    // <I> - Usage of the talon tach
			    int	                                    canID,		// <I> - CAN io ID
			    ctre::phoenix::CANifier::GeneralPin	    generalpin,	// <I> - general pin
                bool                                    reversed
            );

        DragonTalonTach() = delete;
	    virtual ~DragonTalonTach();

        bool Get() const;

    private:
	    TALON_TACH_USAGE                        m_usage;
        ctre::phoenix::CANifier*                m_CAN;
        ctre::phoenix::CANifier::GeneralPin     m_generalpin;
        bool                                    m_reversed;
};
typedef std::vector<DragonTalonTach*> DragonTalonTachVector;

#endif /* SRC_MAIN_INCLUDE_HW_DRAGONTALONTACH_H_*/