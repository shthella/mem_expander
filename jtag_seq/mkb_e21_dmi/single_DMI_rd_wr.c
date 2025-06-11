#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdbool.h>

#define SIZE 0x10000

#define REG_LEN_OFFSET      (0x00 / sizeof(uint32_t))    // Length of shift operation in bits
#define REG_TMS_OFFSET      (0x04 / sizeof(uint32_t))    // TMS (Test Mode Select) register offset
#define REG_TDI_OFFSET      (0x08 / sizeof(uint32_t))    // TDI (Test Data In) register offset
#define REG_TDO_OFFSET      (0x0c / sizeof(uint32_t))    // TDO (Test Data Out) register offset
#define REG_CTRL_OFFSET     (0x10 / sizeof(uint32_t))   // Control register offset

// send_IR_reg DTMCS and DMI opcodes
#define IDCODE                  0x01
#define DTMCS                   0x10
#define DMI                     0x11

// DMI addr[6:0]
#define DMCONTROL_REG       0x10
#define DMSTATUS_REG        0x11
#define HAWINDOW_REG        0x15
#define ABSTRACTCS          0x16
#define COMMAND             0x17
#define PROGBUF0            0x20
#define PROGBUF1            0x21
#define SBCS                0x38
#define DATA0               0x04
#define DATA1               0x05
#define SBADDRESS0          0x39
#define SBADDRESS1          0x3a
#define SBDATA0             0x3c
#define SBDATA1             0x3d
#define HALT_SUM0_REG       0x40
// Debug Registers 
#define DPC                 0x7b1
#define DCSR                0x7b0

/*dmstatus-holds the DM version number and other implementation information. Most importantly,it contains status bits that indicate the current state of the selected hart(s).
  A debugger performs most hart controls through the dmcontrol register.
  */
//scan in(debugger wants to write opcode
//OPCODE(2bit)
#define NO_OP                       0x0//do not intiate any opeation
#define READ_OP                     0x1 //read
#define WRITE_OP                    0x2//wite
#define RSVD_OP                     0x3//resved
#define OP_ERROR		            0x3

#define DEFAULT_VALUE       		0x00000000
#define DMIRESET 	        	    (1<<16)
#define DMACTIVE	        	    (1<<0)
#define DM_HALT_REQ            		(1<<31)
#define DM_RESUME_REQ	        	(1<<30)
#define ANYHAVE_RESET	    		(1<<18)
#define DCSR_STEP_MODE      		0x4000b007
#define DCSR_MODE       		    0x4000b003
#define DMCONTROL_RESUME_REQ   		0x40000000
#define DMSTATUS_RESUMEACK  		0x00020000
#define DMSTATUS_HALTED     		0x00000200
#define SBCS_WRITE_CONFIG   		0x00447000
#define SBCS_READ_CONFIG    		0x00547000
#define PROGBUF_SW          		0x0084a023
#define PROGBUF_LW          		0x0004a403
#define PROGBUF_EBREAK      		0x00100073
#define COMMAND_WRITE_32    		0x00231000
#define COMMAND_READ_32     		0x00221000
#define PROGBUF_MEM			        0x271008
#define PROGBUF_EXE			        0x40000
#define PROGBUF_TRANSFER		    0x221008
volatile uint32_t *ptr;                                                                           
volatile uint64_t TDOout=0x00;                                                                    
uint8_t impebreak; 
volatile uint32_t data,dmcontrol_base;    
static bool rv64 = true, preferSBA = true, sbapresent = false,err;

//for DMi starting steps
void Reset_DMI();                                                                 
void Activate_DM();                                                                          
void Halt();                                                                                
void Resume();                                                                               
void step();

//To select single hart and multiple harts 
void select_harts(uint16_t hartsel ,uint32_t hartarray);

//for multiple harts 
void Setdcsr(uint32_t data);

//DMI functions 
void Read_DMI(uint8_t addr, uint32_t *data, bool*err);                                                                          
void Write_DMI(uint8_t addr,uint32_t data); 

//register access GPR's
void Read_Reg(uint8_t regno, uint64_t *data);
void Write_Reg(uint8_t regno, uint64_t data);

//CSR register access
void Write_CSR(uint32_t regno,uint64_t data);
void Read_CSR(uint32_t regno,uint64_t *data);

//memory Access for sba nd progbuffer 
void Read_Mem(uint64_t addr, uint32_t *data);
void Write_Mem(uint64_t addr, uint32_t data);

//for use system bus access
void Read_Mem_SBA(uint64_t addr, uint32_t *data);
void Write_Mem_sba(uint64_t addr, uint32_t data);

