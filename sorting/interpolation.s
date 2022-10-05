.include "../includeConstantARM64.inc"
.equ CHARPOS,   '@'

.data
szString:           .asciz " string "
szString1:          .asciz "insert"
szString2:          .asciz "abcd@efg"
szString3:          .asciz "abcdef @"
szString4:          .asciz "@ abcdef"
szCarriageReturn:   .asciz "\n"

.bss

.text
.global main
main:
    ldr x0,qAdrszString
    ldr x1,qAdrszString1
    mov x2, #0
    bl strInsert

    bl affichageMess
    ldr x0,qAdrszCarriageReturn
    bl affichageMess

    ldr x0,qAdrszString          
    ldr x1,qAdrszString1         
    mov x2,#3
    bl strInsert                  

    bl affichageMess             
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
 
    ldr x0,qAdrszString          
    ldr x1,qAdrszString1         
    mov x2,#40
    bl strInsert                  

    bl affichageMess             
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
 
    ldr x0,qAdrszString2         
    ldr x1,qAdrszString1         
    bl strInsertAtChar           

    bl affichageMess             
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
 
    ldr x0,qAdrszString3         
    ldr x1,qAdrszString1        
    bl strInsertAtChar           

    bl affichageMess            
    ldr x0,qAdrszCarriageReturn
    bl affichageMess
 
    ldr x0,qAdrszString4        
    ldr x1,qAdrszString1         
    bl strInsertAtChar           

    bl affichageMess             
    ldr x0,qAdrszCarriageReturn
    bl affichageMess

100:
    mov x0, #0                   
    mov x8, #EXIT                
    svc 0                        
qAdrszString:          .quad szString
qAdrszString1:         .quad szString1
qAdrszString2:         .quad szString2
qAdrszString3:         .quad szString3
qAdrszString4:         .quad szString4
qAdrszCarriageReturn:  .quad szCarriageReturn