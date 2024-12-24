module simu;

reg clk;
reg rst;
reg [3:0] weight;
wire light_out, medium_out, heavy_out;

// Instantiate the top_module
top_module tm (
    .clk(clk),
    .rst(rst),
    .weight(weight),
    .light_out(light_out),
    .medium_out(medium_out),
    .heavy_out(heavy_out)
);

initial begin
    clk = 1'b0;
    rst = 1'b1;
    weight = 4'b0000;

    // Test the top_module for different weights
    #20 rst = 1'b0;  // Apply reset
    #100 weight = 4'b0001;  // Test light weight
    #1800 rst = 1'b1;
    #20 rst = 1'b0;
    #100 weight = 4'b0100;  // Test medium weight
    #1800 rst = 1'b1;
    #20 rst = 1'b0;
    #100 weight = 4'b0111;  // Test heavy weight
    #1800 rst = 1'b1;
    #20 rst = 1'b0;
    #100 weight = 4'b0010;  // Test another light weight
    #2000 $finish;
end

always #5 clk = ~clk;  // Clock generation with a period of 10 time units

endmodule
