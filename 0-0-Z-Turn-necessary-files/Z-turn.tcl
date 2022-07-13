start_gui
create_project 1-2-gpio-mio G:/1-2-gpio-mio -part xc7z020clg400-1

set_property board_part myir.com:mys-7z020:part0:2.1 [current_project]
create_bd_design "design_1"

update_compile_order -fileset sources_1

startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 processing_system7_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:processing_system7 -config {make_external "FIXED_IO, DDR" apply_board_preset "1" Master "Disable" Slave "Disable" }  [get_bd_cells processing_system7_0]

startgroup
set_property -dict [list CONFIG.PCW_SDIO_PERIPHERAL_FREQMHZ {50} CONFIG.PCW_EN_CLK0_PORT {0} CONFIG.PCW_EN_CLK1_PORT {0} CONFIG.PCW_QSPI_PERIPHERAL_ENABLE {0} CONFIG.PCW_QSPI_GRP_SINGLE_SS_ENABLE {1} CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {0} CONFIG.PCW_UART0_PERIPHERAL_ENABLE {0} CONFIG.PCW_CAN0_PERIPHERAL_ENABLE {0} CONFIG.PCW_TTC0_PERIPHERAL_ENABLE {0} CONFIG.PCW_USB0_PERIPHERAL_ENABLE {0} CONFIG.PCW_I2C0_PERIPHERAL_ENABLE {0} CONFIG.PCW_I2C1_PERIPHERAL_ENABLE {0} CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {1} CONFIG.PCW_GPIO_EMIO_GPIO_IO {4}] [get_bd_cells processing_system7_0]
endgroup

startgroup
set_property -dict [list CONFIG.PCW_USE_M_AXI_GP0 {0} CONFIG.PCW_USE_S_AXI_HP0 {0} CONFIG.PCW_EN_RST0_PORT {0}] [get_bd_cells processing_system7_0]
endgroup
set_property location {1 187 -137} [get_bd_cells processing_system7_0]
set_property location {1 189 -182} [get_bd_cells processing_system7_0]
set_property location {1 201 -192} [get_bd_cells processing_system7_0]
set_property location {1 200 -203} [get_bd_cells processing_system7_0]
startgroup
set_property -dict [list CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {0}] [get_bd_cells processing_system7_0]
endgroup
