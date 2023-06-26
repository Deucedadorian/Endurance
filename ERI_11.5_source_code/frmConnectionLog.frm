VERSION 5.00
Object = "{BD856031-3F73-11D3-94AA-00104B6CDBC6}#1.0#0"; "freeSize.ocx"
Begin VB.Form frmConnectionLog 
   Caption         =   "Connection log"
   ClientHeight    =   6495
   ClientLeft      =   120
   ClientTop       =   420
   ClientWidth     =   7170
   Icon            =   "frmConnectionLog.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6495
   ScaleWidth      =   7170
   StartUpPosition =   3  'Windows Default
   Begin freeSize.freeSizer freeSizer1 
      Left            =   2280
      Top             =   3720
      _ExtentX        =   1588
      _ExtentY        =   1376
      ResizeObjects   =   -1  'True
   End
   Begin VB.TextBox txtLog 
      Height          =   6495
      Left            =   0
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   0
      Width           =   7215
   End
End
Attribute VB_Name = "frmConnectionLog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Dim FileName As String
    Dim FileNumber As Integer
    Dim L As New Collection
    Dim Lines As Integer
    Dim A As String
    Dim i As Integer
    
    On Error Resume Next
    
    FileName = "c:\Endurance data files\Connection log.txt"
    FileNumber = FreeFile
    
    If Dir(FileName, vbNormal) <> "" Then
        Open FileName For Input As #FreeFile
    End If
    
    
    Do While Not EOF(FileNumber)
        Line Input #FileNumber, A
        L.Add A
    Loop
    
    Close #FileNumber
    
    Lines = L.count
        
    If Lines > 0 Then
    
        For i = 1 To Lines
            txtLog = txtLog + L.Item(i) + vbCr + vbLf
        Next i
        
    End If

End Sub
