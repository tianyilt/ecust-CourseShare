module top_module (
    input wire clk,
    input wire rst,
    input wire [3:0] weight,
    output wire light_out,
    output wire medium_out,
    output wire heavy_out
);

// Instantiate the cargo_sorter module
cargo_sorter cs (
    .weight(weight),
    .light(light),
    .medium_(medium_),
    .heavy(heavy)
);

// Instantiate three timer modules
timer tm_light (
    .clk(clk),
    .rst(rst),
    .start(light),
    .delay(5'd3),
    .out_sig(light_out)
);

timer tm_medium (
    .clk(clk),
    .rst(rst),
    .start(medium_),
    .delay(5'd4),
    .out_sig(medium_out)
);

timer tm_heavy (
    .clk(clk),
    .rst(rst),
    .start(heavy),
    .delay(5'd6),
    .out_sig(heavy_out)
);

endmodule
