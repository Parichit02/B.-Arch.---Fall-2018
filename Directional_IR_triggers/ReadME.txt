The code provided here enables detection of directional gestures. 

Given that only 2 IR sensors are used, the code can only detect the motion going right to left and left to right. This can be extended to detect northward and southware motions with three IR sensors.

The system revolves around the use of a timing parameter that is coupled with each IR trigger. The timing parameter is incremented by one when the IR trigger is detected. 
This parameter is then incrementedd by one in all subsequent frames. This keeps the IR "active". While one IR sensor is active, if there is a trigger in the second IR sensor detected, then the direction is computed based on which IR was triggered first and its relevant behavior is implemented.