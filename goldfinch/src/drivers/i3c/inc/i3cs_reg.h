/********************************************************
 *
 * Register structures of I3C slave
 *
 * ******************************************************/
typedef union 
{
	struct
	{
		uint32_t rsvd1:24;
		uint32_t idle_cnt_multipler:2;
		uint32_t rsvd2:1;
		uint32_t adaptive_i2c_i3c:1;
		uint32_t rsvd3:2;
		uint32_t resume:1;
		uint32_t enable:1;
	};
	uint32_t val;
} u_i3cs_device_ctrl;

typedef union 
{
	struct
	{
		uint32_t static_addr:7;
		uint32_t rsvd1:8;
		uint32_t static_addr_valid:1;
		uint32_t dynamic_addr:7;
		uint32_t rsvd3:8;
		uint32_t dynamic_addr_valid:1;
	};
	uint32_t val;
} u_i3cs_device_addr;

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
} u_i3cs_hw_capability;

typedef union 
{
	struct
	{
		uint32_t command:32;
	};
	uint32_t val;
} u_i3cs_command_queue_port;

typedef union 
{
	struct
	{
		uint32_t response:32;
	};
	uint32_t val;
} u_i3cs_response_queue_port;

typedef union 
{
	struct
	{
		uint32_t tx_data_port:32;
	};
	uint32_t val;
} u_i3cs_tx_data_port;

typedef union 
{
	struct
	{
		uint32_t rx_data_port:32;
	};
	uint32_t val;
} u_i3cs_rx_data_port;


