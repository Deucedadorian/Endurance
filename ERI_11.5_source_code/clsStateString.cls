VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsStateString"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Private mStateString As String
Private mWarningCode As WarningCode
Private mFaultCode As FaultCode
Private mStateCode(0 To 2) As StateEnum

Public Enum StateEnum
    Halt
    Calm
    Cutin
    FreeWheel
    Motor
    GenerateLow
    GenerateHigh
    HighWind
    Fault
    Warning
    UnknownState
End Enum


Public Enum FaultCode
    LSSOverSpeed = 1
    HSSOverSpeed = 2
    RPMError = 3
End Enum

Public Enum WarningCode
    AnemError = 4
    MotorError = 5
    GridFault = 6
End Enum



Public Property Get S() As String
    S = mStateString
End Property

Public Property Let S(ByVal NewS As String)

    If Len(NewS) > 4 Then Exit Property
    
    mStateString = String(4 - Len(NewS), "0") + NewS
    
    mStateCode(0) = Val(Mid(mStateString, 3, 1))    'Current state
    mStateCode(1) = Val(Mid(mStateString, 2, 1))    'Previous state
    mStateCode(2) = Val(Mid(mStateString, 1, 1))    'Oldest state
    
    mWarningCode = 0
    
    
    If mStateCode(0) = Fault Then
        mFaultCode = Val(Mid(mStateString, 4, 1))
    Else
        mFaultCode = 0
    End If
    
    If mStateCode(0) = Warning Then
        mWarningCode = Val(Mid(mStateString, 4, 1))
    Else
        mWarningCode = 0
    End If
    
End Property

Public Property Get State(i As Integer) As StateEnum
    State = mStateCode(i)
End Property


Public Function FaultCodeString(i As FaultCode) As String

    Select Case i
        Case HSSOverSpeed
            FaultCodeString = "HSS overspeed"
        Case LSSOverSpeed
            FaultCodeString = "LSS overspeed"
        Case RPMError
            FaultCodeString = "RPM error"
        Case Else
            FaultCodeString = "Unknown fault"
    End Select
    
End Function

Public Function WarningCodeString(i As WarningCode) As String

    Select Case i
        Case AnemError
            WarningCodeString = "Anem err"
        Case GridFault
            WarningCodeString = "Grid fault"
        Case MotorError
            WarningCodeString = "Motor err"
        Case Else
            WarningCodeString = ""
    End Select
    
End Function

Public Property Get StateLabel(i As Integer) As String
    
    Select Case State(i)
        Case Calm
            StateLabel = "Calm"
        Case Cutin
            StateLabel = "Cutin"
        Case Fault
            StateLabel = "Fault"
            If i = 0 Then StateLabel = StateLabel + " (" + FaultCodeString(mFaultCode) + ")"
        Case FreeWheel
            StateLabel = "Free-wheel"
        Case GenerateHigh
            StateLabel = "Generate high"
        Case GenerateLow
            StateLabel = "Generate low"
        Case Halt
            StateLabel = "Halt"
        Case HighWind
            StateLabel = "High wind"
        Case Motor
            StateLabel = "Motor"
        Case Warning
            StateLabel = "Warning"
            If i = 0 Then StateLabel = StateLabel + " (" + WarningCodeString(mWarningCode) + ")"
        Case Else
            StateLabel = "Unknown state"
    End Select

End Property

