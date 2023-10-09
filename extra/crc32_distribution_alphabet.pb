
EnableExplicit

UseCRC32Fingerprint()

#DictFile$ = "./words_dictionary.json"

#WordMinLength = 1

#CrcMask = %11111111

#CsvDivider = #TAB$


; Checking if the dictionary file exist
If FileSize(#DictFile$) <= 0
	Debug "The file '" + #DictFile$ + "' cannot be found !"
	Debug "You can grab it from 'https://github.com/dwyl/english-words'"
	End 1
EndIf


; We have to wrap c-like arrays in structure in PB.
Structure _TestResult
	HashSegment.q[#CrcMask + 1]
EndStructure

Define TestResult._TestResult


; Clearing memory out
FillMemory(@TestResult, SizeOf(_TestResult), $00, #PB_Byte)


; Loading the dictionary
; We won't use the JSON functions since PB is super slow here for some reason...
NewList DictEntries.s()

If Not ReadFile(0, #DictFile$)
	Debug "Unable to load '" + #DictFile$ + "' !"
	End 1
EndIf

While Eof(0) = 0
	Define DictLine$ = Trim(ReadString(0), " ")
	
	If Left(DictLine$, 1) = #DQUOTE$
		AddElement(DictEntries())
  		DictEntries() = Left(Right(DictLine$, Len(DictLine$) - 1), FindString(DictLine$, #DQUOTE$, 2) - 2)
		;Debug Left(Right(DictLine$, Len(DictLine$) - 1), FindString(DictLine$, #DQUOTE$, 2) - 2)
	EndIf
Wend
CloseFile(0)


; Doing the CRC32B calculations

ForEach DictEntries()
	; I can't get the CRC into a buffer sadly because PB has no clear option for it...
	; And I cannot be bothered to play with peeks and pokes to optimize string concatenations.
	Define Crc32.l = Val("$" + StringFingerprint(DictEntries(), #PB_Cipher_CRC32))
	
	TestResult\HashSegment[Crc32 & #CrcMask] = TestResult\HashSegment[Crc32 & #CrcMask] + 1
Next


; Printing out the results
Define CsvHeaders$ = ""
Define CsvData$ = ""

Define i.i
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

FreeList(DictEntries())