typedef union 
{
	struct
	{
		uint32_t cmd_empty_buf_thld:8;
		uint32_t resp_buf_thld:8;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cs_queue_thld_ctrl;

typedef union 
{
	struct
	{
		uint32_t tx_empty_buf_thld:3;
		uint32_t rsvd1:5;
		uint32_t rx_buf_thld:3;
		uint32_t rsvd2:5;
		uint32_t tx_start_thld:3;
		uint32_t rsvd3:5;
		uint32_t rx_start_thld:3;
		uint32_t rsvd4:5;
	};
	uint32_t val;
} u_i3cs_data_buffer_thld_ctrl;


typedef union 
{
	struct
	{
		uint32_t soft_rst:1;
		uint32_t cmd_queue_rst:1;
		uint32_t resp_queue_rst:1;
		uint32_t tx_fifo_rst:1;
		uint32_t rx_fifo_rst:1;
		uint32_t rsvd1:27;
	};
	uint32_t val;
} u_i3cs_reset_ctrl;
typedef union 
{
	struct
	{
		uint32_t rsvd1:4;
		uint32_t activity_state:2;
		uint32_t mrl_updated :1;
		uint32_t mwl_updated:1;
		uint32_t rsvd2:24;
	};
	uint32_t val;
} u_i3cs_slv_event_status;

typedef union 
{
	struct
	{
		uint32_t tx_thld_sts:1;
		uint32_t rx_thld_sts:1;
		uint32_t rsvd1:1;
		uint32_t cmd_queue_ready_sts:1;
		uint32_t resp_ready_sts:1;
		uint32_t rsvd2:1;
		uint32_t ccc_updated_sts:1;
		uint32_t rsvd3:1;
		uint32_t dyn_addr_assgn_sts:1;
		uint32_t transfer_err_sts:1;
		uint32_t rsvd4:1;
		uint32_t read_req_recv_sts:1;
		uint32_t rsvd5:20;
	};
	uint32_t val;
} u_i3cs_intr_status;

typedef union 
{
	struct
	{
		uint32_t tx_thld_sts_en:1;
		uint32_t rx_thld_sts_en:1;
		uint32_t rsvd1:1;
		uint32_t cmd_queue_ready_sts_en:1;
		uint32_t resp_ready_sts_en:1;
		uint32_t rsvd2:1;
		uint32_t ccc_updated_sts_en:1;
		uint32_t rsvd3:1;
		uint32_t dyn_addr_assgn_sts_en:1;
		uint32_t transfer_err_sts_en:1;
		uint32_t rsvd4:1;
		uint32_t read_req_recv_sts_en:1;
		uint32_t rsvd5:20;
	};
	uint32_t val;
} u_i3cs_intr_status_en;


typedef union 
{
	struct
	{
		uint32_t tx_thld_status_en:1;
		uint32_t rx_thld_status_en:1;
		uint32_t rsvd1:1;
		uint32_t cmd_queue_ready_status_en:1;
		uint32_t resp_ready_status_en:1;
		uint32_t rsvd2:1;
		uint32_t ccc_updated_status_en:1;
		uint32_t rsvd3:1;
		uint32_t dyn_addr_assgn_status_en:1;
		uint32_t transfer_err_status_en:1;
		uint32_t rsvd4:1;
		uint32_t read_req_recv_status_en:1;
		uint32_t rsvd5:20;
	};
	uint32_t val;
} u_i3cs_intr_signal_en;

typedef union 
{
	struct
	{
		uint32_t tx_thld_force_en:1;
		uint32_t rx_thld_force_en:1;
		uint32_t rsvd1:1;
		uint32_t cmd_queue_ready_force_en:1;
		uint32_t resp_ready_force_en:1;
		uint32_t rsvd2:1;
		uint32_t ccc_updated_force_en:1;
		uint32_t rsvd3:1;
		uint32_t dyn_addr_assgn_force_en:1;
		uint32_t transfer_err_force_en:1;
		uint32_t rsvd4:1;
		uint32_t read_req_recv_force_en:1;
		uint32_t rsvd5:20;
	};
	uint32_t val;
} u_i3cs_intr_force;

typedef union 
{
	struct
	{
		uint32_t cmd_queue_empty_loc:8;
		uint32_t resp_buf_blr:8;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cs_queue_status_level;


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
} u_i3cs_data_buffer_status_level;


typedef union 
{
	struct
	{
		uint32_t rsvd1:8;
		uint32_t cm_tfr_sts:6;
		uint32_t rsvd2:10;
		uint32_t cmd_tid:4;
		uint32_t rsvd3:4;
	};
	uint32_t val;
} u_i3cs_present_state;

typedef union 
{
	struct
	{
		uint32_t pending_intr:4;
		uint32_t rsvd1:1;
		uint32_t protocol_err:1;
		uint32_t activity_mode:2;
		uint32_t underflow_err:1;
		uint32_t slave_busy:1;
		uint32_t overflow_err:1;
		uint32_t data_not_ready:1;
		uint32_t buffer_not_avail:1;
		uint32_t frame_err:1;
		uint32_t rsvd2:18;
	};
	uint32_t val;
} u_i3cs_ccc_device_status;

typedef union 
{
	struct
	{
		uint32_t slv_prov_id_sel:1;
		uint32_t slv_mipi_mfg_id:15;
		uint32_t rsvd1:16;
	};
	uint32_t val;
} u_i3cs_slv_mipi_id_value;
typedef union 
{
	struct
	{
		uint32_t slv_pid_dcr:12;
		uint32_t slv_inst_id:4;
		uint32_t slv_part_id:16;
	};
	uint32_t val;
} u_i3cs_slv_pid_value;
typedef union 
{
	struct
	{
		uint32_t max_speed_data_limit:1;
		uint32_t ibi_request_capable:1;
		uint32_t ibi_playload:1;
		uint32_t offline_capable:1;
		uint32_t bridge_identifer:1;
		uint32_t hdr_capable:1;
		uint32_t device_role:2;
		uint32_t dcr:8;
		uint32_t hdr_cap:8;
		uint32_t rsvd1:8;
	};
	uint32_t val;
} u_i3cs_slv_char_ctrl;
typedef union 
{
	struct
	{
		uint32_t mwl:16;
		uint32_t mrl:16;
	};
	uint32_t val;
} u_i3cs_slv_max_length;
typedef union 
{
	struct
	{
		uint32_t mxds_max_rd_turn:24;
		uint32_t rsvd1:8;
	};
	uint32_t val;
} u_i3cs_max_read_turnaround;
typedef union 
{
	struct
	{
		uint32_t mxds_max_wr_speed:3;
		uint32_t rsvd1:5;
		uint32_t mxds_max_rd_speed:3;
		uint32_t rsvd2:5;
		uint32_t mxds_clk_data_turn:3;
		uint32_t rsvd3:13;
	};
	uint32_t val;
} u_i3cs_max_data_speed;
typedef union 
{
	struct
	{
		uint32_t rsvd1:16;
		uint32_t bus_available_time:16;
	};
	uint32_t val;
} u_i3cs_bus_free_avail_timing;
typedef union 
{
	struct
	{
		uint32_t bus_idle_time:20;
		uint32_t rsvd1:12;
	};
	uint32_t val;
} u_i3cs_bus_idle_timing;
typedef union 
{
	struct
	{
		uint32_t i3c_ver_id:32;
	};
	uint32_t val;
} u_i3cs_i3c_ver_id;
typedef union 
{
	struct
	{
		uint32_t i3c_ver_type:32;
	};
	uint32_t val;
} u_i3cs_i3c_ver_type;
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
} u_i3cs_queue_size_capability;
