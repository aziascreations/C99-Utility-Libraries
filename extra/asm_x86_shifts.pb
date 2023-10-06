
EnableExplicit

CompilerIf #PB_Compiler_Processor = #PB_Processor_x86 Or #PB_Compiler_Processor = #PB_Processor_x64
	
CompilerElse
	CompilerError "You need either x86 or x64 !"
CompilerEndIf

Define MyValue.a


;- Test #1 (Check which instruction works)

; --------------
Debug "With SAL"

MyValue = %10000000

EnableASM
MOV al, MyValue
SAL al, 2
MOV MyValue, al
DisableASM

Debug "> 0b" + RSet(Bin(MyValue, #PB_Ascii), 8, "0")

; --------------
Debug "With SHL"

MyValue = %10000000

EnableASM
MOV al, MyValue
SHL al, 2
MOV MyValue, al
DisableASM

Debug "> 0b" + RSet(Bin(MyValue, #PB_Ascii), 8, "0")

; --------------
Debug "With SAR"

MyValue = %10000000

EnableASM
MOV al, MyValue
SAR al, 2
MOV MyValue, al
DisableASM

Debug "> 0b" + RSet(Bin(MyValue, #PB_Ascii), 8, "0")

; --------------
Debug "With SHR"

MyValue = %10000000

EnableASM
MOV al, MyValue
SHR al, 2
MOV MyValue, al
DisableASM

Debug "> 0b" + RSet(Bin(MyValue, #PB_Ascii), 8, "0")


;- Test #2 (Use SAR with ROL)
; Remark: Only works if most important bit is set !
Debug "With SAR & ROL @ 3bits"

MyValue = %10000000

EnableASM
MOV al, MyValue
SAR al, 2
ROL al, 3
MOV MyValue, al
DisableASM

Debug "> 0b" + RSet(Bin(MyValue, #PB_Ascii), 8, "0")
