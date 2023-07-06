`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:06:50 05/06/2023 
// Design Name: 
// Module Name:    seqdet 
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
module seqdet(
input x,clk,rst,
output wire z,
output reg [2:0] state
    );
	 parameter IDLE = 'd0,A='d1,B='d2,C='d3,D='d4,E='d5;
	 assign z = (state==E) ? 1 : 0;
	 always@(posedge clk)
		if(!rst)
			state <= IDLE;
		else casex(state)
			IDLE: if(x == 1) state <= A;
			A: if(x == 1) state <= B;
			B: if(x == 1) state <= C;
				else 		  state <= A;
			C: if(x == 1) state <= D;
				else       state <= A;
			D: if(x == 1) state <= E;
				else       state <= A;
			default:      state <= IDLE;
		endcase
endmodule
