typedef union 
{
	struct
	{
		uint32_t iba_include:1;
		uint32_t rsvd1:6;
		uint32_t i2c_slave_present:1;
		uint32_t hot_join_control:1;
		uint32_t rsvd2:19;
		uint32_t abort:1;
		uint32_t resume:1;
		uint32_t enable:1;
	};
	uint32_t val;
} u_i3cm_device_ctrl;

typedef union 
{
	struct
	{
		uint32_t rsvd1:16;
		uint32_t dynamic_addr:7;
		uint32_t rsvd2:8;
		uint32_t dynamic_addr_valid:1;
	};
	uint32_t val;
} u_i3cm_device_addr;

typedef union 
{
	struct
	{
		uint32_t device_role_config:3;
		uint32_t hdr_addr_en:1;
		uint32_t hdr_ts_en:1;
		uint32_t clock_period:6;
		uint32_t hdr_tx_clock_period:6;
		uint32_t dma_en:1;
		uint32_t slv_hj_cap:1;
		uint32_t slv_ibi_cap:1;
		uint32_t rsvd1:12;
	};
	uint32_t val;
} u_i3cm_hw_capability;

typedef union 
{
	struct
	{
		uint32_t command:32;
	};
	uint32_t val;
} u_i3cm_command_queue_port;

typedef union 
{
	struct
	{
		uint32_t response:32;
	};
	uint32_t val;
} u_i3cm_response_queue_port;

typedef union 
{
	struct
	{
		uint32_t tx_data_port:32;
	};
	uint32_t val;
} u_i3cm_tx_data_port;

typedef union 
{
	struct
	{
		uint32_t rx_data_port:32;
	};
	uint32_t val;
} u_i3cm_rx_data_port;


typedef union 
{
	struct
	{
		uint32_t data_length:8;
		uint32_t ibi_id:8;
		uint32_t rsvd1:12;
		uint32_t ibi_sts:4;
	};
	uint32_t val;
} u_i3cm_ibi_queue_status;

typedef union 
{
	struct
	{
		uint32_t cmd_empty_buf_thld:8;
		uint32_t resp_buf_thld:8;
		uint32_t rsvd1:8;
		uint32_t ibi_status_thld:8;
	};
	uint32_t val;
} u_i3cm_queue_thld_ctrl;

typedef union 
{
	struct
	{
		uint32_t tx_empty_buf_thld:3;
		uint32_t rsvd1:5;
		uint32_t rx_empty_buf_thld:3;
		uint32_t rsvd2:5;
		uint32_t tx_start_thld:3;
		uint32_t rsvd3:5;
		uint32_t rx_start_thld:3;
		uint32_t rsvd4:5;
	};
	uint32_t val;
} u_i3cm_data_buffer_thld_ctrl;

typedef union 
{
	struct
	{
		uint32_t notify_hj_rejected:1;
		uint32_t rsvd1:2;
		uint32_t notify_sir_rejected:1;
		uint32_t rsvd2:28;
	};
	uint32_t val;
} u_i3cm_ibi_queue_ctrl;

typedef union 
{
	struct
	{
		uint32_t ibi_sir_rejecet:32;
	};
	uint32_t val;
} u_i3cm_ibi_sir_req_reject;

typedef union 
{
	struct
	{
		uint32_t soft_rst:1;
		uint32_t cmd_queue_rst:1;
		uint32_t resp_queue_rst:1;
		uint32_t tx_fifo_rst:1;
		uint32_t rx_fifo_rst:1;
		uint32_t ibi_queue_rst:1;
		uint32_t rsvd1:26;
	};
	uint32_t val;
} u_i3cm_reset_ctrl;

typedef union 
{
	struct
	{
		uint32_t tx_thld_sts:1;
		uint32_t rx_thld_sts:1;
		uint32_t ibi_thld_sts:1;
		uint32_t cmd_status_ready_sts:1;
		uint32_t resp_ready_sts:1;
		uint32_t transfer_abort_sts:1;
		uint32_t rsvd1:3;
		uint32_t transfer_err_sts:1;
		uint32_t rsvd2:22;
	};
	uint32_t val;
} u_i3cm_intr_status;

