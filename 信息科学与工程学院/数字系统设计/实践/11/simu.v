`timescale 1ns/1ns
`include "./sys.v"
module simu;
    reg clk;
    reg [7:0] data_buf;
    reg nGet_AD_data;
    reg D_Pin_ena;
    wire [7:0] data;
    // wire clk2;
    wire Dbit_ena;
    assign data = (D_Pin_ena)? data_buf : 8'bz;

initial begin
clk = 0;
nGet_AD_data =1; 
data_buf = 8'b1001_1001;
D_Pin_ena = 0;
end
initial begin
	repeat(100) begin
		# (100 * 14+{$random} %23) nGet_AD_data = 0;
		# (112+{$random} %12) nGet_AD_data= 1;
		# ({$random} %50) D_Pin_ena = 1;
		# (100*3 + {$random}%5) D_Pin_ena = 0;
		# 333 data_buf = data_buf+1; 
		# (100* 11 + {$random} %1000);
	end
end
always #(50+ $random%2) clk = ~clk;
sys ms(.databus(data),
	.use_p_in_bus(D_Pin_ena),
	.Dbit_out(Dbit_out),
	.Dbit_ena(Dbit_ena),
	.nGet_AD_data(nGet_AD_data),
	.clk(clk));

endmodule