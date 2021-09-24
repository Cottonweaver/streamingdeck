f13::

return

f14::

return

f15::

return

f16::
	Send {Media_Prev}
return

f17::
	Send {media_play_pause}
return

f18::
	Send {Media_Next}
return

f21::
Run, c:\windows\system32\control.exe mmsys.cpl    
WinWaitActive, Sound
WinSet, AlwaysOnTop, On, Sound    
Send, {DOWN}    
ControlGet, MyState, Enabled, , Button2
If (MyState = 1){
    ControlClick, Button2, A
} Else {
    Send, {DOWN}
    ControlClick, Button2, A
}    
WinClose, Sound
return

f22::
Send {Volume_Up 1}
return

f23::
Send {Volume_Down 1}
return

f24::
SoundGet, Master_mute,, mute
if Master_mute = On
{
	SoundSet, 0, , mute
}
else
{
	SoundSet, 1, , mute
}
return