typedef union 
{
	struct
	{
		uint32_t tx_thld_sts_en:1;
		uint32_t rx_thld_sts_en:1;
		uint32_t ibi_thld_sts_en:1;
		uint32_t cmd_status_ready_sts_en:1;
		uint32_t resp_ready_sts_en:1;
		uint32_t transfer_abort_sts_en:1;
		uint32_t rsvd1:3;
		uint32_t transfer_err_sts_en:1;
		uint32_t rsvd2:22;
	};
	uint32_t val;
} u_i3cm_intr_status_en;


typedef union 
{
	struct
	{
		uint32_t tx_thld_signal_en:1;
		uint32_t rx_thld_signal_en:1;
		uint32_t ibi_thld_signal_en:1;
		uint32_t cmd_status_ready_signal_en:1;
		uint32_t resp_ready_signal_en:1;
		uint32_t transfer_abort_signal_en:1;
		uint32_t rsvd1:3;
		uint32_t transfer_err_signal_en:1;
		uint32_t rsvd2:22;
	};
	uint32_t val;
} u_i3cm_intr_signal_en;

typedef union 
{
	struct
	{
		uint32_t tx_thld_force_en:1;
		uint32_t rx_thld_force_en:1;
		uint32_t ibi_thld_force_en:1;
		uint32_t cmd_status_ready_force_en:1;
		uint32_t resp_ready_force_en:1;
		uint32_t transfer_abort_force_en:1;
		uint32_t rsvd1:3;
		uint32_t transfer_err_force_en:1;
		uint32_t rsvd2:22;
	};
	uint32_t val;
} u_i3cm_intr_force;

typedef union 
{
	struct
	{
		uint32_t cmd_queue_empty_loc:8;
		uint32_t resp_buf_blr:8;
		uint32_t ibi_buf_blr:8;
		uint32_t ibi_sts_cnt:5;
		uint32_t rsvd1:3;
	};
	uint32_t val;
} u_i3cm_queue_status_level;


typedef union 
{
	struct
	{
		uint32_t tx_buffer_empty_loc:8;
		uint32_t rsvd1:8;
		uint32_t rx_buf_blr:8;
		uint32_t rsvd2:8;
	};
	uint32_t val;
} u_i3cm_data_buffer_status_level;


typedef union 
{
	struct
	{
		uint32_t scl_line_signal_line:1;
		uint32_t sda_line_signal_line:1;
		uint32_t current_matter:1;
		uint32_t rsvd1:5;
		uint32_t cm_tfr_sts:6;
		uint32_t rsvd2:2;
		uint32_t cm_tfr_st_sts:6;
		uint32_t rsvd3:2;
		uint32_t cmd_tid:4;
		uint32_t controller_idle:1;
		uint32_t rsvd4:3;
	};
	uint32_t val;
} u_i3cm_present_state;

typedef union 
{
	struct
	{
		uint32_t p_dev_addr_table_start_addr:16;
		uint32_t dev_addr_table_depth:16;
	};
	uint32_t val;
} u_i3cm_dev_addr_table_pointer;

typedef union 
{
	struct
	{
		uint32_t p_dev_char_table_start_addr:12;
		uint32_t dev_char_table_depth:7;
		uint32_t present_dev_char_table_indx:5;
		uint32_t rsvd1:8;
	};
	uint32_t val;
} u_i3cm_dev_char_table_pointer;

typedef union 
{
	struct
	{
		uint32_t p_vendor_reg_start_addr:16;
		uint32_t rsvd:16;
	};
	uint32_t val;
} u_i3cm_vendor_specific_reg_pointer;

