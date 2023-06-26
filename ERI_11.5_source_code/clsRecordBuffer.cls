VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsRecordBuffer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private mBufferName As String
Private mRecordType As RecordTypeEnum
Private mMaxRecords As Double
Private mNumberOfRecords As Double
Private mLastRecordTime As clsTimeStamp
Private mOldestRecordTime As clsTimeStamp
Private mLastOnFile As clsTimeStamp
Private mFileName As String
Private mBufferInfoString As String
Private mIsValid As Boolean

Public Enum RecordTypeEnum
    rtWindRPM
    rtEvent
End Enum

Public Property Get RecordType() As RecordTypeEnum
    RecordType = mRecordType
End Property

Public Property Let RecordType(ByVal NewRecordType As RecordTypeEnum)
    mRecordType = NewRecordType
End Property
Public Property Get MaxRecords() As Double
    MaxRecords = mMaxRecords
End Property

Public Property Let MaxRecords(ByVal NewMaxRecords As Double)
    mMaxRecords = NewMaxRecords
End Property
Public Property Get NumberOfRecords() As Double
    NumberOfRecords = mNumberOfRecords
End Property

Public Property Let NumberOfRecords(ByVal NewNumberOfRecords As Double)
    mNumberOfRecords = NewNumberOfRecords
End Property

Public Property Get OldestRecordTime() As clsTimeStamp
    OldestRecordTime = mOldestRecordTime
End Property

Public Property Let OldestRecordTime(ByVal NewOldestRecordTime As clsTimeStamp)
    mOldestRecordTime = NewOldestRecordTime
End Property
Public Property Let LastRecordTime(ByVal NewLastRecordTime As clsTimeStamp)
    mLastRecordTime = NewLastRecordTime
End Property
Public Property Get LastOnFile() As clsTimeStamp
    LastOnFile = mLastOnFile
End Property

Public Property Let LastOnFile(ByVal NewLastOnFile As clsTimeStamp)
    mLastOnFile = NewLastOnFile
End Property

Public Property Get BufferInfoString() As String
    BufferInfoString = mBufferInfoString
End Property

Public Property Let BufferInfoString(ByVal NewBufferInfoString As String)
    mBufferInfoString = NewBufferInfoString
    
End Property

Public Property Get IsValid() As Boolean
    IsValid = mIsValid
End Property

