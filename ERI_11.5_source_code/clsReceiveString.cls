VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsReceiveString"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Testing As Boolean

Private mString As String
Private mSequenceNumber As Long
Private mTimeStamp As String
Private mWindSpeed As Double
Private mMaxWindSpeed As Double
Private mPower As Double
Private mMaxPower As Double
Private mRPM As Double
Private mMaxRPM As Double
Private mMotorStarts As Double
Private mBrakeStops As Double
Private mTotalHours As Double
Private mServiceHours As Double
Private mUpSwitches As Double
Private mTestParameters As String
Private mTestMode As TestModeEnum
Private mProgramVersion As String
Private mStateString As New clsStateString
Private mJumperIn As Boolean
Private mValid As Boolean
Private mSiteName As String
Private mFreeMemory As Double
Private mRecordIntervalReceived As Boolean
Private BufferInfo As clsRecordBuffer

Private mRecordNewest As New clsTimeStamp
Private mRecordOldest As New clsTimeStamp
Private mRecordMax As Double
Private mReceivedRecInfo As Boolean
Private mRecordsStarted As Boolean
Private mRecordsCanceled As Boolean
Private mRecordInterval As Integer

Private mIPInfoReceived As Boolean
Private mIPAddress As String
Private mNetmask As String
Private mNameServer As String
Private mGateway As String
Private mPort As String
Private mIPApplied As Boolean
Private mFlashInfoReceived As Boolean
Private mFlashWrites As Double
Private mQueryTestModeReceived As Boolean
Private mQueryTestMode As Boolean
Private mRecordCount As Integer

Private mTestByteCount As Double

Private mFileName As String
Private mFileNumber As Integer
Private mRecordBuffer As RecordBufferEnum

Private mTowerTime As String
Private mTowerDate As String
Private mDateTimeReceived As Boolean
Private mTowerYear As Integer
Private mTowerMonth As Integer
Private mTowerDay As Integer
Private mTowerHour As Integer
Private mTowerMinute As Integer
Private mTowerSecond As Integer

Private mTriggerString As String
Private mTriggerActive As Boolean
Private mTriggersReceived As Boolean

Private mPasswordKey As String
Private mPasswordKeyReceived As Boolean
Private mPassword As String
Private mEncryptedPassword As String
Private mPasswordAccepted As Boolean
Private mPasswordTested As Boolean
Private mNewPasswordValidated As Boolean
Private mNewPasswordApplied As Boolean

Private mWatchdogSet As Boolean


Public Enum RecordBufferEnum
    WindRpm
    Events
    WindRPMDiag
    EventsDiag
End Enum

Public Enum TestModeEnum
    NormalRun = 1
    OverSpeedTest = 2
    RPMErrorTest = 3
    CutoutTest = 4
    AnemomTest = 5
End Enum

'Tower responses
Public Enum CommandEnum
    IPInfo = 1
    IPConfirm = 2
    RecIPApplied = 3
    TR_PasswordKey = 4
    StackInfo = 5
    SiteInfo = 6
    FlashInfo = 7
    QTestMode = 8
    RecordInfo = 9
    TR_RecordsStarted = 10
    TR_RecordsCanceled = 11
    TR_MainRecord = 12
    TR_RecordInterval = 13
    TR_DateTime = 14
    TR_RecordsComplete = 15
    TR_Triggers = 16
    TR_PasswordResponse = 17
    TR_NewPasswordEcho = 18
    TR_NewPasswordApplied = 19
    TR_DisableWatchDog = 20
End Enum

Public Property Get S() As String
    S = mString
End Property

Public Property Let S(ByVal NewS As String)

    Dim A As Variant
    
'Format of the received string is as follows:
'    @!         First 2 chars are always @!
'0   S36583     Squence number
'1   900154027  Time stamp
'2   34         Wind speed
'3   2182       Max wind speed
'4   0          Power
'5   0          Max power
'6   0          RPM
'7   585        Max RPM
'8   186        Motor starts
'9   271        Brake stops
'10  2          Total hours
'11  2          Service hours
'12  0          Up switches
'13  11         Test parameter
'14  1200       State + history
'15  393        Program version
'    #          Last char is always #


    mFlashInfoReceived = False
    mQueryTestModeReceived = False
    
    mValid = True 'Assume string is valid untill proven invalid
    
    mString = ""

    If Left(NewS, 2) = "@*" Then
        ProcessNew NewS
    Else
        ProcessOld NewS
    End If
    

