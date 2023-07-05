`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:42:40 04/26/2023 
// Design Name: 
// Module Name:    edged 
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

//±ßÔµ´¥·¢µÄD´¥·¢Æ÷
module edged(
input d,clk,
output reg q,qn
    );
always@(posedge clk) begin
	q <= d;
	qn <= ~d;
end
endmodule
