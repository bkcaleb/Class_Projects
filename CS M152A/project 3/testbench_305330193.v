`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:02:02 05/14/2021
// Design Name:   vending_machine
// Module Name:   /home/ise/xilinx/Proj3/Proj3/testbench_305330193.v
// Project Name:  Proj3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: vending_machine
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module testbench_305330193;
	//input
	reg CLK;
	reg RESET;
	reg RELOAD;
	reg CARD_IN;
	reg [2:0] ITEM_CODE;
	reg KEY_PRESS;
	reg VALID_TRAN;
	// Outputs
	wire VEND;
	wire INVALID_SEL;
	wire [2:0] COST;
	wire FAILED_TRAN;

	// Instantiate the Unit Under Test (UUT)
	vending_machine uut (
		.CLK(CLK),
		.RESET(RESET), 
		.RELOAD(RELOAD),
		.CARD_IN(CARD_IN), 
		.ITEM_CODE(ITEM_CODE), 
		.KEY_PRESS(KEY_PRESS),  
		.VALID_TRAN(VALID_TRAN), 
		.VEND(VEND), 
		.INVALID_SEL(INVALID_SEL),
		.COST(COST),		
		.FAILED_TRAN(FAILED_TRAN)		
	);

	initial begin
		// Initialize Inputs
		CARD_IN = 0;
		VALID_TRAN = 0;
		ITEM_CODE = 0;
		KEY_PRESS = 0;
		RELOAD = 0;
		CLK = 0;
		RESET = 0;
		// Wait 100 ns for global reset to finish
		#100;
      //first successful case
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 1; // LOAD
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1;
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		CARD_IN = 0;
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 1; //validate to vend
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		
		
		
		//first special case. try to vend without reloading
		#5
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 0; // Don't LOAD The rest of the code will be same as first one from now on
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1;
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		CARD_IN = 0;
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 1; //validate to vend
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		
		//second case Valid_tran is never 1
		#5
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 1; // LOAD
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1;
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		CARD_IN = 0;
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0; //DO NOT validate to vend
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0; //waiting for 5 cycles
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; 
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; //IDLE
		#5
		CLK = 0;		
		
		//third case: selection is invalid
		#5
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 1; // LOAD
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1;
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		CARD_IN = 0;
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b111;
		KEY_PRESS = 1; //second input: 7
		CLK = 0;
		#5 //total input : 27 THIS IS NOT IN RANGE. rest of the code is same as first success code
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 1; //validate to vend
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		
		//fourth case: second digit is not input within 5 cycles
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 1; // LOAD
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1;
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		CARD_IN = 0;
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0; // 5 cycles here
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 1; //validate to vend
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		
		//fifth case: CARD_IN is 1 for 11 transactions without reload
		CLK = 1;
		RESET = 1;
		#5
		CLK = 0;	
		#5 //IDLE
		RESET = 0;
		CLK = 1;
		#5
		CLK = 0;	
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		RELOAD = 1; // LOAD
		#5
		CLK = 1;
		#5
		RELOAD = 0;
		CLK = 0;// IDLE
		#5
		CLK = 1;
		#5
		CARD_IN = 1; //turn this on always for convenience
		CLK = 0; // WAIT FOR INPUT
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		ITEM_CODE = 3'b010;
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		VALID_TRAN = 1; //validate to vend, this will always be on too
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//second transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//third transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//fourth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//fifth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//sixth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//seventh transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//eigth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//ninth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//tenth transaction
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		//eleventh transaction = should output invalid_sel to be 1
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; // first input: 2
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 0;
		CLK = 0;
		#5
		CLK = 1;
		#5
		KEY_PRESS = 1; //second input: 2
		CLK = 0;
		#5 //total input : 22
		CLK = 1;
		#5
		KEY_PRESS = 0; //no more input
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1;
		#5
		CLK = 0;
		#5
		CLK = 1; // idle
		#5
		CLK = 0;
		
		
		end
      
endmodule

