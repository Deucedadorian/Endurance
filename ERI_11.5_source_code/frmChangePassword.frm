VERSION 5.00
Begin VB.Form frmChangePassword 
   Caption         =   "Change password ..."
   ClientHeight    =   3090
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4665
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   3090
   ScaleWidth      =   4665
   StartUpPosition =   2  'CenterScreen
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
      Height          =   375
      Left            =   2280
      TabIndex        =   7
      Top             =   1560
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
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   1560
      Width           =   2055
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
      Height          =   615
      Left            =   1680
      TabIndex        =   3
      Top             =   2400
      Width           =   2895
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
      Height          =   615
      Left            =   120
      TabIndex        =   2
      Top             =   2400
      Width           =   1455
   End
   Begin VB.Frame fraConfirmPassword 
      Caption         =   "Confirm Password "
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
      TabIndex        =   1
      Top             =   840
      Width           =   4455
      Begin VB.TextBox txtConfirmPassword 
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
         MaxLength       =   16
         TabIndex        =   5
         Top             =   240
         Width           =   4215
      End
   End
   Begin VB.Frame fraPassword 
      Caption         =   "New password "
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
      TabIndex        =   0
      Top             =   120
      Width           =   4455
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
         MaxLength       =   16
         TabIndex        =   4
         Top             =   240
         Width           =   4215
      End
   End
   Begin VB.Label lblSending 
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   2040
      Width           =   4455
   End
End
Attribute VB_Name = "frmChangePassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub chkConcealPassword_Click()
    
    If chkConcealPassword.Value = Checked Then
        txtPassword.PasswordChar = "*"
        txtConfirmPassword.PasswordChar = "*"
        If Len(txtPassword) > 0 Then
            chkConcealPassword.Enabled = False
        Else
            chkConcealPassword.Enabled = True
        End If
    Else
        txtPassword.PasswordChar = ""
        txtConfirmPassword.PasswordChar = ""
    End If
    
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()

    If txtConfirmPassword = txtPassword Then
        If txtPassword = "" Then
            Me.lblSending = "Blank password is not allowed"
        Else
            If Len(txtPassword) > 20 Then
                Me.lblSending = "Password must be 20 char or less"
            Else
                If Not ValidChars(txtPassword) Then
                    Me.lblSending = "Password contains invalid characters"
                Else
                    If chkSavePassword = Checked Then
                        SaveSetting App.EXEName, "Settings", "xlz", txtPassword
                    End If
                    
                    SaveSetting App.EXEName, "Settings", "xy", chkConcealPassword
                    SaveSetting App.EXEName, "Settings", "xx", chkSavePassword
                    With frmEndurance
                        .R.NewPasswordValidated = False
                        .SendState = ChangingPassword
                        .PendingPassword = txtPassword
                    End With
                    
                    Me.lblSending = "Sending new password ..."
                End If
            End If
        End If
    Else
     Me.lblSending = "Passwords do not match"
    End If

End Sub

Private Sub Form_Load()
'
'    If Site.Processors(Site.SelectedProcessor).ConcealPassword Then
'        chkConcealPassword = Checked
'        chkConcealPassword.Enabled = True
'        txtPassword.PasswordChar = "*"
'        txtConfirmPassword.PasswordChar = "*"
'    Else
'        chkConcealPassword = Unchecked
'        chkConcealPassword.Enabled = True
'        txtPassword.PasswordChar = ""
'        txtConfirmPassword.PasswordChar = ""
'    End If
'
'    If Site.Processors(Site.SelectedProcessor).SavePassword Then
'        chkSavePassword = Checked
'    End If
    
End Sub

Private Sub txtConfirmPassword_Change()
    Me.lblSending = ""
    CheckConceal
End Sub

Private Sub txtPassword_Change()
    Me.lblSending = ""
    CheckConceal
End Sub

Public Sub CheckConceal()
    If txtPassword = "" And txtConfirmPassword = "" Then
        chkConcealPassword.Enabled = True
    Else
        If chkConcealPassword = Checked Then
            chkConcealPassword.Enabled = False
        Else
            chkConcealPassword.Enabled = True
        End If
    End If

End Sub

Public Function ValidChars(S As String) As Boolean
    Dim i As Integer

    ValidChars = True
    For i = 1 To Len(S)
        If Mid(i, 1, 1) = "#" Then ValidChars = False
        If Mid(i, 1, 1) = "@" Then ValidChars = False
        If Asc(Mid(i, 1, 1)) < 48 Then ValidChars = False
        If Asc(Mid(i, 1, 1)) > 122 Then ValidChars = False
Next i
    
End Function
