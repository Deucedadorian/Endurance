VERSION 5.00
Begin VB.Form frmTrigger 
   Caption         =   "Diagnostic triggers"
   ClientHeight    =   7050
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   3495
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   7050
   ScaleWidth      =   3495
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSendTriggers 
      Caption         =   "Send"
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
      Height          =   615
      Left            =   120
      TabIndex        =   19
      Top             =   6360
      Width           =   3255
   End
   Begin VB.CommandButton cmdTrigger 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   18
      Top             =   4920
      Width           =   3255
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "Exit without sending"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   17
      Top             =   5640
      Width           =   3255
   End
   Begin VB.Frame Frame1 
      Caption         =   "Diagnostic triggers"
      Height          =   4335
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3255
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Power down"
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
         Index           =   15
         Left            =   240
         TabIndex        =   16
         Top             =   3960
         Width           =   2175
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Unknown error"
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
         Index           =   14
         Left            =   240
         TabIndex        =   15
         Top             =   3720
         Width           =   2175
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Grid fault"
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
         Index           =   13
         Left            =   240
         TabIndex        =   14
         Top             =   3480
         Width           =   1815
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Motoring error"
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
         Index           =   12
         Left            =   240
         TabIndex        =   13
         Top             =   3240
         Width           =   2055
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Anemometer error"
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
         Index           =   11
         Left            =   240
         TabIndex        =   12
         Top             =   3000
         Width           =   2295
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "RPM error"
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
         Index           =   10
         Left            =   240
         TabIndex        =   11
         Top             =   2760
         Width           =   2055
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "HSS overspeed fault"
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
         Index           =   9
         Left            =   240
         TabIndex        =   10
         Top             =   2520
         Width           =   2535
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "LSS overspeed fault"
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
         Index           =   8
         Left            =   240
         TabIndex        =   9
         Top             =   2280
         Width           =   2535
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "High wind"
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
         Index           =   7
         Left            =   240
         TabIndex        =   8
         Top             =   2040
         Width           =   2055
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Generate high"
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
         Index           =   6
         Left            =   240
         TabIndex        =   7
         Top             =   1800
         Width           =   2175
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Generate low"
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
         Index           =   5
         Left            =   240
         TabIndex        =   6
         Top             =   1560
         Width           =   2055
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Motor"
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
         Index           =   4
         Left            =   240
         TabIndex        =   5
         Top             =   1320
         Width           =   1935
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Free-wheel"
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
         Index           =   3
         Left            =   240
         TabIndex        =   4
         Top             =   1080
         Width           =   1935
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Cut-in"
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
         Index           =   2
         Left            =   240
         TabIndex        =   3
         Top             =   840
         Width           =   1815
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Calm"
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
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   600
         Width           =   2055
      End
      Begin VB.CheckBox chkTrigger 
         Caption         =   "Halt "
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
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   2415
      End
   End
   Begin VB.Label lblWaiting 
      Caption         =   "lblWaiting"
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
      Left            =   240
      TabIndex        =   20
      Top             =   4560
      Width           =   3135
   End
End
Attribute VB_Name = "frmTrigger"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub cmdSendTriggers_Click()
    
    With frmEndurance
        .R.TriggersReceived = False
        .SendTriggerString = BuildTriggerString(.R.TriggerActive)
        .SendState = SendingTriggers
    End With
    
    DisableButtons
    
End Sub

Public Sub UpdateTriggers()
    Dim T As String
    Dim i As Integer
    
    With frmEndurance
        
        T = .R.TriggerString
        
        For i = 1 To Len(T) - 1
            If Mid(T, i, 1) = "1" Then
                chkTrigger(i - 1).Value = Checked
            Else
                chkTrigger(i - 1).Value = Unchecked
            End If
        Next i
        
        If .R.TriggerActive Then
            cmdTrigger.Caption = "Trigger has occured ... click here to reset trigger"
        Else
            cmdTrigger.Caption = "Waiting for trigger ... click here to trigger manually"
        End If
    
        
    End With
    
    EnableButtons
    
End Sub

Private Sub cmdTrigger_Click()

    With frmEndurance
        .R.TriggersReceived = False
        .SendTriggerString = BuildTriggerString(Not .R.TriggerActive)
        .SendState = SendingTriggers
    End With
    
    DisableButtons

End Sub

Private Sub Form_Load()
    DisableButtons
End Sub

Public Sub DisableButtons()
    Dim i
    
    lblWaiting = "Waiting for response"
    
    cmdSendTriggers.Enabled = False
    cmdTrigger.Enabled = False
    For i = 0 To Me.chkTrigger.count - 1
        Me.chkTrigger(i).Enabled = False
    Next i
    

End Sub
Public Sub EnableButtons()
    Dim i
    
    cmdSendTriggers.Enabled = True
    cmdTrigger.Enabled = True
    For i = 0 To Me.chkTrigger.count - 1
        Me.chkTrigger(i).Enabled = True
    Next i
    
    lblWaiting = ""

End Sub


Public Function BuildTriggerString(Trigger As Boolean) As String
    
    Dim i

    For i = 0 To chkTrigger.count - 1
        If chkTrigger(i) = Checked Then
            BuildTriggerString = BuildTriggerString + "1"
        Else
            BuildTriggerString = BuildTriggerString + "0"
        End If
    Next i
    
    If Trigger Then
        BuildTriggerString = BuildTriggerString + "1"
    Else
        BuildTriggerString = BuildTriggerString + "0"
    End If
    

End Function
