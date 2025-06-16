#ifndef __D2D_H_
#define __D2D_H_

#include "d2d_phy_csr_reg.h"
#include "d2d_LL.h"


#define D2D_PHY_BASE_ADDR 	0x27000000
#define D2D_LL_BASE_ADDR 	0x27008000

//#define BOW_TOP_BASE_ADDR	0x0000
//#define BOW_TX_SLICE_0_ADDR	0x0200
//#define BOW_RX_SLICE_0_ADDR	0x0800

#define readl(addr)      (*(volatile unsigned int *)(addr))
#define writel(val, addr)  (*(volatile unsigned int *)(addr)) = (unsigned int)(val)

int32_t d2d_mode_init(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_set_rx_mode_train(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_set_tx_train_mode(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_rx_train(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_skew_correction(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_set_tx_mode_idle(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_poll_rx_for_tx_idle_mode(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_set_rx_mode_wait(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_set_tx_mode_run(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);
int32_t d2d_poll_rx_mode_run(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL);

uint32_t d2d_phy_read(uint32_t  regAddr, uint32_t regVal);
uint32_t d2d_phy_write(uint32_t  regAddr, uint32_t regVal);
uint32_t d2d_ll_read(uint32_t regAddr, uint32_t regVal);
uint32_t d2d_ll_write(uint32_t regAddr, uint32_t regVal);

#endif /* __D2d_H_ */
