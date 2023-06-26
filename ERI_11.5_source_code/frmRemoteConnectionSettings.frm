VERSION 5.00
Begin VB.Form frmRemoteConnectionSettings 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Remote connection settings"
   ClientHeight    =   2850
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4680
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2850
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send"
      Height          =   615
      Left            =   2160
      TabIndex        =   11
      Top             =   2160
      Width           =   2415
   End
   Begin VB.TextBox txtPort 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1800
      TabIndex        =   10
      Top             =   1680
      Width           =   2655
   End
   Begin VB.TextBox txtGateway 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1800
      TabIndex        =   9
      Top             =   1320
      Width           =   2655
   End
   Begin VB.TextBox txtNameServer 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1800
      TabIndex        =   8
      Top             =   960
      Width           =   2655
   End
   Begin VB.TextBox txtNetmask 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1800
      TabIndex        =   7
      Top             =   600
      Width           =   2655
   End
   Begin VB.TextBox txtIPAddress 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   315
      Left            =   1800
      TabIndex        =   1
      Top             =   240
      Width           =   2655
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   2160
      Width           =   1935
   End
   Begin VB.Label lblPort 
      Alignment       =   1  'Right Justify
      Caption         =   "Port"
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
      TabIndex        =   6
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label lblGateway 
      Alignment       =   1  'Right Justify
      Caption         =   "Gateway"
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
      TabIndex        =   5
      Top             =   1320
      Width           =   1455
   End
   Begin VB.Label lblNameServer 
      Alignment       =   1  'Right Justify
      Caption         =   "Name server"
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
      TabIndex        =   4
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label lblNetmask 
      Alignment       =   1  'Right Justify
      Caption         =   "Netmask"
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
      TabIndex        =   3
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label lblIPAddress 
      Alignment       =   1  'Right Justify
      Caption         =   "IP address"
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
      TabIndex        =   2
      Top             =   240
      Width           =   1455
   End
End
Attribute VB_Name = "frmRemoteConnectionSettings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mIPAddress As String
Private mGateway As String
Private mNetmask As String
Private mNameServer As String
Private mPort As String

Public IPConfirmed As Boolean




Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    
    frmEndurance.SendState = SendingNulls
    Unload Me

End Sub


Public Property Get IPAddress() As String
    IPAddress = mIPAddress
End Property

Public Property Let IPAddress(ByVal NewIPAddress As String)
    mIPAddress = NewIPAddress
    txtIPAddress = mIPAddress
End Property
Public Property Get Netmask() As String
    Netmask = mNetmask
End Property

Public Property Let Netmask(ByVal NewNetmask As String)
    mNetmask = NewNetmask
    txtNetmask = mNetmask
End Property

Public Property Get Gateway() As String
    Gateway = mGateway
End Property

Public Property Let Gateway(ByVal NewGateway As String)
    mGateway = NewGateway
    txtGateway = mGateway
End Property

Public Property Get NameServer() As String
    NameServer = mNameServer
End Property

Public Property Let NameServer(ByVal NewNameServer As String)
    mNameServer = NewNameServer
    txtNameServer = mNameServer
End Property
Public Property Get Port() As String
    Port = mPort
End Property

Public Property Let Port(ByVal NewPort As String)
    mPort = NewPort
    txtPort = mPort
End Property

Private Sub cmdSend_Click()
    Dim ValidData As Boolean
        
        ValidData = True
        
        If Not ValidIP(txtIPAddress) Then ValidData = False
        If Not ValidIP(txtNetmask) Then ValidData = False
        If Not ValidIP(txtGateway) Then ValidData = False
        If Not ValidIP(txtNameServer) Then ValidData = False
        If Not (IsNumeric(txtPort)) Then ValidData = False
        If Val(txtPort) < 0 Then ValidData = False
        
        If ValidData Then
            mIPAddress = txtIPAddress
            mNetmask = txtNetmask
            mGateway = txtGateway
            mNameServer = txtNameServer
            mPort = txtPort

            txtIPAddress = ""
            txtNetmask = ""
            txtGateway = ""
            txtNameServer = ""
            txtPort = ""
        
            frmEndurance.R.IPInfoReceived = False
            frmEndurance.SendState = WaitingForIPConfirm
        Else
            MsgBox ("Error in IP settings")
        End If
        
End Sub

Private Sub txtGateway_Change()
    ColorIPBox txtGateway
End Sub

Private Sub txtIPAddress_Change()
    ColorIPBox txtIPAddress
End Sub

Public Sub ColorIPBox(Box As TextBox)
    Dim S As String
    
    S = Box.Text
    
    If ValidIP(S) Then
        Box.ForeColor = &H80000008
    Else
        Box.ForeColor = &HFF
    End If

End Sub

Private Sub txtNameServer_Change()
    ColorIPBox txtNameServer
End Sub

Private Sub txtNetmask_Change()
    ColorIPBox txtNetmask

End Sub