End Property
Public Property Get SequenceNumber() As Long
    SequenceNumber = mSequenceNumber
End Property
Public Property Get TimeStamp() As String
    TimeStamp = mTimeStamp
End Property
Public Property Get WindSpeed() As Double
    WindSpeed = mWindSpeed
End Property
Public Property Get MaxWindSpeed() As Double
    MaxWindSpeed = mMaxWindSpeed
End Property
Public Property Get Power() As Double
    Power = mPower
End Property
Public Property Get Maxpower() As Double
    Maxpower = mMaxPower
End Property
Public Property Get rpm() As Double
    rpm = mRPM
End Property
Public Property Get Maxrpm() As Double
    Maxrpm = mMaxRPM
End Property
Public Property Get MotorStarts() As Double
    MotorStarts = mMotorStarts
End Property
Public Property Get BrakeStops() As Double
    BrakeStops = mBrakeStops
End Property
Public Property Get TotalHours() As Double
    TotalHours = mTotalHours
End Property
Public Property Get ServiceHours() As Double
    ServiceHours = mServiceHours
End Property
Public Property Get TestParameters() As Double
    TestParameters = mTestParameters
End Property
Public Property Get UpSwitches() As Double
    UpSwitches = mUpSwitches
End Property
Public Property Get State(i As Integer) As StateEnum
    State = mStateString.State(i)
End Property
Public Property Get ProgramVersion() As String
    ProgramVersion = mProgramVersion
End Property

Public Property Get StateLabel(i As Integer) As String

    StateLabel = mStateString.StateLabel(i)
End Property

Private Function CommTestString(i As Integer) As String
    Select Case i
        Case 1
            CommTestString = "  Normal run"
        Case 2
            CommTestString = " Over-speed Test"
        Case 3
            CommTestString = " RPM Error Test"
        Case 4
            CommTestString = "  Cut out test"
        Case 5
            CommTestString = " Anemom test"
        Case Else
            CommTestString = "Unknown"
    End Select
End Function


Public Property Get TestMode() As TestModeEnum
    TestMode = mTestMode
End Property


Public Property Get TestModeString() As String
    TestModeString = CommTestString(TestMode)
End Property


Public Property Get JumperIn() As Boolean
    JumperIn = mJumperIn
End Property

Private Sub Class_Initialize()
    mJumperIn = True
End Sub

Public Property Get IsValid() As Boolean
    IsValid = mValid
End Property


Public Sub ProcessOld(ByVal NewS As String)
    Dim A As Variant
    
'Format of the received string is as follows:
'    @!         First 2 chars are always @!
'0   S36583     Squence number
'1   900154027  Time stamp
'2   34         Wind speed
'3   2182       Max wind speed
'4   0          Power
'5   0          Max power
'6   0          RPM
'7   585        Max RPM
'8   186        Motor starts
'9   271        Brake stops
'10  2          Total hours
'11  2          Service hours
'12  0          Up switches
'13  11         Test parameter
'14  1200       State + history
'15  393        Program version
'    #          Last char is always #

    mValid = True 'Assume string is valid untill proven invalid
    
    mString = ""


    If Left(NewS, 2) <> "@!" Then
        mValid = False
        Exit Sub
    End If
    
    If Right$(NewS, 1) <> "#" Then
        mValid = False
        Exit Sub
    End If
    
    mString = Mid$(NewS, 3, Len(NewS) - 3)

    
    A = Split(NewS, ",")
    
    If UBound(A) <> 15 Then
        mValid = False
        Exit Sub
    End If
    
    mString = Mid$(NewS, 3, Len(NewS) - 3)
    
    mTowerHour = HexToDec(Left(A(1), 2))
    mTowerMinute = HexToDec(Mid(A(1), 3, 2))
    mTowerSecond = HexToDec(Mid(A(1), 5, 2))
    
    mSequenceNumber = Val(A(0))
