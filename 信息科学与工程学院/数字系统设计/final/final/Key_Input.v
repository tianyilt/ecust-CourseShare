    // // √‹¬Î ‰»Îƒ£øÈ
    // Key_Input Key_Input(
    //     .Key_RW(Key_RW),
    //     .Key_Input(Key_Input),
    //     .Key_Select(Key_Select)
    // );

module Key_Input(
    input Key_RW,
    input [3:0] Key_Input,
    input [1:0] Key_Select,
	 output reg Key_RW_indicator,
	 output reg [3:0] Key_1,
    output reg [3:0] Key_2,
    output reg [3:0] Key_3,
    output reg [3:0] Key_4,
    output reg [3:0] Key_Current	 
);
    
    parameter   Selet_1 = 2'b00,
                Selet_2 = 2'b01,
                Selet_3 = 2'b10,
                Selet_4 = 2'b11;
					 

	 always @(*)begin
		Key_RW_indicator = Key_RW;
	 end
	 
    always @(Key_RW)
    begin
		if (Key_RW) begin
        casex (Key_Select)
            Selet_1: Key_1 <= Key_Input;
            Selet_2: Key_2 <= Key_Input;
            Selet_3: Key_3 <= Key_Input;
            Selet_4: Key_4 <= Key_Input;
		  endcase
		end
    end
	 
 	 always @(Key_Select or Key_RW) begin
		  casex (Key_Select)
            Selet_1: Key_Current = Key_1;
            Selet_2: Key_Current = Key_2;
            Selet_3: Key_Current = Key_3;
            Selet_4: Key_Current = Key_4;
		  endcase
	 end

endmodule