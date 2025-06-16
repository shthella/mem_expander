#include <spi_common.h>
#include <flash_mem_layout.h>

/* IMPORTANT NOTE:
 * Please make sure all your copy operations & parameters are 4byte boundaries
 */
int32_t spi_copy_data(uint8_t *s_addr, uint8_t *d_addr, uint32_t len) 
{
	uint32_t copied_len = 0, data_block, addr_pos = 0;

    if (((uint32_t)s_addr%4) || (len%4)) {
        return -1;
    }

	while (copied_len < len){
		Sf_if_sahb_0 sf_if_sahb_0 = {0};
		Sf_if_sahb_1 sf_if_sahb_1 = {0};
		
		//writel(0x0d0407fc,0x26001008);
		/* 0000 1101 0000 0100 0000 0111 1111 1100 */
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 0;
		sf_if_sahb_0.sf_if_0_spi_mode = 0;
		sf_if_sahb_0.sf_if_0_cmd_en = 1;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 0;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0;
		sf_if_sahb_0.sf_if_0_adr_byte = 2;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 0;
		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);

		//writel(0xa3600000,0x26001004);
		//1010 0011 0110 0000 0000 0000 0000 0000
		Sf_ctrl_1 sf_ctrl_1 = {0};
		sf_ctrl_1.sf_ahb2sram_en = 1;
		sf_ctrl_1.sf_ahb2sif_en = 0;
		sf_ctrl_1.sf_if_en = 1;
		sf_ctrl_1.sf_if_fn_sel = 0;
		sf_ctrl_1.sf_ahb2sif_stop = 0;
		sf_ctrl_1.sf_ahb2sif_stopped = 0;
		sf_ctrl_1.sf_if_reg_wp = 1;
		sf_ctrl_1.sf_if_reg_hold = 1;
		sf_ctrl_1.sf_ahb2sif_diswrap = 0;
		sf_ctrl_1.sf_if_0_ack_lat = 0x6;
		sf_ctrl_1.rsvd0 = 0;
		sf_ctrl_1.sf_if_sr_int_set = 0;
		sf_ctrl_1.sf_if_sr_int_en = 0;
		sf_ctrl_1.sf_if_sr_int = 0;
		sf_ctrl_1.sf_if_sr_pat = 0x0;
		sf_ctrl_1.sf_if_sr_pat_mask = 0x0;
		writel(sf_ctrl_1.val, SF_CSR_BASE_ADDR + SF_CTRL_1);

		/* 1byte opcode, 3byte address */
        sf_if_sahb_1.sf_if_0_cmd_buf_0 = (SINGLE_READ << 24) | ((uint32_t)(s_addr + copied_len) & 0x00FFFFFF);
		writel(sf_if_sahb_1.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_1);

		//writel(0x0d0407fe,0x26001008);
		//0000 1101 0000 0100 0000 0111 1111 1110
		sf_if_sahb_0.val = 0x0;
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 0;
		sf_if_sahb_0.sf_if_0_spi_mode = 0;
		sf_if_sahb_0.sf_if_0_cmd_en = 1;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 0;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0x0;
		sf_if_sahb_0.sf_if_0_adr_byte = 0x2;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0x0;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 1;
		sf_if_sahb_0.sf_if_busy = 0;
		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);

		while((readl(SF_CSR_BASE_ADDR + SF_IF_SAHB_0)&0x1) != 0);

		for (addr_pos=0; addr_pos < data_block; addr_pos+=4) {
            uint8_t readChar;
            uint32_t readVal;

            readVal = readl(SF_SRAM_ADDRESS + addr_pos);
            writel(readVal, d_addr + copied_len + addr_pos);
		}
		copied_len += data_block;
	}

	return TEST_SUCCESS;
}