'    mTimeStamp = A(1)
    mWindSpeed = Val(A(2)) / 100
    mMaxWindSpeed = Val(A(3)) / 100
    mPower = Val(A(4)) / 100
    mMaxPower = Val(A(5)) / 100
    mRPM = Val(A(6))
    mMaxRPM = Val(A(7))

    

    mMotorStarts = Val(A(8))
    mBrakeStops = Val(A(9))
    mTotalHours = Val(A(10))
    mServiceHours = Val(A(11))
    mUpSwitches = Val(A(12))

    
    If Len(A(13)) < 2 Then
        mTestParameters = "0" + A(13)
    Else
        mTestParameters = A(13)
    End If
    
    mTestMode = Val(Right(mTestParameters, 1))
    If Val(Left(mTestParameters, 1)) = 1 Then
        mJumperIn = False
    Else
        mJumperIn = True
    End If
    
    mStateString.S = A(14)
    mProgramVersion = Mid(A(15), 1, 1) + "." + Mid(A(15), 2, 1) + "." + Mid(A(15), 3, 1)

End Sub

Public Sub ProcessNew(ByVal NewS As String)
    Dim A As Variant
    Dim CommandNumber As CommandEnum

    'Format of the received string is as follows:
    '    @!CMD,n,d1,d1,... ...#
    'First 5 characters are always '@*CMD'
    'n is the command number used to determine what function to call
    'd1,d2,.. are the data required for the function
    'Last character is always "#"

    mValid = True 'Assume string is valid untill proven invalid
    
    mString = ""

    'First 5 characters are always '@*CMD'
    If Left(NewS, 5) <> "@*CMD" Then
        mValid = False
        Exit Sub
    End If
    
    'Last character is always '#'
    If Right$(NewS, 1) <> "#" Then
        mValid = False
        Exit Sub
    End If
    
    mString = Mid$(NewS, 7, Len(NewS) - 7)

    
    A = Split(mString, ",")
    
    
    CommandNumber = Val(A(0))
    
    Select Case CommandNumber
        Case IPInfo
            SetIPInfo A
        Case IPConfirm
        Stop
            CheckIPConfirm A
        Case RecIPApplied
            mIPApplied = True
        Case TR_PasswordKey
            ProcessPasswordKey A
        Case StackInfo
            ParseStackInfo A
            
        Case SiteInfo
            ParseSiteInfo A
        
        Case FlashInfo
            ParseFlashInfo A
            
        Case QTestMode
            ParseQueryTestMode A
            
        Case RecordInfo
            ParseRecordInfo A
            
        Case TR_RecordsStarted

            ParseRecordsStarted A
            
        Case TR_RecordsCanceled
            ParseRecordsCanceled A
        
        Case TR_MainRecord
            ParseMainRecord A
        
        Case TR_RecordInterval
            ParseRecordInterval A
            
        Case TR_DateTime
            ParseDateTime A
            
        Case TR_RecordsComplete
            ParesRecordsComplete A
        Case TR_Triggers
            ParseTriggers A
        Case TR_PasswordResponse
            ParsePasswordResponse A
        Case TR_NewPasswordEcho
            ParceNewPasswordEcho A
        Case TR_NewPasswordApplied
            ParceNewPasswordApplied A
        Case TR_DisableWatchDog
            ParseDisableWatchDog A
        Case Else
            mValid = False
            Exit Sub
    End Select
    
End Sub

Public Property Get IPInfoReceived() As Boolean
    IPInfoReceived = mIPInfoReceived
End Property

Public Property Let IPInfoReceived(ByVal NewIPInfoReceived As Boolean)
    mIPInfoReceived = NewIPInfoReceived
End Property

Private Sub SetIPInfo(A As Variant)
    
    If UBound(A) <> 5 Then
        mValid = False
        Exit Sub
    End If

    mIPInfoReceived = True
    mIPAddress = A(1)
    mNetmask = A(2)
    mNameServer = A(3)
    mGateway = A(4)
    mPort = A(5)


End Sub

Public Property Get IPAddress() As String
    IPAddress = mIPAddress
End Property
Public Property Get NameServer() As String
    NameServer = mNameServer
End Property
Public Property Get Netmask() As String
    Netmask = mNetmask
End Property
Public Property Get Gateway() As String
    Gateway = mGateway
End Property

Public Property Get Port() As String
    Port = mPort
End Property


Private Sub CheckIPConfirm(A As Variant)
    If A(2) = frmRemoteConnectionSettings.txtIPAddress Then
    
    End If
End Sub

Public Property Get IPApplied() As Boolean
    IPApplied = mIPApplied
