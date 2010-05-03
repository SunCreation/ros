/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2008, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#ifndef ROSBAG_TIME_TRANSLATOR_H
#define ROSBAG_TIME_TRANSLATOR_H

#include "ros/time.h"

namespace rosbag {

//! Helper class for translating between two times
/*!
 * The time translator can be configured with a Real start time, a
 * Translated start time, and a time scale.
 * 
 * It will convert a time from a series starting at realStartTime to a
 * comparable time series instead starting at translatedStartTime.
 * All durations in the time-sequence as scaled by 1/(timeScale).
 *
 * That is, a time-sequence with time-scale 2 will finish twice as
 * quickly.
 */
class TimeTranslator
{
public:
    TimeTranslator() : time_scale_(1.0), real_start_(ros::TIME_MIN), translated_start_(ros::TIME_MIN) {}

    void setTimeScale(const double& s) {time_scale_ = s; }
    
    void setRealStartTime(const ros::Time& t) { real_start_ = t; }

    //! Increments the translated start time by shift.  Useful for pausing.
    void setTranslatedStartTime(const ros::Time& t) { translated_start_ = t; }

    //! Increments the translated start time by shift.  Useful for pausing.
    void shift(const ros::Duration& d) {translated_start_ += d;}

    ros::Time translate(const ros::Time& t)
    {
        return  translated_start_ + (t - real_start_) * ( 1.0 / time_scale_);
    }

    private:
    
    double time_scale_;
    ros::Time real_start_;
    ros::Time translated_start_;
};

}

#endif