    // // ÃÜÂëÎ»Ñ¡ÔñÄ£¿é
    // Key_Selector Key_Selector(
    //     .Key_Switch_left(Key_Switch_left),
    //     .Key_Switch_right(Key_Switch_right),
    //     .Key_Select(Key_Select)
    // );

module  Key_Selector(
	Key_Switch_left,
	Key_Switch_right,
	Key_Select
);

    input Key_Switch_left;
    input Key_Switch_right;
    output reg [1:0] Key_Select = 0;

    always @(posedge Key_Switch_left or posedge Key_Switch_right)
    begin
        if(Key_Switch_left)
				// if(Key_Select != 2'b00)
            Key_Select = Key_Select - 1;
        else if(Key_Switch_right)
				// if(Key_Select != 2'b11)
            Key_Select = Key_Select + 1;
    end

endmodule