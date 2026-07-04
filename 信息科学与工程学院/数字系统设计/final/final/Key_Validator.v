    // // ÃÜÂëÑéÖ¤Ä£¿é
    // Key_Validator Key_Vaildator(
    //     .Key_Check(Key_Check),
    //     .Key_1(Key_1),
    //     .Key_2(Key_2),
    //     .Key_3(Key_3),
    //     .Key_4(Key_4),
    //     .Key_1_real(Key_1_real),
    //     .Key_2_real(Key_2_real),
    //     .Key_3_real(Key_3_real),
    //     .Key_4_real(Key_4_real),
    //     .Key_Select(Key_Select),
    //     .Lock_State(Lock_State)
    // );

module Key_Validator(
     Key_Check,
     Key_1,
     Key_2,
     Key_3,
     Key_4,
     Key_1_real,
     Key_2_real,
     Key_3_real,
     Key_4_real,
     Key_Select,
     Lock_State
);
    input Key_Check;
    input [3:0] Key_1;
    input [3:0] Key_2;
    input [3:0] Key_3;
    input [3:0] Key_4;
    input [3:0] Key_1_real;
    input [3:0] Key_2_real;
    input [3:0] Key_3_real;
    input [3:0] Key_4_real;
    input [1:0] Key_Select;
    output Lock_State;

	 reg Lock_State;

    parameter   Locked   = 0;
    parameter   Unlocked = 1;

    always @(posedge Key_Check)
    begin
        if(Key_1_real == Key_1 && Key_2_real == Key_2 && Key_3_real == Key_3&& Key_4_real == Key_4)
            Lock_State <= Unlocked;
        else
            Lock_State <= Locked;
    end
	 
endmodule