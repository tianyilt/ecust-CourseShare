`timescale 1ns / 100ps

module simu;
    wire [7:0] indata;
    reg clk, reset, start, rd; 
    wire [10:0] address; 
    wire [7:0] outdata; 
    wire nconvst1, nconvst2, nconvst3, wr, enout1, enout2,nbusy1, nbusy2, nbusy3; 

    con3ad uut (
        .indata(indata),
        .CLK(clk),
        .reset(reset),
        .start(start),
        .nbusy1(nbusy1),
        .nbusy2(nbusy2),
        .nbusy3(nbusy3),
        .address(address),
        .outdata(outdata),
        .nconvst1(nconvst1),
        .nconvst2(nconvst2),
        .nconvst3(nconvst3),
        .wr(wr),
        .enout1(enout1),
        .enout2(enout2)
    );

    parameter HALF_PERIOD = 15;

    initial begin
        clk = 1;
        forever # HALF_PERIOD clk = ~clk;
    end

    initial begin
        reset = 1;
        #110 reset = 0;
        #140 reset = 1;
    end

    initial begin
        start = 0;
        rd = 1;
        #420 start = 1;
        #120 start = 0;
        #107600 start = 1;
        #150 start = 0;
    end

endmodule
