`timescale 1ns / 100ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:12:26 04/26/2023 
// Design Name: 
// Module Name:    fdivision 
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

module fdivision(
    input F10M, RESET,
    output reg F500KB
); 
    reg [7:0] j;
    always @(posedge F10M)
		if(!RESET) begin
         F500KB <= 0; 
         j <= 0;
      end
      else begin
        if(j==19) begin
           j <= 0;
           F500KB <= ~F500KB;
		  end
		  else j <= j+1;
		end
endmodule