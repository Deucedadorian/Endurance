VERSION 5.00
Begin VB.Form frmSelectSerialPort 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Connection settings"
   ClientHeight    =   4425
   ClientLeft      =   45
   ClientTop       =   525
   ClientWidth     =   4815
   ControlBox      =   0   'False
   Icon            =   "frmSelectSerialPort.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4425
   ScaleWidth      =   4815
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame fraPassword 
      Caption         =   "Password"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   120
      TabIndex        =   9
      Top             =   2400
      Width           =   4575
      Begin VB.CheckBox chkConcealPAssword 
         Caption         =   "Conceal password"
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
         Left            =   2160
         TabIndex        =   12
         Top             =   600
         Width           =   2295
      End
      Begin VB.CheckBox chkSavePassword 
         Caption         =   "Save password"
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
         TabIndex        =   11
         Top             =   600
         Width           =   1935
      End
      Begin VB.TextBox txtPassword 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   120
         TabIndex        =   10
         Top             =   240
         Width           =   4335
      End
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
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
      TabIndex        =   8
      Top             =   3600
      Width           =   2055
   End
   Begin VB.Frame fraNetworkAddress 
      Caption         =   "Network address"
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
      Height          =   855
      Left            =   120
      TabIndex        =   6
      Top             =   1440
      Visible         =   0   'False
      Width           =   4575
      Begin VB.TextBox txtNetworkAddress 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   345
         Left            =   120
         TabIndex        =   7
         Top             =   360
         Width           =   4335
      End
   End
   Begin VB.Frame fraConnectUsing 
      Caption         =   "Connect using"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   4575
      Begin VB.OptionButton optConnectionType 
         Caption         =   "Network"
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
         TabIndex        =   5
         Top             =   720
         Width           =   1335
      End
      Begin VB.OptionButton optConnectionType 
         Caption         =   "Serial port"
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
         TabIndex        =   4
         Top             =   360
         Value           =   -1  'True
         Width           =   1575
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
      Height          =   735
      Left            =   2280
      TabIndex        =   2
      Top             =   3600
      Width           =   2415
   End
   Begin VB.Frame fraPorts 
      Caption         =   "Select a serial port "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   120
      TabIndex        =   0
      Top             =   1440
      Width           =   4215
      Begin VB.ComboBox cboPort 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   120
         TabIndex        =   1
         Text            =   "Combo1"
         Top             =   360
         Width           =   3975
      End
   End
   Begin VB.Menu mnuTimeOut 
      Caption         =   "Time out settings"
   End
End
Attribute VB_Name = "frmSelectSerialPort"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    Private mComm As SaxComm
    

Public Property Get Sax() As SaxComm
    Set Sax = mComm
End Property

Public Property Let Sax(ByVal NewSax As SaxComm)
    Dim Port As Variant
    Dim SavedSerialPort As String
    Dim FoundSavedPort As Boolean
    Dim i As Integer
    
    Set mComm = NewSax
    
    
    SavedSerialPort = GetSetting(App.EXEName, "Settings", "SavedSerialPort", "")

    With Me
        'Populate the combo box with all available serial ports
        .cboPort.Clear
        For Each Port In mComm.CommPorts
            If mComm.GetPortType(Port) = PortType_Serial Then
                .cboPort.AddItem Format(Port)
            End If
        Next Port
        
        If .cboPort.ListCount > 0 Then
    
            '.cboPort.List(.cboPort.ListIndex) = SComm.CommPort

            For i = 0 To .cboPort.ListCount - 1
                If .cboPort.List(i) = SavedSerialPort Then
                    .cboPort.ListIndex = i
                End If
            Next i
        Else
            'No serial ports so default to network
            optConnectionType(1) = True
            optConnectionType(1).Enabled = True
            
            optConnectionType(0).Enabled = False
        End If
        
        
    End With
End Property

Private Sub Check2_Click()
    
    If chkConcealPAssword.Value = Checked Then
        txtPassword.PasswordChar = "*"
        If Len(txtPassword) > 0 Then
            chkConcealPAssword.Enabled = False
        Else
            chkConcealPAssword.Enabled = True
        End If
    Else
        txtPassword.PasswordChar = ""
    End If


End Sub

Private Sub chkConcealPassword_Click()
    
    If chkConcealPAssword.Value = Checked Then
        txtPassword.PasswordChar = "*"
        If Len(txtPassword) > 0 Then
            chkConcealPAssword.Enabled = False
        Else
            chkConcealPAssword.Enabled = True
        End If
    Else
        txtPassword.PasswordChar = ""
    End If


End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
        
    mComm.CommPort = Me.cboPort.List(Me.cboPort.ListIndex)
    mComm.Settings = "57600,N,8,1"
    mComm.PortOpen = True
    SaveSetting App.EXEName, "Settings", "SavedSerialPort", cboPort.List(cboPort.ListIndex)
    SaveSetting App.EXEName, "Settings", "NetworkAddress", txtNetworkAddress

    If optConnectionType(0) Then
        'Serial port
        SaveSetting App.EXEName, "Settings", "ConnectionType", "SerialPort"
    Else
        'Network
        SaveSetting App.EXEName, "Settings", "ConnectionType", "Network"
    End If


    If chkSavePassword = Checked Then
        SaveSetting App.EXEName, "Settings", "xlz", txtPassword
    Else
        SaveSetting App.EXEName, "Settings", "xlz", ""
    End If
    
    SaveSetting App.EXEName, "Settings", "xy", chkConcealPAssword
    SaveSetting App.EXEName, "Settings", "xx", chkSavePassword
    frmEndurance.R.Password = txtPassword
    Unload Me

        
        Unload Me
        
End Sub

Private Sub Form_Load()
    txtNetworkAddress = GetSetting(App.EXEName, "Settings", "NetworkAddress", "192.168.0.61:3500")
    
        
    chkSavePassword = GetSetting(App.EXEName, "Settings", "xx", chkSavePassword)
    chkConcealPAssword = GetSetting(App.EXEName, "Settings", "xy", Checked)
    txtPassword = GetSetting(App.EXEName, "Settings", "xlz", "")

    
End Sub

Private Sub mnuTimeOut_Click()

    frmNetworkTimeoutSettings.Show 1
    
End Sub

Private Sub optConnectionType_Click(Index As Integer)
    Dim TempLeft As Double
    Dim TempTop As Double
    
    If optConnectionType(0) Then
        Me.fraNetworkAddress.Enabled = False
        Me.fraPorts.Enabled = True
        Me.fraNetworkAddress.Visible = False
        Me.fraPorts.Visible = True
        Me.mnuTimeOut.Visible = False
    Else
        Me.fraNetworkAddress.Enabled = True
        Me.fraPorts.Enabled = False
        Me.fraNetworkAddress.Visible = True
        Me.fraPorts.Visible = False
        Me.mnuTimeOut.Visible = True
    End If

End Sub

Private Sub txtPassword_Change()

    If txtPassword = "" Then
        chkConcealPAssword.Enabled = True
    Else
        If chkConcealPAssword = Checked Then
            chkConcealPAssword.Enabled = False
        Else
            chkConcealPAssword.Enabled = True
        End If
    End If

End Sub
