VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmRecordsEvents 
   Caption         =   "Records (Events)"
   ClientHeight    =   6135
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   6270
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   6135
   ScaleWidth      =   6270
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Left            =   5400
      Top             =   5400
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   855
      Left            =   120
      TabIndex        =   8
      Top             =   5160
      Width           =   6015
   End
   Begin VB.Frame fraMainRecords 
      Caption         =   "Events"
      Height          =   4935
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6015
      Begin VB.CommandButton cmdDownLoad 
         Caption         =   "Download"
         Height          =   495
         Left            =   4440
         TabIndex        =   2
         Top             =   240
         Width           =   1455
      End
      Begin MSComctlLib.ProgressBar pbMainRecords 
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   2280
         Width           =   5775
         _ExtentX        =   10186
         _ExtentY        =   450
         _Version        =   393216
         Appearance      =   1
         Scrolling       =   1
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
         TabIndex        =   7
         Top             =   720
         Width           =   2775
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
         TabIndex        =   6
         Top             =   1080
         Width           =   3975
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
         TabIndex        =   4
         Top             =   360
         Width           =   4095
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
         TabIndex        =   3
         Top             =   1920
         Width           =   3495
      End
   End
End
Attribute VB_Name = "frmRecordsEvents"
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
                .R.OpenRecordFile Events
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


Public Function GetNewestDate() As String
    Dim A$
    Dim X As Variant
    Dim FileName As String
    Dim FileNumber As Integer
    Dim Temp As String
    Dim pD As String
    Dim pT As String
    
    On Error GoTo Err
    
    FileName = frmEndurance.R.FileName(Events)
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
Public Function fnReadLastLine(strFileName As String) As String

    Dim fPos As Long, LastLine As String, aByte As Byte
    Dim testCRLF As String * 2
    Const LF = 10

    On Error GoTo fnReadLastLine_Error

    Open strFileName For Binary As #1
    fPos = LOF(1) + 1
    Do
        fPos = fPos - 2
        Seek #1, fPos
        Get #1, , testCRLF
    Loop While testCRLF = vbCrLf
    Do
        fPos = fPos - 1
        Seek #1, fPos
        Get #1, , aByte
        
        'Debug.Print Chr$(aByte)
        
    Loop Until aByte = LF
    Line Input #1, LastLine
    Close #1
    fnReadLastLine = Trim$(LastLine)

ExitHere:
    On Error GoTo 0
    Exit Function

fnReadLastLine_Error:
    fnReadLastLine = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
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

