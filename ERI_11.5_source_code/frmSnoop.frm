VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form frmSnoop 
   Caption         =   "Snoop"
   ClientHeight    =   4485
   ClientLeft      =   225
   ClientTop       =   825
   ClientWidth     =   6285
   Icon            =   "frmSnoop.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   4485
   ScaleWidth      =   6285
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog 
      Left            =   360
      Top             =   480
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CheckBox chkReceive 
      Caption         =   "Receive"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   4080
      Value           =   1  'Checked
      Width           =   1095
   End
   Begin VB.CheckBox chkSend 
      Caption         =   "Send"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   3840
      Value           =   1  'Checked
      Width           =   1095
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Height          =   495
      Left            =   1320
      TabIndex        =   3
      Top             =   3840
      Width           =   1335
   End
   Begin VB.CommandButton cmdPause 
      Caption         =   "Pause"
      Height          =   495
      Left            =   2760
      TabIndex        =   2
      Top             =   3840
      Width           =   1455
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   4320
      TabIndex        =   1
      Top             =   3840
      Width           =   1935
   End
   Begin RichTextLib.RichTextBox rtbSnoop 
      Height          =   3615
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   6376
      _Version        =   393217
      HideSelection   =   0   'False
      ScrollBars      =   3
      TextRTF         =   $"frmSnoop.frx":058A
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "Save &as"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEditCut 
         Caption         =   "Cu&t"
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "&Copy"
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "&Paste"
      End
      Begin VB.Menu mnuEditFind 
         Caption         =   "&Find"
      End
      Begin VB.Menu mnuSelectAll 
         Caption         =   "Select all"
      End
   End
   Begin VB.Menu mnuDecoder 
      Caption         =   "Decoder"
      Visible         =   0   'False
   End
End
Attribute VB_Name = "frmSnoop"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mSnoopState As SnoopStateEnum
Private mSnooping As Boolean

Private Enum SnoopStateEnum
    ssUnknown
    ssTransmitting
    ssReceving
End Enum



Private Sub cmdClear_Click()
    Me.rtbSnoop.Text = ""
End Sub

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Sub cmdPause_Click()
    
    If Snooping Then
        Snooping = False
    Else
        Snooping = True
    End If
    
End Sub

Private Sub cmdResume_Click()
    If Snooping Then
        Snooping = False
    Else
        Snooping = True
    End If
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
'    If KeyCode = 122 Then frmDecode.Show
End Sub

Private Sub Form_Load()
    Call FormOnTop(Me.hWnd, True)
    Snooping = True
End Sub

Private Sub Form_Resize()
    Dim Spacing As Single
    Dim ButtonTop As Single
    Dim ButtonWidth As Single
    
    If Me.ScaleHeight > 1000 Then
        Spacing = 60
        ButtonTop = Me.ScaleHeight - Spacing - cmdPause.Height
        ButtonWidth = (Me.ScaleWidth - 4 * Spacing) / 4
        chkSend.Move Spacing, ButtonTop, ButtonWidth
        chkReceive.Move Spacing, chkSend.Top + chkSend.Height + Spacing / 2, ButtonWidth
        cmdClear.Move chkSend.Left + ButtonWidth + Spacing, ButtonTop, ButtonWidth
        cmdPause.Move cmdClear.Left + cmdClear.Width + Spacing, ButtonTop, ButtonWidth
        cmdOK.Move cmdPause.Left + cmdPause.Width + Spacing, ButtonTop, ButtonWidth
        
        rtbSnoop.Move Spacing, 0, Me.Width - 4 * Spacing, cmdClear.Top - Spacing
    End If
    
End Sub

Public Property Get Snooping() As Boolean
    Snooping = mSnooping
End Property

Public Property Let Snooping(ByVal NewSnooping As Boolean)
    mSnooping = NewSnooping
    
    If mSnooping Then
        cmdPause.Caption = "Pause"
    Else
        cmdPause.Caption = "Resume"
    End If
    
End Property

Public Sub Receive(DataStream As String)
    
    'Receive snoop
    
    
    
    If chkReceive = Checked Then
    
        If Snooping Then
            Select Case mSnoopState
                Case ssUnknown, ssTransmitting
                    Me.rtbSnoop.Text = Me.rtbSnoop.Text + vbCr + vbLf + "Receiving --------------"
                Case Else
            End Select
            
            mSnoopState = ssReceving
            
            Me.rtbSnoop.Text = Me.rtbSnoop.Text + Display(DataStream, False) ' + vbCr + vbLf
            Me.rtbSnoop.SelStart = Len(Me.rtbSnoop.Text)
        Else
            mSnoopState = ssUnknown
        End If
    End If

End Sub

Public Sub Transmit(Char As String)

    

    If chkSend = Checked Then
        
        If Snooping Then
            Select Case mSnoopState
                Case ssUnknown, ssReceving
                    Me.rtbSnoop.Text = Me.rtbSnoop.Text + vbCr + vbLf + "Sending --------------"
                Case Else
            End Select
            
            mSnoopState = ssTransmitting
            
            Me.rtbSnoop.Text = Me.rtbSnoop.Text + Display(Char, False)
            Me.rtbSnoop.SelStart = Len(Me.rtbSnoop.Text)
        Else
            mSnoopState = ssUnknown
        End If
        
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    frmEndurance.mnuTestSnoop.Checked = False
    SaveSetting App.EXEName, "Settings", "Snooping", frmEndurance.mnuTestSnoop.Checked
    
End Sub

Private Sub mnuEditCopy_Click()
    
    Clipboard.Clear
    Clipboard.SetText rtbSnoop.SelText
  
End Sub

Private Sub mnuEditCut_Click()
    
    Clipboard.Clear
    Clipboard.SetText rtbSnoop.SelText
    rtbSnoop.SelText = ""

End Sub

Private Sub mnuEditPaste_Click()
    rtbSnoop.SelText = Clipboard.GetText()
End Sub

Private Sub mnuFileSaveAs_Click()
    
    Dim FileNumber As Integer
    Dim FileName As String
    
    'On Error GoTo Err_Handler
    
    With CommonDialog
        If Dir("c:\Microvent monitor data files", vbDirectory) <> "" Then
            .InitDir = App.Path
        End If
        .Filter = "Text files|*.txt|All files|*.*"
        .ShowSave
        .FileName = "Snoop.txt"
        
        FileNumber = FreeFile
        Open .FileName For Output As #FileNumber
            Print #FileNumber, Me.rtbSnoop.Text
        Close #FileNumber
        
    End With
    

Exit Sub
Err_Handler:
    MsgBox (Err.Description)
End Sub

Private Sub mnuSelectAll_Click()
    rtbSnoop.SelStart = 0
    rtbSnoop.SelLength = Len(rtbSnoop)
End Sub
Public Function Display(S As String, Split As Boolean) As String
    Dim Char As Byte
    
    Dim i As Integer
    
    For i = 1 To Len(S)
        Char = Asc(Mid(S, i, 1))
        Select Case Char
            Case 32 To 122
                Display = Display + Chr$(Char)
            Case 243
                Display = Display + vbCr + vbLf + "[243]"
            Case 13
                If Split Then
                    Display = Display + "[13]" + vbCr + vbLf
                Else
                    Display = Display + "[13]"
                End If
            Case Else
                Display = Display + "[" + Format(Char) + "]"
        End Select
    Next i
    
End Function

