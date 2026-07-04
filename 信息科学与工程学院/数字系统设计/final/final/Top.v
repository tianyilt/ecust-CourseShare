`include "./Key_Selector.v"
`include "./Key_Input.v"
`include "./Key_Validator.v"
`timescale 1ps/1ps
`define timeslice 1 

  
module Top(
		Key_Input,
		Key_Switch_left,
		Key_Switch_right,
		Key_Check,
		Key_RW,
		Key_RW_indicator,
		Lock_State,
		Key_Select,
		Key_Current);
		
	input 	[3:0] Key_Input;
	input	Key_Switch_left;
	input	Key_Switch_right;
	input	Key_Check;
	output	Lock_State;
	output	[1:0] Key_Select;
		
	output [3:0] Key_Current;
	input	Key_RW;
	output Key_RW_indicator; 
		
    // 输入信号
    wire Key_Switch_left;
    wire Key_Switch_right;
    wire Key_Check;
    wire Key_RW;
	 wire Key_RW_indicator;
    wire [3:0] Key_Input;
	 wire [3:0] Key_Current;
    
    // 输出信号  
    wire [3:0] Key_1;
    wire [3:0] Key_2;
    wire [3:0] Key_3;
    wire [3:0] Key_4;
    wire [1:0] Key_Select;
    wire       Lock_State; 
    
    // 实际密码设置
    reg [3:0] Key_1_real = 4'b0001; // 1
    reg [3:0] Key_2_real = 4'b0101; // 5
    reg [3:0] Key_3_real = 4'b0111; // 7 
    reg [3:0] Key_4_real = 4'b1000; // 8

    // 密码位选择模块
    Key_Selector m1(
        .Key_Switch_left(Key_Switch_left),
        .Key_Switch_right(Key_Switch_right),
        .Key_Select(Key_Select)
    );

    // 密码验证模块
    Key_Validator m2(
        .Key_Check(Key_Check),
        .Key_1(Key_1),
        .Key_2(Key_2),
        .Key_3(Key_3),
        .Key_4(Key_4),
        .Key_1_real(Key_1_real),
        .Key_2_real(Key_2_real),
        .Key_3_real(Key_3_real),
        .Key_4_real(Key_4_real),
        .Key_Select(Key_Select),
        .Lock_State(Lock_State)
    );

    // 密码输入模块
    Key_Input m3(
        .Key_RW(Key_RW),
        .Key_Input(Key_Input),
		  .Key_RW_indicator(Key_RW_indicator),
        .Key_Select(Key_Select),
        .Key_1(Key_1),
        .Key_2(Key_2),
        .Key_3(Key_3),
        .Key_4(Key_4),
		  .Key_Current(Key_Current)
    );
endmodule 