//for accesing teh prog buffer 
void Read_Mem_Progbuf(uint64_t addr, uint32_t *data);
void Write_Mem_Progbuf(uint64_t addr, uint32_t data);                                                  

//wait functions for all process
void WaitDMI(uint8_t addr, uint32_t mask);  
void Wait_SBA();
void WaitAbstract();                                                    



void jtag_send(uint32_t tms, uint64_t tdi, uint32_t len) {
	ptr[REG_LEN_OFFSET] = len;                                      
	ptr[REG_TMS_OFFSET] = tms;                                                                                                   
	ptr[REG_TDI_OFFSET] = tdi;                                        
	ptr[REG_CTRL_OFFSET] = 0x1; // Trigger JTAG transfer                     
}                                                         

void idle_to_cap_ir() {                                                                                                                                                       
	jtag_send(0xc, 0x0, 4);                                       
}    

//exit toshift_ir                                                     
void exit_ir_to_shift_dr() {                                                 
	jtag_send(0x14, 0x0, 5);                                                                
}   

//exit to idle                                                               
void exit_to_idle() {                                             
	jtag_send(0x5, 0x0, 4);                                              
	printf("TMS Read/Write Sequence Complete\n");                                           
}    

void DMI_send_IR(uint8_t bits, uint8_t value) {                                                   
	// Move TAP controller to Capture-IR state                                            
	idle_to_cap_ir();  // Typically sends TMS=1 -> 1 -> 0 (to Capture-IR)                   

	//shift_ir state                                                                     
	jtag_send(0,value,bits);                                                                            

	jtag_send(0x1, 0, 2);  // Exit1-IR->Update-IR // Update-IR-> Idle                      
}    

//to send any no.of bits to max 32 bits size                                                 
void DMI_send_DR(uint64_t bits, uint64_t value) {                                                 
	jtag_send(0x1, 0x0, 3); // Idle -> Select-DR -> Capture-DR                            
	TDOout = 0;                                                                               
	uint64_t shift_tdo = 0;                                                               
	int tdo_data = 0;                                                                      

	while (bits > 0) {                                            
		uint8_t size = (bits >= 32) ? 32 : bits;                     
		uint32_t chunk = value & ((1ULL << size) - 1);
		jtag_send(0, chunk, size);                          
		uint32_t tdo_chunk = ptr[REG_TDO_OFFSET];                               
		shift_tdo |= ((uint64_t)tdo_chunk << tdo_data);       
		tdo_data += size;                                            
		value >>= size;                               
		bits -= size;                                                
	}                                                                                                                                                                     
	TDOout = shift_tdo;                                           
	exit_to_idle();//ext to idle                                                             
}      

void WaitDMI(uint8_t addr, uint32_t mask) {                                  
	uint32_t val = 0;                                                                       
	bool err = false;  
	printf("wait dmi is called\n");	
	do{                                                                  
		Read_DMI(addr,&val,&err);                                                       
	}while ((val & mask)==0);                                         
	printf("the value from thet address is %08x\n",val); 
	printf("wait dmi is done\n");	
}      
void Wait_SBA(void) {
	uint32_t val;
	bool err = false;
	do {
		Read_DMI(SBCS, &val, &err);
	} while ((val>>21)&1);
}

void WaitAbstract(void) {
	uint32_t val;
	bool err = false;
	do {
		Read_DMI(ABSTRACTCS, &val, &err);
	} while ((val>>12)&1);
}

void select_harts(uint16_t hartsel ,uint32_t hartarray){
	if(hartarray!=0){ //
		dmcontrol_base = DMACTIVE | (1 << 26) | (hartsel << 16);//here set dmactive , ndmreset,hartsel 
	}
	else{
		dmcontrol_base = DMACTIVE | (hartsel << 16);
	}
	Write_DMI(DMCONTROL_REG,dmcontrol_base);
	Write_DMI(HAWINDOW_REG,hartarray);
}
//for multiple harts
//set dcsr of all selected harts 
void Setdcsr(uint32_t data){
	uint32_t hartarray;
	bool err;
	int i=0;
	Write_CSR(DCSR,data);
	if((dmcontrol_base >>26)&1){ //if the hasel == 1 
		Read_DMI(HAWINDOW_REG,&hartarray,&err);
		for (i=0;i<32;i++){//32 harts are in sifi core  
			if(hartarray & (1<<i)){
				Write_DMI(DMCONTROL_REG,(i<<16) | 1); //hartsel=i
				Write_CSR(DCSR,data);
			}
		}
		Write_DMI(DMCONTROL_REG,dmcontrol_base);
	}
}
void Reset_DMI(){                                                            
	printf("reset_dmi step\n");                               

	DMI_send_IR(5, DTMCS);//shift_ir                                           
	DMI_send_DR(32, DEFAULT_VALUE);//shift_dr
    //access dmi from shift ir for next clock cycle                   
	DMI_send_IR(5, DMI); 
	//check the dmcontrol value for 0 or not                  
	Read_DMI(DMCONTROL_REG,&data,&err);                                                
	printf("resetdmi done\n");                                        
}                                         
//Activate the debug module                                                     
void Activate_DM() {                                                                            
	printf("activate dmi start\n");                              
	//write 1 to dmcontrol register             
	Write_DMI(DMCONTROL_REG, DMACTIVE);                                  
	WaitDMI(DMCONTROL_REG, DMACTIVE);                                                
	printf("activate dmi done\n");             
} 