int32_t qspi_mode_init(void) {
	/* WRITE addr:0x26002000, data:0x0 */
	/*
	addr=0x2600_2000 l1c_config 
	[31:14] 18'h0 r/w reserved 
	[13:12] 2’b0 r/w Sf_clk_div 00=25Mhz, 01=50MHz, 10=100MHz 
	[11:8] 4'h0 r/w l1c_way_dis Disable part of cache ways & used as AHB SRAM 
	[7:2] 6'h0 r/w reserved 
	[1] 1'h0 r/w l1c_cnten cache performance counter enable 
	[0] 1'h0 r/w l1c_cacheable cacheable region enable
	*/
	writel(0x0, L1C_CSR_BASE_ADDR);

	/* WRITE addr:0x26001004, data:0xa360_0000 */
	Sf_ctrl_1 sf_ctrl_1 = {0};
	sf_ctrl_1.sf_ahb2sram_en = 1;
	sf_ctrl_1.sf_ahb2sif_en = 0;
	sf_ctrl_1.sf_if_en = 1;
	sf_ctrl_1.sf_if_fn_sel = 0;
	sf_ctrl_1.sf_ahb2sif_stop = 0;
	sf_ctrl_1.sf_ahb2sif_stopped = 0;
	sf_ctrl_1.sf_if_reg_wp = 1;
	sf_ctrl_1.sf_if_reg_hold = 1;
	sf_ctrl_1.sf_ahb2sif_diswrap = 0;
	sf_ctrl_1.sf_if_0_ack_lat = 0x6;
	sf_ctrl_1.rsvd0 = 0;
	sf_ctrl_1.sf_if_sr_int_set = 0;
	sf_ctrl_1.sf_if_sr_int_en = 0;
	sf_ctrl_1.sf_if_sr_int = 0;
	sf_ctrl_1.sf_if_sr_pat = 0x0;
	sf_ctrl_1.sf_if_sr_pat_mask = 0x0;

	writel(sf_ctrl_1.val, SF_CSR_BASE_ADDR + SF_CTRL_1);

	/* WRITE addr:0x2600100c, data:0x6100_0000 */
	Sf_if_sahb_1 sf_if_sahb_1 = {0};
	/* 1byte opcode, 3byte address */
	sf_if_sahb_1.sf_if_0_cmd_buf_0 = 0x61000000;

	writel(sf_if_sahb_1.sf_if_0_cmd_buf_0, SF_CSR_BASE_ADDR + SF_IF_SAHB_1);

	/* WRITE addr:0x26001600, data:0x5f */
	/* [31:0] r/w Sf_sram Address [6:0]=sf sram address. */
	writel(0x5f, SF_CSR_BASE_ADDR + SF_SRAM_BASE_ADDR);

	/* WRITE addr:0x26001008, data:0x0984_0000 */
    // 0000 1001 1000 0100 0000 0000 0000 0000
	Sf_if_sahb_0 sf_if_sahb_0 = {0};
	sf_if_sahb_0.val =0x0;
	sf_if_sahb_0.sf_if_0_qpi_mode_en = 0;
    sf_if_sahb_0.sf_if_0_spi_mode = 0;
    sf_if_sahb_0.sf_if_0_cmd_en = 1;
	sf_if_sahb_0.sf_if_0_adr_en = 0;
	sf_if_sahb_0.sf_if_0_dmy_en=0;
    sf_if_sahb_0.sf_if_0_dat_en = 1;
    sf_if_sahb_0.sf_if_0_dat_rw = 1;
	sf_if_sahb_0.sf_if_0_cmd_byte= 0;
    sf_if_sahb_0.sf_if_0_adr_byte = 2;
    sf_if_sahb_0.sf_if_0_dmy_byte = 0;
    sf_if_sahb_0.sf_if_0_dat_byte = 0;
	sf_if_sahb_0.sf_if_0_trig = 0;
	writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);


	/* WRITE addr:0x26001008, data:0x0984_0002 */
    // 0000 1001 1000 0100 0000 0000 0000 0010
	sf_if_sahb_0.val =0x0;
	sf_if_sahb_0.sf_if_0_qpi_mode_en = 0;
    sf_if_sahb_0.sf_if_0_spi_mode = 0;
    sf_if_sahb_0.sf_if_0_cmd_en = 1;
	sf_if_sahb_0.sf_if_0_adr_en = 0;
	sf_if_sahb_0.sf_if_0_dmy_en=0;
    sf_if_sahb_0.sf_if_0_dat_en = 1;
    sf_if_sahb_0.sf_if_0_dat_rw = 1;
	sf_if_sahb_0.sf_if_0_cmd_byte= 0;
    sf_if_sahb_0.sf_if_0_adr_byte = 2;
    sf_if_sahb_0.sf_if_0_dmy_byte = 0;
    sf_if_sahb_0.sf_if_0_dat_byte = 0;
	sf_if_sahb_0.sf_if_0_trig = 1;
	writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);
 
	/* Poll for  bit 0 to be 0 of SF_IF_SAHB_0 */
	/* READ addr:0x26001008 */
	while((readl(SF_CSR_BASE_ADDR + SF_IF_SAHB_0) & 0x1) != 0);

	return 0;
}

