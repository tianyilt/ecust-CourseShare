`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:54:01 06/11/2024
// Design Name:   Top
// Module Name:   D:/test/final/t0.v
// Project Name:  final
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module t0;

	// Inputs
	reg [3:0] Key_Input;
	reg Key_Switch_left;
	reg Key_Switch_right;
	reg Key_Check;
	reg Key_RW;

	// Outputs
	wire Key_RW_indicator;
	wire Lock_State;
	wire [1:0] Key_Select;
	wire [3:0] Key_Current;

	// Instantiate the Unit Under Test (UUT)
	Top uut (
		.Key_Input(Key_Input), 
		.Key_Switch_left(Key_Switch_left), 
		.Key_Switch_right(Key_Switch_right), 
		.Key_Check(Key_Check), 
		.Key_RW(Key_RW), 
		.Key_RW_indicator(Key_RW_indicator), 
		.Lock_State(Lock_State), 
		.Key_Select(Key_Select), 
		.Key_Current(Key_Current)
	);

	initial begin
		// Initialize Inputs
		Key_Input = 0;
		Key_Switch_left = 0;
		Key_Switch_right = 0;
		Key_Check = 0;
		Key_RW = 0;

		// Wait 10 ns for global reset to finish
		#10;
        
		// Add stimulus here
		
		// 验证密码
		#10 Key_Check = 1;
		#5 Key_Check = 0;

		// 分别设置输入, 并写入
		#10 Key_Input = 1;
		#10 Key_RW = 1;
		#10 Key_RW = 0;
		
		
		// 调向下一个密码位
		#10 Key_Switch_right = 1;
		#5 Key_Switch_right = 0;

		#10 Key_Input = 5;
		#10 Key_RW = 1;
		#10 Key_RW = 0;
		
		
		#10 Key_Switch_right = 1;
		#5 Key_Switch_right = 0;

		#10 Key_Input = 7;
		#10 Key_RW = 1;
		#10 Key_RW = 0;
		
		
		#10 Key_Switch_right = 1;
		#5 Key_Switch_right = 0;
		
		#10 Key_Input = 8;
		#10 Key_RW = 1;
		#10 Key_RW = 0;
		
		
		// 完成写入

		// 验证密码
		#10 Key_Check = 1;
		#5 Key_Check = 0;

		#15 $stop;

	end
      
endmodule

