`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:06:16 06/05/2021 
// Design Name: 
// Module Name:    parking_meter 
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
module parking_meter(input add1, input add2, input add3, input add4, input rst1, input rst2, input clk, input rst,
	 output reg [6:0] led_seg, output reg a1, output reg a2, output reg a3, 
	 output reg a4, output [3:0] val1, output [3:0] val2, output [3:0] val3, output [3:0] val4
    );
	parameter initFlash = 2'b00;
	parameter flash180 = 2'b01;
	parameter flash = 2'b10;
	
	reg[1:0] current;
	reg[1:0] next;
	reg[13:0] seconds;
	reg reduce = 0;
	reg reduce2 = 0;
	reg flashy;
	reg[6:0] counter_time;
	reg added = 0;
	
	always @(posedge clk) begin
		reduce <= ~reduce;
	end

	always @(negedge clk)
		reduce2 <= ~reduce2;

	
	always @(*)begin
		if(rst)
			current = initFlash;
		else if(rst1 || rst2)
			current = flash;
		else if (reduce == reduce2)
			current = next;
		end
	
	//counts time for us
	always @(*) begin
		if(rst || rst1 || rst2 || add1 || add2 || add3 || add4)
			counter_time = 7'd0;
		else if(reduce2==reduce && counter_time == 7'd99)
			counter_time = 7'd0;
		else if(reduce2==reduce)
			counter_time  = counter_time + 7'd1;
	end
	

		
	//updates time
	always @ (*) begin
		if(rst)
			seconds = 14'd0;
		else if(rst1)
			seconds = 14'd16;
		else if(rst2)
			seconds = 14'd150;
		else if(add1 && !added)
			seconds = ((seconds + 14'd60) > 14'd9999)?14'd9999:(seconds + 14'd60);
		else if(add2 && !added)
			seconds = ((seconds + 14'd120) > 14'd9999)?14'd9999:(seconds + 14'd120);
		else if(add3 && !added)
			seconds = ((seconds + 14'd180) > 14'd9999)?14'd9999:(seconds + 14'd180);
		else if(add4 && !added)
			seconds = ((seconds + 14'd300) > 14'd9999)?14'd9999:(seconds + 14'd300);
		else if(reduce==reduce2 && seconds > 14'd0 && counter_time == 7'd99)
			seconds = seconds - 14'd1;
		
		if(add1 || add2 || add3 || add4)
			added = 1;
		else
			added = 0;
	end
	
	always @(*) begin
	case(current)
		initFlash: begin
			if(counter_time == 7'd0)
				flashy = 1;
			else if(counter_time == 7'd50)
				flashy = 0;
			
			if(seconds > 14'd180)
				next = flash180;
			else if (seconds == 14'd0)
				next = initFlash;
			else
				next = flash;
		end
		flash: begin
			if(seconds % 2 == 1)
				flashy = 0;
			else
				flashy = 1;
			if(seconds > 14'd180)
				next = flash180;
			else if (seconds == 14'd0)
				next = initFlash;
			else
				next = flash;
		end
		flash180: begin 
			flashy = 1;
			if(seconds > 14'd180)
				next = flash180;
			else if (seconds == 14'd0)
				next = initFlash;
			else
				next = flash;
		end
	endcase
	end
	

	assign val4 = seconds / 1000;
	assign val3 = (seconds - 1000 * val4) / 100;
	assign val2 = ((seconds - 1000 * val4) - 100 * val3) / 10;
	assign val1 = ((seconds - 1000 * val4) - 100 * val3) - 10 * val2;
	
	reg[1:0] anode_counter;
	always@(*)begin
		if(rst||rst1||rst2)
			anode_counter = 2'd0;
		else if(reduce==reduce2)
			anode_counter = anode_counter + 2'd1;
	end
	
	always@(posedge clk) begin
		if(rst || rst1||rst2) begin
			a1 <= 1;
			a2 <= 1;
			a3 <= 1;
			a4 <= 1;
		end
		else if(flashy) begin
			if(anode_counter == 2'd0) begin
				a1 <= 1;
				a2 <= 1;
				a3 <= 1;
				a4 <= 0;
				if(val4 == 0) led_seg <= 7'b0000001;
				if(val4 == 1) led_seg <= 7'b1001111;
				if(val4 == 2) led_seg <= 7'b0010010;
				if(val4 == 3) led_seg <= 7'b0000110;
				if(val4 == 4) led_seg <= 7'b1001100;
				if(val4 == 5) led_seg <= 7'b0100100;
				if(val4 == 6) led_seg <= 7'b0100000;
				if(val4 == 7) led_seg <= 7'b0001111;
				if(val4 == 8) led_seg <= 7'b0000000;
				if(val4 == 9) led_seg <= 7'b0000100;
			end
			else if(anode_counter == 2'd1)begin
				a1 <= 1;
				a2 <= 1;
				a3 <= 0;
				a4 <= 1;
				if(val3 == 0) led_seg <= 7'b0000001;
				if(val3 == 1) led_seg <= 7'b1001111;
				if(val3 == 2) led_seg <= 7'b0010010;
				if(val3 == 3) led_seg <= 7'b0000110;
				if(val3 == 4) led_seg <= 7'b1001100;
				if(val3 == 5) led_seg <= 7'b0100100;
				if(val3 == 6) led_seg <= 7'b0100000;
				if(val3 == 7) led_seg <= 7'b0001111;
				if(val3 == 8) led_seg <= 7'b0000000;
				if(val3 == 9) led_seg <= 7'b0000100;
			end
			else if(anode_counter == 2'd2)begin
				a1 <= 1;
				a2 <= 0;
				a3 <= 1;
				a4 <= 1;
				if(val2 == 0) led_seg <= 7'b0000001;
				if(val2 == 1) led_seg <= 7'b1001111;
				if(val2 == 2) led_seg <= 7'b0010010;
				if(val2 == 3) led_seg <= 7'b0000110;
				if(val2 == 4) led_seg <= 7'b1001100;
				if(val2 == 5) led_seg <= 7'b0100100;
				if(val2 == 6) led_seg <= 7'b0100000;
				if(val2 == 7) led_seg <= 7'b0001111;
				if(val2 == 8) led_seg <= 7'b0000000;
				if(val2 == 9) led_seg <= 7'b0000100;
			end
			else if(anode_counter == 2'd3)begin
				a1 <= 0;
				a2 <= 1;
				a3 <= 1;
				a4 <= 1;
				if(val1 == 0) led_seg <= 7'b0000001;
				if(val1 == 1) led_seg <= 7'b1001111;
				if(val1 == 2) led_seg <= 7'b0010010;
				if(val1 == 3) led_seg <= 7'b0000110;
				if(val1 == 4) led_seg <= 7'b1001100;
				if(val1 == 5) led_seg <= 7'b0100100;
				if(val1 == 6) led_seg <= 7'b0100000;
				if(val1 == 7) led_seg <= 7'b0001111;
				if(val1 == 8) led_seg <= 7'b0000000;
				if(val1 == 9) led_seg <= 7'b0000100;
			end
		end
		else begin
			a1 <= 1;
			a2 <= 1;
			a3 <= 1;
			a4 <= 1;
		end
	end
endmodule
