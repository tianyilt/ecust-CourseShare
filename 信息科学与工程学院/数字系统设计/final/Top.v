`include "Key_Selector.v"
`include "Key_Vaildator.v"
`include "Key_Input.v"

`timescale 1ps/1ps
`define timeslice 1

// 实现一个电子密码锁
// 需要的输出信号:
// 1. 4位密码输入 Key_1[3:0] Key_2[3:0] Key_3[3:0] Key_4[3:0]
// 2. 密码锁状态锁状态 Lock_State (parameter Yes No 表示开锁和闭锁)
// 3. 密码位数选择(表示当前选中第几位) Key_Select[2:0]

// 需要的直接输入信号
// 4. 密码验证 Key_Check
// 5. 密码位置切换 Key_Switch_left Key_Switch_right
// 6. 密码读写状态 Key_RW (parameter Read Write 表示读写)
// 7. 密码输入 Key_Input[3:0]

// 需要设计的模块
// 1. 密码位选择模块 Key_Selector (根据Key_Switch_left和Key_Switch_right选择当前密码位, 并在Key_Select上输出)
// 2. 密码验证模块 Key_Vaildator (当密码确认按钮被按下时, 改变Key_Check的状态)
// 3. 密码输入模块 Key_Input (修改当前的读写状态, 当写入时, 将Key_Input写入到当前密码位)

module Top;
    // 输入信号
    wire Key_Switch_left;
    wire Key_Switch_right;
    wire Key_Check;
    wire Key_RW;
    wire [3:0] Key_Input;
    
    // 输出信号
    wire [3:0] Key_1;
    wire [3:0] Key_2;
    wire [3:0] Key_3;
    wire [3:0] Key_4;
    wire [2:0] Key_Select;
    wire       Lock_State;

    // 实际密码设置
    parameter [3:0] Key_1_real = 4'b0001; // 1
    parameter [3:0] Key_2_real = 4'b0101; // 5
    parameter [3:0] Key_3_real = 4'b0111; // 7 
    parameter [3:0] Key_4_real = 4'b1000; // 8

    // 密码位选择模块
    Key_Selector Key_Selector(
        .Key_Switch_left(Key_Switch_left),
        .Key_Switch_right(Key_Switch_right),
        .Key_Select(Key_Select)
    );

    // 密码验证模块
    Key_Vaildator Key_Vaildator(
        .Key_Check(Key_Check),
        .Key_1(Key_1),
        .Key_2(Key_2),
        .Key_3(Key_3),
        .Key_4(Key_4),
        .Key_1_real(Key_1_real),
        .Key_2_real(Key_2_real),
        .Key_3_real(Key_3_real),
        .Key_4_real(Key_4_real),
        .Key_Select(Key_Select),
        .Lock_State(Lock_State)
    );

    // 密码输入模块
    Key_Input Key_Input(
        .Key_RW(Key_RW),
        .Key_1(Key_1),
        .Key_2(Key_2),
        .Key_3(Key_3),
        .Key_4(Key_4),
        .Key_Input(Key_Input),
        .Key_Select(Key_Select)
    );
endmodule