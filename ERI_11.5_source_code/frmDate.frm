VERSION 5.00
Object = "{8E27C92E-1264-101C-8A2F-040224009C02}#7.0#0"; "MSCAL.OCX"
Begin VB.Form frmDate 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Tower date ..."
   ClientHeight    =   4800
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   8310
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4800
   ScaleWidth      =   8310
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin MSACAL.Calendar Calendar 
      Height          =   3735
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   7815
      _Version        =   524288
      _ExtentX        =   13785
      _ExtentY        =   6588
      _StockProps     =   1
      BackColor       =   -2147483633
      Year            =   2005
      Month           =   2
      Day             =   8
      DayLength       =   1
      MonthLength     =   2
      DayFontColor    =   0
      FirstDay        =   1
      GridCellEffect  =   1
      GridFontColor   =   10485760
      GridLinesColor  =   -2147483632
      ShowDateSelectors=   -1  'True
      ShowDays        =   -1  'True
      ShowHorizontalGrid=   -1  'True
      ShowTitle       =   -1  'True
      ShowVerticalGrid=   -1  'True
      TitleFontColor  =   10485760
      ValueIsNull     =   0   'False
      BeginProperty DayFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty GridFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      BeginProperty TitleFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton cmdEqualDate 
      Caption         =   "Set turbine controller date to the same date as the computer"
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
      Left            =   360
      TabIndex        =   0
      Top             =   3960
      Width           =   3975
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
      Left            =   4440
      TabIndex        =   1
      Top             =   3960
      Width           =   3615
   End
End
Attribute VB_Name = "frmDate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public Sub SendDate()
    
    Dim sDay As String
    Dim sMonth As String
    Dim sYear As String
    
    sDay = Format(Calendar.Day, "00")
    sMonth = Format(Calendar.Month, "00")
    sYear = Right$(Format(Calendar.Year, "00"), 2)

    'sDay sMonth + sYear + Chr(199) + vbCr

    
End Sub

Private Sub Calendar_Click()
    
    With frmEndurance
        .DateToSend = Format(Calendar.Value, "yy-mm-dd")
        .R.DateTimeReceived = False
        .SendState = SendingDate
    End With
    
End Sub

Private Sub cmdEqualDate_Click()
    Calendar.Today
    
    With frmEndurance
        .DateToSend = Format(Calendar.Value, "yy-mm-dd")
        .R.DateTimeReceived = False
        .SendState = SendingDate
    End With

End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub Command1_Click()

    With frmEndurance
        .DateToSend = "08-12-13" 'yy-mm-dd
        .SendState = SendingDate
        
    End With
    
End Sub

