VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmNotifications 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Notifications"
   ClientHeight    =   5730
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   9180
   Icon            =   "frmNotifications.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5730
   ScaleWidth      =   9180
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   120
      TabIndex        =   2
      Top             =   4680
      Width           =   3495
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   3720
      TabIndex        =   0
      Top             =   4680
      Width           =   5295
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   3240
      Top             =   1320
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSFlexGridLib.MSFlexGrid grid 
      Height          =   4455
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   8895
      _ExtentX        =   15690
      _ExtentY        =   7858
      _Version        =   393216
      AllowBigSelection=   0   'False
      ScrollBars      =   0
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
End
Attribute VB_Name = "frmNotifications"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()

SaveSetting App.EXEName, "Settings", "RestoreOnHalt", grid.TextMatrix(1, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnCalm", grid.TextMatrix(2, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnCutin", grid.TextMatrix(3, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnFreeWheel", grid.TextMatrix(4, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnMotor", grid.TextMatrix(5, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnGenerateLow", grid.TextMatrix(6, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnGenerateHigh", grid.TextMatrix(7, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnHighWind", grid.TextMatrix(8, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnFault", grid.TextMatrix(9, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnWarning", grid.TextMatrix(10, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnCommLost", grid.TextMatrix(11, 1)
SaveSetting App.EXEName, "Settings", "RestoreOnService", grid.TextMatrix(12, 1)


SaveSetting App.EXEName, "Settings", "HaltSound", grid.TextMatrix(1, 2)
SaveSetting App.EXEName, "Settings", "CalmSound", grid.TextMatrix(2, 2)
SaveSetting App.EXEName, "Settings", "CutinSound", grid.TextMatrix(3, 2)
SaveSetting App.EXEName, "Settings", "FreeWheelSound", grid.TextMatrix(4, 2)
SaveSetting App.EXEName, "Settings", "MotorSound", grid.TextMatrix(5, 2)
SaveSetting App.EXEName, "Settings", "GenerateLowSound", grid.TextMatrix(6, 2)
SaveSetting App.EXEName, "Settings", "GenerateHighSound", grid.TextMatrix(7, 2)
SaveSetting App.EXEName, "Settings", "HighWindSound", grid.TextMatrix(8, 2)
SaveSetting App.EXEName, "Settings", "FaultSound", grid.TextMatrix(9, 2)
SaveSetting App.EXEName, "Settings", "WarningSound", grid.TextMatrix(10, 2)
SaveSetting App.EXEName, "Settings", "CommLostSound", grid.TextMatrix(11, 2)
SaveSetting App.EXEName, "Settings", "ServiceSound", grid.TextMatrix(12, 2)

SaveSetting App.EXEName, "Settings", "HaltRepeat", grid.TextMatrix(1, 3)
SaveSetting App.EXEName, "Settings", "CalmRepeat", grid.TextMatrix(2, 3)
SaveSetting App.EXEName, "Settings", "CutinRepeat", grid.TextMatrix(3, 3)
SaveSetting App.EXEName, "Settings", "FreeWheelRepeat", grid.TextMatrix(4, 3)
SaveSetting App.EXEName, "Settings", "MotorRepeat", grid.TextMatrix(5, 3)
SaveSetting App.EXEName, "Settings", "GenerateLowRepeat", grid.TextMatrix(6, 3)
SaveSetting App.EXEName, "Settings", "GenerateHighRepeat", grid.TextMatrix(7, 3)
SaveSetting App.EXEName, "Settings", "HighWindRepeat", grid.TextMatrix(8, 3)
SaveSetting App.EXEName, "Settings", "FaultRepeat", grid.TextMatrix(9, 3)
SaveSetting App.EXEName, "Settings", "WarningRepeat", grid.TextMatrix(10, 3)
SaveSetting App.EXEName, "Settings", "CommLostRepeat", grid.TextMatrix(11, 3)
SaveSetting App.EXEName, "Settings", "ServiceRepeat", grid.TextMatrix(12, 3)

frmEndurance.LoadNotifications

Unload Me

End Sub

Private Sub Form_Load()
    Dim i As Integer
    
    grid.Cols = 4
    grid.Rows = 13
    
    grid.TextMatrix(0, 0) = "Event"
    grid.TextMatrix(0, 1) = "Notify"
    grid.TextMatrix(0, 2) = "Sound to play"
    grid.TextMatrix(0, 3) = "Repeat interval"
    
    For i = 0 To grid.Cols - 1
        grid.ColWidth(i) = grid.Width / grid.Cols
    Next i
    
    
    grid.TextMatrix(1, 0) = "Halt"
    grid.TextMatrix(2, 0) = "Calm"
    grid.TextMatrix(3, 0) = "Cutin"
    grid.TextMatrix(4, 0) = "Free wheel"
    grid.TextMatrix(5, 0) = "Motor"
    grid.TextMatrix(6, 0) = "Generate low"
    grid.TextMatrix(7, 0) = "Generate high"
    grid.TextMatrix(8, 0) = "HighWind"
    grid.TextMatrix(9, 0) = "Fault"
    grid.TextMatrix(10, 0) = "Warning"
    grid.TextMatrix(11, 0) = "Communications lost"
    grid.TextMatrix(12, 0) = "Service hours > 6000"
    
    With frmEndurance
        For i = 0 To 11
            grid.TextMatrix(i + 1, 1) = .NotificationArray(i, 1)
            grid.TextMatrix(i + 1, 2) = .NotificationArray(i, 2)
            grid.TextMatrix(i + 1, 3) = .NotificationArray(i, 3)
        Next i
    End With
    

End Sub

Private Sub grid_Click()
    
    Select Case grid.Col
        Case 1
            If grid.TextMatrix(grid.Row, 1) = "Yes" Then
                grid.TextMatrix(grid.Row, 1) = "No"
            Else
                grid.TextMatrix(grid.Row, 1) = "Yes"
            End If
        Case 2, 3
            frmSelectSound.Row = grid.Row
            frmSelectSound.Text1 = grid.TextMatrix(grid.Row, 2)
            If frmSelectSound.Text1 = "None" Then
                frmSelectSound.chkPlaySound.Value = Unchecked
            Else
                frmSelectSound.chkPlaySound.Value = Checked
            End If
            frmSelectSound.Caption = "Sound for ... " + grid.TextMatrix(grid.Row, 0)
            frmSelectSound.RepeatInterval = Val(grid.TextMatrix(grid.Row, 3))
            frmSelectSound.Show 1
    End Select

End Sub
