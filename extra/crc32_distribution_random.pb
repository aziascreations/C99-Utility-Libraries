
EnableExplicit

UseCRC32Fingerprint()

#CrcLoopCount = 1000000
#CrcMask = %11111111

#CsvDivider = #TAB$

; We have to wrap c-like arrays in structure in PB.
Structure _TestResult
	HashSegment.q[#CrcMask + 1]
EndStructure

Define TestResult._TestResult


; Clearing memory out
FillMemory(@TestResult, SizeOf(_TestResult), $00, #PB_Byte)


; Doing the CRC32B calculations
OpenCryptRandom()

Define i.i
For i = 0 To #CrcLoopCount - 1
	Define DataLength.a = CryptRandom(255 - 16)
	DataLength = DataLength + 16
	
	Define *DataBuffer = AllocateMemory(DataLength)
	CryptRandomData(*DataBuffer, DataLength)
	
	; I can't get the CRC into a buffer sadly because PB has no clear option for it...
	; And I cannot be bothered to play with peeks and pokes to optimize string concatenations.
	Define Crc32.l = Val("$" + Fingerprint(*DataBuffer, DataLength, #PB_Cipher_CRC32))
	
	TestResult\HashSegment[Crc32 & #CrcMask] = TestResult\HashSegment[Crc32 & #CrcMask] + 1
	
	FreeMemory(*DataBuffer)
Next

CloseCryptRandom()


; Printing out the results
Define CsvHeaders$ = ""
Define CsvData$ = ""

For i = 0 To #CrcMask
	If i > 0
		CsvHeaders$ = CsvHeaders$ + #CsvDivider
		CsvData$ = CsvData$ + #CsvDivider
	EndIf
	
	CsvHeaders$ = CsvHeaders$ + Str(i)
	CsvData$ = CsvData$ + Str(TestResult\HashSegment[i])
Next

Debug CsvHeaders$
Debug CsvData$
