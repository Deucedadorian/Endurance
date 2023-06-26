VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsTimeStamp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private mString As String
Private mValid As Boolean

Private mSecond As Integer
Private mMinute As Integer
Private mHour As Integer
Private mDay As Integer
Private mMonth As Integer
Private mYear As Integer
Private mDateString As String
Private mTimeString As String


Public Property Get S() As String
    S = mString
End Property

Public Property Let S(ByVal NewS As String)
    Dim SS As String
    Dim mm As String
    Dim hh As String
    Dim dd As String
    Dim mn As String
    Dim yy As String
        


    mValid = True
    mString = NewS
    
    If Len(NewS) <> 6 Then
        mValid = False
    Else
        mSecond = Asc(Mid(NewS, 1, 1)) - 65
        mMinute = Asc(Mid(NewS, 2, 1)) - 65
        mHour = Asc(Mid(NewS, 3, 1)) - 65
        mDay = Asc(Mid(NewS, 4, 1)) - 65
        mMonth = Asc(Mid(NewS, 5, 1)) - 65
        mYear = Asc(Mid(NewS, 6, 1)) - 65
        
        
        If mSecond > 59 Then mValid = False
        If mMinute > 59 Then mValid = False
        If mHour > 23 Then mValid = False
        If mDay > 31 Then mValid = False
        If mYear > 147 Then mValid = False
        If mYear < 80 Then mValid = False
        
        mYear = mYear + 1900
    
    End If
    

    If mValid Then
        SS = Format(mSecond)
        mm = Format(mMinute)
        hh = Format(mHour)
        dd = Format(mDay)
        mn = Format(mMonth)
        
        yy = Format(mYear)
        
        
        If Len(SS) = 1 Then SS = "0" + SS
        If Len(mm) = 1 Then mm = "0" + mm
        If Len(hh) = 1 Then hh = "0" + hh
        If Len(dd) = 1 Then dd = "0" + dd
        If Len(mn) = 1 Then mn = "0" + mn
        
        mDateString = yy + "-" + mn + "-" + dd
        mTimeString = hh + ":" + mm + ":" + SS
        
    Else
        mDateString = "NotValid"
        mTimeString = "NotValid"
    End If
    
End Property

Public Property Get Valid() As Boolean
    Valid = mValid
End Property


Public Property Get DateString() As String

    DateString = mDateString
End Property


Public Property Get TimeString() As String
    TimeString = mTimeString
End Property


Public Property Get Year() As Integer
    Year = mYear
End Property


Public Property Get Month() As Integer
    Month = mMonth
End Property


Public Property Get Day() As Integer
    Day = mDay
End Property

Public Property Get Hour() As Integer
    Hour = mHour
End Property


Public Property Get Minute() As Integer
    Minute = mMinute
End Property


Public Property Get Second() As Integer
    Second = mSecond
End Property

