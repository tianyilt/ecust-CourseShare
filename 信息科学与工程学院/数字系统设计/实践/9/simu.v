`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:18:51 05/06/2023
// Design Name:   seqdet
// Module Name:   E:/exp9/simu.v
// Project Name:  exp9
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: seqdet
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module simu;
	reg clk,rst;
	reg [23:0] data;
	wire z,x;
	wire [2:0] state;
	assign x = data[23];
	always #10 clk = ~clk;
	always@(posedge clk) data = {data[22:0],data[23]};
	seqdet uut (.x(x), .clk(clk), .rst(rst), .z(z), .state(state));
	initial begin
		clk = 0;
		rst = 1;
		#2 rst = 0;
		#30 rst = 1;
		data = 'b1000_1001_0000_1111_0100;
	end
endmodule

