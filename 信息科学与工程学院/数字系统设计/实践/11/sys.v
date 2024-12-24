`include "./P_S.v"
`include "./S_P.v"
module sys(input wire nGet_AD_data,
           input wire clk,
           input use_p_in_bus,
           inout [7:0] databus,
           output wire Dbit_out,
           output wire Dbit_ena);
    wire [7:0] data;
    assign databus = (!use_p_in_bus) ? data : 8'bzzzz_zzzz;
    P_S m0(.Dbit_out(Dbit_out),.link_S_out(Dbit_ena),.data(databus),
    .nGet_AD_data(nGet_AD_data),.clk(clk));
    S_P m1(.data(data),.Dbit_in(Dbit_out),
    .Dbit_ena(Dbit_ena),.clk(clk));
endmodule
