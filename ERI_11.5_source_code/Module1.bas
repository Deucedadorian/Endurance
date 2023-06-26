Attribute VB_Name = "Module1"
Option Explicit
Public Sub ConnectionLog(S As String)
    Dim FileName As String
    Dim FileNumber As Integer
    Dim Events(1000) As String
    Dim L As New Collection
    Dim Lines As Integer
    Dim A As String
    Dim i As Integer
    Dim FirstItem As Integer
    
    FileName = "c:\Endurance data files\Connection log.txt"
    FileNumber = FreeFile
    
    If Dir(FileName, vbNormal) <> "" Then
        Open FileName For Input As #FreeFile
    Else
        Open FileName For Output As #FreeFile
        Print #FileNumber, "File created: " + Format(Date) + "--" + Format(Time)
        Close #FileNumber
        FileNumber = FreeFile
        Open FileName For Input As #FreeFile
    End If
    
    
    Do While Not EOF(FileNumber)
        Line Input #FileNumber, A
        L.Add A
    Loop
    Close #FileNumber
    
    FileNumber = FreeFile
    Open FileName For Output As #FreeFile
    
        Lines = L.count
        
        If Lines > 500 Then
            FirstItem = Lines - 9
        Else
            FirstItem = 1
        End If
    
        For i = FirstItem To Lines
            Print #FileNumber, L.Item(i)
        Next i
    
        Print #FileNumber, Format(Date) + "," + Format(Time) + "," + S
    
    Close #FileNumber

End Sub
