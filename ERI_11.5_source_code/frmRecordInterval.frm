VERSION 5.00
Begin VB.Form frmRecordInterval 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Recording interval "
   ClientHeight    =   3210
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6330
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3210
   ScaleWidth      =   6330
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send"
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
      TabIndex        =   14
      Top             =   2520
      Width           =   4215
   End
   Begin VB.Frame Frame2 
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
      Height          =   1935
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6135
      Begin VB.OptionButton optInterval 
         Caption         =   "60 minute"
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
         Index           =   15
         Left            =   4680
         TabIndex        =   19
         Top             =   1440
         Width           =   1335
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
         Index           =   14
         Left            =   4680
         TabIndex        =   18
         Top             =   1080
         Width           =   1335
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "20 minute"
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
         Index           =   13
         Left            =   4680
         TabIndex        =   17
         Top             =   720
         Width           =   1335
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
         Index           =   12
         Left            =   4680
         TabIndex        =   16
         Top             =   360
         Width           =   1335
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "2 second"
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
         TabIndex        =   13
         Top             =   360
         Width           =   1455
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "5 second"
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
         TabIndex        =   12
         Top             =   720
         Width           =   1455
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "10 second"
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
         TabIndex        =   11
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
         Index           =   3
         Left            =   240
         TabIndex        =   10
         Top             =   1440
         Width           =   1455
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "20 second"
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
         Left            =   1800
         TabIndex        =   9
         Top             =   360
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
         Index           =   5
         Left            =   1800
         TabIndex        =   8
         Top             =   720
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
         Index           =   6
         Left            =   1800
         TabIndex        =   7
         Top             =   1080
         Width           =   1455
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "2 minute"
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
         Left            =   1800
         TabIndex        =   6
         Top             =   1440
         Width           =   1455
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "3 minute"
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
         Left            =   3240
         TabIndex        =   5
         Top             =   360
         Width           =   1335
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "4 minute"
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
         Left            =   3240
         TabIndex        =   4
         Top             =   720
         Width           =   1335
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
         Index           =   10
         Left            =   3240
         TabIndex        =   3
         Top             =   1080
         Width           =   1335
      End
      Begin VB.OptionButton optInterval 
         Caption         =   "10 minute"
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
         Left            =   3240
         TabIndex        =   2
         Top             =   1440
         Width           =   1335
      End
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
      Height          =   615
      Left            =   4440
      TabIndex        =   0
      Top             =   2520
      Width           =   1815
   End
   Begin VB.Label lblWaiting 
      Caption         =   "Waiting for response ..."
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
      TabIndex        =   15
      Top             =   2160
      Width           =   6135
   End
End
Attribute VB_Name = "frmRecordInterval"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()
    Unload Me
End Sub


Public Sub WaitForResponse()
    Dim i As Integer
    
    lblWaiting = "Waiting for response"
    
    For i = 0 To optInterval.count - 1
        optInterval(i).Enabled = False
    Next i
    
    cmdSend.Enabled = False
    
    
    
    
    
    
End Sub

Public Sub UpdateInterval()
    Dim i As Integer
    
    lblWaiting = ""
    
    For i = 0 To optInterval.count - 1
        optInterval(i).Enabled = True
    Next i
    
    optInterval(frmEndurance.R.RecordInterval) = True
    
    cmdSend.Enabled = True

End Sub

Private Sub cmdSend_Click()
    Dim i As Integer
    
    For i = 0 To optInterval.count - 1
        If optInterval(i) = True Then
            frmEndurance.RecIntervalString = Format(i, "00")
        End If
    Next i
        
    frmEndurance.R.RecordIntervalReceived = False
    frmEndurance.SendState = SettingRecordInterval
    WaitForResponse
    
End Sub
