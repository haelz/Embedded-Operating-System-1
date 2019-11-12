// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.1.3 (win64) Build 2644227 Wed Sep  4 09:45:24 MDT 2019
// Date        : Fri Nov  8 23:45:38 2019
// Host        : DESKTOP-LVJ56DR running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/FPGA/Assignment_1/FPGA/PongDesign/PongDesign.srcs/sources_1/bd/design_1/ip/design_1_ila_0_1/design_1_ila_0_1_stub.v
// Design      : design_1_ila_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z007sclg225-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "ila,Vivado 2019.1.3" *)
module design_1_ila_0_1(clk, probe0)
/* synthesis syn_black_box black_box_pad_pin="clk,probe0[23:0]" */;
  input clk;
  input [23:0]probe0;
endmodule