typedef union 
{
	struct
	{
		uint32_t dev_operation_mode:2;
		uint32_t rsvd:30;
	};
	uint32_t val;
} u_i3cm_device_ctrl_extended;
typedef union 
{
	struct
	{
		uint32_t i3c_od_lcnt:8;
		uint32_t rsvd1:8;
		uint32_t i3c_od_hcnt:8;
		uint32_t rsvd2:8;
	};
	uint32_t val;
} u_i3cm_scl_i3c_od_timing;
typedef union 
{
	struct
	{
		uint32_t i3c_pp_lcnt:8;
		uint32_t rsvd1:8;
		uint32_t i3c_pp_hcnt:8;
		uint32_t rsvd2:8;
	};
	uint32_t val;
} u_i3cm_scl_i3c_pp_timing;
typedef union 
{
	struct
	{
		uint32_t i2c_fm_lcnt:16;
		uint32_t i2c_fm_hcnt:16;
	};
	uint32_t val;
} u_i3cm_scl_i2c_fm_timing;
typedef union 
{
	struct
	{
		uint32_t i2c_fmp_lcnt:16;
		uint32_t i2c_fmp_hcnt:8;
		uint32_t rsvd1:8;
	};
	uint32_t val;
} u_i3cm_scl_i2c_fmp_timing;
typedef union 
{
	struct
	{
		uint32_t i3c_ext_lcnt1:8;
		uint32_t i3c_ext_lcnt2:8;
		uint32_t i3c_ext_lcnt3:8;
		uint32_t i3c_ext_lcnt4:8;
	};
	uint32_t val;
} u_i3cm_scl_ext_lcnt_timing;
typedef union 
{
	struct
	{
		uint32_t i3c_ext_termn_lcnt:4;
		uint32_t rsvd1:24;
		uint32_t stop_hld_cnt:4;
	};
	uint32_t val;
} u_i3cm_scl_ext_termn_lcnt_timing;
typedef union 
{
	struct
	{
		uint32_t rsvd1:16;
		uint32_t i3c_sda_tx_hold:3;
		uint32_t rsvd2:13;
	};
	uint32_t val;
} u_i3cm_sda_hold_switch_dly_timing;
typedef union 
{
	struct
	{
		uint32_t bus_free_time:16;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cm_bus_free_avail_timing;
typedef union 
{
	struct
	{
		uint32_t i3c_ver_id:32;
	};
	uint32_t val;
} u_i3cm_i3c_ver_id;
typedef union 
{
	struct
	{
		uint32_t i3c_ver_type:32;
	};
	uint32_t val;
} u_i3cm_i3c_ver_type;
typedef union 
{
	struct
	{
		uint32_t tx_buf_size:4;
		uint32_t rx_buf_size:4;
		uint32_t cmd_buf_size:4;
		uint32_t resp_buf_size:4;
		uint32_t ibi_buf_size:4;
		uint32_t rsvd1:12;
	};
	uint32_t val;
} u_i3cm_queue_size_capability;
typedef union 
{
	struct
	{
		uint32_t msb_provisional_id:32;
	};
	uint32_t val;
} u_i3cm_dev_char_table1_loc1;
typedef union 
{
	struct
	{
		uint32_t lsb_provisional_id:16;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cm_dev_char_table1_loc2;
typedef union 
{
	struct
	{
		uint32_t dcr:8;
		uint32_t bcr:8;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cm_dev_char_table1_loc3;
typedef union 
{
	struct
	{
		uint32_t dev_dynamic_addr:8;
		uint32_t rsvd1:24;
	};
	uint32_t val;
} u_i3cm_dev_char_table1_loc4;
typedef union 
{
	struct
	{
		uint32_t dev_static_addr:7;
		uint32_t rsvd1:9;
		uint32_t dev_dynamic_addr:8;
		uint32_t rsvd2:5;
		uint32_t dev_nack_retry_cnt:2;
		uint32_t legacy_i2c_device:1;
	};
	uint32_t val;
} u_i3cm_dev_addr_table_loc1;
