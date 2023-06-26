VERSION 5.00
Begin VB.Form frmCommTest 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Select test mode"
   ClientHeight    =   4020
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   2445
   Icon            =   "frmCommTest.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4020
   ScaleWidth      =   2445
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCommTest 
      Caption         =   "Anemometer test"
      Height          =   735
      Index           =   4
      Left            =   240
      TabIndex        =   4
      Top             =   3120
      Width           =   2055
   End
   Begin VB.CommandButton cmdCommTest 
      Caption         =   "Cut out test"
      Height          =   735
      Index           =   3
      Left            =   240
      TabIndex        =   3
      Top             =   2400
      Width           =   2055
   End
   Begin VB.CommandButton cmdCommTest 
      Caption         =   "RPM error test"
      Height          =   735
      Index           =   2
      Left            =   240
      TabIndex        =   2
      Top             =   1680
      Width           =   2055
   End
   Begin VB.CommandButton cmdCommTest 
      Caption         =   "Over speed test"
      Height          =   735
      Index           =   1
      Left            =   240
      TabIndex        =   1
      Top             =   960
      Width           =   2055
   End
   Begin VB.CommandButton cmdCommTest 
      Caption         =   "Normal run"
      Height          =   735
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   2055
   End
End
Attribute VB_Name = "frmCommTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdCommTest_Click(Index As Integer)

With frmEndurance
    .TestModeSent = False
    .TestMode = Index + 1
    .SetNetworkTimeout
    .SendState = WatingForCommTest
End With
    
Unload Me

End Sub

