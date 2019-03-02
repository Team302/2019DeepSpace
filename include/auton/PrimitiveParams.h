/*
 * PrimitiveParams.h
 *
 *  Created on: Jan 18, 2018
 *      Author: Jonah Shader
 */

#ifndef SRC_AUTON_PRIMITIVEPARAMS_H_
#define SRC_AUTON_PRIMITIVEPARAMS_H_

#include <auton/PrimitiveEnums.h>

#include <vector>


class PrimitiveParams
{
    public:

        PrimitiveParams
        (
                PRIMITIVE_IDENTIFIER        id,
                float                       time,
                float                       distance,
                float                       xLoc,
                float                       yLoc,
                float                       heading,
                float                       startDriveSpeed,
                float                       endDriveSpeed
        );//Constructor. Takes in all parameters

        PrimitiveParams() = delete;
        virtual ~PrimitiveParams();//Destructor


        //Some getters
        PRIMITIVE_IDENTIFIER GetID() const;
        float GetTime() const;
        float GetDistance() const;
        float GetXLocation() const;
        float GetYLocation() const;
        float GetHeading() const;
        float GetDriveSpeed() const;
        float GetEndDriveSpeed() const;

        //Setters
        void SetDistance(float distance);

    private:
        //Primitive Parameters
        PRIMITIVE_IDENTIFIER        m_id; //Primitive ID
        float                       m_time;
        float                       m_distance;
        float                       m_xLoc;
        float                       m_yLoc;
        float                       m_heading;
        float                       m_startDriveSpeed;
        float                       m_endDriveSpeed;
};

typedef std::vector<PrimitiveParams*> PrimitiveParamsVector;



#endif /* SRC_AUTON_PRIMITIVEPARAMS_H_ */