End Property

Public Property Let IPApplied(ByVal NewIPApplied As Boolean)
    mIPApplied = NewIPApplied
End Property

Public Sub ParseStackInfo(A As Variant)
    
    If UBound(A) <> 16 Then
        mValid = False
    Else
        frmStackInfo.TaskArray = A
        frmStackInfo.Show
    End If

End Sub

Public Sub ParseSiteInfo(A As Variant)

    Dim T As New clsTimeStamp

    Select Case UBound(A)
        
        
        Case 2
            If Me.ProgramVersion > "8.0.6" Then
                mSiteName = A(1)
                T.S = A(2)
                frmEndurance.ProgramSerialNumber = T.DateString + ",  " + T.TimeString
                frmEndurance.mnuTestTimeStampResult.Caption = frmEndurance.ProgramSerialNumber
            End If
        Case 1
            mSiteName = A(1)
        Case Else
        
    End Select
    
End Sub

Public Property Get SiteName() As String
    SiteName = mSiteName
End Property


Public Sub ClearSiteName()
    mSiteName = ""
    frmEndurance.mnuSettingsSiteName.Enabled = False
End Sub

Public Sub ParseFlashInfo(A As Variant)

    If UBound(A) = 2 Then
        mFlashInfoReceived = True
        mFlashWrites = A(1)
        mFreeMemory = A(2)
    Else
        mFlashInfoReceived = False
    End If
    
End Sub

Public Property Get FlashWrites() As Double
    FlashWrites = mFlashWrites
End Property


Public Property Get FlashInfoReceived() As Boolean
    FlashInfoReceived = mFlashInfoReceived
End Property


Public Sub ParseQueryTestMode(A As Variant)
    
    If UBound(A) = 1 Then
        
        mQueryTestModeReceived = True
        
        If A(1) = 0 Then
            mQueryTestMode = False
        Else
            mQueryTestMode = True
        End If
        
    Else
        
        mQueryTestModeReceived = False
        
    End If

End Sub

Public Property Get QueryTestModeReceived() As Boolean
    QueryTestModeReceived = mQueryTestModeReceived
End Property


Public Property Get QueryTestMode() As Boolean
    QueryTestMode = mQueryTestMode
End Property


Public Property Get FreeMemory() As Double
    FreeMemory = mFreeMemory
End Property


Public Property Get ReceivedRecInfo() As Boolean
    ReceivedRecInfo = mReceivedRecInfo
End Property
Public Property Let ReceivedRecInfo(ByVal NewReceivedRecInfo As Boolean)
    mReceivedRecInfo = NewReceivedRecInfo
End Property

Public Sub ParseRecordInfo(A As Variant)

    Dim T As New clsTimeStamp
    
    mValid = True
    
    If UBound(A) = 5 Then

        mReceivedRecInfo = True
        
        mRecordCount = A(1)
        mRecordOldest.S = A(2)
        mRecordNewest.S = A(3)
        mRecordMax = A(4)
        mRecordInterval = A(5)
    Else
        mValid = False
    End If

End Sub
Public Property Get Recordmax() As Integer
    Recordmax = mRecordMax
End Property

Public Property Get RecordNewest() As clsTimeStamp
    Set RecordNewest = mRecordNewest
End Property

Public Property Get RecordOldest() As clsTimeStamp
    Set RecordOldest = mRecordOldest
End Property

Public Property Get RecordCount() As Integer
    RecordCount = mRecordCount
End Property

Public Property Get RecordsStarted() As Boolean
    RecordsStarted = mRecordsStarted
End Property

Public Property Let RecordsStarted(ByVal NewRecordsStarted As Boolean)
    mRecordsStarted = NewRecordsStarted
End Property
Public Property Get RecordsCanceled() As Boolean
    RecordsCanceled = mRecordsCanceled
End Property

Public Property Let RecordsCanceled(ByVal NewRecordsCanceled As Boolean)
    mRecordsCanceled = NewRecordsCanceled
End Property


Public Sub ParseRecordsStarted(A As Variant)
    Dim i As Integer
    Dim F As Form
    
    Set F = frmRecords2
    
    Select Case mRecordBuffer
        Case Events
        Case WindRpm
        Case EventsDiag
        Case WindRPMDiag
    End Select
    
    
    If UBound(A) = 1 Then
        'A(1) has the number of records to be downloaded
        If A(1) > 0 Then
            F.pbRecords.Max = A(1)
        Else
        
        
            F.fraBuffer.Enabled = True