//for multiple hart       
void Resume(){
	//dcsr= is in privilage in machine mode ,ebreaks,m,u in mode and 0x4 externel debug support
	Setdcsr(DCSR_MODE);                                             //debug control and satus register 
	Write_DMI(DMCONTROL_REG,dmcontrol_base | DM_RESUME_REQ);        //0x40000000
	WaitDMI(DMSTATUS_REG,DMSTATUS_RESUMEACK);                       //check the 17th for allresumeack 
}
//halt
void Halt(){
	Write_DMI(DMCONTROL_REG,dmcontrol_base | DM_HALT_REQ);          //0x80000000
	WaitDMI(DMSTATUS_REG,DMSTATUS_HALTED);                          //check the 9th for any selected harts are halted
}
void step(){		 
	//dcsr= is in privilage in machine mode ,step bit ,ebreaks,m,u in mode and 0x4 externel debug support	
	Setdcsr(DCSR_STEP_MODE);    
	Write_DMI(DMCONTROL_REG, dmcontrol_base | DMCONTROL_RESUME_REQ);
	WaitDMI(DMSTATUS_REG,DMSTATUS_RESUMEACK);                       //anyresume ack bit 
	WaitDMI(DMSTATUS_REG,DMSTATUS_HALTED);                          //all halted 
}
//register access
//for gpr to perfom read /write using abstract command    
void Write_Reg(uint8_t regno, uint64_t data) {
	Write_DMI(DATA0, data);		                     //write to addr(DATA0=0x04//values in these registers may not be preserved after an command is executed,if command fails there is no data in this registers  
	Write_DMI(COMMAND, COMMAND_WRITE_32 + regno);     //addr=command(0x17),transfer,write,0x300
	WaitAbstract();
}

void Read_Reg(uint8_t regno,uint64_t *data){
	bool *err=false;
	uint32_t low=0,high=0;
	Write_DMI(COMMAND, COMMAND_READ_32 + regno);//write to address command(0x17),transfer and size=32
	WaitAbstract();				                //checking the command status
	Read_DMI(DATA0, &low, &err);                //read from the data0 address for value 
	data=((uint64_t)high <<32) | low;
	printf("read_reg is complted\n");
} 
//for csr register sto perform read/write using teh progbuffer (via progbuffer we can access csr registers)
void Write_CSR(uint32_t regno,uint64_t data){
    Write_Reg(DATA0,data);
	Write_DMI(PROGBUF0, 0x00041073 + (regno<<20));  //addr= progbuf0 ,instruction 
	Write_DMI(PROGBUF1, PROGBUF_EBREAK);            // ebreak
	Write_DMI(DATA0, data);			                //write a new value to addr=DATA0
	Write_DMI(COMMAND, PROGBUF_MEM);                //32 bits ,write,tranfer,progbuf,1008 register (gpr)
	WaitAbstract();
}
void Read_CSR(uint32_t regno, uint64_t *data){
    Write_DMI(PROGBUF0, 0x00002473 + (regno<<20));  //write a value to progbuf0  
	Write_DMI(PROGBUF1, PROGBUF_EBREAK);            // ebreak
	Write_DMI(COMMAND,PROGBUF_EXE);                 //execute progbuffer 
	Write_DMI(COMMAND, PROGBUF_TRANSFER);	        //write to addr= command and value,transfer,regno=1008(221008)
	WaitAbstract();					                //check teh status of comamnd 
    Read_Reg(DATA0,data);
}

