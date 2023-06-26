VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmStackInfo 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Stack info"
   ClientHeight    =   3435
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7035
   Icon            =   "frmStackInfo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3435
   ScaleWidth      =   7035
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   855
      Left            =   120
      TabIndex        =   1
      Top             =   2520
      Width           =   6735
   End
   Begin MSFlexGridLib.MSFlexGrid grid 
      Height          =   2415
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6735
      _ExtentX        =   11880
      _ExtentY        =   4260
      _Version        =   393216
      Rows            =   9
      Cols            =   4
      FixedCols       =   0
      ScrollBars      =   0
   End
End
Attribute VB_Name = "frmStackInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Dim row
    Dim col
    
    For col = 0 To grid.Cols - 1
        grid.ColWidth(col) = grid.Width / grid.Cols
    Next col
    
    grid.TextMatrix(0, 0) = "Task"
    grid.TextMatrix(0, 1) = "Stack size"
    grid.TextMatrix(0, 2) = "Max used"
    grid.TextMatrix(0, 3) = "Min free"
    
    grid.TextMatrix(1, 0) = "Start"
    grid.TextMatrix(2, 0) = "AeroCommReceive"
    grid.TextMatrix(3, 0) = "MeasureSpeeds"
    grid.TextMatrix(4, 0) = "FaultMonitor"
    grid.TextMatrix(5, 0) = "Status"
    grid.TextMatrix(6, 0) = "TCPIP"
    grid.TextMatrix(7, 0) = "Timers"
    grid.TextMatrix(8, 0) = "MainThread"
    
    
    For row = 1 To grid.Rows - 1
        For col = 1 To grid.Cols - 1
            grid.row = row
            grid.col = col
            grid.CellAlignment = 4
        Next col
    Next row
    
    
    
End Sub


Public Property Let TaskArray(ByVal NewTaskArray As Variant)
    Dim i As Integer
    Dim row As Integer
    
    row = 1
    For i = 1 To 15 Step 2
        grid.TextMatrix(row, 1) = Format(Val(NewTaskArray(i)) + Val(NewTaskArray(i + 1)))
        grid.TextMatrix(row, 2) = NewTaskArray(i)
        grid.TextMatrix(row, 3) = NewTaskArray(i + 1)
        row = row + 1
    Next i
    
End Property