'            For i = 0 To F.optBuffer.count - 1
'                F.optBuffer(i).Enabled = True
'            Next i
            
            
        
            With F
                .cmdDownload.Caption = "Download"
                .pbRecords.Value = 0
            End With
     
            CloseFile

        End If
        
        F.lblProgress = Format(A(1)) + " new records found"
        
        mRecordsStarted = True
    Else
        mValid = False
    End If
    
End Sub
Public Sub ParseRecordsCanceled(A As Variant)
    Dim i As Integer
    
    
    mRecordsCanceled = True
    
    With frmRecords2
        .cmdDownload.Caption = "Download"
        .pbRecords.Value = 0
        .lblProgress = "Download canceled"
        .fraBuffer.Enabled = True
'        For i = 0 To .optBuffer.count - 1
'            .optBuffer(i).Enabled = True
'        Next i
        
    End With

End Sub


Public Sub ParseMainRecord(A As Variant)
    On Error Resume Next
    
    Dim i As Integer
    
    Dim SS As String
    
    Dim T As New clsTimeStamp
    
    Dim rpm As Double
    Dim WindSpeed As Double
    Dim EventNumber As Integer
    Dim RecSize As Integer
    Dim Power As Integer

If UBound(A) = 1 Then

    
    frmRecords2.lblProgress = "Receiving records"
    SS = A(1)
    
    Select Case RecordBuffer
        Case WindRpm, WindRPMDiag
            RecSize = 14
        Case Events, EventsDiag
            RecSize = 8
    End Select
            
    Do While Len(SS) >= RecSize
        
        T.S = Left(SS, 6)
        frmRecords2.pbRecords.Value = frmRecords2.pbRecords.Value + 1
        
        Select Case RecordBuffer
            Case WindRpm, WindRPMDiag
                WindSpeed = HexToDec(Mid(SS, 11, 4)) / 100
                If Me.ProgramVersion >= "9.1.0" Then
                    Power = HexToDec(Mid(SS, 7, 4))
                    Print #mFileNumber, T.DateString; ",", T.TimeString; ",", WindSpeed; ","; , Power
                Else
                    rpm = HexToDec(Mid(SS, 7, 4)) / 100
                    Print #mFileNumber, T.DateString; ",", T.TimeString; ",", WindSpeed; ","; , rpm
                End If
            Case WindRPMDiag
                WindSpeed = HexToDec(Mid(SS, 7, 4)) / 100
                rpm = HexToDec(Mid(SS, 11, 4)) / 100
                Print #mFileNumber, T.DateString; ",", T.TimeString; ",", WindSpeed; ","; , rpm
            Case Events, EventsDiag
                EventNumber = HexToDec(Mid(SS, 7, 2))
                Print #mFileNumber, T.DateString + ",", T.TimeString + ",", Format(EventNumber) + ",", frmEndurance.ET.EventText(EventNumber)
        End Select
        
        frmRecords2.grid.TextMatrix(4, 1) = T.DateString + "," + T.TimeString
        
        If frmRecords2.pbRecords.Value = frmRecords2.pbRecords.Max Then

        'Last record received
            frmRecords2.lblProgress = "Download complete"
            frmRecords2.cmdDownload.Caption = "Download"
            frmRecords2.pbRecords.Value = 0
            'Debug.Print Time
            CloseFile
            frmRecords2.fraBuffer.Enabled = True
        End If
        
        SS = Right(SS, Len(SS) - RecSize)
    
    Loop
    
Else
    
    mValid = False

End If

End Sub