//memory access
void Write_Mem(uint64_t addr, uint32_t data) {
	if (preferSBA && sbapresent) {         //we use sba and progbuffer on the capability and sbapresent and prefersba(variable for the prefered type of memory operations)
		Write_Mem_sba(addr, data);
	} else {
		Write_Mem_Progbuf(addr, data);
	}
}
//sba memory
void Write_Mem_sba(uint64_t addr, uint32_t data) {
	Write_DMI(SBADDRESS, addr);
	Write_DMI(SBCS, SBCS_WRITE_CONFIG);       //write to adr=sbcs the system bus accesses can be initiated by the debug module. 
	Write_DMI(SBDATA0, data);                 //write to sdata0 addr to data
	Wait_SBA();
}
//progbuf memory 
void Write_Mem_Progbuf(uint64_t addr, uint32_t data) {
	Write_DMI(PROGBUF0, PROGBUF_SW);            //sw instruction
	Write_DMI(PROGBUF1, PROGBUF_EBREAK);        //ebreak
	Write_DMI(DATA0, data);                     //write to data0
	Write_DMI(COMMAND, PROGBUF_MEM);            //size=32 write,//data0->x8 ,run progbuffer
	Write_DMI(DATA0, addr);                     //write to data0
	Write_DMI(COMMAND, 0x251009);               //size=32 write,//data0->x8 ,run progbuffer
	WaitAbstract();                             //check teh status of command
}

void Read_Mem(uint64_t addr, uint32_t *data) {
	if (preferSBA && sbapresent) {
		Read_Mem_SBA(addr, data);
	} else {
		Read_Mem_Progbuf(addr, data);
	}
}
void Read_Mem_SBA(uint64_t addr, uint32_t *data) {
	bool *err = false;
	Write_DMI(SBADDRESS0, addr);
	Write_DMI(SBCS, SBCS_READ_CONFIG);          //write to adr=sbcs the system bus accesses can be initiated by the debug module. 
	Wait_SBA();
	Read_DMI(SBDATA0, data, &err);              //value read from previous 
}

void Read_Mem_Progbuf(uint64_t addr, uint32_t *data) {

	Write_DMI(PROGBUF0, PROGBUF_LW);            //instruction 
	Write_DMI(PROGBUF1, PROGBUF_EBREAK);        //ebreak
	Write_DMI(DATA0, addr);	                    //write a value to data0 addr 
	Write_DMI(COMMAND, PROGBUF_MEM);            //command(0x17) to execute progbuffer,data0->x8 ,run progbuffer  
	WaitAbstract();
	Read_Reg(8, &result);                       //to read value in x8//read s0
	data = (uint32_t)result; 
}

//to read/write on DMI 
void Read_DMI(uint8_t addr, uint32_t *data, bool *err) {
	*err = false;
	printf("ReadDMI is called\n");

	// Send Read request
	DMI_send_DR(41, ((uint64_t)addr << 34) | READ_OP);
	// Send NO-OP to get result
	DMI_send_DR(41, ((uint64_t)addr << 34) | NO_OP);

	TDOout = ptr[REG_TDO_OFFSET];

	// If OP_ERROR, reset and retry
	while ((TDOout & OP_ERROR) == OP_ERROR) {
		printf("Before operation completed, initiating new operation\n");

		DMI_send_IR(5, DTMCS);
		DMI_send_DR(32, DMIRESET);

		DMI_send_IR(5, DMI);
		DMI_send_DR(41, ((uint64_t)addr << 34) | NO_OP);
	}

	if ((TDOout & 0x3) != NO_OP) {
		*data = 0;
		*err = true;
	} else {
		*data = (uint32_t)(TDOout >> 2);
		*err = false;
	}

	printf("addr = 0x%02X\n", addr);
	printf("data = 0x%08X\n", *data);
	printf("ReadDMI is done\n");
}

