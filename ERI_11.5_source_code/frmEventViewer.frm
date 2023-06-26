VERSION 5.00
Object = "{BD856031-3F73-11D3-94AA-00104B6CDBC6}#1.0#0"; "freeSize.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmEventViewer 
   Caption         =   "Diagnostic event viewer"
   ClientHeight    =   9450
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7815
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   9450
   ScaleWidth      =   7815
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame Frame1 
      Caption         =   "Source file ..."
      Height          =   615
      Left            =   120
      TabIndex        =   5
      Top             =   120
      Width           =   7575
      Begin VB.CommandButton cmdBrowse 
         Caption         =   "Browse..."
         Height          =   255
         Left            =   6480
         TabIndex        =   7
         Top             =   240
         Width           =   975
      End
      Begin VB.TextBox txtSource 
         Height          =   285
         Left            =   120
         Locked          =   -1  'True
         TabIndex        =   6
         Top             =   240
         Width           =   6255
      End
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2760
      Top             =   1680
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin freeSize.freeSizer freeSizer1 
      Left            =   6000
      Top             =   3720
      _ExtentX        =   1588
      _ExtentY        =   1376
      ResizeFonts     =   -1  'True
      ResizeObjects   =   -1  'True
      MoveObjects     =   -1  'True
      SmartSizing     =   -1  'True
      SmartPositioning=   -1  'True
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   9000
      Width           =   7575
   End
   Begin VB.HScrollBar hsbEvents 
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   8640
      Width           =   7575
   End
   Begin VB.Image imgFlow 
      Height          =   7335
      Left            =   120
      Stretch         =   -1  'True
      Top             =   840
      Width           =   7575
   End
   Begin VB.Label lblText 
      Caption         =   "lblText"
      Height          =   255
      Left            =   4560
      TabIndex        =   4
      Top             =   8280
      Width           =   3135
   End
   Begin VB.Label lblCode 
      Caption         =   "lblCode"
      Height          =   255
      Left            =   3240
      TabIndex        =   3
      Top             =   8280
      Width           =   1215
   End
   Begin VB.Label lblDate 
      Caption         =   "lblDate"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   8280
      Width           =   2895
   End
End
Attribute VB_Name = "frmEventViewer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Events(12000, 0 To 2) 'Date, Time, Event code
Private mRecordCount As Integer
Private mFileName As String
Private EventCodes(255, 1 To 2) 'File name, text

Private Sub cmdBrowse_Click()
    
    With CommonDialog1
        If Dir("c:\Endurance data files", vbDirectory) <> "" Then
            .InitDir = "c:\Endurance data files"
        End If
        .Filter = "Diagnostic events files|diagnostic events.txt|All text files|*.txt"
        .ShowOpen
    End With
    
    txtSource = CommonDialog1.FileName
    SaveSetting App.EXEName, "Logging", "Diagnostic events file name", txtSource
    
End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Me.lblCode = ""
    Me.lblDate = ""
    Me.lblText = ""
End Sub

Private Sub hsbEvents_Change()
    UpdateLabels
End Sub

Public Sub UpdateLabels()
    Dim DString As String
    Dim FileName As String
    Dim jpeg As String
    Dim i As Integer
    Dim EvalDate As Date
    On Error Resume Next
    
    'If Date > CDate("may 19,2009") Then
    '    Exit Sub
    'End If
    
    DString = Events(hsbEvents.Value, 0)
    EvalDate = CDate(DString)
    
  '  If EvalDate > CDate("may 19,2009") Then
  '      DString = DString + " " + Events(hsbEvents.Value, 1)
  '      Me.lblCode = "Code=??"
  '      Me.lblDate = DString
  '      Me.lblText = ""
  '  Else
        DString = DString + " " + Events(hsbEvents.Value, 1)
        Me.lblCode = "Code=" + Format(Events(hsbEvents.Value, 2))
        Me.lblDate = DString
        Me.lblText = EventCodes(Events(hsbEvents.Value, 2), 2)
    
    
        i = hsbEvents
        Do Until EventCodes(Events(i, 2), 1) <> ""
            If i > 1 Then
                i = i - 1
            Else
                Exit Do
            End If
        Loop
        jpeg = EventCodes(Events(i, 2), 1)
        
        If jpeg <> "" Then
            FileName = App.Path + "\" + jpeg
            If Dir(FileName) <> "" Then
                If imgFlow <> FileName Then
                    imgFlow = LoadPicture(FileName)
                End If
            End If
        Else
            imgFlow = LoadPicture("")
        End If
        
    'End If
    
End Sub

Private Sub hsbEvents_Scroll()
    UpdateLabels

End Sub

Public Sub GetEvents()
    Dim FileNumber As Integer
    Dim A$
    Dim Record As Variant
    Dim LastPic As String
    
    
    'mFileName = "c:\Endurance data files\Floyd's desk\" + "diagnostic events.txt"
    mFileName = Me.txtSource
    If mFileName <> "" Then
        If Dir(mFileName) <> "" Then
            
            FileNumber = FreeFile
            Open mFileName For Input As #FileNumber
            mRecordCount = 0
            Do While Not EOF(FileNumber)
                Line Input #FileNumber, A$
                
                Record = Split(A$, ",")
                
                If UBound(Record) = 3 Then
                    If IsDate(Record(0)) And IsDate(Record(1)) Then
                        If IsNumeric(Record(2)) Then
                            Events(mRecordCount, 0) = Record(0) 'Date
                            Events(mRecordCount, 1) = Record(1) 'Time
                            Events(mRecordCount, 2) = Record(2) 'Code
                            mRecordCount = mRecordCount + 1
                        End If
                    End If
                End If
                
                If mRecordCount > 12000 Then
                    MsgBox ("More than 12000 records ... please delete some of the older records")
                    Exit Do
                End If
                
            Loop
            
            Close #FileNumber
            
            hsbEvents.Min = 0
            
            If mRecordCount > 0 Then
                hsbEvents.Max = mRecordCount - 1
            Else
                hsbEvents.Max = 0
            End If
            
            hsbEvents.Value = hsbEvents.Max
                
        Else
            MsgBox (mFileName + " not found")
            Unload Me
        End If
    End If
    
End Sub

Public Sub GetTranslations()
    
    Dim FileNumber As Integer
    Dim A$
    Dim Record As Variant
    Dim pRecordCount As Integer
    Dim pCode As Integer
    
    mFileName = App.Path + "\Event codes.txt"

    FileNumber = FreeFile
    If Dir(mFileName) <> "" Then
        Open mFileName For Input As #FileNumber
    
        Do While Not EOF(FileNumber)
            Line Input #FileNumber, A$
                If Left(A$, 1) <> ";" Then
                Record = Split(A$, ",")
                If UBound(Record) = 2 Then
                    If IsNumeric(Record(0)) Then
                        pCode = Record(0)
                        EventCodes(pCode, 1) = RemoveWhiteSpace(Record(1))
                        EventCodes(pCode, 2) = RemoveWhiteSpace(Record(2))
                    End If
                End If
            End If
        Loop
        
        Close #FileNumber
        
    End If 'Dir(mFileName) <> "" Then
    
End Sub

Private Sub txtSource_Change()

    GetTranslations 'Opens "event codes.txt"
    GetEvents 'Opens "diagnostic events.txt"
    UpdateLabels

End Sub