Public Sub OpenRecordFile(ByVal Buffer As RecordBufferEnum)

    Close
    mRecordBuffer = Buffer
    mFileName = FileName(Buffer)
    mFileNumber = FreeFile
    
    If Dir(FolderName, vbDirectory) = "" Then
        MkDir (FolderName)
    End If
    
    If Dir(mFileName, vbNormal) = "" Then
        Open mFileName For Output As #mFileNumber
        Print #mFileNumber, "Site name = " + frmEndurance.R.SiteName
        Print #mFileNumber, "File created " + Format(Date) + "   " + Format(Time)
        Print #mFileNumber, "File created by Endurance Remote Interface version " + Format(App.Major) + "." + Format(App.Minor)
        Print #mFileNumber,
        
            Select Case Buffer
                Case WindRpm
                    If Me.ProgramVersion >= "9.1.0" Then
                        Print #mFileNumber, "yyyy-mm-dd,", "hh:mm:ss,", "Wind (m/s),", "power (watts)"
                    Else
                        Print #mFileNumber, "yyyy-mm-dd,", "hh:mm:ss,", "Wind (m/s),", "rpm"
                    End If
                    Print #mFileNumber,
                Case WindRPMDiag
                    Print #mFileNumber, "yyyy-mm-dd,", "hh:mm:ss,", "Wind (m/s),", "rpm"
                    Print #mFileNumber,
                Case Events, EventsDiag
                    Print #mFileNumber, "yyyy-mm-dd,", "hh:mm:ss,", "Code", "Event"
                    Print #mFileNumber,
                    SaveSetting App.EXEName, "Logging", "Diagnostic events file name", mFileName
            End Select
        
        
        
        
        Close #mFileNumber
    End If
    
    mFileNumber = FreeFile
    Open mFileName For Append As #mFileNumber

End Sub

Public Sub CloseFile()
    Close #mFileNumber
End Sub

Public Property Get RecordInterval() As Variant
    RecordInterval = mRecordInterval
End Property


Public Property Get RecordIntervalReceived() As Boolean
    RecordIntervalReceived = mRecordIntervalReceived
End Property

Public Property Let RecordIntervalReceived(ByVal NewRecordIntervalReceived As Boolean)
    mRecordIntervalReceived = NewRecordIntervalReceived
End Property

Private Sub ParseRecordInterval(A As Variant)

    If UBound(A) = 1 Then
        mRecordInterval = A(1)
        mRecordIntervalReceived = True
    Else
        mValid = False
    End If
    
End Sub

Public Property Get TowerTime() As String
    TowerTime = mTowerTime
End Property


Public Property Get TowerDate() As String
    TowerDate = mTowerDate
End Property

Public Property Get DateTimeReceived() As Boolean
    DateTimeReceived = mDateTimeReceived
End Property

Public Property Let DateTimeReceived(ByVal NewDateTimeReceived As Boolean)
    mDateTimeReceived = NewDateTimeReceived
End Property

Public Sub ParseDateTime(A As Variant)
    Dim T As New clsTimeStamp
    
    If UBound(A) = 1 Then
        
        T.S = A(1)
        
        If T.Valid Then
            mDateTimeReceived = True
            mTowerDate = T.DateString
            mTowerTime = T.TimeString
            
            mTowerYear = T.Year
            mTowerMonth = T.Month
            mTowerDay = T.Day
            
            mTowerHour = T.Hour
            mTowerMinute = T.Minute
            mTowerSecond = T.Second
            
        Else
            mValid = False
            
        End If
        
    Else
        mValid = False
    End If
    
End Sub
Public Property Get TowerYear() As Integer
    TowerYear = mTowerYear
End Property


Public Property Get TowerMonth() As Integer
    TowerMonth = mTowerMonth
End Property


Public Property Get TowerDay() As Integer
    TowerDay = mTowerDay
End Property


Public Property Get TowerHour() As Integer
    TowerHour = mTowerHour
End Property


Public Property Get TowerMinute() As Integer
    TowerMinute = mTowerMinute
End Property


Public Property Get TowerSecond() As Integer
    TowerSecond = mTowerSecond
End Property


Public Sub ParesRecordsComplete(A As Variant)
    
    CloseFile
    
End Sub

Public Property Get FileName(ByVal Buffer As RecordBufferEnum) As String

    Select Case Buffer
        Case WindRpm
            If Me.ProgramVersion >= "9.1.0" Then
                FileName = FolderName + "\wind and power.txt"
            Else
                FileName = FolderName + "\wind and rpm.txt"
            End If
        Case Events
            FileName = FolderName + "\events.txt"
        Case WindRPMDiag
            FileName = FolderName + "\diagnostic wind and rpm.txt"
        Case EventsDiag
            FileName = FolderName + "\diagnostic events.txt"
    End Select

End Property


Public Property Get RecordBuffer() As RecordBufferEnum
    RecordBuffer = mRecordBuffer
