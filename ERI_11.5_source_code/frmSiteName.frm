VERSION 5.00
Begin VB.Form frmSiteName 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Site name"
   ClientHeight    =   1500
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7710
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1500
   ScaleWidth      =   7710
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   2175
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   2400
      TabIndex        =   1
      Top             =   960
      Width           =   5175
   End
   Begin VB.TextBox txtName 
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
      MaxLength       =   100
      TabIndex        =   0
      Top             =   120
      Width           =   7455
   End
   Begin VB.Label lblErrorMessage 
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
      Top             =   600
      Width           =   7455
   End
End
Attribute VB_Name = "frmSiteName"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private mStartName As String
Private mSendName As String

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()

    If InStr(txtName, "#") <> 0 Or InStr(txtName, "@") <> 0 Or InStr(txtName, "!") <> 0 Then
        MsgBox ("Site name contains an invalid character")
    Else
        If Len(txtName) = 0 Then
            MsgBox ("The site name must have at least 1 character")
        Else
            If Me.txtName <> mStartName Then
                    mSendName = txtName
                    txtName = ""
                    frmEndurance.R.ClearSiteName
                    frmEndurance.SendState = WaitingForSiteNameConfirm
            Else
                Unload Me
            End If
        End If
    End If
    
End Sub

Public Property Get StartName() As String
    StartName = mStartName
End Property

Public Property Let StartName(ByVal NewStartName As String)
    mStartName = NewStartName
    txtName = mStartName
End Property


Public Property Get SendName() As String
    SendName = mSendName
End Property

Private Sub txtName_Change()
    Dim S As String
    
    S = ValidName(txtName)
    
    Me.lblErrorMessage = S
    
    If S = "" Then
        'Site name OK
        txtName.ForeColor = &H80000008
        cmdOK.Enabled = True
    Else
        'Invalid site name
        txtName.ForeColor = &HFF
        cmdOK.Enabled = False
        
    End If
    
End Sub

Private Function ValidName(N As String) As String
    Dim i As Integer
    Dim T As String
    
    ValidName = ""
    
    If Len(N) < 1 Then
        ValidName = "Site name must contain at least 1 character"
        Exit Function
    End If
    
    
    For i = 1 To Len(N)
        T = Mid$(N, i, 1)
        If T = "@" Then ValidName = "@ not allowed in site name"
        If T = "!" Then ValidName = "! not allowed in site name"
        If T = "#" Then ValidName = "# not allowed in site name"
    Next i
    
    If IsNumeric(Left(N, 1)) Then
        ValidName = "First character in site name can not be a number"
    End If

End Function
