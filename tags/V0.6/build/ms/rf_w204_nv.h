/*----------------------------------------------------------------
        本文件包含对于特定机型的通用校准参数，在文件系统重建
        时可以自动写入到NV中。
        
        请根据机型的具体情况改写本文件中的列表。
        
        一般的修改的修改方法：
        1.取10台工作良好的手机，计算Calibration Nv的均值
        2.通过QPST的工具设置好需要的NV值，保存为QCN文件。
        3.使用QCN View转为txt文件。
        4.将其中的值复制到本表中。
----------------------------------------------------------------*/
#define AUTO_NV_RF_VERSION      0x22

//Fixed rf nv, it'may adjust for certain target.
const nv_auto_set_type nv_auto_set_rf_fixed_list[] =
{ 
    {NV_RF_CONFIG_I,                        {0x01}}, // Any
    {NV_RF_HW_CONFIG_I,                     {0x26}}, // For 1100 and 1110
    {NV_RF_BC_CONFIG_I,                     {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, //BC1 Only
    {NV_FTM_MODE_I,                         {0x00}}, //FTM Mode,
    {NV_CDMA_DYNAMIC_RANGE_I,               {0x00, 0x04}},    
    {NV_CDMA_MIN_RX_RSSI_I,                 {0x82, 0xFB}},
    {NV_BC1_ENC_BTF_I,                      {0x9f, 0x0c}},
    
    // RX
    {NV_C0_BC1_RX_CAL_CHAN_I,               {0x19, 0x00, 0x71, 0x00, 0xbc, 0x00, 0x07, 0x01, 0x52, 0x01, 0x9d, 0x01, 0xe8, 0x01, 0x33, 0x02,
                                             0x7e, 0x02, 0xc9, 0x02, 0x14, 0x03, 0x5f, 0x03, 0xaa, 0x03, 0xf5, 0x03, 0x40, 0x04, 0x97, 0x04}},
    {NV_C0_BC1_RX_CAL_CHAN_LRU_I,           {0x10, 0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01}},
    {NV_C0_BC1_LNA_SWITCHPOINTS_LPM_1_I,    {0xc3, 0xdd, 0x2a, 0x7f, 0xbb, 0xd3, 0x20, 0x7f,}},
    {NV_C0_BC1_INTELLICEIVER_DET_THRESH_I,  {0x00, 0xc4, 0xc4, 0xc4, 0xc4, 0x00, 0xe2, 0xe2, 0xe2, 0xe2}},
    {NV_C0_BC1_LNA_1_RISE_I,                {0xc3}},
    {NV_C0_BC1_LNA_2_RISE_I,                {0xdd}},
    {NV_C0_BC1_LNA_3_RISE_I,                {0x2a}},
    {NV_C0_BC1_LNA_4_RISE_I,                {0x7f}},
    {NV_C0_BC1_LNA_1_FALL_I,                {0xbb}},
    {NV_C0_BC1_LNA_2_FALL_I,                {0xd3}},
    {NV_C0_BC1_LNA_3_FALL_I,                {0x20}},
    {NV_C0_BC1_LNA_4_FALL_I,                {0x7f}},
    {NV_C0_BC1_IM_LEVEL1_I,                 {0xc3}},
    {NV_C0_BC1_IM_LEVEL2_I,                 {0xdd}},
    {NV_C0_BC1_IM_LEVEL3_I,                 {0x2a}},
    {NV_C0_BC1_IM_LEVEL4_I,                 {0x7f}},
    
    // TX
    {NV_BC1_PA_R_MAP_I,                     {0xfe}},
    {NV_C0_BC1_TX_CAL_CHAN_I,               {0x19, 0x00, 0x71, 0x00, 0xbc, 0x00, 0x07, 0x01, 0x52, 0x01, 0x9d, 0x01, 0xe8, 0x01, 0x33, 0x02,
                                             0x7e, 0x02, 0xc9, 0x02, 0x14, 0x03, 0x5f, 0x03, 0xaa, 0x03, 0xf5, 0x03, 0x40, 0x04, 0x97, 0x04}},
    {NV_BC1_PA_R1_RISE_I,                   {0xb8}},
    {NV_BC1_PA_R2_RISE_I,                   {0xff}},
    {NV_BC1_PA_R3_RISE_I,                   {0xff}},
    {NV_BC1_PA_R1_FALL_I,                   {0xb3}},
    {NV_BC1_PA_R2_FALL_I,                   {0xff}},
    {NV_BC1_PA_R3_FALL_I,                   {0xff}}
};

//Cal rf nv which must adjust for every Model.
//---------------------------------------------------
//NOTICE:Please get at least 10 calibration Value 
//for 1 Model then set it's average value here.
//---------------------------------------------------
const nv_auto_set_type nv_auto_set_rf_cal_list[] =
{    
    {NV_VBATT_I,                            {0x85, 0xab}},
    {NV_THERM_BINS_I,                       {0xa1, 0x06, 0x01, 0x07, 0x60, 0x07, 0xc0, 0x07, 0x1f, 0x08, 0x7f, 0x08, 0xdf, 0x08, 0x3e, 0x09}},
    
    // RX
    {NV_C0_BC1_VGA_GAIN_OFFSET_VS_FREQ_I,   {0xde, 0xdd, 0xe1, 0xe5, 0xe8, 0xeb, 0xe9, 0xe6, 0xe5, 0xe4, 0xe7, 0xe6, 0xe0, 0xe0, 0xdf, 0xde,
                                             0x18, 0x18, 0x1c, 0x20, 0x24, 0x24, 0x23, 0x1f, 0x1e, 0x1d, 0x20, 0x1f, 0x19, 0x19, 0x17, 0x16}},
    {NV_C0_BC1_VGA_GAIN_OFFSET_I,           {0xcc, 0xff}},
    {NV_C0_BC1_LNA_1_OFFSET_VS_FREQ_I,      {0x03, 0x05, 0x04, 0x02, 0x00, 0x02, 0x03, 0x04, 0x05, 0x05, 0x04, 0x04, 0x04, 0x05, 0x06, 0x07,
                                             0xfa, 0xfc, 0xfb, 0xf9, 0xf9, 0xf8, 0xfa, 0xfa, 0xfb, 0xfb, 0xfa, 0xf9, 0xf9, 0xfb, 0xfa, 0xfb}},
    {NV_C0_BC1_LNA_2_OFFSET_VS_FREQ_I,      {0x05, 0xfd, 0xff, 0x03, 0x07, 0x0a, 0x08, 0x04, 0x03, 0x01, 0x03, 0x06, 0x08, 0x06, 0x05, 0x03,
                                             0xfd, 0xf6, 0xf8, 0xfc, 0x01, 0x01, 0x00, 0xfb, 0xf9, 0xf8, 0xfa, 0xfd, 0xfe, 0xfc, 0xfa, 0xf9}},
    {NV_C0_BC1_LNA_3_OFFSET_VS_FREQ_I,      {0x06, 0x05, 0x06, 0x08, 0x08, 0x08, 0x06, 0x04, 0x04, 0x04, 0x06, 0x06, 0x05, 0x04, 0x04, 0x03,
                                             0xfd, 0xfd, 0xff, 0x00, 0x02, 0xfe, 0xfd, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb, 0xfa, 0xf8, 0xf8}},
    {NV_C0_BC1_LNA_4_OFFSET_VS_FREQ_I,      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
    {NV_C0_BC1_LNA_1_OFFSET_I,              {0x85, 0x00}},
    {NV_C0_BC1_LNA_2_OFFSET_I,              {0xe6, 0x00}},
    {NV_C0_BC1_LNA_3_OFFSET_I,              {0x79, 0x01}},
    {NV_C0_BC1_LNA_4_OFFSET_I,              {0x00, 0x00}},
    {NV_C0_BC1_INTELLICEIVER_CAL_I,         {0x33, 0x02, 0xc8, 0x00, 0x08, 0x00, 0xa0, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00}},
    
    // TX
    {NV_BC1_TX_PDM_0_I,                     {0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00,
                                             0x08, 0x00, 0x09, 0x00, 0x0a, 0x00, 0x0b, 0x00, 0x0c, 0x00, 0x0d, 0x00, 0x0e, 0x00, 0x0f, 0x00,
                                             0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13, 0x00, 0x14, 0x00, 0x15, 0x00, 0x16, 0x00, 0x17, 0x00,
                                             0x18, 0x00, 0x19, 0x00, 0x1a, 0x00, 0x1b, 0x00, 0x1c, 0x00, 0x1d, 0x00, 0x1e, 0x00, 0x1f, 0x00,
                                             0x20, 0x00, 0x21, 0x00, 0x22, 0x00, 0x23, 0x00, 0x24, 0x00, 0x25, 0x00, 0x26, 0x00, 0x27, 0x00,
                                             0x28, 0x00, 0x29, 0x00, 0x2a, 0x00, 0x2b, 0x00, 0x2c, 0x00, 0x2d, 0x00, 0x2e, 0x00, 0x2f, 0x00,
                                             0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f,
                                             0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f}},
    {NV_BC1_TX_PDM_1_I,                     {0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00,
                                             0x08, 0x00, 0x09, 0x00, 0x0a, 0x00, 0x0b, 0x00, 0x0c, 0x00, 0x0d, 0x00, 0x0e, 0x00, 0x0f, 0x00,
                                             0x10, 0x00, 0x11, 0x00, 0x12, 0x00, 0x13, 0x00, 0x14, 0x00, 0x15, 0x00, 0x16, 0x00, 0x17, 0x00,
                                             0x18, 0x00, 0x19, 0x00, 0x1a, 0x00, 0x1b, 0x00, 0x1c, 0x00, 0x1d, 0x00, 0x1e, 0x00, 0x1f, 0x00,
                                             0x20, 0x00, 0x21, 0x00, 0x22, 0x00, 0x23, 0x00, 0x24, 0x00, 0x25, 0x00, 0x26, 0x00, 0x27, 0x00,
                                             0x28, 0x00, 0x29, 0x00, 0x2a, 0x00, 0x2b, 0x00, 0x2c, 0x00, 0x2d, 0x00, 0x2e, 0x00, 0x2f, 0x00,
                                             0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00, 0x34, 0x00, 0x35, 0x00, 0x36, 0x00, 0x37, 0x00,
                                             0x38, 0x00, 0x39, 0x00, 0x3b, 0x00, 0x3a, 0x00, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f}},
    {NV_BC1_TX_LIN_0_I,                     {0x35, 0x00, 0x2a, 0x00, 0x28, 0x00, 0x19, 0x00, 0x12, 0x00, 0x0b, 0x00, 0xff, 0xff, 0xf6, 0xff,
                                             0xec, 0xff, 0xe2, 0xff, 0xd4, 0xff, 0xc9, 0xff, 0xbb, 0xff, 0xb0, 0xff, 0xa2, 0xff, 0x95, 0xff,
                                             0x89, 0xff, 0x7c, 0xff, 0x72, 0xff, 0x66, 0xff, 0x5b, 0xff, 0x4d, 0xff, 0x43, 0xff, 0x38, 0xff,
                                             0x2b, 0xff, 0x1c, 0xff, 0x0e, 0xff, 0xfe, 0xfe, 0xf0, 0xfe, 0xe4, 0xfe, 0xd8, 0xfe, 0xcb, 0xfe,
                                             0xc0, 0xfe, 0xb3, 0xfe, 0xa7, 0xfe, 0x9b, 0xfe, 0x8e, 0xfe, 0x82, 0xfe, 0x78, 0xfe, 0x6a, 0xfe,
                                             0x5e, 0xfe, 0x54, 0xfe, 0x47, 0xfe, 0x39, 0xfe, 0x2f, 0xfe, 0x25, 0xfe, 0x18, 0xfe, 0x0c, 0xfe,
                                             0x00, 0xfe, 0xf5, 0xfd, 0xe9, 0xfd, 0xdd, 0xfd, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
                                             0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80}},
    {NV_BC1_TX_LIN_1_I,                     {0x1f, 0x01, 0x1a, 0x01, 0x17, 0x01, 0x12, 0x01, 0x0e, 0x01, 0x08, 0x01, 0x01, 0x01, 0xfb, 0x00,
                                             0xf6, 0x00, 0xef, 0x00, 0xe7, 0x00, 0xe0, 0x00, 0xd8, 0x00, 0xce, 0x00, 0xc7, 0x00, 0xba, 0x00,
                                             0xb0, 0x00, 0xa7, 0x00, 0x9d, 0x00, 0x95, 0x00, 0x8c, 0x00, 0x86, 0x00, 0x7d, 0x00, 0x71, 0x00,
                                             0x66, 0x00, 0x59, 0x00, 0x50, 0x00, 0x46, 0x00, 0x3e, 0x00, 0x35, 0x00, 0x2d, 0x00, 0x22, 0x00,
                                             0x19, 0x00, 0x12, 0x00, 0x09, 0x00, 0x00, 0x00, 0xf7, 0xff, 0xee, 0xff, 0xe6, 0xff, 0xde, 0xff,
                                             0xd5, 0xff, 0xcd, 0xff, 0xc4, 0xff, 0xbd, 0xff, 0xb4, 0xff, 0xab, 0xff, 0xa2, 0xff, 0x9b, 0xff,
                                             0x93, 0xff, 0x8a, 0xff, 0x81, 0xff, 0x79, 0xff, 0x70, 0xff, 0x68, 0xff, 0x60, 0xff, 0x57, 0xff,
                                             0x4f, 0xff, 0x47, 0xff, 0x3e, 0xff, 0x3e, 0xff, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80}},
    {NV_BC1_TX_PWR_COMP0_I,                 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                             0x01, 0xfc, 0xfc, 0xfb, 0xfb, 0xfd, 0xff, 0x00, 0x00, 0xfc, 0xf9, 0xf5, 0xf1, 0xf0, 0xf2, 0xf4}},
    {NV_BC1_TX_PWR_COMP1_I,                 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                             0xff, 0xf8, 0xf8, 0xf9, 0xfb, 0xfe, 0x01, 0x00, 0xfd, 0xf7, 0xf3, 0xf0, 0xed, 0xed, 0xf2, 0xf6}},
    {NV_BC1_TX_LIM_VS_FREQ_I,               {0xfd, 0x03, 0x06, 0x06, 0x07, 0x04, 0x02, 0x00, 0x00, 0x03, 0x08, 0x0b, 0x10, 0x11, 0x0f, 0x08}},
    {NV_BC1_EXP_HDET_VS_AGC_V2_I,           {0xa9, 0x01, 0xee, 0x01, 0x53, 0x02, 0xe4, 0x02, 0xaa, 0x03, 0xf2, 0x04, 0xaa, 0x06, 0x05, 0x09,
                                             0xaf, 0x0c, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f}},
    {NV_BC1_HDET_OFF_V2_I,                  {0xce, 0x03}},
    {NV_BC1_HDET_SPN_V2_I,                  {0xf1, 0x0a}}
};                                               
                                                 
                                                 
                                                 
                                                 
                                                 
                                                 