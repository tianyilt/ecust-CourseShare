`timescale 1ns / 100ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   20:23:03 05/08/2023
// Design Name:   writing
// Module Name:   E:/exp10/simu.v
// Project Name:  exp10
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: writing
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////
`define cc 15
module simu;
	reg reset,clk;
	reg [7:0] data, address;
	wire ack,sda;
	writing uut (.reset(reset), .clk(clk), .data(data), .address(address), .ack(ack), .sda(sda));
	
	always #`cc clk = ~clk;
	initial begin
		reset = 1;
		clk = 0;
		data = 0;
		address = 0;
		#(2*`cc) reset = 0;
		#(2*`cc) reset = 1;
		#(100*`cc) $stop;
	end
   always@(posedge ack) begin
		data = data + 1;
		address = address + 1;
	end
endmodule