int32_t qspi_copy_data(uint8_t *s_addr, uint8_t *d_addr, uint32_t len) {
	uint32_t copied_len = 0, data_block, addr_pos = 0;

    if (((uint32_t)s_addr%4)) {
        return -1;
    }

	if((uint32_t)s_addr > FLASH_MAX_ADDR) {
		return -1;
	}
	
	while (copied_len < len){
		Sf_if_sahb_1 sf_if_sahb_1 = {0};
		Sf_if_sahb_0 sf_if_sahb_0 = {0};

		/* WRITE addr:0x2600100c, data:0xeb00_0000 */
		sf_if_sahb_1.val =0x0;
        sf_if_sahb_1.sf_if_0_cmd_buf_0 = (QUAD_INPUT_OUTPUT_FAST_READ << 24) | ((uint32_t)(s_addr + copied_len) & 0x00FFFFFF);
		writel(sf_if_sahb_1.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_1);

		/* READ addr:0x26001008, data:0x09840002 */
		//readl(0x26001008); //Not required
		
		/* WRITE addr:0x26001008, data:0xc706_47fc */
		//1100 0111 0000 0110 0100 0111 1111 1100
		sf_if_sahb_0.val =0x0;
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 1;
		sf_if_sahb_0.sf_if_0_spi_mode = 4;
		sf_if_sahb_0.sf_if_0_cmd_en = 0;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 1;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0x0;
		sf_if_sahb_0.sf_if_0_adr_byte = 0x3;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0x4;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 0;
		sf_if_sahb_0.sf_if_busy = 0;
		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);

		/* WRITE addr:0x26001008, data:0xc706_47fe */
		sf_if_sahb_0.val =0x0;
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 1;
		sf_if_sahb_0.sf_if_0_spi_mode = 4;
		sf_if_sahb_0.sf_if_0_cmd_en = 0;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 1;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0x0;
		sf_if_sahb_0.sf_if_0_adr_byte = 0x3;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0x4;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 1;
		sf_if_sahb_0.sf_if_busy = 0;

		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);
 
		/* Poll for  bit 0 to be 0 of SF_IF_SAHB_0 */
		/* READ addr:0x26001008 */
		while((readl(SF_CSR_BASE_ADDR + SF_IF_SAHB_0) & 0x1) != 0);

		for (addr_pos=0; addr_pos < data_block; addr_pos+=4) {
            uint8_t readChar;
            int32_t readVal;

            readVal = readl(SF_SRAM_ADDRESS + addr_pos);
            writel(readVal, d_addr + copied_len + addr_pos);
		}
		copied_len += data_block;
	}

	return 0;
}

int32_t qspi_data_transfer_handler(void *pInfo, CopyFunc pFunc, uint32_t s_addr, uint32_t d_addr, uint32_t len) {
	uint32_t copied_len = 0, data_block, addr_pos = 0;

    if (((uint32_t)s_addr%4)) {
        return -1;
    }

	if((uint32_t)s_addr > FLASH_MAX_ADDR) {
		return -1;
	}
	
	while (copied_len < len){
		Sf_if_sahb_1 sf_if_sahb_1 = {0};
		Sf_if_sahb_0 sf_if_sahb_0 = {0};

		/* WRITE addr:0x2600100c, data:0xeb00_0000 */
		sf_if_sahb_1.val =0x0;
        sf_if_sahb_1.sf_if_0_cmd_buf_0 = (QUAD_INPUT_OUTPUT_FAST_READ << 24) | ((uint32_t)(s_addr + copied_len) & 0x00FFFFFF);
		writel(sf_if_sahb_1.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_1);

		/* READ addr:0x26001008, data:0x09840002 */
		//readl(0x26001008); //Not required
		
		/* WRITE addr:0x26001008, data:0xc706_47fc */
		//1100 0111 0000 0110 0100 0111 1111 1100
		sf_if_sahb_0.val =0x0;
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 1;
		sf_if_sahb_0.sf_if_0_spi_mode = 4;
		sf_if_sahb_0.sf_if_0_cmd_en = 0;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 1;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0x0;
		sf_if_sahb_0.sf_if_0_adr_byte = 0x3;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0x4;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 0;
		sf_if_sahb_0.sf_if_busy = 0;
		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);

		/* WRITE addr:0x26001008, data:0xc706_47fe */
		sf_if_sahb_0.val =0x0;
		sf_if_sahb_0.sf_if_0_qpi_mode_en = 1;
		sf_if_sahb_0.sf_if_0_spi_mode = 4;
		sf_if_sahb_0.sf_if_0_cmd_en = 0;
		sf_if_sahb_0.sf_if_0_adr_en = 1;
		sf_if_sahb_0.sf_if_0_dmy_en = 1;
		sf_if_sahb_0.sf_if_0_dat_en = 1;
		sf_if_sahb_0.sf_if_0_dat_rw = 0;
		sf_if_sahb_0.sf_if_0_cmd_byte = 0x0;
		sf_if_sahb_0.sf_if_0_adr_byte = 0x3;
		sf_if_sahb_0.sf_if_0_dmy_byte = 0x4;
		data_block = (len - copied_len) >= 0x200?0x200:(len - copied_len);
		sf_if_sahb_0.sf_if_0_dat_byte = data_block-1;
		sf_if_sahb_0.sf_if_0_trig = 1;
		sf_if_sahb_0.sf_if_busy = 0;

		writel(sf_if_sahb_0.val, SF_CSR_BASE_ADDR + SF_IF_SAHB_0);
 
		/* Poll for  bit 0 to be 0 of SF_IF_SAHB_0 */
		/* READ addr:0x26001008 */
		while((readl(SF_CSR_BASE_ADDR + SF_IF_SAHB_0) & 0x1) != 0);
        pFunc(pInfo, (SF_SRAM_ADDRESS + addr_pos), d_addr+copied_len, data_block);
		copied_len += data_block;
	}

	return 0;
}
