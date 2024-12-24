`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:57:49 04/17/2023 
// Design Name: 
// Module Name:    mux_4to1 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module mux_4to1(y,a,b,c,d,sel
    );
	 input a,b,c,d;
	 input [1:0]sel;
	 output y;
	 reg y_reg;
	 assign y=y_reg;
	 always@(sel or a or b or c or d)
	 begin
	   case(sel)
		2'b00: y_reg = a;
		2'b01: y_reg = b;
		2'b10: y_reg = c;
		2'b11: y_reg = d;
	   default: y_reg = 1'b1;
		endcase
	end
endmodule
