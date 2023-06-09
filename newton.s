
.text
.global newton

newton:
    LDR R3, =bolitaFija  
    LDRB R0, [R3]    

    LDR R4, =bolitaMovil  
    LDRB R1, [R4]        

    MOVS R5, #1       
    MOVS R6, #0           

loop:
    CMP R5, #1         
    BEQ move_right        

move_left:
    SUBS R6, R6, #1    

    CMP R6, #0            
    BNE print_line      

    MOVS R5, #1
    B loop              

move_right:
    ADDS R6, R6, #1   

    CMP R6, #6         
    BNE print_line       

    MOVS R5, #0          
    B loop              

print_line:
    MOV R7, #0x5F        
    STRB R7, [SP]      

    CMP R6, #3          
    BNE print_movil     

    LDR R7, =bolitaFija  
    LDRB R7, [R7]       
    STRB R7, [SP]       
    B next_char          

print_movil:
    LDR R7, =bolitaMovil  
    LDRB R7, [R7]        

next_char:
    STRB R7, [SP, R6]    

    ADDS R6, R6, #1    

    CMP R6, #7           
    BNE next_char      

    LDR R0, =7          
    LDR R1, =SP           

    BL printf      

    BL usleep           

    B loop           

done:
    NOP          
    MOV PC,LR    

bolitaFija: .asciz "*"
bolitaMovil: .asciz "*"

.end

