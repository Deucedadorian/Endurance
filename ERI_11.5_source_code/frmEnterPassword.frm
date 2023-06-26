VERSION 5.00
Begin VB.Form frmEnterPassword 
   Caption         =   "Form1"
   ClientHeight    =   2130
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5040
   LinkTopic       =   "Form1"
   ScaleHeight     =   2130
   ScaleWidth      =   5040
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   735
      Left            =   120
      TabIndex        =   5
      Top             =   1320
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   735
      Left            =   1560
      TabIndex        =   2
      Top             =   1320
      Width           =   3375
   End
   Begin VB.Frame fraPassword 
      Caption         =   "Password"
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4815
      Begin VB.CheckBox chkConcealPassword 
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
         Left            =   2400
         TabIndex        =   4
         Top             =   720
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
         TabIndex        =   3
         Top             =   720
         Width           =   2055
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
         TabIndex        =   1
         Top             =   240
         Width           =   4575
      End
   End
End
Attribute VB_Name = "frmEnterPassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub chkConcealPassword_Click()
    
    If chkConcealPassword.Value = Checked Then
        txtPassword.PasswordChar = "*"
        If Len(txtPassword) > 0 Then
            chkConcealPassword.Enabled = False
        Else
            chkConcealPassword.Enabled = True
        End If
    Else
        txtPassword.PasswordChar = ""
    End If

End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()

    If chkSavePassword = Checked Then
        SaveSetting App.EXEName, "Settings", "xlz", txtPassword
    Else
        SaveSetting App.EXEName, "Settings", "xlz", ""
    End If
    
    SaveSetting App.EXEName, "Settings", "xy", chkConcealPassword
    SaveSetting App.EXEName, "Settings", "xx", chkSavePassword
    frmEndurance.R.Password = txtPassword
    Unload Me

End Sub

Private Sub Form_Load()
    
    chkSavePassword = GetSetting(App.EXEName, "Settings", "xx", False)
    chkConcealPassword = GetSetting(App.EXEName, "Settings", "xy", Checked)
    txtPassword = GetSetting(App.EXEName, "Settings", "xlz", "")

End Sub

Private Sub txtPassword_Change()
    If txtPassword = "" Then
        chkConcealPassword.Enabled = True
    Else
        If chkConcealPassword = Checked Then
            chkConcealPassword.Enabled = False
        Else
            chkConcealPassword.Enabled = True
        End If
    End If
    
End Sub
