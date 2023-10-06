
EnableExplicit

CompilerIf #PB_Compiler_Debugger
	CompilerWarning "Using PureBasic's debugger WILL impact performances on non-ASM code !"
	#TestCount = 1000000  ; 1M tests
CompilerElse
	#TestCount = 100000000  ; 100M tests
CompilerEndIf

CompilerIf Not #PB_Compiler_Optimizer
	CompilerWarning "Please use the 'Optimize generated code' option !"
CompilerEndIf

; Assumptions & expectations for ASM:
;  * The code is in the middle of a function.
;  * No quick return through EAX register.
;  * Final value MUST be assigned in a variable.
;  * Number of bits set is given as a non-first parameter  (No quick load through EAX)

Procedure.l TestAsm1(BitCount.b)
	Define MyValue.l = 0
	
	EnableASM
	; Unable to set EAX to $80000000, it just gets set to 0...
	MOV eax, $00000001
	MOV cl, BitCount
	SHL eax, cl
	DEC eax
	MOV MyValue, eax
	DisableASM
	
	ProcedureReturn MyValue
EndProcedure

Procedure.l TestManual1(BitCount.b)
	Define MyValue.l = 0
	
	MyValue = (%1 << BitCount) - 1
	
	ProcedureReturn MyValue
EndProcedure

; These functions will ignore the restrictions.
Procedure.l TestAsm2(BitCount.b)
	EnableASM
	MOV eax, $00000001
	MOV cl, BitCount
	SHL eax, cl
	DEC eax
	ProcedureReturn
	DisableASM
EndProcedure

Procedure.l TestManual2(BitCount.b)
	ProcedureReturn (%1 << BitCount) - 1
EndProcedure

Define i.i
Define StartTime.q
Define EndTime.q

Define ManualTime1.q
Define AsmTime1.q

Define ManualTime2.q
Define AsmTime2.q

StartTime = ElapsedMilliseconds()
Debug "> 0b" + RSet(Bin(TestManual1(5), #PB_Byte), 32, "0")
For i=0 To #TestCount - 1
	TestManual1(5)
Next
EndTime = ElapsedMilliseconds()
ManualTime1 = EndTime - StartTime

StartTime = ElapsedMilliseconds()
Debug "> 0b" + RSet(Bin(TestAsm1(5), #PB_Byte), 32, "0")
For i=0 To #TestCount - 1
	TestAsm1(5)
Next
EndTime = ElapsedMilliseconds()
AsmTime1 = EndTime - StartTime


StartTime = ElapsedMilliseconds()
Debug "> 0b" + RSet(Bin(TestManual2(5), #PB_Byte), 32, "0")
For i=0 To #TestCount - 1
	TestManual2(5)
Next
EndTime = ElapsedMilliseconds()
ManualTime2 = EndTime - StartTime

StartTime = ElapsedMilliseconds()
Debug "> 0b" + RSet(Bin(TestAsm2(5), #PB_Byte), 32, "0")
For i=0 To #TestCount - 1
	TestAsm2(5)
Next
EndTime = ElapsedMilliseconds()
AsmTime2 = EndTime - StartTime


; On my side: (AMD Ryzen 5 3600)
; > Manual1: 214ms
; > Assembly1: 212ms
;
; > Manual2: 200ms
; > Assembly2: 184ms

MessageRequester("Results", 
                 "Manual1: "+Str(ManualTime1)+"ms"+#CRLF$+
                 "Assembly1: "+Str(AsmTime1)+"ms"+#CRLF$+
                 #CRLF$+
                 "Manual2: "+Str(ManualTime2)+"ms"+#CRLF$+
                 "Assembly2: "+Str(AsmTime2)+"ms")
