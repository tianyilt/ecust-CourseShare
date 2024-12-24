// 整个 Verilog 代码设计了一个定时器模块，可以按照设定的延迟时间（delay）输出一个信号（out_sig）。内部使用了一个 32 位计数器用于计算时钟周期，当计数器累积到 1 秒时，会减去 1 秒的时间，直到全部延迟时间耗尽。当计时结束后，输出信号会被清零。

module timer (
    input wire clk,         // 时钟信号
    input wire rst,         // 复位信号
    input wire start,       // 开始信号
    input wire [4:0] delay, // 5位延迟（单位：秒）
    output reg out_sig      // 输出信号
);

reg [31:0] counter;        // 32位计数器，用于计算时钟周期数
reg [4:0] elapsed_seconds; // 计时开始后已过去的秒数
reg enable_count;          // 启动计数

// 计算1秒对应的时钟周期数（假设时钟频率为100MHz）
localparam CLK_CYCLES_PER_SECOND = 10;
// localparam CLK_CYCLES_PER_SECOND = 100_000_000;

always @(posedge clk) begin
    if (rst) begin
        counter <= 32'b0;         // 复位时清零计数器
        out_sig <= 1'b0;          // 复位时清除输出信号
        elapsed_seconds <= 5'b0;  // 复位时清零已过去的秒数
        enable_count <= 1'b0;     // 复位时禁止计数
    end
    else if (enable_count) begin
        counter <= counter + 32'b1; // 增加计数器值

        if (counter == CLK_CYCLES_PER_SECOND - 1) begin
            counter <= 32'b0;         // 计数器达到1秒，重置为0
            if (elapsed_seconds > 5'b0) begin
                elapsed_seconds <= elapsed_seconds - 5'b1; // 已过去的秒数递减1秒
            end else begin
                out_sig <= 1'b0;      // 计时完成，清除输出信号
                enable_count <= 1'b0; // 禁止计数
            end
        end
    end
	//  else if (start) begin
	// 	  elapsed_seconds <= delay; // 当开始信号为高电平并检测到上升沿时，将延迟值赋给已过去的秒数
    //     enable_count <= 1'b1;     // 启动计数
    //     counter <= 32'b0;         // 清零计数器
    //     out_sig <= 1'b1;          // 设置输出信号
	//  end
end
always@(posedge start) begin
    if (!rst && !enable_count) begin
        elapsed_seconds <= delay; // 当开始信号为高电平并检测到上升沿时，将延迟值赋给已过去的秒数
        enable_count <= 1'b1;     // 启动计数
        counter <= 32'b0;         // 清零计数器
        out_sig <= 1'b1;          // 设置输出信号
    end
end
endmodule
