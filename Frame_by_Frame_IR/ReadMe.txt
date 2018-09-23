I got lot of questions about potentially using the IR trigger to create a SoftPWM reaction using the frame by frame approach. 
It is awesome that you guys are asking great questions like this!

So the key with the frame by frame approach is that we can't just create a conditional in one frame. So if we use the format we were using in earlier iterations, we'll just be making the condition in one frame.
In the rest of the frames, it'll just go back to actuating the LED.

One very simple way to combat this would be to introduce a new variable that tracks whether the IR is active or not. If there is an IR trigger, this variable is 1 (denoting active). Otherwise it is 0. 
I have some code written up here. Let me know if anyone has any questions. 

Thanks everyone. 