VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsRecTranslator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Private EventCodes(255, 1 To 2) 'File name, text



Private Sub Class_Initialize()
    Dim FileNumber As Integer
    Dim FileName As String
    Dim A$
    Dim Record As Variant
    Dim pRecordCount As Integer
    Dim pCode As Integer
    
    
    On Error Resume Next
    FileName = App.Path + "\Event codes.txt"

    FileNumber = FreeFile
    If Dir(FileName) <> "" Then
        Open FileName For Input As #FileNumber
    
        Do While Not EOF(FileNumber)
            Line Input #FileNumber, A$
                If Left(A$, 1) <> ";" Then
                Record = Split(A$, ",")
                If UBound(Record) = 2 Then
                    If IsNumeric(Record(0)) Then
                        pCode = Record(0)
                        EventCodes(pCode, 1) = RemoveWhiteSpace(Record(1))
                        EventCodes(pCode, 2) = RemoveWhiteSpace(Record(2))
                    End If
                End If
            End If
        Loop
        
        Close #FileNumber
        
    End If 'Dir(mFileName) <> "" Then
    
End Sub


Public Function EventText(Code As Integer) As String
    EventText = EventCodes(Code, 2)
End Function
Public Function EventPic(Code As String) As String
    EventPic = App.Path + "\" + EventCodes(Code, 2)
End Function

