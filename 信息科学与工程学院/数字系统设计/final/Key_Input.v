    // // 密码输入模块
    // Key_Input Key_Input(
    //     .Key_RW(Key_RW),
    //     .Key_1(Key_1),
    //     .Key_2(Key_2),
    //     .Key_3(Key_3),
    //     .Key_4(Key_4),
    //     .Key_Input(Key_Input),
    //     .Key_Select(Key_Select)
    // );

module Key_Input(
    input Key_RW,
    input [3:0] Key_1,
    input [3:0] Key_2,
    input [3:0] Key_3,
    input [3:0] Key_4,
    input [3:0] Key_Input,
    input [2:0] Key_Select
);

    parameter   Selet_1 = 2'b00,
                Selet_2 = 2'b01,
                Selet_3 = 2'b10,
                Selet_4 = 2'b11;


    always @(posedge Key_RW)
    begin
        case(Key_Select)
            Selet_1: Key_1 <= Key_Input;
            Selet_2: Key_2 <= Key_Input;
            Selet_3: Key_3 <= Key_Input;
            Selet_4: Key_4 <= Key_Input;
        endcase
    end

endmodule