End Property

Public Property Let RecordBuffer(ByVal NewRecordBuffer As RecordBufferEnum)
    mRecordBuffer = NewRecordBuffer
End Property



Private Sub ParseTriggers(A As Variant)

    mTriggersReceived = False 'Assume false until verified
    
    If UBound(A) = 1 Then
        mTriggerString = Left(A(1), Len(A(1)) - 1)
    
        If Right(A(1), 1) = "0" Then
            mTriggerActive = False
        Else
            mTriggerActive = True
        End If
        
        mTriggersReceived = True
    Else
        mTriggerString = ""
    End If

End Sub

Public Property Get TriggerString() As String
    TriggerString = mTriggerString
End Property


Public Property Get TriggersReceived() As Boolean
    TriggersReceived = mTriggersReceived
End Property

Public Property Let TriggersReceived(ByVal NewTriggersReceived As Boolean)
    mTriggersReceived = NewTriggersReceived
End Property

Public Property Get TriggerActive() As Boolean
    TriggerActive = mTriggerActive
End Property

Public Property Get FolderName() As String
    
    FolderName = "c:\Endurance data files\" + mSiteName

End Property


Public Property Get PasswordKeyReceived() As Boolean
    PasswordKeyReceived = mPasswordKeyReceived
End Property

Public Property Let PasswordKeyReceived(ByVal NewPasswordKeyReceived As Boolean)
    mPasswordKeyReceived = NewPasswordKeyReceived
End Property

Public Property Get PasswordKey() As String
    PasswordKey = mPasswordKey
End Property


Public Property Get EncryptedPassword() As String
    EncryptedPassword = mEncryptedPassword
End Property


Public Property Get Password() As String
    Password = mPassword
End Property

Public Property Let Password(ByVal NewPassword As String)
    mPassword = NewPassword
End Property

Public Sub ProcessPasswordKey(A As Variant)

    If UBound(A) = 1 Then
        mPasswordKey = A(1)
        mPasswordKeyReceived = True
        mEncryptedPassword = Encrypt(mPassword, mPasswordKey)
    End If
    

End Sub

Public Sub ParsePasswordResponse(A As Variant)
    
    If UBound(A) = 1 Then
        mPasswordTested = True
        If A(1) = "1" Then
            mPasswordAccepted = True
        Else
            mPasswordAccepted = False
        End If
    Else
        mValid = False
    End If

End Sub

Public Property Get PasswordAccepted() As Boolean
    PasswordAccepted = mPasswordAccepted
End Property

Public Property Let PasswordAccepted(ByVal NewPasswordAccepted As Boolean)
    mPasswordAccepted = NewPasswordAccepted
End Property

Public Property Get PasswordTested() As Boolean
    PasswordTested = mPasswordTested
End Property

Public Property Let PasswordTested(ByVal NewPasswordTested As Boolean)
    mPasswordTested = NewPasswordTested
End Property

Public Sub ParceNewPasswordEcho(A As Variant)
    If UBound(A) = 1 Then
        If A(1) = frmEndurance.PendingPassword Then
            mNewPasswordValidated = True
        End If
    End If
End Sub

Public Property Get NewPasswordValidated() As Boolean
    NewPasswordValidated = mNewPasswordValidated
End Property

Public Property Let NewPasswordValidated(ByVal NewNewPasswordValidated As Boolean)
    mNewPasswordValidated = NewNewPasswordValidated
End Property

Private Sub ParceNewPasswordApplied(A As Variant)
    If UBound(A) = 1 Then
        mNewPasswordApplied = True
    End If
End Sub


Public Property Get NewPasswordApplied() As Boolean
    NewPasswordApplied = mNewPasswordApplied
End Property

Public Property Let NewPasswordApplied(ByVal NewNewPasswordApplied As Boolean)
    mNewPasswordApplied = NewNewPasswordApplied
End Property


Public Property Get WatchdogSet() As Boolean
    WatchdogSet = mWatchdogSet
End Property

Public Property Let WatchdogSet(ByVal NewWatchdogSet As Boolean)
    mWatchdogSet = NewWatchdogSet
End Property

Public Sub ParseDisableWatchDog(A As Variant)

    If UBound(A) = 1 Then
        mWatchdogSet = True
    End If
        
End Sub
