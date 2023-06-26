Attribute VB_Name = "modAPI"
Option Explicit

Private Declare Function sndPlaySound Lib "winmm.dll" Alias "sndPlaySoundA" (ByVal lpszSoundName As String, ByVal uFlags As Long) As Long
Private Const SND_ASYNC = &H1         '  play asynchronously




Public Sub PlaySound(SoundFile As String)
    
    If Dir(SoundFile) <> "" Then
        Call sndPlaySound(SoundFile, SND_ASYNC)
    End If

End Sub


