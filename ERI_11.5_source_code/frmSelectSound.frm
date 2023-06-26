VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmSelectSound 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Form1"
   ClientHeight    =   3135
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7800
   Icon            =   "frmSelectSound.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3135
   ScaleWidth      =   7800
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrRepeat 
      Interval        =   5000
      Left            =   3720
      Top             =   0
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4680
      Top             =   120
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Height          =   735
      Left            =   120
      TabIndex        =   7
      Top             =   1440
      Width           =   7575
      Begin VB.HScrollBar hsbRepeat 
         Height          =   375
         Left            =   5040
         Max             =   60
         TabIndex        =   8
         Top             =   240
         Value           =   5
         Width           =   2295
      End
      Begin VB.Label lblRepeat 
         Caption         =   "Repeat sound every 5 seconds"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   4455
      End
   End
   Begin VB.CommandButton cmdTestSound 
      Caption         =   "Test sound"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   2160
      TabIndex        =   6
      Top             =   2280
      Width           =   3015
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   5280
      TabIndex        =   5
      Top             =   2280
      Width           =   2415
   End
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
      Height          =   735
      Left            =   120
      TabIndex        =   4
      Top             =   2280
      Width           =   1935
   End
   Begin VB.CheckBox chkPlaySound 
      Caption         =   "Play sound"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   2055
   End
   Begin VB.Frame fraSound 
      Caption         =   "Sound file"
      Height          =   855
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   7575
      Begin VB.CommandButton cmdBrowse 
         Caption         =   "Browse ..."
         Height          =   375
         Left            =   6120
         TabIndex        =   2
         Top             =   240
         Width           =   1215
      End
      Begin VB.TextBox Text1 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   5895
      End
   End
   Begin VB.Label lblCounter 
      Alignment       =   1  'Right Justify
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6480
      TabIndex        =   10
      Top             =   120
      Visible         =   0   'False
      Width           =   1095
   End
End
Attribute VB_Name = "frmSelectSound"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mRow As Integer
Private mRepeatInterval As Integer
Private mSecondsLeft As Integer

Private Sub cmdBrowse_Click()
    Dim A As Variant
    Dim i As Integer
    Dim Directory As String
    
    With CommonDialog1
        Directory = GetSetting(App.EXEName, "Settings", "InitDirectory", App.Path)
        .InitDir = Directory
        .Filter = "Wave files|*.wav"
        .ShowOpen
    End With
    
    Text1 = CommonDialog1.FileName
    
    A = Split(Text1.Text, "\")
    Directory = ""
    For i = 0 To UBound(A) - 2
        Directory = Directory + A(i)
    Next i

    SaveSetting App.EXEName, "Settings", "InitDirectory", Directory


Exit Sub
Err_Handler:
    MsgBox (Err.Description)

End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    With frmNotifications.grid
        If Me.chkPlaySound = Checked Then
            .TextMatrix(mRow, 2) = Text1
            .TextMatrix(mRow, 3) = mRepeatInterval
        Else
            .TextMatrix(mRow, 2) = "None"
            .TextMatrix(mRow, 3) = 0
        End If
    End With
    Unload Me
End Sub

Public Property Get Row() As Integer
    Row = mRow
End Property

Public Property Let Row(ByVal NewRow As Integer)
    mRow = NewRow
End Property

Private Sub cmdTestSound_Click()

    Select Case cmdTestSound.Caption
        Case "Test sound"
            PlaySound Text1
            
            If mRepeatInterval > 0 Then
                mSecondsLeft = mRepeatInterval
                Me.lblCounter.Caption = Format(mSecondsLeft)
                Me.lblCounter.Visible = True
                tmrRepeat.Interval = 1000
                tmrRepeat.Enabled = True
                cmdTestSound.Caption = "Stop test"
            End If
            
        Case Else
            tmrRepeat.Enabled = False
            cmdTestSound.Caption = "Test sound"
            Me.lblCounter.Visible = False
    End Select
    
End Sub

Public Sub UpdateRepeat()
    mRepeatInterval = hsbRepeat
    Me.lblRepeat = "Repeat sound every " + Format(Me.hsbRepeat) + " seconds"
    
    If mRepeatInterval = 0 Then
        cmdTestSound.Caption = "Test sound"
        tmrRepeat.Enabled = False
    End If
    
End Sub

Private Sub hsbRepeat_Change()
UpdateRepeat
End Sub

Private Sub hsbRepeat_Scroll()
UpdateRepeat
End Sub

Private Sub tmrRepeat_Timer()
    mSecondsLeft = mSecondsLeft - 1
    Me.lblCounter = Format(mSecondsLeft)
    
    If mSecondsLeft = 0 Then
        PlaySound Text1
        tmrRepeat.Interval = 1000
        mSecondsLeft = mRepeatInterval
    End If
    
    Me.lblCounter = Format(mSecondsLeft)
    
End Sub

Public Property Get RepeatInterval() As Integer
    RepeatInterval = mRepeatInterval
End Property

Public Property Let RepeatInterval(ByVal NewRepeatInterval As Integer)
    mRepeatInterval = NewRepeatInterval
    Me.hsbRepeat.Value = NewRepeatInterval
End Property
