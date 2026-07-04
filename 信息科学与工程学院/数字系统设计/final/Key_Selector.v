    // // 密码位选择模块
    // Key_Selector Key_Selector(
    //     .Key_Switch_left(Key_Switch_left),
    //     .Key_Switch_right(Key_Switch_right),
    //     .Key_Select(Key_Select)
    // );

module  Key_Selector(
    input Key_Switch_left,
    input Key_Switch_right,
    output [2:0] Key_Select
);

    always @(posedge Key_Switch_left or posedge Key_Switch_right)
    begin
        if(Key_Switch_left)
            Key_Select <= Key_Select - 1;
        else
            Key_Select <= Key_Select + 1;
    end

endmodule