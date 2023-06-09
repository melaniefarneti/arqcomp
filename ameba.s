.text
.global ameba

ameba:
    LDR R0, =ameba1         
    LDR R1, =17            

    MOV R2, #128           

loop:
    CMP R2, #0             
    BEQ done              

    ANDS R3, R0, R2       
    CMP R3, #0             
    BEQ print_underscore 

print_asterisk:
    LDR R4, =42          
    STRB R4, [SP]          

    B next_char          

print_underscore:
    LDR R4, =95            
    STRB R4, [SP]         

next_char:
    ADDS R0, R0, #1      
    SUBS R1, R1, #1       

    CMP R1, #0            
    BNE next_char      

    MOV R0, #10           
    BL putchar           

    LSRS R2, R2, #1       

    B loop                 
done:
    NOP         
    MOV PC,LR   


ameba1:  .byte 0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x83, 0x83, 0x8C, 0x98, 0xB0, 0xE0, 0xE1, 0x71, 0x39, 0x1D, 0x0F

.end
