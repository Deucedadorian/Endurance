VERSION 5.00
Object = "{82D1F7B2-21F5-11D5-8CE1-0080C86ADD99}#1.0#0"; "LED.ocx"
Begin VB.Form frmOutputs 
   Caption         =   "Processor I/O"
   ClientHeight    =   6000
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   3615
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   6000
   ScaleWidth      =   3615
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame fraInputs 
      Caption         =   "Inputs"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   120
      TabIndex        =   18
      Top             =   240
      Width           =   3375
      Begin VB.Label lblInupts 
         Caption         =   "Reset switch"
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
         TabIndex        =   24
         Top             =   1560
         Width           =   2775
      End
      Begin VB.Label lblInupts 
         Caption         =   "Test jumper"
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
         TabIndex        =   23
         Top             =   1320
         Width           =   2775
      End
      Begin VB.Label lblInupts 
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
         Index           =   3
         Left            =   240
         TabIndex        =   22
         Top             =   1080
         Width           =   2775
      End
      Begin VB.Label lblInupts 
         Caption         =   "Anemometer"
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
         TabIndex        =   21
         Top             =   840
         Width           =   2775
      End
      Begin VB.Label lblInupts 
         Caption         =   "High speed shaft"
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
         TabIndex        =   20
         Top             =   600
         Width           =   2775
      End
      Begin VB.Label lblInupts 
         Caption         =   "Low speed shaft"
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
         TabIndex        =   19
         Top             =   360
         Width           =   2775
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
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
      Height          =   735
      Left            =   120
      TabIndex        =   1
      Top             =   5160
      Width           =   3375
   End
   Begin VB.Frame fraOutputs 
      Caption         =   "Digital outputs"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2655
      Left            =   120
      TabIndex        =   0
      Top             =   2400
      Width           =   3375
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   0
         Left            =   240
         TabIndex        =   2
         Top             =   480
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   1
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   2
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   3
         Left            =   240
         TabIndex        =   5
         Top             =   1200
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   4
         Left            =   240
         TabIndex        =   6
         Top             =   1440
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   5
         Left            =   240
         TabIndex        =   7
         Top             =   1680
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   6
         Left            =   240
         TabIndex        =   8
         Top             =   1920
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin LEDcontrolProject.LED ledOutput 
         Height          =   180
         Index           =   7
         Left            =   240
         TabIndex        =   9
         Top             =   2160
         Width           =   180
         _ExtentX        =   318
         _ExtentY        =   318
         Color           =   1
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D7 Brake release"
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
         Left            =   600
         TabIndex        =   17
         Top             =   2160
         Width           =   2175
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D6 Run cap"
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
         Left            =   600
         TabIndex        =   16
         Top             =   1920
         Width           =   1695
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D5 Resistor"
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
         Left            =   600
         TabIndex        =   15
         Top             =   1680
         Width           =   1695
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D4 SSR Hot 1"
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
         Left            =   600
         TabIndex        =   14
         Top             =   1440
         Width           =   1695
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D3 External watchdog"
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
         Left            =   600
         TabIndex        =   13
         Top             =   1200
         Width           =   2535
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D2 Motor"
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
         Left            =   600
         TabIndex        =   12
         Top             =   960
         Width           =   1695
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D1 SSR Hot 2"
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
         Left            =   600
         TabIndex        =   11
         Top             =   720
         Width           =   1695
      End
      Begin VB.Label lblOutputs 
         Caption         =   "D0 SSR Neutral"
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
         Left            =   600
         TabIndex        =   10
         Top             =   480
         Width           =   1695
      End
   End
End
Attribute VB_Name = "frmOutputs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOK_Click()
    Unload Me
End Sub
