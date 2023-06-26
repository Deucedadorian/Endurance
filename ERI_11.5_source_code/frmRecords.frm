VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmRecords 
   Caption         =   "Records"
   ClientHeight    =   6390
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   6210
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   6390
   ScaleWidth      =   6210
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Left            =   4680
      Top             =   5640
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   5640
      Top             =   5760
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame fraMainRecords 
      Caption         =   "Wind and rpm"
      Height          =   4935
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   6015
      Begin MSComctlLib.ProgressBar pbMainRecords 
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   2280
         Width           =   5775
         _ExtentX        =   10186
         _ExtentY        =   450
         _Version        =   393216
         Appearance      =   1
         Scrolling       =   1
      End
      Begin VB.Frame Frame1 
         Caption         =   "Recording interval"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2175
         Left            =   120
         TabIndex        =   6
         Top             =   2640
         Width           =   5775
         Begin VB.OptionButton optInterval 
            Caption         =   "12 hour"
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
            Index           =   11
            Left            =   3840
            TabIndex        =   20
            Top             =   1440
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "8 hour"
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
            Index           =   10
            Left            =   3840
            TabIndex        =   17
            Top             =   1080
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "4 hour"
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
            Index           =   9
            Left            =   3840
            TabIndex        =   16
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "2 hour"
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
            Index           =   8
            Left            =   3840
            TabIndex        =   15
            Top             =   360
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "1 hour"
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
            Index           =   7
            Left            =   2040
            TabIndex        =   14
            Top             =   1440
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "30 minute"
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
            Index           =   6
            Left            =   2040
            TabIndex        =   13
            Top             =   1080
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "15 minute"
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
            Index           =   5
            Left            =   2040
            TabIndex        =   12
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "5 minute"
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
            Index           =   4
            Left            =   2040
            TabIndex        =   11
            Top             =   360
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "1 minute"
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
            Index           =   3
            Left            =   240
            TabIndex        =   10
            Top             =   1440
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "30 second"
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
            Index           =   2
            Left            =   240
            TabIndex        =   9
            Top             =   1080
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "15 second"
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
            Index           =   1
            Left            =   240
            TabIndex        =   8
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton optInterval 
            Caption         =   "1 second"
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
            Index           =   0
            Left            =   240
            TabIndex        =   7
            Top             =   360
            Width           =   1455
         End
         Begin VB.Label lblResponse 
            Height          =   255
            Left            =   240
            TabIndex        =   21
            Top             =   1800
            Width           =   5175
         End
      End
      Begin VB.CommandButton cmdDownLoad 
         Caption         =   "Download"
         Height          =   495
         Left            =   4440
         TabIndex        =   3
         Top             =   240
         Width           =   1455
      End
      Begin VB.Label lblNew 
         Alignment       =   1  'Right Justify
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
         Left            =   2280
         TabIndex        =   22
         Top             =   1920
         Width           =   3495
      End
      Begin VB.Label lblMaximum 
         Caption         =   "Maximum"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   360
         Width           =   4095
      End
      Begin VB.Label lblNewest 
         Caption         =   "Newest"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   1440
         Width           =   4095
      End
      Begin VB.Label lblOldest 
         Caption         =   "Oldest"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   1080
         Width           =   3975
      End
      Begin VB.Label lblMainCount 
         Caption         =   "Record count"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   2775
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   975
      Left            =   120
      TabIndex        =   0
      Top             =   5280
      Width           =   6015
   End
End
Attribute VB_Name = "frmRecords"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public AutoOption As Boolean
Private TimerString As String

Private Sub cmdDownLoad_Click()
    Dim LastRecordTime As String

    'Debug.Print Time
    Select Case cmdDownLoad.Caption
        
        Case "Download"
            
            LastRecordTime = GetNewestDate
            
            'Debug.Print LastRecordTime
            
            With frmEndurance
                
                .RecordRequestDate = LastRecordTime
                .R.RecordsStarted = False
                
                .SendState = RequestMainRecords
                
                cmdDownLoad.Caption = "Cancel"
                Me.pbMainRecords.Value = 0
                .R.OpenRecordFile WindRpm
            End With
            
            lblNew = "Searching for new records..."
            Timer1.Interval = 150
            Timer1.Enabled = True
            
        Case "Cancel"
            
            frmEndurance.R.RecordsCanceled = False
            frmEndurance.SendState = CancelMainRecords
            frmEndurance.R.CloseFile
            lblNew = "Sending cancel request"
            
    End Select
    
End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)

    frmEndurance.R.CloseFile

End Sub

Private Sub ProgressBar1_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)

End Sub

Private Sub optInterval_Click(Index As Integer)

    If Not AutoOption Then
    
        lblResponse = "Waiting for response from tower"
        
        With frmEndurance
            .R.RecordIntervalReceived = False
            .RecIntervalString = "@!C79" + " " + Format(Index) + "#" + vbCr + vbLf
            .SendState = WaitingForRecordInterval
        End With
        
    End If
    
End Sub

Public Function GetNewestDate() As String
    Dim A$
    Dim X As Variant
    Dim FileName As String
    Dim FileNumber As Integer
    Dim Temp As String
    Dim pD As String
    Dim pT As String
    
    On Error GoTo Err
    
    FileName = frmEndurance.R.FileName(WindRpm)
    FileNumber = FreeFile
    
    GetNewestDate = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
    If Dir(FileName, vbNormal) <> "" Then
        
        Temp = fnReadLastLine(FileName)
        X = Split(Temp, ",")
        
        If UBound(X) = 3 Then
            pD = Trim(X(0))
            pT = Trim(X(1))
            If IsDate(pT) And IsDate(pD) Then
                GetNewestDate = pD + "," + pT
            End If
        End If
        
        
    End If
    
    Exit Function
    
Err:
    GetNewestDate = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
End Function

Private Sub Timer1_Timer()
    Select Case lblNew
        Case "Searching for new records..."
            lblNew = "Searching for new records.."
        Case "Searching for new records.."
            lblNew = "Searching for new records."
        Case "Searching for new records."
            lblNew = "Searching for new records"
        Case "Searching for new records"
            lblNew = "Searching for new records..."
        Case Else
            lblNew = "Searching for new records"
    End Select
End Sub