void Write_DMI(uint8_t addr, uint32_t data) {
	printf("WriteDMI is called\n");

	DMI_send_DR(41, ((uint64_t)addr << 34) | ((uint64_t)data << 2) | WRITE_OP);
	DMI_send_DR(41, ((uint64_t)addr << 34) | NO_OP);

	TDOout = ptr[REG_TDO_OFFSET];

	while ((TDOout & OP_ERROR) == OP_ERROR) {
		printf("Before operation completed, initiating new operation\n");

		DMI_send_IR(5, DTMCS);
		DMI_send_DR(32, DMIRESET);
		DMI_send_IR(5, DMI);
		DMI_send_DR(41, ((uint64_t)addr << 34) | NO_OP);
	}

	printf("addr = 0x%02X\n", addr);
	printf("data = 0x%08X\n", data);
	printf("WriteDMI is done\n");
}
int main(int argc, char *argv[]) {
	int fd;
	uint8_t cmd;
	uint64_t addr;
	uint32_t data;
	void *mapped;

	// Open and map memory
	fd = open("/dev/uio0", O_RDWR | O_SYNC);
	if (fd < 0) {
		perror("open /dev/uio0");
		return -1;
	}

	mapped = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mapped == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -1;
	}
	ptr = (volatile uint32_t *)((char *)mapped); 
	if (argc < 2) {
		printf("Usage:\n");
		printf("  Reset DMI     : %s 0\n", argv[0]);
		printf("  Activate DM   : %s 1\n", argv[0]);
		printf("  Halt          : %s 2\n", argv[0]);
		printf("  Resume        : %s 3\n", argv[0]);
		printf("  Step          : %s 4\n", argv[0]);
		printf("  Read_Reg      : %s 5 <regno>\n", argv[0]);
		printf("  Write_Reg     : %s 6 <regno> <data>\n", argv[0]);
		printf("  Read_CSR      : %s 7 <csrno>\n", argv[0]);
		printf("  Write_CSR     : %s 8 <csrno> <data>\n", argv[0]);
		printf("  Read_Mem      : %s 9 <addr>\n", argv[0]);
		printf("  Write_Mem     : %s 10 <addr> <data>\n", argv[0]);
		return -1;
	}

	switch (cmd) {
		case 0: Reset_DMI(); break;
		case 1: Activate_DM(); break;
		case 2: Halt(); break;
		case 3: Resume(); break;
		case 4: step(); break;

		case 5: { // Read_Reg
				if (argc != 3 || sscanf(argv[2], "%x", &addr) != 1) {
					printf("Usage: %s 5 <regno>\n", argv[0]);
					return -1;
				}
				uint64_t val64;
				Read_Reg((uint8_t)addr, &val64);
				printf("Reg[%u] = 0x%016lx\n", addr, val64);
				break;
			}
		case 6: { // Write_Reg
				if (argc != 4 || sscanf(argv[2], "%x", &addr) != 1 || sscanf(argv[3], "%lx", (unsigned long *)&data) != 1) {
					printf("Usage: %s 6 <regno> <data>\n", argv[0]);
					return -1;
				}
				Write_Reg((uint8_t)addr, (uint64_t)data);
				break;
			}
		case 7: { // Read_CSR
				if (argc != 3 || sscanf(argv[2], "%x", &addr) != 1) {
					printf("Usage: %s 9 <csrno>\n", argv[0]);
					return -1;
				}
				uint64_t val;
				Read_CSR(addr, &val);
				printf("CSR[0x%03x] = 0x%016lx\n", addr, val);
				break;
			}
		case 8: { // Write_CSR
				uint64_t dataval = 0;
				if (argc != 4 || sscanf(argv[2], "%x", &addr) != 1 || sscanf(argv[3], "%lx", &dataval) != 1) {
					printf("Usage: %s 10 <csrno> <data>\n", argv[0]);
					return -1;
				}
				Write_CSR(addr, dataval);
				break;
			}
		case 9: { // Read_Mem
				if (argc != 3 || sscanf(argv[2], "%x", &addr) != 1) {
					printf("Usage: %s 7 <addr>\n", argv[0]);
					return -1;
				}
				uint32_t val;
				Read_Mem(addr, &val);
				printf("Mem[0x%08x] = 0x%08x\n", addr, val);
				break;
			}
		case 10: { // Write_Mem from .bin file
				if (argc != 5 || strcmp(argv[3], "-f") != 0 || sscanf(argv[2], "%lx", &addr) != 1) {
					printf("Usage: %s 10 <addr> -f <binary_file>\n", argv[0]);
					return -1;
				}

				const char *file_path = argv[4]; //get the file path 
				FILE *fp = fopen(file_path, "rb"); //open the file path 
				if (!fp) {
					perror("Failed to open binary file");
					return -1;
				}

				fseek(fp, 0, SEEK_END);//move file pointer to the end of file 
				size_t size = ftell(fp); //size of the file 
				rewind(fp);//reset th fp to start of the file 

				//to allocate memory based on the size of file 
				unit8_t *buffer = malloc(size);
				if(!buffer){
					printf("failed to allocate memory\n");
					fclose(fp);
				}
				
				//to read from binfile to buffer
				fread(buffer,1,size,fp);
				fclose(fp);

				 //to write 32-bits at a time 
				for (size_t i = 0; i < size; i += 4) {
       				uint32_t word = 0;
       				memcpy(&word, buffer + i, (size - i >= 4) ? 4 : (size - i));
        			Write_Mem(addr + i, word);
    			}
				free(buffer);
			}				
		default:
			printf("Invalid command: %d\n", cmd);
			break;
	}
	if (munmap(mapped, SIZE) < 0) {
		perror("munmap");
	}
	close(fd);
	return 0;
}
