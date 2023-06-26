VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmRecords2 
   Caption         =   "Records "
   ClientHeight    =   4305
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   10065
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4305
   ScaleWidth      =   10065
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ProgressBar pbRecords 
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   3120
      Width           =   9735
      _ExtentX        =   17171
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
      Scrolling       =   1
   End
   Begin VB.Frame fraInfo 
      Height          =   2535
      Left            =   3840
      TabIndex        =   7
      Top             =   120
      Width           =   6015
      Begin MSFlexGridLib.MSFlexGrid grid 
         Height          =   1815
         Left            =   120
         TabIndex        =   8
         Top             =   240
         Width           =   5775
         _ExtentX        =   10186
         _ExtentY        =   3201
         _Version        =   393216
         Rows            =   5
         FixedRows       =   0
         FixedCols       =   0
         ScrollBars      =   0
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Times New Roman"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   6480
      TabIndex        =   6
      Top             =   3480
      Width           =   3375
   End
   Begin VB.CommandButton cmdDownload 
      Caption         =   "Download"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   120
      TabIndex        =   5
      Top             =   3480
      Width           =   6255
   End
   Begin VB.Frame fraBuffer 
      Caption         =   "Record buffer "
      Height          =   2535
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3615
      Begin VB.OptionButton optBuffer 
         Caption         =   "Events (Diagnostic)"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   3
         Left            =   240
         TabIndex        =   4
         Top             =   1920
         Width           =   2295
      End
      Begin VB.OptionButton optBuffer 
         Caption         =   "Wind and RPM (Diagnostic)"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   465
         Index           =   2
         Left            =   240
         TabIndex        =   3
         Top             =   1350
         Width           =   3255
      End
      Begin VB.OptionButton optBuffer 
         Caption         =   "Events"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   960
         Width           =   1695
      End
      Begin VB.OptionButton optBuffer 
         Caption         =   "Wind and Power"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   3015
      End
   End
   Begin VB.Label lblProgress 
      Caption         =   "lblProgress"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   2760
      Width           =   9735
   End
End
Attribute VB_Name = "frmRecords2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private mFileExists As Boolean
Private mBuffer As Integer
Private mNewestDateOnFile As String

Private Sub cmdDownload_Click()
    Dim LastRecordTime As String
    Dim i As Integer
    
    Select Case cmdDownload.Caption
        
        Case "Download"
            
            
            With frmEndurance
                
                .RecordRequestDate = mNewestDateOnFile
                .R.RecordsStarted = False
                
                .SendState = RequestMainRecords
                
                cmdDownload.Caption = "Cancel"
                
                Me.fraBuffer.Enabled = False
                
                
                Me.pbRecords.Value = 0
                .R.OpenRecordFile mBuffer
            End With
            
            lblProgress = "Searching for new records..."
            
        Case "Cancel"
            
            frmEndurance.R.RecordsCanceled = False
            frmEndurance.SendState = CancelMainRecords
            frmEndurance.R.CloseFile
            lblProgress = "Sending cancel request"
            
    End Select
    

End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub


Private Sub Form_Load()
    Dim i As Integer
    
    With grid
        .Cols = 2
        .Rows = 5
        .ColWidth(0) = 0.5 * .Width
        .ColWidth(1) = .Width - .ColWidth(0)
        .TextMatrix(0, 0) = "Max records at turbine"
        .TextMatrix(1, 0) = "Records at turbine"
        .TextMatrix(2, 0) = "Oldest record at turbine"
        .TextMatrix(3, 0) = "Newest record at turbine"
        .TextMatrix(4, 0) = "Newest record on file"
        
        'left justify column 1
        .Col = 1
        For i = 0 To .Rows - 1
            .Row = i
            .CellAlignment = 1
        Next i
        
    End With
    
    
    If frmEndurance.R.ProgramVersion >= "9.1.0" Then
        Me.optBuffer(0).Caption = "Wind and Power"
    Else
        Me.optBuffer(0).Caption = "Wind and RPM"
    End If
    
    optBuffer_Click 0
    
End Sub

Private Sub Label1_Click()
End Sub

Private Sub optBuffer_Click(Index As Integer)
    Dim X
    Dim i As Integer
    
    ClearGrid



    lblProgress = "Waiting for record info"
    
    mBuffer = Index
    
    With frmEndurance
        .R.RecordBuffer = Index
        .R.ReceivedRecInfo = False
        .SendState = RequestRecordInfo
    End With

    Select Case mBuffer
        Case WindRpm
            Me.fraInfo.Caption = "Wind and RPM record buffer"
        Case Events
            Me.fraInfo.Caption = "Events record buffer"
        Case WindRPMDiag
            Me.fraInfo.Caption = "Diagnostic Wind and RPM record buffer"
        Case EventsDiag
            Me.fraInfo.Caption = "Diagnostic events record buffer"
    End Select
    
    mNewestDateOnFile = GetNewestDate(mBuffer) 'Also sets mFileExists to true or false
    
    If mFileExists Then
        grid.TextMatrix(4, 1) = mNewestDateOnFile
    Else
        grid.TextMatrix(4, 1) = "N/A"
    End If
    
    
    Me.fraBuffer.Enabled = False
    Me.cmdDownload.Enabled = False

End Sub

Public Sub ClearGrid()
    Dim Row As Integer
    Dim Col As Integer
    
    Col = 1
    
    For Row = 0 To grid.Rows - 1
        grid.TextMatrix(Row, Col) = ""
    Next Row
    
    
End Sub
Private Function GetNewestDate(ByVal Buf As Integer) As String
    Dim A$
    Dim X As Variant
    Dim FileNumber As Integer
    Dim FileName As String
    Dim Temp As String
    Dim pD As String
    Dim pT As String
    
    On Error GoTo Err
    
    FileName = frmEndurance.R.FileName(Buf)
    FileNumber = FreeFile
    
    GetNewestDate = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
    If Dir(FileName, vbNormal) <> "" Then
        mFileExists = True
        Temp = fnReadLastLine(FileName)
        X = Split(Temp, ",")
        
        If UBound(X) > 1 Then
            pD = Trim(X(0))
            pT = Trim(X(1))
            If IsDate(pT) And IsDate(pD) Then
                GetNewestDate = pD + "," + pT
            End If
        End If
        
    Else
        mFileExists = False
    End If
    
    Exit Function
    
Err:
    GetNewestDate = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
End Function


