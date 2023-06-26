Attribute VB_Name = "modUtilities"
Option Explicit


Public Function ValidIP(IPAddress As String) As Boolean
    Dim A As Variant
    Dim i As Integer
    
    A = Split(IPAddress, ".")
    
    If UBound(A) <> 3 Then
        ValidIP = False
        Exit Function
    End If
    
    For i = 0 To 3
        
        If Len(A(i)) > 3 Then
            ValidIP = False
            Exit Function
        End If
        
        If Not IsNumeric(A(i)) Then
            ValidIP = False
            Exit Function
        End If
        
        If Val(A(i)) < 0 Or Val(A(i)) > 255 Then
            ValidIP = False
            Exit Function
        End If
        
    Next i
    
    ValidIP = True
    
End Function

Public Function Encrypt(S As String, Key As String)
    Dim RandomString As String
    Dim i As Integer
    Dim j As Integer
    Dim Offset As Integer
    Dim PadLength As Integer
    
    
    
    RandomString = "cSX<>k$iob'HtlD|s)zBPf(VK:[]79pnU~v3^{5N,}ZQ-.g=&FAwyG;12_LJdC40Y*Rr?jMEua`I+WhxmOq8T6e/"

    For i = 1 To Len(S)
        j = ((i - 1) Mod (Len(Key))) + 1 'J points to char in key
        
        Offset = (Asc(Mid(Key, j, 1)) + Asc(Mid(S, i, 1))) Mod Len(RandomString)
        Offset = Offset + 1
        Encrypt = Encrypt + Mid(RandomString, Offset, 1)
        
    Next i
    
    PadLength = Int((20 - Len(S)) / 2)
    
    For i = 1 To PadLength
        j = Int(Len(RandomString) * Rnd + 1)
        Encrypt = Encrypt + Mid(RandomString, j, 1)
        j = Int(Len(RandomString) * Rnd + 1)
        Encrypt = Mid(RandomString, j, 1) + Encrypt

    Next i
    
    
    Debug.Print "key="; Key
    Debug.Print "Password="; S
    Debug.Print "Encrypted="; Encrypt
    
End Function
Public Function HexToDec(X As String) As Single
    Dim i
    Dim A$
    Dim D
    
    HexToDec = 0
    For i = 1 To Len(X)
        A$ = Mid$(X, Len(X) - i + 1, 1)
        Select Case Asc(A$)
            Case Asc("0") To Asc("9")
                D = Asc(A$) - Asc("0")
            Case Asc("A") To Asc("F")
                D = Asc(A$) - Asc("A") + 10
            Case Asc("a") To Asc("f")
                D = Asc(A$) - Asc("a") + 10
            Case Else
                D = 0
        End Select
        HexToDec = HexToDec + D * 16 ^ (i - 1)
    Next i
End Function

Public Function fnReadLastLine(strFileName As String) As String

    Dim fPos As Long, LastLine As String, aByte As Byte
    Dim testCRLF As String * 2
    Const LF = 10

    On Error GoTo fnReadLastLine_Error

    Open strFileName For Binary As #1
    fPos = LOF(1) + 1
    Do
        fPos = fPos - 2
        Seek #1, fPos
        Get #1, , testCRLF
    Loop While testCRLF = vbCrLf
    Do
        fPos = fPos - 1
        Seek #1, fPos
        Get #1, , aByte
        
        'Debug.Print Chr$(aByte)
        
    Loop Until aByte = LF
    Line Input #1, LastLine
    Close #1
    fnReadLastLine = Trim$(LastLine)

    Exit Function

fnReadLastLine_Error:
    fnReadLastLine = "1980-01-01,00:00:00" 'yyyy-mm-dd,hh:mm:ss
    
End Function


Public Function RemoveWhiteSpace(ByVal S As String) As String
    Dim Ret As String
    Dim Temp As String
    Dim i As Integer
    
    For i = 1 To Len(S)
        Temp = Mid(S, i, 1)
        If Asc(Temp) <> 9 Then
            Ret = Ret + Temp
        End If
    Next i
    
    RemoveWhiteSpace = Trim(Ret)
    
End Function
